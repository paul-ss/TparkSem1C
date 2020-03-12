//
// Created by paul_s on 11.03.2020.
//

#ifndef HW_2_ARRAY_H
#define HW_2_ARRAY_H

#include <stdio.h>


typedef struct array {
  size_t size;
  double *data;
} array;

array *create_array(size_t size);
void free_array(array *arr_ptr);


#endif //HW_2_ARRAY_H
