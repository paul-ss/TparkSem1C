//
// Created by paul_s on 11.03.2020.
//

#include "array.h"
#include <stdlib.h>


array *create_array(size_t size) {
  array *arr_ptr = calloc(1, sizeof(array));
  if (arr_ptr == NULL) {
    return NULL;
  }

  arr_ptr->data = calloc(size, sizeof(double));
  if (arr_ptr->data == NULL) {
    free(arr_ptr);
    return NULL;
  }

  arr_ptr->size = size;

  return arr_ptr;
}


void free_array(array *arr_ptr) {
  free(arr_ptr->data);
  free(arr_ptr);
}