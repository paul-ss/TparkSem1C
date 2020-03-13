#include "matrix.h"
#include "array.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

#include <math.h>

#include "time.h"

#include <omp.h>

static __inline__ unsigned long long rdtsc(void)
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}



int main(int argc, char* argv[]) {


  if (argc < 2) {
    printf("Invalid input arguments\n");
    return 0;
  }

  matrix *mat_ptr = create_matrix_from_file(argv[1]);
  //print_matrix(mat_ptr);
  printf("\n");



  double wstart = omp_get_wtime();
  long cycles1 = rdtsc();
  unsigned int start = clock();
  array *arr_ptr1 = matrix_col_sum(mat_ptr);
  unsigned int finish = clock();
  long cycles2 = rdtsc();
  double wfinish = omp_get_wtime();

  printf("long method \nproc time: %d\ntacts: %ld\nwtime: %lf\n\n", finish - start, cycles2 - cycles1, wfinish - wstart);




 /* for (size_t i = 0; i < arr_ptr1->size; i++) {
      if (fabs(arr_ptr1->data[i] - arr_ptr2->data[i]) > 0.00001) {
        printf("%lf  diff12\n", arr_ptr1->data[i] - arr_ptr2->data[i]);
        break;
      }
    if (fabs(arr_ptr1->data[i] - arr_ptr3->data[i]) > 0.00001) {
      printf("%lf  diff13\n", arr_ptr1->data[i] - arr_ptr3->data[i]);
      break;
    }
  } */

  free_array(arr_ptr1);
  free_matrix(mat_ptr);
  return 0;
}

