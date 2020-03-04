//
// Created by paul_s on 28.02.2020.
//

#ifndef PROJECT_INCLUDE_IO_DATA_H_
#define  PROJECT_INCLUDE_IO_DATA_H_

#include <stdio.h>

#define STRING_LENGTH 20
#define STRING_LENGTH_STR "20"

typedef struct vector vector;

typedef struct data {
  char name[STRING_LENGTH + 1];
  char surname[STRING_LENGTH + 1];
  char role[STRING_LENGTH + 1];
  int degree;
} data;

int read_data(data *result);
void print_data(data *person, size_t number);
void run_interface(vector *vec_ptr);
void custom_flush();
vector *conditional_get_data(vector *vec_ptr,
                              const char *role,
                              int min_degree,
                              int max_degree,
                              int ignore_degree);
void print_interface(vector *vec_ptr);

#endif  // PROJECT_INCLUDE_IO_DATA_H_
