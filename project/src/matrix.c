//
// Created by paul_s on 09.03.2020.
//

#include "matrix.h"
#include "array.h"

#include <stdlib.h>
#include <string.h>



matrix *create_matrix(size_t rows, size_t cols) {
  matrix *mat_ptr = calloc(1, sizeof(matrix));
  if (mat_ptr == NULL) {
    return NULL;
  }

  mat_ptr->data = calloc(rows * cols, sizeof(double));
  if (mat_ptr->data == NULL) {
    free(mat_ptr);
    return NULL;
  }

  mat_ptr->rows = rows;
  mat_ptr->cols = cols;

  return mat_ptr;
}

void free_matrix(matrix *mat_ptr) {
  free(mat_ptr->data);
  free(mat_ptr);
}



void print_matrix(matrix *mat_ptr) {
  if (mat_ptr->data == NULL) {
    free(mat_ptr);
    return;
  }


  for (size_t i = 0; i < mat_ptr->rows; i++) {
    for (size_t j = 0; j < mat_ptr->cols; j++) {
      printf("%lf ", mat_ptr->data[j + i * mat_ptr->cols]);
    }

    printf("\n");
  }
}


matrix *create_matrix_from_file(const char *file_name) {
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    return NULL;
  }

  size_t rows = 0;
  size_t cols = 0;
  if (fscanf(fp, "%zu %zu", &rows, &cols) != 2) {
    fclose(fp);
    return NULL;
  }

  matrix *mat_ptr = create_matrix(rows, cols);
  double elem = 0;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (fscanf(fp, "%lf", &elem) != 1) {
        free_matrix(mat_ptr);
        fclose(fp);
      }
      set_elem(mat_ptr, elem, i, j);
    }
  }

  return mat_ptr;
}

int set_elem(matrix *mat_ptr, double elem, size_t row, size_t col) {
  if (mat_ptr == NULL) {
    return -1;
  }

  if (row >= mat_ptr->rows || col >= mat_ptr->cols) {
    return -1;
  }

  mat_ptr->data[col + row * mat_ptr->cols] = elem;
  return 0;
}


int get_elem(matrix *mat_ptr, double *elem, size_t row, size_t col) {
  if (mat_ptr == NULL) {
    return -1;
  }

  if (row >= mat_ptr->rows || col >= mat_ptr->cols) {
    return -1;
  }

  *elem = mat_ptr->data[col + row * mat_ptr->cols];
  return 0;
}





array *matrix_col_sum_naive(matrix *mat_ptr) {
  if (mat_ptr == NULL) {
    return NULL;
  }

  array *arr_ptr = create_array(mat_ptr->cols);
  if (arr_ptr == NULL) {
    return NULL;
  }


  for (size_t i = 0; i < mat_ptr->cols; i++) {
    double sum = 0;
    for (size_t j = 0; j < mat_ptr->rows; j++) {
      //get_elem(mat_ptr, &elem, j, i);
      sum += mat_ptr->data[i + j * mat_ptr->cols];
    }
    arr_ptr->data[i] = sum;
  }

  return arr_ptr;
}

array *matrix_col_sum_common(matrix *mat_ptr) {
  if (mat_ptr == NULL) {
    return NULL;
  }

  array *arr_ptr = create_array(mat_ptr->cols);
  if (arr_ptr == NULL) {
    return NULL;
  }


  for (size_t i = 0; i < mat_ptr->rows; i++) {
    double sum = 0;
    for (size_t j = 0; j < mat_ptr->cols; j++) {
      //get_elem(mat_ptr, &elem, j, i);
      arr_ptr->data[j] += mat_ptr->data[j + i * mat_ptr->cols];
    }
  }

  return arr_ptr;
}

