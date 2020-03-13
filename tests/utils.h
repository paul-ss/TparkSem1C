//
// Created by paul_s on 13.03.2020.
//

#ifndef HW_2_UTILS_H
#define HW_2_UTILS_H


#include <iostream>
#include <fstream>
#include <vector>
#include "gtest/gtest.h"


extern "C" {
#include "matrix.h"
#include "array.h"
}

void is_equal(matrix *mat_ptr1, matrix *mat_ptr2);
void is_equal(array *arr_ptr1, array *arr_ptr2);
matrix *generate_matrix(size_t rows, size_t cols);

#endif //HW_2_UTILS_H
