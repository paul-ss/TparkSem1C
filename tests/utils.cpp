//
// Created by paul_s on 13.03.2020.
//
#include <iostream>
#include <random>
#include "utils.h"

#define EPSILON 0.00001

void is_equal(matrix *mat_ptr1, matrix *mat_ptr2) {
  ASSERT_TRUE(mat_ptr1 != nullptr);
  ASSERT_TRUE(mat_ptr2 != nullptr);
  ASSERT_EQ(mat_ptr1->rows, mat_ptr2->rows);
  ASSERT_EQ(mat_ptr1->cols, mat_ptr2->cols);

  for (size_t i = 0; i < mat_ptr1->rows; i++) {
    for (size_t j = 0; j < mat_ptr1->cols; j++) {
      ASSERT_NEAR(mat_ptr1->data[j + i * mat_ptr1->cols], mat_ptr2->data[j + i * mat_ptr2->cols], EPSILON);
    }
  }
}

void is_equal(double_array *arr_ptr1, double_array *arr_ptr2) {
  ASSERT_TRUE(arr_ptr1 != nullptr);
  ASSERT_TRUE(arr_ptr2 != nullptr);
  ASSERT_EQ(arr_ptr1->size, arr_ptr2->size);

  for (size_t j = 0; j < arr_ptr1->size; j++) {
    ASSERT_NEAR(arr_ptr1->data[j], arr_ptr2->data[j], EPSILON);
  }
}


matrix *generate_matrix(size_t rows, size_t cols) {
  std::random_device rd;
  std::mt19937 mersenne(rd());

  matrix *mat_ptr = create_matrix(rows, cols);
  if (mat_ptr == nullptr) {
    return nullptr;
  }

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      mat_ptr->data[j + i * mat_ptr->cols] = (double) ((int) mersenne()) / 1000000.0;
    }
  }

  return mat_ptr;
}
