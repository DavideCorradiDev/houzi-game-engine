// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/mth/matrix.hpp"

#include "hou/cor/is_same_signedness.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_matrix : public Test
{};

class test_matrix_death_test : public test_matrix
{};

}  // namespace



TEST_F(test_matrix, default_constructor)
{
  mat3x2i m;
  EXPECT_EQ(0, m(0));
  EXPECT_EQ(0, m(1));
  EXPECT_EQ(0, m(2));
  EXPECT_EQ(0, m(3));
  EXPECT_EQ(0, m(4));
  EXPECT_EQ(0, m(5));
}



TEST_F(test_matrix, initializer_list_constructor)
{
  mat3x2i mi = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(1, mi(0));
  EXPECT_EQ(2, mi(1));
  EXPECT_EQ(3, mi(2));
  EXPECT_EQ(4, mi(3));
  EXPECT_EQ(5, mi(4));
  EXPECT_EQ(6, mi(5));

  mat3x2f mf = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
  EXPECT_FLOAT_EQ(1.f, mf(0));
  EXPECT_FLOAT_EQ(2.f, mf(1));
  EXPECT_FLOAT_EQ(3.f, mf(2));
  EXPECT_FLOAT_EQ(4.f, mf(3));
  EXPECT_FLOAT_EQ(5.f, mf(4));
  EXPECT_FLOAT_EQ(6.f, mf(5));
}



TEST_F(test_matrix, element_constructor)
{
  mat3x2i mi(1, 2, 3, 4, 5, 6);
  EXPECT_EQ(1, mi(0));
  EXPECT_EQ(2, mi(1));
  EXPECT_EQ(3, mi(2));
  EXPECT_EQ(4, mi(3));
  EXPECT_EQ(5, mi(4));
  EXPECT_EQ(6, mi(5));
}



TEST_F(test_matrix, conversion_constructor)
{
  mat3x2f mf = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
  mat3x2i mi = mf;
  EXPECT_EQ(1, mi(0));
  EXPECT_EQ(2, mi(1));
  EXPECT_EQ(3, mi(2));
  EXPECT_EQ(4, mi(3));
  EXPECT_EQ(5, mi(4));
  EXPECT_EQ(6, mi(5));
}



TEST_F(test_matrix, size_operators)
{
  mat3x2i m;

  EXPECT_EQ(3u, m.get_row_count());
  EXPECT_EQ(6u, m.size());
  EXPECT_EQ(2u, m.get_column_count());

  EXPECT_EQ(3u, mat3x2i::get_row_count());
  EXPECT_EQ(6u, mat3x2i::size());
  EXPECT_EQ(2u, mat3x2i::get_column_count());
}



TEST_F(test_matrix, unchecked_element_access_operator)
{
  mat3x2i m;

  m[0] = 1;
  m[1] = 2;
  m[2] = 3;
  m[3] = 4;
  m[4] = 5;
  m[5] = 6;

  EXPECT_EQ(1, m[0]);
  EXPECT_EQ(2, m[1]);
  EXPECT_EQ(3, m[2]);
  EXPECT_EQ(4, m[3]);
  EXPECT_EQ(5, m[4]);
  EXPECT_EQ(6, m[5]);
}



TEST_F(test_matrix, element_access_operator)
{
  mat3x2i m;

  m(0) = 1;
  m(1) = 2;
  m(2) = 3;
  m(3) = 4;
  m(4) = 5;
  m(5) = 6;

  EXPECT_EQ(1, m(0));
  EXPECT_EQ(2, m(1));
  EXPECT_EQ(3, m(2));
  EXPECT_EQ(4, m(3));
  EXPECT_EQ(5, m(4));
  EXPECT_EQ(6, m(5));

  EXPECT_EQ(1, m(0, 0));
  EXPECT_EQ(2, m(0, 1));
  EXPECT_EQ(3, m(1, 0));
  EXPECT_EQ(4, m(1, 1));
  EXPECT_EQ(5, m(2, 0));
  EXPECT_EQ(6, m(2, 1));

  m(0, 0) = 7;
  m(0, 1) = 8;
  m(1, 0) = 9;
  m(1, 1) = 10;
  m(2, 0) = 11;
  m(2, 1) = 12;

  EXPECT_EQ(7, m(0));
  EXPECT_EQ(8, m(1));
  EXPECT_EQ(9, m(2));
  EXPECT_EQ(10, m(3));
  EXPECT_EQ(11, m(4));
  EXPECT_EQ(12, m(5));
}



TEST_F(test_matrix_death_test, element_access_operator_error_out_of_range)
{
  mat3x2i m;
  EXPECT_ERROR_0(m(3, 1), out_of_range);
  EXPECT_ERROR_0(m(2, 2), out_of_range);
  EXPECT_ERROR_0(m(3, 2), out_of_range);
  EXPECT_ERROR_0(m(7), out_of_range);
}



TEST_F(test_matrix, element_access_x)
{
  mat1x1i m1{1};
  mat2x1i m2{1, 2};
  mat3x1i m3{1, 2, 3};
  mat4x1i m4{1, 2, 3, 4};

  EXPECT_EQ(1, m1.x());
  EXPECT_EQ(1, m2.x());
  EXPECT_EQ(1, m3.x());
  EXPECT_EQ(1, m4.x());

  m1.x() = 2;
  EXPECT_EQ(2, m1.x());

  m2.x() = 2;
  EXPECT_EQ(2, m2.x());

  m3.x() = 2;
  EXPECT_EQ(2, m3.x());

  m4.x() = 2;
  EXPECT_EQ(2, m4.x());
}



TEST_F(test_matrix, element_access_y)
{
  mat2x1i m2{1, 2};
  mat3x1i m3{1, 2, 3};
  mat4x1i m4{1, 2, 3, 4};

  EXPECT_EQ(2, m2.y());
  EXPECT_EQ(2, m3.y());
  EXPECT_EQ(2, m4.y());

  m2.y() = 5;
  EXPECT_EQ(5, m2.y());

  m3.y() = 5;
  EXPECT_EQ(5, m3.y());

  m4.y() = 5;
  EXPECT_EQ(5, m4.y());
}



TEST_F(test_matrix, element_access_z)
{
  mat3x1i m3{1, 2, 3};
  mat4x1i m4{1, 2, 3, 4};

  EXPECT_EQ(3, m3.z());
  EXPECT_EQ(3, m4.z());

  m3.z() = 5;
  EXPECT_EQ(5, m3.z());

  m4.z() = 5;
  EXPECT_EQ(5, m4.z());
}



TEST_F(test_matrix, element_access_w)
{
  mat4x1i m4{1, 2, 3, 4};

  EXPECT_EQ(4, m4.w());

  m4.w() = 5;
  EXPECT_EQ(5, m4.w());
}



TEST_F(test_matrix, data)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  int data_ref[] = {1, 2, 3, 4, 5, 6};
  EXPECT_ARRAY_EQ(data_ref, m.data(), m.size());
}



TEST_F(test_matrix, iterator_begin)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m[0], *m.begin());
  *m.begin() = 88;
  EXPECT_EQ(88, *m.begin());
}



TEST_F(test_matrix, iterator_begin_const_matrix)
{
  const mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m[0], *m.begin());
}



TEST_F(test_matrix, iterator_end)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m.begin() + m.size(), m.end());
}



TEST_F(test_matrix, iterator_end_const_matrix)
{
  const mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m.begin() + m.size(), m.end());
}



TEST_F(test_matrix, const_iterator_begin)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m[0], *m.cbegin());
}



TEST_F(test_matrix, const_iterator_begin_const_matrix)
{
  const mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m[0], *m.cbegin());
}



TEST_F(test_matrix, const_iterator_end)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m.cbegin() + m.size(), m.cend());
}



TEST_F(test_matrix, const_iterator_end_const_matrix)
{
  const mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m.cbegin() + m.size(), m.cend());
}



TEST_F(test_matrix, reverse_iterator_begin)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m[5], *m.rbegin());
  *m.rbegin() = 88;
  EXPECT_EQ(88, *m.rbegin());
}



TEST_F(test_matrix, reverse_iterator_begin_const_matrix)
{
  const mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m[5], *m.rbegin());
}



TEST_F(test_matrix, reverse_iterator_end)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m.rbegin() + m.size(), m.rend());
}



TEST_F(test_matrix, reverse_iterator_end_const_matrix)
{
  const mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m.rbegin() + m.size(), m.rend());
}



TEST_F(test_matrix, const_reverse_iterator_begin)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m[5], *m.crbegin());
}



TEST_F(test_matrix, const_reverse_iterator_begin_const_matrix)
{
  const mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m[5], *m.crbegin());
}



TEST_F(test_matrix, const_reverse_iterator_end)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m.crbegin() + m.size(), m.crend());
}



TEST_F(test_matrix, const_reverse_iterator_end_const_matrix)
{
  const mat3x2i m = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(m.crbegin() + m.size(), m.crend());
}



TEST_F(test_matrix, set)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  m.set(7, 8, 9, 10, -1, -2);
  mat3x2i m_ref = {7, 8, 9, 10, -1, -2};
  EXPECT_EQ(m_ref, m);
}



TEST_F(test_matrix, fill)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  m.fill(1);
  mat3x2i m_ref = {1, 1, 1, 1, 1, 1};
  EXPECT_EQ(m_ref, m);
}



TEST_F(test_matrix, comparison_operators)
{
  mat3x2i m1 = {0, 1, 2, 3, 4, 5};
  mat3x2i m2 = {6, 7, 8, 9, 10, 11};
  mat3x2i m3 = m1;

  EXPECT_FALSE(m1 == m2);
  EXPECT_TRUE(m1 != m2);
  EXPECT_TRUE(m1 == m3);
  EXPECT_FALSE(m1 != m3);
}



TEST_F(test_matrix, floating_point_comparison)
{
  mat3x2f m1 = {0.f, 1.f, 2.3456f, 3.f, 4.f, 5.f};
  mat3x2f m2 = m1;
  mat3x2f m3 = {0.f, 1.f, 2.3458f, 3.f, 4.f, 5.f};

  EXPECT_TRUE(close(m1, m2));
  EXPECT_TRUE(close(m1, m3, 1e-3f));
  EXPECT_FALSE(close(m1, m3, 1e-4f));
}



TEST_F(test_matrix, addition)
{
  mat3x2i m1 = {0, 1, 2, 3, 4, 5};
  mat3x2i m2 = {6, 7, 8, -5, 10, 0};
  mat3x2i m_sum = m1 + m2;
  mat3x2i m_sum_incremental = m1;
  m_sum_incremental += m2;
  mat3x2i m_sum_ref = {6, 8, 10, -2, 14, 5};

  EXPECT_EQ(m_sum_ref, m_sum);
  EXPECT_EQ(m_sum_ref, m_sum_incremental);
}



TEST_F(test_matrix, subtraction)
{
  mat3x2i m1 = {0, 1, 2, 3, 4, 5};
  mat3x2i m2 = {6, 7, 1, -5, 10, 0};
  mat3x2i m_diff = m1 - m2;
  mat3x2i m_diff_incremental = m1;
  m_diff_incremental -= m2;
  mat3x2i m_diff_ref = {-6, -6, 1, 8, -6, 5};

  EXPECT_EQ(m_diff_ref, m_diff);
  EXPECT_EQ(m_diff_ref, m_diff_incremental);
}



TEST_F(test_matrix, opposite)
{
  mat3x2i m = {1, -2, 3, -4, 5, -6};
  mat3x2i m_opp = -m;
  mat3x2i m_opp_ref = {-1, 2, -3, 4, -5, 6};

  EXPECT_EQ(m_opp_ref, m_opp);
}



TEST_F(test_matrix, scalar_multiplication)
{
  mat3x2i m = {0, 1, 2, 3, -4, 5};
  int factor = 3;
  mat3x2i m_mult_left = factor * m;
  mat3x2i m_mult_right = m * factor;
  mat3x2i m_mult_incremental = m;
  m_mult_incremental *= factor;
  mat3x2i m_mult_ref = {0, 3, 6, 9, -12, 15};

  EXPECT_EQ(m_mult_ref, m_mult_left);
  EXPECT_EQ(m_mult_ref, m_mult_right);
  EXPECT_EQ(m_mult_ref, m_mult_incremental);
}



TEST_F(test_matrix, mixed_scalar_multiplication)
{
  mat3x2f m = {0.f, 1.f, 2.f, 3.f, -4.f, 5.f};
  int factor = 3;
  mat3x2f m_mult_left = factor * m;
  mat3x2f m_mult_right = m * factor;
  mat3x2f m_mult_incremental = m;
  m_mult_incremental *= factor;
  mat3x2f m_mult_ref = {0.f, 3.f, 6.f, 9.f, -12.f, 15.f};

  EXPECT_EQ(m_mult_ref, m_mult_left);
  EXPECT_EQ(m_mult_ref, m_mult_right);
  EXPECT_EQ(m_mult_ref, m_mult_incremental);
}



TEST_F(test_matrix, multiplication)
{
  mat3x2i m1 = {0, 1, 2, 3, -4, 5};
  mat2x1i m2 = {-4, 7};
  mat3x1i res = m1 * m2;
  mat3x1i res_ref = {7, 13, 51};

  EXPECT_EQ(res_ref, res);
}



TEST_F(test_matrix, scalar_division)
{
  mat3x2i m = {0, 2, -4, 6, 8, 10};
  int divisor = 2;
  mat3x2i m_div = m / divisor;
  mat3x2i m_div_incremental = m;
  m_div_incremental /= divisor;
  mat3x2i m_div_ref = {0, 1, -2, 3, 4, 5};

  EXPECT_EQ(m_div_ref, m_div);
  EXPECT_EQ(m_div_ref, m_div_incremental);
}



TEST_F(test_matrix, mixed_scalar_division)
{
  mat3x2f m = {0.f, 2.f, -4.f, 6.f, 8.f, 10.f};
  int divisor = 2;
  mat3x2f m_div = m / divisor;
  mat3x2f m_div_incremental = m;
  m_div_incremental /= divisor;
  mat3x2f m_div_ref = {0.f, 1.f, -2.f, 3.f, 4.f, 5.f};

  EXPECT_EQ(m_div_ref, m_div);
  EXPECT_EQ(m_div_ref, m_div_incremental);
}



TEST_F(test_matrix, reduce3x2)
{
  // clang-format off
  mat3x2i m =
  {
    1, 2,
    3, 4,
    5, 6
  };
  {
    mat2x1i mReduced_ref =
    {
      4,
      6
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 0, 0));
  }
  {
    mat2x1i mReduced_ref =
    {
      3,
      5
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 0, 1));
  }
  {
    mat2x1i mReduced_ref =
    {
      2,
      6
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 1, 0));
  }
  {
    mat2x1i mReduced_ref =
    {
      1,
      5
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 1, 1));
  }
  {
    mat2x1i mReduced_ref =
    {
      2,
      4
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 2, 0));
  }
  {
    mat2x1i mReduced_ref =
    {
      1,
      3
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 2, 1));
  }
  // clang-format on
}



TEST_F(test_matrix, reduce3x3)
{
  // clang-format off
  mat3x3i m =
  {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  };
  {
    mat2x2i mReduced_ref =
    {
      5, 6,
      8, 9
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 0, 0));
  }
  {
    mat2x2i mReduced_ref =
    {
      4, 6,
      7, 9
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 0, 1));
  }
  {
    mat2x2i mReduced_ref =
    {
      4, 5,
      7, 8
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 0, 2));
  }
  {
    mat2x2i mReduced_ref =
    {
      2, 3,
      8, 9
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 1, 0));
  }
  {
    mat2x2i mReduced_ref =
    {
      1, 3,
      7, 9
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 1, 1));
  }
  {
    mat2x2i mReduced_ref =
    {
      1, 2,
      7, 8
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 1, 2));
  }
  {
    mat2x2i mReduced_ref =
    {
      2, 3,
      5, 6
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 2, 0));
  }
  {
    mat2x2i mReduced_ref =
    {
      1, 3,
      4, 6
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 2, 1));
  }
  {
    mat2x2i mReduced_ref =
    {
      1, 2,
      4, 5
    };
    EXPECT_EQ(mReduced_ref, reduce(m, 2, 2));
  }
  // clang-format on
}



TEST_F(test_matrix, transpose)
{
  mat3x2i m = {1, 2, 3, 4, 5, 6};
  mat2x3i mTranspose = transpose(m);
  mat2x3i mTranspose_ref = {1, 3, 5, 2, 4, 6};
  EXPECT_EQ(mTranspose_ref, mTranspose);
}



TEST_F(test_matrix, adjugate1x1)
{
  mat1x1i m = {2};
  EXPECT_EQ(mat1x1i::identity(), adjugate(m));
  m.adjugate();
  EXPECT_EQ(mat1x1i::identity(), m);
}



TEST_F(test_matrix, adjugate2x2)
{
  mat2x2i m = {1, 2, 3, 4};
  mat2x2i mAdjugate_ref = {4, -2, -3, 1};
  EXPECT_EQ(mAdjugate_ref, adjugate(m));
  m.adjugate();
  EXPECT_EQ(mAdjugate_ref, m);
}



TEST_F(test_matrix, adjugate3x3)
{
  // clang-format off
  mat3x3i m =
  {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  };
  mat3x3i mAdjugate_ref =
  {
    -3, 6, -3,
    6, -12, 6,
    -3, 6, -3
  };
  // clang-format on
  EXPECT_EQ(mAdjugate_ref, adjugate(m));
  m.adjugate();
  EXPECT_EQ(mAdjugate_ref, m);
}



TEST_F(test_matrix, inverse1x1)
{
  mat1x1f m = {2.f};
  mat1x1f mInv = inverse(m);
  mat1x1f mInv_ref = {0.5f};
  EXPECT_FLOAT_CLOSE(mInv_ref, mInv);
  EXPECT_FLOAT_CLOSE(mat1x1f::identity(), m * mInv);
  m.invert();
  EXPECT_FLOAT_CLOSE(mInv_ref, mInv);
}



TEST_F(test_matrix, inverse2x2)
{
  mat2x2f m = {1.f, 2.f, 3.f, 4.f};
  mat2x2f mInv = inverse(m);
  mat2x2f mInv_ref = {-2.f, 1.f, 1.5f, -0.5f};
  EXPECT_FLOAT_CLOSE(mInv_ref, mInv);
  EXPECT_FLOAT_CLOSE(mat2x2f::identity(), m * mInv);
  m.invert();
  EXPECT_FLOAT_CLOSE(mInv_ref, mInv);
}



TEST_F(test_matrix, inverse3x3)
{
  // clang-format off
  mat3x3f m =
  {
    1.f, 2.f, 3.f,
    3.f, 2.f, 1.f,
    1.f, 3.f, 2.f
  };
  mat3x3f mInv_ref =
  {
    1.f / 12.f, 5.f / 12.f, -1.f / 3.f,
    -5.f / 12.f, -1.f / 12.f, 2.f / 3.f,
    7.f / 12.f, -1.f / 12.f, -1.f / 3.f
  };
  // clang-format on
  mat3x3f mInv = inverse(m);
  EXPECT_FLOAT_CLOSE(mInv_ref, mInv);
  EXPECT_FLOAT_CLOSE(mat3x3f::identity(), m * mInv);
  m.invert();
  EXPECT_FLOAT_CLOSE(mInv_ref, mInv);
}



TEST_F(test_matrix_death_test, inverse_failure_null_determinant)
{
  mat2x2f m = mat2x2f::zero();
  EXPECT_ERROR_0(inverse(m), inversion_error);
  EXPECT_ERROR_0(m.invert(), inversion_error);
}



TEST_F(test_matrix, determinant1x1)
{
  EXPECT_EQ(1, det(mat1x1i{1}));
  EXPECT_FLOAT_EQ(-3.f, det(mat1x1f{-3.f}));
}



TEST_F(test_matrix, determinant2x2)
{
  EXPECT_EQ(-6, det(mat2x2i{0, 2, 3, 9}));
  EXPECT_FLOAT_EQ(-11.f, det(mat2x2f{-1.f, 2.f, 3.f, 5.f}));
}



TEST_F(test_matrix, determinant3x3)
{
  EXPECT_EQ(381, det(mat3x3i{0, 2, 3, 9, -1, -4, 3, 10, -7}));
  EXPECT_FLOAT_EQ(
    66.f, det(mat3x3f{-1.f, 2.f, 3.f, 5.f, -4.f, 5.f, -2.f, 7.f, 5.f}));
}



TEST_F(test_matrix, determinant4x4)
{
  // clang-format off
  mat4x4i mi =
  {
    0, -1, 4, -7,
    2, 3, 4, 5,
    -2, -3, 13, 10,
    16, -1, 0, 4
  };
  // clang-format on
  EXPECT_EQ(8686, det(mi));

  // clang-format off
  mat4x4f mf =
  {
    -1.5f, 0.5f, 5.f, -8.f,
    3.f, 2.f, 7.f, 0.f,
    15.f, -5.f, 7.f, 9.f,
    1.f, 3.f, -2.f, -4.5f
  };
  // clang-format on
  EXPECT_FLOAT_EQ(3571.25f, det(mf));
}



TEST_F(test_matrix, trace1x1)
{
  mat1x1i m{2};
  EXPECT_EQ(2, trace(m));
}



TEST_F(test_matrix, trace2x2)
{
  mat2x2i m{2, 3, -5, 1};
  EXPECT_EQ(3, trace(m));
}



TEST_F(test_matrix, trace3x3)
{
  // clang-format off
  mat3x3i m
  {
    2, 3, -5,
    1, -3, 4,
    7, 2, 9,
  };
  // clang-format on
  EXPECT_EQ(8, trace(m));
}



TEST_F(test_matrix, trace4x4)
{
  // clang-format off
  mat4x4i m
  {
    2, 3, -5, 2,
    1, -3, 4, 0,
    7, 2, 9, 7,
    2, -1, -3, -5,
  };
  // clang-format on
  EXPECT_EQ(3, trace(m));
}



TEST_F(test_matrix, norm_mat3x1f)
{
  mat3x1f m{3.f, 4.f, 12.f};
  EXPECT_FLOAT_EQ(169.f, square_norm(m));
  EXPECT_FLOAT_EQ(13.f, norm(m));
}



TEST_F(test_matrix, normalization_mat3x1f)
{
  mat3x1f m{3.f, 4.f, 12.f};

  mat3x1f mNorm = normalized(m);
  EXPECT_FLOAT_CLOSE(m / 13.f, mNorm);
  EXPECT_FLOAT_EQ(1.f, square_norm(mNorm));
  EXPECT_FLOAT_EQ(1.f, norm(mNorm));

  m.normalize();
  EXPECT_FLOAT_CLOSE(mNorm, m);
  EXPECT_FLOAT_EQ(1.f, square_norm(m));
  EXPECT_FLOAT_EQ(1.f, norm(m));
}



TEST_F(test_matrix, normalization_failure_null_norm)
{
  EXPECT_PRECOND_ERROR(normalized(mat3x1f::zero()));
}



TEST_F(test_matrix, identity)
{
  EXPECT_EQ(mat3x3i({1, 0, 0, 0, 1, 0, 0, 0, 1}), mat3x3i::identity());
}



TEST_F(test_matrix, zero)
{
  EXPECT_EQ(mat3x2i({0, 0, 0, 0, 0, 0}), mat3x2i::zero());
}



TEST_F(test_matrix, filled)
{
  EXPECT_EQ(mat3x2i({2, 2, 2, 2, 2, 2}), mat3x2i::filled(2));
}



TEST_F(test_matrix, diagonal)
{
  mat3x3i m_ref{1, 0, 0, 0, 2, 0, 0, 0, 3};
  EXPECT_EQ(m_ref, mat3x3i::diagonal(vec3i(1, 2, 3)));
  EXPECT_EQ(m_ref, mat3x3i::diagonal(1, 2, 3));
}



TEST_F(test_matrix, output_stream_operator)
{
  EXPECT_OUTPUT("(0)\n(1)", mat2x1i(0, 1));
  EXPECT_OUTPUT("(0, 1)\n(2, 3)\n(4, 5)", mat3x2i(0, 1, 2, 3, 4, 5));
}



TEST_F(test_matrix, is_signed)
{
  EXPECT_TRUE(std::is_signed<mat2x2i>::value);
  EXPECT_FALSE(std::is_signed<mat2x2u>::value);
  EXPECT_TRUE(std::is_signed<mat2x2f>::value);
  EXPECT_TRUE(std::is_signed<mat2x2d>::value);
}



TEST_F(test_matrix, is_same_signedness)
{
  using check_mat2x2i_mat2x1i = is_same_signedness<mat2x2i, mat2x1i>;
  using check_mat2x2i_mat2x2i = is_same_signedness<mat2x2i, mat2x2i>;
  using check_mat2x2i_mat2x2u = is_same_signedness<mat2x2i, mat2x2u>;
  using check_mat2x2i_mat2x2f = is_same_signedness<mat2x2i, mat2x2f>;
  using check_mat2x2i_mat2x2d = is_same_signedness<mat2x2i, mat2x2d>;

  using check_mat2x2u_mat2x1i = is_same_signedness<mat2x2u, mat2x1i>;
  using check_mat2x2u_mat2x2i = is_same_signedness<mat2x2u, mat2x2i>;
  using check_mat2x2u_mat2x2u = is_same_signedness<mat2x2u, mat2x2u>;
  using check_mat2x2u_mat2x2f = is_same_signedness<mat2x2u, mat2x2f>;
  using check_mat2x2u_mat2x2d = is_same_signedness<mat2x2u, mat2x2d>;

  using check_mat2x2f_mat2x1i = is_same_signedness<mat2x2f, mat2x1i>;
  using check_mat2x2f_mat2x2i = is_same_signedness<mat2x2f, mat2x2i>;
  using check_mat2x2f_mat2x2u = is_same_signedness<mat2x2f, mat2x2u>;
  using check_mat2x2f_mat2x2f = is_same_signedness<mat2x2f, mat2x2f>;
  using check_mat2x2f_mat2x2d = is_same_signedness<mat2x2f, mat2x2d>;

  using check_mat2x2d_mat2x1i = is_same_signedness<mat2x2d, mat2x1i>;
  using check_mat2x2d_mat2x2i = is_same_signedness<mat2x2d, mat2x2i>;
  using check_mat2x2d_mat2x2u = is_same_signedness<mat2x2d, mat2x2u>;
  using check_mat2x2d_mat2x2f = is_same_signedness<mat2x2d, mat2x2f>;
  using check_mat2x2d_mat2x2d = is_same_signedness<mat2x2d, mat2x2d>;

  EXPECT_TRUE(check_mat2x2i_mat2x1i::value);
  EXPECT_TRUE(check_mat2x2i_mat2x2i::value);
  EXPECT_FALSE(check_mat2x2i_mat2x2u::value);
  EXPECT_TRUE(check_mat2x2i_mat2x2f::value);
  EXPECT_TRUE(check_mat2x2i_mat2x2d::value);

  EXPECT_FALSE(check_mat2x2u_mat2x1i::value);
  EXPECT_FALSE(check_mat2x2u_mat2x2i::value);
  EXPECT_TRUE(check_mat2x2u_mat2x2u::value);
  EXPECT_FALSE(check_mat2x2u_mat2x2f::value);
  EXPECT_FALSE(check_mat2x2u_mat2x2d::value);

  EXPECT_TRUE(check_mat2x2f_mat2x1i::value);
  EXPECT_TRUE(check_mat2x2f_mat2x2i::value);
  EXPECT_FALSE(check_mat2x2f_mat2x2u::value);
  EXPECT_TRUE(check_mat2x2f_mat2x2f::value);
  EXPECT_TRUE(check_mat2x2f_mat2x2d::value);

  EXPECT_TRUE(check_mat2x2d_mat2x1i::value);
  EXPECT_TRUE(check_mat2x2d_mat2x2i::value);
  EXPECT_FALSE(check_mat2x2d_mat2x2u::value);
  EXPECT_TRUE(check_mat2x2d_mat2x2f::value);
  EXPECT_TRUE(check_mat2x2d_mat2x2d::value);
}



TEST_F(test_matrix, narrow_cast_int_to_uint)
{
  EXPECT_EQ(mat2x1u::zero(), narrow_cast<mat2x1u>(mat2x1i::zero()));
  EXPECT_EQ(mat2x1u(1u, 2u), narrow_cast<mat2x1u>(mat2x1i(1, 2)));
  EXPECT_EQ(mat2x1u(1u, static_cast<uint>(std::numeric_limits<int>::max())),
    narrow_cast<mat2x1u>(mat2x1i(1, std::numeric_limits<int>::max())));
}



TEST_F(test_matrix_death_test, narrow_cast_int_to_uint_failure)
{
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1i(0, -1)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1i(-1, 0)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1i(-1, -1)), narrowing_error);
}



TEST_F(test_matrix, narrow_cast_uint_to_int)
{
  EXPECT_EQ(mat2x1i::zero(), narrow_cast<mat2x1i>(mat2x1u::zero()));
  EXPECT_EQ(mat2x1i(1, 2), narrow_cast<mat2x1i>(mat2x1u(1u, 2u)));
  EXPECT_EQ(mat2x1i(1, std::numeric_limits<int>::max()),
    narrow_cast<mat2x1i>(
      mat2x1u(1u, static_cast<uint>(std::numeric_limits<int>::max()))));
}



TEST_F(test_matrix_death_test, narrow_cast_uint_to_int_failure)
{
  static constexpr uint of_val
    = static_cast<uint>(std::numeric_limits<int>::max()) + 1u;
  EXPECT_ERROR_0(narrow_cast<mat2x1i>(mat2x1u(0u, of_val)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1i>(mat2x1u(of_val, 0u)), narrowing_error);
  EXPECT_ERROR_0(
    narrow_cast<mat2x1i>(mat2x1u(of_val, of_val)), narrowing_error);
}



TEST_F(test_matrix, narrow_cast_int_to_float)
{
  EXPECT_FLOAT_CLOSE(mat2x1f::zero(), narrow_cast<mat2x1f>(mat2x1i::zero()));
  EXPECT_FLOAT_CLOSE(
    mat2x1f(-42.f, 88.f), narrow_cast<mat2x1f>(mat2x1i(-42, 88)));
}



TEST_F(test_matrix, narrow_cast_float_to_int)
{
  EXPECT_EQ(mat2x1i::zero(), narrow_cast<mat2x1i>(mat2x1f::zero()));
  EXPECT_EQ(mat2x1i(-42, 88), narrow_cast<mat2x1i>(mat2x1f(-42.f, 88.f)));
}



TEST_F(test_matrix_death_test, narrow_cast_float_to_int_failure)
{
  static constexpr float of_val = std::numeric_limits<float>::max();
  EXPECT_ERROR_0(narrow_cast<mat2x1i>(mat2x1f(0.f, of_val)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1i>(mat2x1f(of_val, 0.f)), narrowing_error);
  EXPECT_ERROR_0(
    narrow_cast<mat2x1i>(mat2x1f(of_val, of_val)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1i>(mat2x1f(0.f, 2.5f)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1i>(mat2x1f(2.5f, 0.f)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1i>(mat2x1f(2.5f, 2.5f)), narrowing_error);
}



TEST_F(test_matrix, narrow_cast_float_to_uint)
{
  EXPECT_EQ(mat2x1u::zero(), narrow_cast<mat2x1u>(mat2x1f::zero()));
  EXPECT_EQ(mat2x1u(42u, 88u), narrow_cast<mat2x1u>(mat2x1f(42.f, 88.f)));
}



TEST_F(test_matrix_death_test, narrow_cast_float_to_uint_failure)
{
  static constexpr float of_val = std::numeric_limits<float>::max();
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1f(0.f, of_val)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1f(of_val, 0.f)), narrowing_error);
  EXPECT_ERROR_0(
    narrow_cast<mat2x1u>(mat2x1f(of_val, of_val)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1f(0.f, 2.5f)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1f(2.5f, 0.f)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1f(2.5f, 2.5f)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1f(0.f, -1.f)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1f(-0.1f, 0.f)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<mat2x1u>(mat2x1f(-0.1f, -1.f)), narrowing_error);
}
