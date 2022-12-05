#include "tmatrix.h"

#include <gtest.h>

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

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(3);
	v[0] = 25;
	v[1] = 11;
	TDynamicVector<int> n = v;
	EXPECT_EQ(v, n);


}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(2);
	v[0] = 1;
	v[1] = 2;
	TDynamicVector<int> n = v;

	EXPECT_NE(&v, &n);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(3);
	EXPECT_ANY_THROW(v[-1] = 5;);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(3);
	EXPECT_ANY_THROW(v[MAX_VECTOR_SIZE + 1] = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	EXPECT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	
	TDynamicVector<int> v(4), n(4);
	v[0] = 1;
	n = v;
	EXPECT_EQ(n, v);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(2), n(5);
	v = n;

	EXPECT_EQ(v.size(), 5);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(2), n(5);
	v = n;

	EXPECT_EQ(n, v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(3), n(3);
	v[0] = 4;
	n[0] = 4;
	
	EXPECT_TRUE(v == n);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(3);

	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(4), n(5);

	EXPECT_TRUE(v != n);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 4;
	v[1] = -1;
	v[2] = -2;
	v = v + 2;
	res[0] = 6;
	res[1] = 1;
	res[2] = 0;

	EXPECT_EQ(res, v);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 4;
	v[1] = -1;
	v[2] = -2;
	v = v - 2;
	res[0] = 2;
	res[1] = -3;
	res[2] = -4;

	EXPECT_EQ(res, v);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 4;
	v[1] = -1;
	v[2] = -2;
	v = v * 2;
	res[0] = 8;
	res[1] = -2;
	res[2] = -4;

	EXPECT_EQ(res, v);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(2), n(2), res(2);
	v[0] = 2; v[1] = 2;
	n[0] = 4; n[1] = 7;
	res[0] = 6, res[1] = 9;

	EXPECT_EQ(res, v + n);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), n(5);

	EXPECT_ANY_THROW(v + n);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(2), n(2), res(2);
	v[0] = 4; v[1] = 2;
	n[0] = 1; n[1] =3;
	res[0] = 3, res[1] = -1;

	EXPECT_EQ(res, v - n);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), n(4);

	EXPECT_ANY_THROW(v - n);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(2), n(2);
	v[0] = 1; v[1] = 2;
	n[0] = 3; n[1] = 4;
	int res = 11;

	EXPECT_EQ(res, v * n);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), n(6);

	EXPECT_ANY_THROW(v * n);
}
 

