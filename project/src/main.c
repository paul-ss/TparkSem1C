#include "matrix.h"
#include "array.h"

#include <stdio.h>
#include <omp.h>

#define N_ITERATIONS 5

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi) << 32 );
}


int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Invalid input arguments\n");
    return 0;
  }

  matrix *mat_ptr = create_matrix_from_file(argv[1]);
  if (mat_ptr == NULL) {
    printf("Invalid matrix file\n");
    return 0;
  }

  long cycles = 0;
  double wtime = 0.0;
  for (int i = 0; i < N_ITERATIONS; i++) {
    double wstart = omp_get_wtime();
    long cycles1 = rdtsc();
    double_array *arr_ptr = matrix_col_sum(mat_ptr);
    long cycles2 = rdtsc();
    double wfinish = omp_get_wtime();

    wtime += (wfinish - wstart);
    cycles += (cycles2 - cycles1);

    free_double_array(arr_ptr);
  }

  wtime /= N_ITERATIONS;
  cycles /= N_ITERATIONS;

  printf("Matrix %zux%zu\n", mat_ptr->rows, mat_ptr->cols);
  printf("proc cycles: %ld\nwtime: %lf\n\n", cycles, wtime);


  free_matrix(mat_ptr);
  return 0;
}

