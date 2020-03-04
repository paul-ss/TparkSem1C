//
// Created by paul_s on 04.03.2020.
//

#include <iostream>
#include <vector>
#include "gtest/gtest.h"

extern "C" {
#include <sys/stat.h>

#include "vector.h"
#include "io_data.h"
}

void is_data_eq(data *expected_data_ptr, data *got_data_ptr) {
  ASSERT_STREQ(expected_data_ptr->name, got_data_ptr->name);
  ASSERT_STREQ(expected_data_ptr->surname, got_data_ptr->surname);
  ASSERT_STREQ(expected_data_ptr->role, got_data_ptr->role);
  ASSERT_EQ(expected_data_ptr->degree, got_data_ptr->degree);
}



TEST (test_io_data, test_read_data) {
  struct cpp_data {
    std::string name;
    std::string surname;
    std::string role;
    int degree;
  };

  std::vector <cpp_data> input_vector;
  cpp_data input_data1 = {"name", "surname", "role", 123};
  cpp_data input_data2 = {"namenamenamanamenamename",
                          "surnamesurnamesurnamesurname",
                          "rolerolerolerolerolerolerolerole",
                          -4};
  cpp_data input_data3 = {"name654321",
                          "surname0745645678",
                          "role3465765698",
                          -123};

  input_vector.push_back(input_data1);
  input_vector.push_back(input_data2);
  input_vector.push_back(input_data3);

  FILE *out_fd = fopen("tst_read_data.txt", "w");
  for (auto &input_data : input_vector) {
    fprintf(out_fd,
            "%s\n%s\n%s\n%d\n",
            input_data.name.c_str(),
            input_data.surname.c_str(),
            input_data.role.c_str(),
            input_data.degree);
  }
  fclose(out_fd);

  FILE *input_fd = freopen("tst_read_data.txt", "r", stdin);
    if (input_fd == NULL) {
    FAIL() << "Can't redirect input";
  }

  data got_data = {};
  for (auto &input_data : input_vector) {
    ASSERT_EQ(read_data(&got_data), 0);

    ASSERT_STREQ(got_data.name, input_data.name.substr(0, STRING_LENGTH).c_str());
    ASSERT_STREQ(got_data.surname, input_data.surname.substr(0, STRING_LENGTH).c_str());
    ASSERT_STREQ(got_data.role, input_data.role.substr(0, STRING_LENGTH).c_str());
    ASSERT_EQ(got_data.degree, input_data.degree);
  }

  fclose(input_fd);
  remove("tst_read_data.txt");
}

TEST (test_io_data, conditional_get_data) {
  vector *vec_ptr = create_vec(0);
  data test_data1 = {"name1", "surname1", "role1", 1};
  data test_data2 = {"name2", "surname2", "role2", 2};
  data test_data3 = {"name3", "surname3", "role3", 3};
  push_back(vec_ptr, &test_data1);
  push_back(vec_ptr, &test_data2);
  push_back(vec_ptr, &test_data3);

  data got_data = {};

  vector *got_vec_ptr = conditional_get_data(vec_ptr, "all", 0, 1, 0);
  ASSERT_EQ(get_elem(got_vec_ptr, &got_data, 0), 0);
  is_data_eq(&got_data, &test_data1);
  free_vec(got_vec_ptr);
  got_vec_ptr = NULL;

  got_vec_ptr = conditional_get_data(vec_ptr, "all", 2, 2, 0);
  ASSERT_EQ(get_elem(got_vec_ptr, &got_data, 0), 0);
  is_data_eq(&got_data, &test_data2);
  free_vec(got_vec_ptr);
  got_vec_ptr = NULL;

  got_vec_ptr = conditional_get_data(vec_ptr, "all", 3, 10, 0);
  ASSERT_EQ(get_elem(got_vec_ptr, &got_data, 0), 0);
  is_data_eq(&got_data, &test_data3);
  free_vec(got_vec_ptr);
  got_vec_ptr = NULL;

  got_vec_ptr = conditional_get_data(vec_ptr, "role1", 3, 10, 1);
  ASSERT_EQ(get_elem(got_vec_ptr, &got_data, 0), 0);
  is_data_eq(&got_data, &test_data1);
  free_vec(got_vec_ptr);
  got_vec_ptr = NULL;

  got_vec_ptr = conditional_get_data(vec_ptr, "role2", 0, 1, 0);
  if (got_vec_ptr != NULL) {
    FAIL();
  }

  free_vec(vec_ptr);
}

