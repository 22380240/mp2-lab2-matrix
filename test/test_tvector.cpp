#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length) {
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector) {
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length) {
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector) {
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one) {
  TDynamicVector<int> v(10);
  v[1] = 5;
  TDynamicVector<int> v1(v);

  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory) {
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(v);

  EXPECT_NE(&v[0], &v1[0]);
}

TEST(TDynamicVector, can_get_size) {
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element) {
  TDynamicVector<int> v(10);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index) {
  TDynamicVector<int> v(10);

  EXPECT_ANY_THROW(v[-1] = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index) {
  TDynamicVector<int> v(10);

  EXPECT_ANY_THROW(v[MAX_VECTOR_SIZE + 1] = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself) {
  TDynamicVector<int> v(10);

  EXPECT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size) {
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(10);
  v1[1] = 2;

  EXPECT_NO_THROW(v = v1);
  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size) {
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);
  v = v1;

  EXPECT_EQ(v.size(), 11);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size) {
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);

  EXPECT_NO_THROW(v = v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true) {
  TDynamicVector<int> v(10);
  v[1] = 2;
  TDynamicVector<int> v1(11);
  v1[1] = 2;

  EXPECT_TRUE(v != v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true) {
  TDynamicVector<int> v(10);

  EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal) {
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);

  EXPECT_FALSE(v == v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector) {
  TDynamicVector<int> v(10);
  v[3] = 1;
  TDynamicVector<int> v1;

  EXPECT_NO_THROW(v1 = v + 2);
  EXPECT_EQ(v1[0], 2);
  EXPECT_EQ(v1[3], 3);
  EXPECT_EQ(v1[4], 2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector) {
  TDynamicVector<int> v(10);
  v[3] = 1;
  TDynamicVector<int> v1;

  EXPECT_NO_THROW(v1 = v - 2);
  EXPECT_EQ(v1[0], -2);
  EXPECT_EQ(v1[3], -1);
  EXPECT_EQ(v1[4], -2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector) {

  TDynamicVector<int> v(10);
  v[3] = 2;
  TDynamicVector<int> v1;

  EXPECT_NO_THROW(v1 = v * 2);
  EXPECT_EQ(v1[0], 0);
  EXPECT_EQ(v1[3], 4);
  EXPECT_EQ(v1[4], 0);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size) {
  TDynamicVector<int> v(10);
  v[3] = 1;
  TDynamicVector<int> v1(10);
  v1[3] = 2;
  v1[4] = 2;
  TDynamicVector<int> v2;

  EXPECT_NO_THROW(v2 = v + v1);
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[3], 3);
  EXPECT_EQ(v2[4], 2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) {
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);

  EXPECT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size) {
  TDynamicVector<int> v(10);
  v[3] = 1;
  TDynamicVector<int> v1(10);
  v1[3] = 2;
  v1[4] = 2;
  TDynamicVector<int> v2;

  EXPECT_NO_THROW(v2 = v - v1);
  EXPECT_EQ(v2[0], 0);
  EXPECT_EQ(v2[3], -1);
  EXPECT_EQ(v2[4], -2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size) {
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);

  EXPECT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size) {
  TDynamicVector<int> v(10);
  v[3] = 3;
  TDynamicVector<int> v1(10);
  v1[3] = 2;
  v1[4] = 2;
  int v2;

  EXPECT_NO_THROW(v2 = v * v1);
  EXPECT_EQ(v2, 6);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) {
  TDynamicVector<int> v(10);
  TDynamicVector<int> v1(11);

  ASSERT_ANY_THROW(v * v1);
}
