#include <sstream>
#include "gtest.h"
#include "tmatrix.h"

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, can_move_vector_using_move_constructor)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(std::move(v)));
}

TEST(TDynamicVector, can_move_vector_using_move_operator)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(5);
	ASSERT_NO_THROW(v1 = std::move(v2));
}

TEST(TDynamicVector, move_constructor_makes_source_empty)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(std::move(v1));

	EXPECT_EQ(0, v1.size());
}

TEST(TDynamicVector, move_assignment_makes_source_empty)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(5);
	v2 = std::move(v1);

	EXPECT_EQ(0, v1.size());
}

TEST(TDynamicVector, move_constructor_keeps_old_memory)
{
	TDynamicVector<int> v1(10);
	int* old_data = &v1[0];
	TDynamicVector<int> v2(std::move(v1));

	EXPECT_EQ(old_data, &v2[0]);
}

TEST(TDynamicVector, move_assignment_keeps_old_memory)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(5);
	int* old_data = &v1[0];
	v2 = std::move(v1);

	EXPECT_EQ(old_data, &v2[0]);
}

TEST(TDynamicVector, moved_vector_keeps_source_data)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(std::move(v1));
	TDynamicVector<int> exp(arr, 5);

	EXPECT_EQ(exp, v2);
}

TEST(TDynamicVector, self_move_assignment_is_possible)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(v = std::move(v));
}

TEST(TDynamicVector, self_move_assignment_keeps_vector_data)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);
	v = std::move(v);

	EXPECT_EQ(5, v.size());
	EXPECT_EQ(1, v[0]);
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(v1);

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(v1);

	EXPECT_NE(&v1[0], &v2[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);

	EXPECT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);

	EXPECT_ANY_THROW(v.at(7));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int arr[] = {1, 2, 3, 4, 5};
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(v1);
	v2 = v2;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(5);
	v2 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(1);
	v2 = v1;

	EXPECT_EQ(5, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(1);
	v2 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(arr, 5);

	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);

	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(7);

	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);
	v = v + 1;
	int arrExp[] = {2, 3, 4, 5, 6};
	TDynamicVector<int> vExp(arrExp, 5);

	EXPECT_EQ(vExp, v);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);
	v = v - 1;
	int arrExp[] = {0, 1, 2, 3, 4};
	TDynamicVector<int> vExp(arrExp, 5);

	EXPECT_EQ(vExp, v);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);
	v = v * 2;
	int arrExp[] = {2, 4, 6, 8, 10};
	TDynamicVector<int> vExp(arrExp, 5);

	EXPECT_EQ(vExp, v);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(arr, 5);
	int arrExp[] = {2, 4, 6, 8, 10};
	TDynamicVector<int> vExp(arrExp, 5);

	EXPECT_EQ(vExp, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(7);

	EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int arr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(arr, 5);
	int arrExp[] = {0, 0, 0, 0, 0};
	TDynamicVector<int> vExp(arrExp, 5);

	EXPECT_EQ(vExp, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(7);

	EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int arr[] = {2, 2, 2, 2, 2};
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(arr, 5);
	int exp = 20;

	EXPECT_EQ(exp, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(7);

	EXPECT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, can_read_vector)
{
  TDynamicVector<int> v(5);
  TDynamicVector<int> expected(5);
  for (int i = 0; i < 5; i++) expected[i] = i;
  
  std::stringstream sstr;
  sstr << "0 1 2 3 4\n";
  sstr >> v;
  
  EXPECT_EQ(expected, v);
}

TEST(TDynamicVector, can_write_vector)
{
  TDynamicVector<int> v(5);
  for (int i = 0; i < 5; i++) v[i] = i;
  std::string expected = "0 1 2 3 4 ";
  
  std::stringstream sstr;
  sstr << v;
  
  EXPECT_EQ(expected, sstr.str());
}
