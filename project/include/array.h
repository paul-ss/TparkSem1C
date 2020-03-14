//
// Created by paul_s on 11.03.2020.
//

#ifndef PROJECT_INCLUDE_ARRAY_H_
#define PROJECT_INCLUDE_ARRAY_H_

#include <stdio.h>


typedef struct array {
  size_t size;
  double *data;
} array;

array *create_array(size_t size);
void free_array(array *arr_ptr);


#endif  // PROJECT_INCLUDE_ARRAY_H_
