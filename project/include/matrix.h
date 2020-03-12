
//
// Created by paul_s on 09.03.2020.
//

#ifndef HW_2_MATRIX_H
#define HW_2_MATRIX_H

#include <stdio.h>
#include "array.h"

typedef struct matrix {
    size_t rows;
    size_t cols;
    double *data;
} matrix;

matrix *create_matrix_from_file(const char *file_name);
void free_matrix(matrix *mat_ptr);
int set_elem(matrix *mat_ptr, double elem, size_t row, size_t col);
int get_elem(matrix *mat_ptr, double *elem, size_t row, size_t col);
void print_matrix(matrix *mat_ptr);

array *matrix_col_sum_common(matrix *mat_ptr);
array *matrix_col_sum_naive(matrix *mat_ptr);
array *matrix_col_sum_optimised(matrix *mat_ptr);

#endif //HW_2_MATRIX_H
