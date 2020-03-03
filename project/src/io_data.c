//
// Created by paul_s on 28.02.2020.
//
#include <string.h>

#include "io_data.h"
#include "vector.h"

#define INPUT_STRING_FORMAT  "%19s"


int read_data(data *result) {
  printf("Enter name: ");
  if (scanf(INPUT_STRING_FORMAT, result->name) != 1) {
    return -1;
  }
  custom_flush();

  printf("Enter surname: ");
  if (scanf(INPUT_STRING_FORMAT, result->surname) != 1) {
    return -1;
  }
  custom_flush();

  printf("Enter role: ");
  if (scanf(INPUT_STRING_FORMAT, result->role) != 1) {
    return -1;
  }
  custom_flush();

  printf("Enter degree: ");
  if (scanf("%d", &result->degree) != 1) {
    result->degree = 0;
  }
  custom_flush();

  return 0;
}

void print_data(data *person, size_t number) {
    printf("Person %zu\n", number);
    printf("Name: %s\n", person->name);
    printf("Surname: %s\n", person->surname);
    printf("Role: %s\n", person->role);
    printf("Degree: %d\n", person->degree);
    printf("\n");
}


void run_interface(vector *vec_ptr) {
  printf("1 - add new person\n");
  printf("2 - display persons\n");
  printf("3 - quit\n");

  int command = 0;
  while (scanf("%d", &command) != -1) {
    custom_flush();
    data person;

    switch (command) {
      case 1:
        read_data(&person);
        push_back(vec_ptr, &person);
        break;
      case 2:
        print_interface(vec_ptr);
        break;
      case 3:
        return;
      default:
        printf("Invalid command\n");
        break;
    }

    command = 0;

    printf("1 - add new person\n");
    printf("2 - display persons\n");
    printf("3 - quit\n");
  }
}

void custom_flush() {
  while (getchar() != '\n') {;
  }
}

// role = "all" - print all roles, ignore_degree = 1 - print all degrees
vector *conditional_get_data(vector *vec_ptr, char *role, int min_degree, int max_degree, int ignore_degree) {
  vector *res_ptr = create_vec(0);

  data person;
  for (size_t i = 0; i < vec_ptr->size; i++) {
    if (get_elem(vec_ptr, &person, i)) {
      continue;
    }

    // all cases, then role is not chosen
    if (!strncmp("all", role, STRING_SIZE)) {
      if (ignore_degree == 1) {
        push_back(res_ptr, &person);
        // print_data(&person, i);
      } else {
        if (person.degree <= max_degree && person.degree >= min_degree) {
          push_back(res_ptr, &person);
          // print_data(&person, i);
        }
      }
    }

    // all cases, then the role is chosen
    if (!strncmp(person.role, role, STRING_SIZE)) {
      if (ignore_degree == 1) {
        push_back(res_ptr, &person);
        // print_data(&person, i);
      } else {
        if (person.degree <= max_degree && person.degree >= min_degree) {
          push_back(res_ptr, &person);
          // print_data(&person, i);
        }
      }
    }
  }

  if (res_ptr->size == 0) {
    free_vec(res_ptr);
    return NULL;
  }

  return res_ptr;
}

void print_interface(vector *vec_ptr) {
  char role[STRING_SIZE];
  printf("Enter person role ('all' - to see all) : ");
  if (scanf(INPUT_STRING_FORMAT, role) != 1) {
    snprintf(role, STRING_SIZE - 1, "all");
  }
  custom_flush();

  int ignore_degree = 0;
  printf("Ignore degree? (1 - YES, 0 - NO): ");
  if (scanf("%d", &ignore_degree) != 1) {
    ignore_degree = 1;
  }
  custom_flush();

  int min_degree = 0;
  int max_degree = 0;
  if (ignore_degree == 0) {
    printf("Set degree range in format 'min:max' : ");
    if (scanf("%d : %d", &min_degree, &max_degree) != 2) {
      ignore_degree = 1;
    }

    custom_flush();
  }

  vector *print_vec_ptr = conditional_get_data(vec_ptr, role, min_degree, max_degree, ignore_degree);
  if (print_vec_ptr != NULL) {
    for (size_t i = 0; i < print_vec_ptr->size; i++) {
      print_data(&print_vec_ptr->arr_ptr[i], i);
    }

    free_vec(print_vec_ptr);
  }
}
