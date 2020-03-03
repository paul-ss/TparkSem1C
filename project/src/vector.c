//
// Created by paul_s on 28.02.2020.
//
#include <stdlib.h>

#include "vector.h"

#define INCREASE_COEFF 2

vector *create_vec(size_t cap) {
  vector *vec_ptr = calloc(1, sizeof(vector));
  if (vec_ptr == NULL) {
    return NULL;
  }

  vec_ptr->size = 0;
  vec_ptr->capacity = cap;

  vec_ptr->arr_ptr = calloc(cap, sizeof(data));
  if (cap != 0 && vec_ptr->arr_ptr == NULL) {
    free(vec_ptr);
    return NULL;
  }

  return vec_ptr;
}

int increase_vec(vector *vec_ptr) {
  if (vec_ptr == NULL) {
    return -1;
  }

  if (vec_ptr->size == vec_ptr->capacity) {
    size_t new_cap = vec_ptr->capacity * INCREASE_COEFF;
    if (new_cap == 0) {
      new_cap = 1;
    }

    data *new_arr_ptr = realloc(vec_ptr->arr_ptr, sizeof(data) * new_cap);
    if (new_arr_ptr == NULL) {
      return -1;
    }

    vec_ptr->capacity = new_cap;
    vec_ptr->arr_ptr = new_arr_ptr;
  }

  return 0;
}


void free_vec(vector *vec_ptr) {
  free(vec_ptr->arr_ptr);
  free(vec_ptr);
}

int push_back(vector *vec_ptr, const data *data_ptr) {
  if (vec_ptr == NULL || data_ptr == NULL) {
    return -1;
  }

  if (increase_vec(vec_ptr)) {
    return -1;
  }

  vec_ptr->arr_ptr[vec_ptr->size++] = *data_ptr;
  return 0;
}

int get_elem(vector *vec_ptr, data *data_ptr, size_t index) {
  if (vec_ptr == NULL || data_ptr == NULL) {
    return -1;
  }

  if (index >= vec_ptr->size) {
    return -1;
  }

  *data_ptr = vec_ptr->arr_ptr[index];
  return 0;
}

