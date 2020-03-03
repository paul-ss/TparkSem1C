//
// Created by paul_s on 02.03.2020.
//

#include <iostream>
#include "gtest/gtest.h"

extern "C" {
  #include "vector.h"
  #include "io_data.h"
}


TEST(vector_test, create_vector_5) {
  vector *vec_ptr = create_vec(5);
  if (vec_ptr == NULL) {
    FAIL() << "Can't allocate vector";
  }
  if (vec_ptr->arr_ptr == NULL) {
    FAIL() << "Can't allocate array";
  }

  ASSERT_EQ(vec_ptr->size, 0);
  ASSERT_EQ(vec_ptr->capacity, 5);

  free_vec(vec_ptr);
}

TEST(vector_test, create_vector_0) {
  vector *vec_ptr = create_vec(0);
  if (vec_ptr == NULL) {
    FAIL() << "Can't allocate vector";
  }

  free_vec(vec_ptr);
}

TEST(vector_test, create_vector_minus_5) {
  vector *vec_ptr = create_vec(-5);
  if (vec_ptr != NULL) {
    FAIL() << "Allocated array with negative size";
  }
}

TEST(vector_test, increase_vector_0) {
  vector *vec_ptr = create_vec(0);
  increase_vec(vec_ptr);
  if (vec_ptr == NULL) {
    FAIL() << "Vector ptr is NULL";
  }

  if (vec_ptr->arr_ptr == NULL) {
    FAIL() << "Array ptr is NULL";
  }

  ASSERT_EQ(vec_ptr->size, 0);
  ASSERT_EQ(vec_ptr->capacity, 1);

  free_vec(vec_ptr);
}

TEST(vector_test, increase_vector_1) {
  vector *vec_ptr = create_vec(1);
  ASSERT_EQ(increase_vec(vec_ptr), 0);

  vec_ptr->size = 1;
  ASSERT_EQ(increase_vec(vec_ptr), 0);
  ASSERT_EQ(vec_ptr->size, 1);
  ASSERT_EQ(vec_ptr->capacity, 2);

  free_vec(vec_ptr);
}

TEST(vector_test, increase_vector_null) {
  ASSERT_EQ(increase_vec(NULL), -1);
}

TEST(vector_test, push_back_vector) {
  vector *vec_ptr = create_vec(0);
  data expected_data = {"name", "surname", "role", 123};

  ASSERT_EQ(push_back(vec_ptr, &expected_data), 0);
  ASSERT_EQ(vec_ptr->size, 1);

  ASSERT_STREQ(vec_ptr->arr_ptr[0].name, expected_data.name);
  ASSERT_STREQ(vec_ptr->arr_ptr[0].surname, expected_data.surname);
  ASSERT_STREQ(vec_ptr->arr_ptr[0].role, expected_data.role);
  ASSERT_EQ(vec_ptr->arr_ptr[0].degree, expected_data.degree);

  free_vec(vec_ptr);
}

TEST(vector_test, push_back_vector_null) {
  ASSERT_EQ(push_back(NULL, NULL), -1);
}

TEST(vector_test, get_elem) {
  vector *vec_ptr = create_vec(0);
  data expected_data = {"name", "surname", "role", 123};
  data got_data = {};
  push_back(vec_ptr, &expected_data);

  ASSERT_NE(get_elem(vec_ptr, &got_data, 5), 0);
  ASSERT_NE(get_elem(vec_ptr, &got_data, -5), 0);
  ASSERT_EQ(get_elem(vec_ptr, &got_data, 0), 0);

  ASSERT_STREQ(got_data.name, expected_data.name);
  ASSERT_STREQ(got_data.surname, expected_data.surname);
  ASSERT_STREQ(got_data.role, expected_data.role);
  ASSERT_EQ(got_data.degree, expected_data.degree);

  ASSERT_NE(get_elem(NULL, NULL, 1), 0);

  free_vec(vec_ptr);
}