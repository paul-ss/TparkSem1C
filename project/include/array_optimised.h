//
// Created by paul_s on 18.03.2020.
//

#ifndef HW_2_ARRAY_OPTIMISED_H
#define HW_2_ARRAY_OPTIMISED_H


#include "matrix.h"
#include "array.h"


#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>

typedef struct worker_attr {
  double_array *sums_arr_ptr;
  const matrix *mat_ptr;
  size_t row_begin;
  size_t row_end;
} worker_attr;


typedef struct pthread_t_array {
  size_t size;
  pthread_t *data;
} pthread_t_array;

typedef struct worker_attr_array {
  size_t size;
  worker_attr *data;
} worker_attr_array;


pthread_t_array *create_pthread_t_array(size_t size);
void free_pthread_t_array(pthread_t_array *arr_ptr);
worker_attr_array *create_worker_attr_array(size_t size);
void free_worker_attr_array(worker_attr_array *arr_ptr);


#endif //HW_2_ARRAY_OPTIMISED_H
