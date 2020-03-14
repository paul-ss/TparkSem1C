//
// Created by paul_s on 10.03.2020.
//

#define _GNU_SOURCE

#include "array.h"
#include "matrix.h"

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct worker_attr {
  array *sums_arr_ptr;
  const matrix *mat_ptr;
  size_t row_begin;
  size_t row_end;
} worker_attr;

pthread_mutex_t sums_lock;



int set_workers_attr(worker_attr w_attr [], array *sums_arr_ptr, const matrix *mat_ptr, size_t n_child_threads) {
  if (w_attr == NULL || sums_arr_ptr == NULL || mat_ptr == NULL) {
    return -1;
  }

  size_t row_range = mat_ptr->rows / n_child_threads;

  for (size_t i = 0; i <  n_child_threads; ++i) {
    w_attr[i].sums_arr_ptr = sums_arr_ptr;
    w_attr[i].mat_ptr = mat_ptr;
    w_attr[i].row_begin = i * row_range;

    if (i + 1 != n_child_threads) {
      w_attr[i].row_end = (i + 1) * row_range;
    } else {
      w_attr[i].row_end = mat_ptr->rows;
    }
  }

  return 0;
}



int join_child_threads(const pthread_t child_threads [], size_t n_child_threads) {
  if (child_threads == NULL) {
    return -1;
  }

  int status = 0;
  for (size_t i = 0; i < n_child_threads; i++) {
    if (child_threads[i] > 0) {
      void *retval = 0;

      if (pthread_join(child_threads[i], &retval) != 0) {
        status = -1;
      }

      if (*((int *)retval) != 0) {
        status = -1;
      }

      free(retval);
    }
  }

  return status;
}

// [row_begin; row_end)
void *thread_worker(void *void_attr_ptr) {
  worker_attr *attr_ptr = void_attr_ptr;
 // printf("Thread#%zu, CPU%d\n", attr_ptr->row_begin,  sched_getcpu());

  int *return_stat = calloc(1, sizeof(int));

  if (attr_ptr == NULL || attr_ptr->sums_arr_ptr == NULL || attr_ptr->mat_ptr == NULL) {
    *return_stat = -1;
    return return_stat;
  }

  if (attr_ptr->sums_arr_ptr->size != attr_ptr->mat_ptr->cols) {
    *return_stat = -1;
    return return_stat;
  }

  array *tmp_arr_ptr = create_array(attr_ptr->mat_ptr->cols);
  if (tmp_arr_ptr == NULL) {
    *return_stat = -1;
    return return_stat;
  }

  register size_t row_begin = attr_ptr->row_begin;
  register size_t row_end = attr_ptr->row_end;
  register size_t cols = attr_ptr->mat_ptr->cols;
  register double *mat_data_ptr = attr_ptr->mat_ptr->data;
  register double *tmp_arr_ptr_data = tmp_arr_ptr->data;

  for (size_t i = row_begin; i < row_end; i++) {
    for (size_t j = 0; j < cols; j++) {
      tmp_arr_ptr_data[j] += mat_data_ptr[j + i * cols];
    }
  }

  register double *target_sums_array_ptr = attr_ptr->sums_arr_ptr->data;
  pthread_mutex_lock(&sums_lock);
  for (size_t j = 0; j < cols; j++) {
    target_sums_array_ptr[j] += tmp_arr_ptr_data[j];
  }
  pthread_mutex_unlock(&sums_lock);

  free_array(tmp_arr_ptr);
  *return_stat = 0;
  return return_stat;
}



array *matrix_col_sum(matrix *mat_ptr) {
  if (mat_ptr == NULL) {
    return NULL;
  }

  // numder of cores
  long proc_number = sysconf(_SC_NPROCESSORS_ONLN);
 // printf("proc number: %ld\n", proc_number);
  assert(proc_number >= 1);
  size_t n_child_threads =  proc_number;

  // array for storing result
  array *col_sums_ptr = create_array(mat_ptr->cols);
  if (col_sums_ptr == NULL) {
    return NULL;
  }

  pthread_t child_threads[n_child_threads];
  memset(child_threads, 0, (n_child_threads) * sizeof(pthread_t));

  worker_attr w_attr[n_child_threads];
  memset(w_attr, 0, (n_child_threads) * sizeof(worker_attr));
  if (set_workers_attr(w_attr, col_sums_ptr, mat_ptr, n_child_threads) != 0) {
    free_array(col_sums_ptr);
    return NULL;
  }

  //create threads
  for (size_t i = 0; i <  n_child_threads ; i++) {
    if (pthread_create(&child_threads[i], NULL, thread_worker, &w_attr[i]) != 0) {
      join_child_threads(child_threads, n_child_threads);
      free_array(col_sums_ptr);
      return NULL;
    }

    // set affinity
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(i, &cpuset);

    if (pthread_setaffinity_np(child_threads[i], sizeof(cpu_set_t), &cpuset) != 0) {
      join_child_threads(child_threads, n_child_threads);
      free_array(col_sums_ptr);
      return NULL;
    }
  }

  join_child_threads(child_threads, n_child_threads);
  return col_sums_ptr;
}
