//
// Created by paul_s on 13.03.2020.
//

#include "utils.h"
#include "gtest/gtest.h"




TEST(matrix, create) {
  matrix *mat_ptr1 = create_matrix(0, 0);
  ASSERT_TRUE(mat_ptr1 == nullptr);

  matrix *mat_ptr2 = create_matrix(1, -2);
  ASSERT_TRUE(mat_ptr2 == nullptr);

  matrix *mat_ptr3 = create_matrix(5, 10);
  ASSERT_TRUE(mat_ptr3 != nullptr);
  ASSERT_EQ(mat_ptr3->rows, 5);
  ASSERT_EQ(mat_ptr3->cols, 10);


  free_matrix(mat_ptr1);
  free_matrix(mat_ptr2);
  free_matrix(mat_ptr3);
}

TEST(matrix, create_from_file) {
  std::ofstream os("1.txt");
  if (!os) {
    FAIL();
  }

  matrix *exp_ptr = create_matrix(3, 4);
  os << 3 << " " << 4 << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      os << i * j / 3.0 << " ";
      set_elem(exp_ptr, i * j / 3.0, i, j);
    }
    os << std::endl;
  }

  os.close();

  matrix *got_ptr = create_matrix_from_file("1.txt");
  ASSERT_EQ(remove("1.txt"), 0);
  is_equal(exp_ptr, got_ptr);
  free_matrix(exp_ptr);
  free_matrix(got_ptr);
}

TEST(matrix, create_from_not_existing_file) {
  matrix *mat_ptr = create_matrix_from_file("2");
  ASSERT_TRUE(mat_ptr == nullptr);
}


TEST(matrix, create_from_bad_file) {
  std::ofstream os1("1.txt");
  if (!os1) {
    FAIL();
  }
  os1 << 3 << " " << 4 << " " << 5 << std::endl;
  os1.close();
  ASSERT_TRUE(create_matrix_from_file("1.txt") == nullptr);
  ASSERT_EQ(remove("1.txt"), 0);

  std::ofstream os2("2.txt");
  if (!os2) {
    FAIL();
  }
  os2 << 3 << std::endl;
  os2.close();
  ASSERT_TRUE(create_matrix_from_file("2.txt") == nullptr);
  ASSERT_EQ(remove("2.txt"), 0);
}

TEST(matrix, set_get_elem) {
  matrix *mat_ptr = create_matrix(10, 10);
  ASSERT_TRUE(mat_ptr != nullptr);

  ASSERT_EQ(set_elem(mat_ptr, 5.0, 2, 3), 0);
  double elem = 0.0;
  ASSERT_EQ(get_elem(mat_ptr, &elem, 2, 3), 0);
  ASSERT_DOUBLE_EQ(elem, 5.0);

  ASSERT_EQ(set_elem(mat_ptr, 5.0, 2, 30), -1);
  ASSERT_EQ(set_elem(mat_ptr, 5.0, 20, 3), -1);
  ASSERT_EQ(set_elem(nullptr, 5.0, 2, 3), -1);
  ASSERT_EQ(set_elem(mat_ptr, 5.0, 20, -3), -1);

  ASSERT_EQ(get_elem(mat_ptr, &elem, 2, 30), -1);
  ASSERT_EQ(get_elem(mat_ptr, &elem, 20, 3), -1);
  ASSERT_EQ(get_elem(nullptr, &elem, 2, 3), -1);
  ASSERT_EQ(get_elem(mat_ptr, &elem, 20, -3), -1);
  ASSERT_EQ(get_elem(mat_ptr, nullptr, 2, 3), -1);

  free_matrix(mat_ptr);
}

TEST(matrix, col_sums) {
  matrix *mat_ptr = generate_matrix(100, 100);
  ASSERT_TRUE(mat_ptr != nullptr);

  array *arr_ptr1 = matrix_col_sum(mat_ptr);
  ASSERT_TRUE(arr_ptr1 != nullptr);

  array *arr_ptr2 = matrix_col_sum_common(mat_ptr);
  ASSERT_TRUE(arr_ptr2 != nullptr);

  is_equal(arr_ptr1, arr_ptr2);

  free_matrix(mat_ptr);
  free_array(arr_ptr1);
  free_array(arr_ptr2);
}