#include <stdio.h>
#include "io_data.h"
#include "vector.h"
int main() {
  vector *v = create_vec(0);
  run_interface(v);
  free_vec(v);

  return 0;
}