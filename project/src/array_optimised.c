//
// Created by paul_s on 18.03.2020.
//

#include "array_optimised.h"
#include <stdlib.h>


pthread_t_array *create_pthread_t_array(size_t size) {
  pthread_t_array *arr_ptr = calloc(1, sizeof(pthread_t_array));
  if (arr_ptr == NULL) {
    return NULL;
  }

  arr_ptr->data = calloc(size, sizeof(pthread_t));
  if (arr_ptr->data == NULL) {
    free(arr_ptr);
    return NULL;
  }

  arr_ptr->size = size;

  return arr_ptr;
}


void free_pthread_t_array(pthread_t_array *arr_ptr) {
  if (arr_ptr != NULL) {
    free(arr_ptr->data);
  }
  free(arr_ptr);
}



worker_attr_array *create_worker_attr_array(size_t size) {
  worker_attr_array *arr_ptr = calloc(1, sizeof(worker_attr_array));
  if (arr_ptr == NULL) {
    return NULL;
  }

  arr_ptr->data = calloc(size, sizeof(worker_attr));
  if (arr_ptr->data == NULL) {
    free(arr_ptr);
    return NULL;
  }

  arr_ptr->size = size;

  return arr_ptr;
}


void free_worker_attr_array(worker_attr_array *arr_ptr) {
  if (arr_ptr != NULL) {
    free(arr_ptr->data);
  }
  free(arr_ptr);
}
