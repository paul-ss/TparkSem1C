//
// Created by paul_s on 28.02.2020.
//

#ifndef PROJECT_INCLUDE_VECTOR_H_
#define PROJECT_INCLUDE_VECTOR_H_

#include "io_data.h"


struct vector {
  data *arr_ptr;
  size_t size;
  size_t capacity;
};

typedef struct vector vector;

vector *create_vec(size_t cap);
int increase_vec(vector *vec_ptr);
void free_vec(vector *vec_ptr);
int push_back(vector *vec_ptr, const data *data_ptr);
int get_elem(vector *vec_ptr, data *data_ptr, size_t index);


#endif  // PROJECT_INCLUDE_VECTOR_H_
