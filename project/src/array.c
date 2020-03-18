//
// Created by paul_s on 11.03.2020.
//

#include "array.h"
#include <stdlib.h>


double_array *create_double_array(size_t size) {
  double_array *arr_ptr = calloc(1, sizeof(double_array));
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


void free_double_array(double_array *arr_ptr) {
  if (arr_ptr != NULL) {
    free(arr_ptr->data);
  }
  free(arr_ptr);
}
