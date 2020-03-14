//
// Created by paul_s on 13.03.2020.
//
#include "matrix.h"
#include "array.h"


array *matrix_col_sum(matrix *mat_ptr) {
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
      sum += mat_ptr->data[i + j * mat_ptr->cols];
    }
    arr_ptr->data[i] = sum;
  }

  return arr_ptr;
}


