#include "matrix.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

#include <math.h>

#include "time.h"
#include "array.h"

int main(int argc, char* argv[]) {

  if (argc < 2) {
    printf("Invalid input arguments\n");
    return 0;
  }

  matrix *mat_ptr = create_matrix_from_file(argv[1]);
  //print_matrix(mat_ptr);
  printf("\n");


  double elem = 0;
  elem = 1;
  unsigned int start = clock();
  array *arr_ptr1 = matrix_col_sum_naive(mat_ptr);
  unsigned int finish = clock();

  printf("long method: %d\n", finish - start);


  start = clock();
  array *arr_ptr2 = matrix_col_sum_optimised(mat_ptr);
  finish = clock();
  printf("quick method: %d\n", finish - start);


  start = clock();
  array *arr_ptr3 = matrix_col_sum_common(mat_ptr);
  finish = clock();

  printf("common method: %d\n", finish - start);

  for (size_t i = 0; i < arr_ptr1->size; i++) {
      if (fabs(arr_ptr1->data[i] - arr_ptr2->data[i]) > 0.00001) {
        printf("%lf  diff12\n", arr_ptr1->data[i] - arr_ptr2->data[i]);
        break;
      }
    if (fabs(arr_ptr1->data[i] - arr_ptr3->data[i]) > 0.00001) {
      printf("%lf  diff13\n", arr_ptr1->data[i] - arr_ptr3->data[i]);
      break;
    }
  }

  free_array(arr_ptr1);
  free_array(arr_ptr2);
  free_array(arr_ptr3);
  free_matrix(mat_ptr);
  return 0;
}

