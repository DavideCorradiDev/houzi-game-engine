// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/mth/Matrix.hpp"

#include "hou/cor/cor_error.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestMatrix : public Test {};
class TestMatrixDeathTest : public TestMatrix {};

}



TEST_F(TestMatrix, DefaultConstructor)
{
  Mat3x2i m;
  EXPECT_EQ(0, m(0));
  EXPECT_EQ(0, m(1));
  EXPECT_EQ(0, m(2));
  EXPECT_EQ(0, m(3));
  EXPECT_EQ(0, m(4));
  EXPECT_EQ(0, m(5));
}



TEST_F(TestMatrix, InitializerListConstructor)
{
  Mat3x2i mi = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(1, mi(0));
  EXPECT_EQ(2, mi(1));
  EXPECT_EQ(3, mi(2));
  EXPECT_EQ(4, mi(3));
  EXPECT_EQ(5, mi(4));
  EXPECT_EQ(6, mi(5));

  Mat3x2f mf = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
  EXPECT_FLOAT_EQ(1.f, mf(0));
  EXPECT_FLOAT_EQ(2.f, mf(1));
  EXPECT_FLOAT_EQ(3.f, mf(2));
  EXPECT_FLOAT_EQ(4.f, mf(3));
  EXPECT_FLOAT_EQ(5.f, mf(4));
  EXPECT_FLOAT_EQ(6.f, mf(5));
}



TEST_F(TestMatrixDeathTest, InitializerListConstructorWrongSize)
{
  HOU_EXPECT_ERROR(Mat3x2i({1, 2, 3}), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(Mat3x2i({1, 2, 3, 4, 5, 6, 7}), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestMatrix, ElementConstructor)
{
  Mat3x2i mi(1, 2, 3, 4, 5, 6);
  EXPECT_EQ(1, mi(0));
  EXPECT_EQ(2, mi(1));
  EXPECT_EQ(3, mi(2));
  EXPECT_EQ(4, mi(3));
  EXPECT_EQ(5, mi(4));
  EXPECT_EQ(6, mi(5));
}



TEST_F(TestMatrix, ConversionConstructor)
{
  Mat3x2f mf = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
  Mat3x2i mi = mf;
  EXPECT_EQ(1, mi(0));
  EXPECT_EQ(2, mi(1));
  EXPECT_EQ(3, mi(2));
  EXPECT_EQ(4, mi(3));
  EXPECT_EQ(5, mi(4));
  EXPECT_EQ(6, mi(5));
}



TEST_F(TestMatrix, SizeOperators)
{
  Mat3x2i m;

  EXPECT_EQ(3u, m.getRowsCount());
  EXPECT_EQ(6u, m.getSize());
  EXPECT_EQ(2u, m.getColumnsCount());

  EXPECT_EQ(3u, Mat3x2i::getRowsCount());
  EXPECT_EQ(6u, Mat3x2i::getSize());
  EXPECT_EQ(2u, Mat3x2i::getColumnsCount());
}



TEST_F(TestMatrix, ElementAccessOperators)
{
  Mat3x2i m;

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

  EXPECT_EQ(1, m(0,0));
  EXPECT_EQ(2, m(0,1));
  EXPECT_EQ(3, m(1,0));
  EXPECT_EQ(4, m(1,1));
  EXPECT_EQ(5, m(2,0));
  EXPECT_EQ(6, m(2,1));

  m(0,0) = 7;
  m(0,1) = 8;
  m(1,0) = 9;
  m(1,1) = 10;
  m(2,0) = 11;
  m(2,1) = 12;

  EXPECT_EQ(7, m(0));
  EXPECT_EQ(8, m(1));
  EXPECT_EQ(9, m(2));
  EXPECT_EQ(10, m(3));
  EXPECT_EQ(11, m(4));
  EXPECT_EQ(12, m(5));
}



TEST_F(TestMatrixDeathTest, ElementAccessOutOfBounds)
{
  Mat3x2i m;
  HOU_EXPECT_ERROR(m(3,1), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(m(2,2), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(m(3,2), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(m(7), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestMatrix, ElementAccessX)
{
  Mat1x1i m1{1};
  Mat2x1i m2{1, 2};
  Mat3x1i m3{1, 2, 3};
  Mat4x1i m4{1, 2, 3, 4};

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



TEST_F(TestMatrix, ElementAccessY)
{
  Mat2x1i m2{1, 2};
  Mat3x1i m3{1, 2, 3};
  Mat4x1i m4{1, 2, 3, 4};

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



TEST_F(TestMatrix, ElementAccessZ)
{
  Mat3x1i m3{1, 2, 3};
  Mat4x1i m4{1, 2, 3, 4};

  EXPECT_EQ(3, m3.z());
  EXPECT_EQ(3, m4.z());

  m3.z() = 5;
  EXPECT_EQ(5, m3.z());

  m4.z() = 5;
  EXPECT_EQ(5, m4.z());
}



TEST_F(TestMatrix, ElementAccessW)
{
  Mat4x1i m4{1, 2, 3, 4};

  EXPECT_EQ(4, m4.w());

  m4.w() = 5;
  EXPECT_EQ(5, m4.w());
}



TEST_F(TestMatrix, Data)
{
  Mat3x2i m = {1, 2, 3, 4, 5, 6};
  int dataRef[] = {1, 2, 3, 4, 5, 6};
  HOU_EXPECT_ARRAY_EQ(dataRef, m.data(), m.getSize());

}



TEST_F(TestMatrix, Set)
{
  Mat3x2i m = {1, 2, 3, 4, 5, 6};
  m.set(7, 8, 9, 10, -1, -2);
  Mat3x2i mRef = {7, 8, 9, 10, -1, -2};
  EXPECT_EQ(mRef, m);
}



TEST_F(TestMatrix, Fill)
{
  Mat3x2i m = {1, 2, 3, 4, 5, 6};
  m.fill(1);
  Mat3x2i mRef = {1, 1, 1, 1, 1, 1};
  EXPECT_EQ(mRef, m);
}



TEST_F(TestMatrix, ComparisonOperators)
{
  Mat3x2i m1 = {0, 1, 2, 3, 4, 5};
  Mat3x2i m2 = {6, 7, 8, 9, 10, 11};
  Mat3x2i m3 = m1;

  EXPECT_FALSE(m1 == m2);
  EXPECT_TRUE(m1 != m2);
  EXPECT_TRUE(m1 == m3);
  EXPECT_FALSE(m1 != m3);
}



TEST_F(TestMatrix, FloatingPointComparison)
{
  Mat3x2f m1 = {0.f, 1.f, 2.3456f, 3.f, 4.f, 5.f};
  Mat3x2f m2 = m1;
  Mat3x2f m3 = {0.f, 1.f, 2.3458f, 3.f, 4.f, 5.f};

  EXPECT_TRUE(close(m1, m2));
  EXPECT_TRUE(close(m1, m3, 1e-3f));
  EXPECT_FALSE(close(m1, m3, 1e-4f));
}



TEST_F(TestMatrix, Addition)
{
  Mat3x2i m1 = {0, 1, 2, 3, 4, 5};
  Mat3x2i m2 = {6, 7, 8, -5, 10, 0};
  Mat3x2i mSum = m1 + m2;
  Mat3x2i mSumIncremental = m1;
  mSumIncremental += m2;
  Mat3x2i mSumRef = {6, 8, 10, -2, 14, 5};

  EXPECT_EQ(mSumRef, mSum);
  EXPECT_EQ(mSumRef, mSumIncremental);
}



TEST_F(TestMatrix, Subtraction)
{
  Mat3x2i m1 = {0, 1, 2, 3, 4, 5};
  Mat3x2i m2 = {6, 7, 1, -5, 10, 0};
  Mat3x2i mDiff = m1 - m2;
  Mat3x2i mDiffIncremental = m1;
  mDiffIncremental -= m2;
  Mat3x2i mDiffRef = {-6, -6, 1, 8, -6, 5};

  EXPECT_EQ(mDiffRef, mDiff);
  EXPECT_EQ(mDiffRef, mDiffIncremental);
}



TEST_F(TestMatrix, Opposite)
{
  Mat3x2i m = {1, -2, 3, -4, 5, -6};
  Mat3x2i mOpp = -m;
  Mat3x2i mOppRef = {-1, 2, -3, 4, -5, 6};

  EXPECT_EQ(mOppRef, mOpp);
}



TEST_F(TestMatrix, ScalarMultiplication)
{
  Mat3x2i m = {0, 1, 2, 3, -4, 5};
  int factor = 3;
  Mat3x2i mMultLeft = factor * m;
  Mat3x2i mMultRight = m * factor;
  Mat3x2i mMultIncremental = m;
  mMultIncremental *= factor;
  Mat3x2i mMultRef = {0, 3, 6, 9, -12, 15};

  EXPECT_EQ(mMultRef, mMultLeft);
  EXPECT_EQ(mMultRef, mMultRight);
  EXPECT_EQ(mMultRef, mMultIncremental);
}



TEST_F(TestMatrix, MixedScalarMultiplication)
{
  Mat3x2f m = {0, 1, 2, 3, -4, 5};
  int factor = 3;
  Mat3x2f mMultLeft = factor * m;
  Mat3x2f mMultRight = m * factor;
  Mat3x2f mMultIncremental = m;
  mMultIncremental *= factor;
  Mat3x2f mMultRef = {0, 3, 6, 9, -12, 15};

  EXPECT_EQ(mMultRef, mMultLeft);
  EXPECT_EQ(mMultRef, mMultRight);
  EXPECT_EQ(mMultRef, mMultIncremental);
}



TEST_F(TestMatrix, Multiplication)
{
  Mat3x2i m1 = {0, 1, 2, 3, -4, 5};
  Mat2x1i m2 = {-4, 7};
  Mat3x1i res = m1 * m2;
  Mat3x1i resRef = {7, 13, 51};

  EXPECT_EQ(resRef, res);
}



TEST_F(TestMatrix, ScalarDivision)
{
  Mat3x2i m = {0, 2, -4, 6, 8, 10};
  int divisor = 2;
  Mat3x2i mDiv = m / divisor;
  Mat3x2i mDivIncremental = m;
  mDivIncremental /= divisor;
  Mat3x2i mDivRef = {0, 1, -2, 3, 4, 5};

  EXPECT_EQ(mDivRef, mDiv);
  EXPECT_EQ(mDivRef, mDivIncremental);
}



TEST_F(TestMatrix, MixedScalarDivision)
{
  Mat3x2f m = {0, 2, -4, 6, 8, 10};
  int divisor = 2;
  Mat3x2f mDiv = m / divisor;
  Mat3x2f mDivIncremental = m;
  mDivIncremental /= divisor;
  Mat3x2f mDivRef = {0, 1, -2, 3, 4, 5};

  EXPECT_EQ(mDivRef, mDiv);
  EXPECT_EQ(mDivRef, mDivIncremental);
}



TEST_F(TestMatrix, Reduce3x2)
{
  Mat3x2i m =
  {
    1, 2,
    3, 4,
    5, 6
  };
  {
    Mat2x1i mReducedRef =
    {
      4,
      6
    };
    EXPECT_EQ(mReducedRef, reduce(m, 0, 0));
  }
  {
    Mat2x1i mReducedRef =
    {
      3,
      5
    };
    EXPECT_EQ(mReducedRef, reduce(m, 0, 1));
  }
  {
    Mat2x1i mReducedRef =
    {
      2,
      6
    };
    EXPECT_EQ(mReducedRef, reduce(m, 1, 0));
  }
  {
    Mat2x1i mReducedRef =
    {
      1,
      5
    };
    EXPECT_EQ(mReducedRef, reduce(m, 1, 1));
  }
  {
    Mat2x1i mReducedRef =
    {
      2,
      4
    };
    EXPECT_EQ(mReducedRef, reduce(m, 2, 0));
  }
  {
    Mat2x1i mReducedRef =
    {
      1,
      3
    };
    EXPECT_EQ(mReducedRef, reduce(m, 2, 1));
  }
}



TEST_F(TestMatrix, Reduce3x3)
{
  Mat3x3i m =
  {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  };
  {
    Mat2x2i mReducedRef =
    {
      5, 6,
      8, 9
    };
    EXPECT_EQ(mReducedRef, reduce(m, 0, 0));
  }
  {
    Mat2x2i mReducedRef =
    {
      4, 6,
      7, 9
    };
    EXPECT_EQ(mReducedRef, reduce(m, 0, 1));
  }
  {
    Mat2x2i mReducedRef =
    {
      4, 5,
      7, 8
    };
    EXPECT_EQ(mReducedRef, reduce(m, 0, 2));
  }
  {
    Mat2x2i mReducedRef =
    {
      2, 3,
      8, 9
    };
    EXPECT_EQ(mReducedRef, reduce(m, 1, 0));
  }
  {
    Mat2x2i mReducedRef =
    {
      1, 3,
      7, 9
    };
    EXPECT_EQ(mReducedRef, reduce(m, 1, 1));
  }
  {
    Mat2x2i mReducedRef =
    {
      1, 2,
      7, 8
    };
    EXPECT_EQ(mReducedRef, reduce(m, 1, 2));
  }
  {
    Mat2x2i mReducedRef =
    {
      2, 3,
      5, 6
    };
    EXPECT_EQ(mReducedRef, reduce(m, 2, 0));
  }
  {
    Mat2x2i mReducedRef =
    {
      1, 3,
      4, 6
    };
    EXPECT_EQ(mReducedRef, reduce(m, 2, 1));
  }
  {
    Mat2x2i mReducedRef =
    {
      1, 2,
      4, 5
    };
    EXPECT_EQ(mReducedRef, reduce(m, 2, 2));
  }
}



TEST_F(TestMatrix, Transpose)
{
  Mat3x2i m = {1, 2, 3, 4, 5, 6};
  Mat2x3i mTranspose = transpose(m);
  Mat2x3i mTransposeRef = {1, 3, 5, 2, 4, 6};
  EXPECT_EQ(mTransposeRef, mTranspose);
}



TEST_F(TestMatrix, Adjugate1x1)
{
  Mat1x1i m = {2};
  EXPECT_EQ(Mat1x1i::identity(), adjugate(m));
  m.adjugate();
  EXPECT_EQ(Mat1x1i::identity(), m);
}



TEST_F(TestMatrix, Adjugate2x2)
{
  Mat2x2i m = {1, 2, 3, 4};
  Mat2x2i mAdjugateRef = {4, -2, -3, 1};
  EXPECT_EQ(mAdjugateRef, adjugate(m));
  m.adjugate();
  EXPECT_EQ(mAdjugateRef, m);
}



TEST_F(TestMatrix, Adjugate3x3)
{
  Mat3x3i m =
  {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  };
  Mat3x3i mAdjugateRef =
  {
    -3, 6, -3,
    6, -12, 6,
    -3, 6, -3
  };
  EXPECT_EQ(mAdjugateRef, adjugate(m));
  m.adjugate();
  EXPECT_EQ(mAdjugateRef, m);
}



TEST_F(TestMatrix, Inverse1x1)
{
  Mat1x1f m = {2.f};
  Mat1x1f mInv = inverse(m);
  Mat1x1f mInvRef = {0.5f};
  HOU_EXPECT_FLOAT_CLOSE(mInvRef, mInv);
  HOU_EXPECT_FLOAT_CLOSE(Mat1x1f::identity(), m * mInv);
  m.invert();
  HOU_EXPECT_FLOAT_CLOSE(mInvRef, mInv);
}



TEST_F(TestMatrix, Inverse2x2)
{
  Mat2x2f m = {1.f, 2.f, 3.f, 4.f};
  Mat2x2f mInv = inverse(m);
  Mat2x2f mInvRef = {-2.f, 1.f, 1.5f, -0.5f};
  HOU_EXPECT_FLOAT_CLOSE(mInvRef, mInv);
  HOU_EXPECT_FLOAT_CLOSE(Mat2x2f::identity(), m * mInv);
  m.invert();
  HOU_EXPECT_FLOAT_CLOSE(mInvRef, mInv);
}



TEST_F(TestMatrix, Inverse3x3)
{
  Mat3x3f m =
  {
    1.f, 2.f, 3.f,
    3.f, 2.f, 1.f,
    1.f, 3.f, 2.f
  };
  Mat3x3f mInv = inverse(m);
  Mat3x3f mInvRef =
  {
    1.f / 12.f, 5.f / 12.f, -1.f / 3.f,
    -5.f / 12.f, -1.f / 12.f, 2.f / 3.f,
    7.f / 12.f, -1.f / 12.f, -1.f / 3.f
  };
  HOU_EXPECT_FLOAT_CLOSE(mInvRef, mInv);
  HOU_EXPECT_FLOAT_CLOSE(Mat3x3f::identity(), m * mInv);
  m.invert();
  HOU_EXPECT_FLOAT_CLOSE(mInvRef, mInv);
}



TEST_F(TestMatrixDeathTest, InverseFailureNullDeterminant)
{
  Mat2x2f m = Mat2x2f::zero();
  HOU_EXPECT_ERROR(inverse(m), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestMatrix, Determinant1x1)
{
  EXPECT_EQ(1, det(Mat1x1i{1}));
  EXPECT_FLOAT_EQ(-3.f, det(Mat1x1f{-3.f}));
}



TEST_F(TestMatrix, Determinant2x2)
{
  EXPECT_EQ(-6, det(Mat2x2i{0, 2, 3, 9}));
  EXPECT_FLOAT_EQ(-11.f, det(Mat2x2f{-1.f, 2.f, 3.f, 5.f}));
}



TEST_F(TestMatrix, Determinant3x3)
{
  EXPECT_EQ(381, det(Mat3x3i{0, 2, 3, 9, -1, -4, 3, 10, -7}));
  EXPECT_FLOAT_EQ(66.f, det(Mat3x3f{-1.f, 2.f, 3.f, 5.f, -4.f, 5.f, -2., 7.f, 5.f}));
}



TEST_F(TestMatrix, Determinant4x4)
{
  Mat4x4i mi =
  {
    0, -1, 4, -7,
    2, 3, 4, 5,
    -2, -3, 13, 10,
    16, -1, 0, 4
  };
  EXPECT_EQ(8686, det(mi));

  Mat4x4f mf =
  {
    -1.5f, 0.5f, 5.f, -8.f,
    3.f, 2.f, 7.f, 0.f,
    15.f, -5.f, 7.f, 9.f,
    1.f, 3.f, -2.f, -4.5f
  };
  EXPECT_FLOAT_EQ(3571.25f, det(mf));
}



TEST_F(TestMatrix, Trace1x1)
{
  Mat1x1i m{2};
  EXPECT_EQ(2, trace(m));
}



TEST_F(TestMatrix, Trace2x2)
{
  Mat2x2i m{2, 3, -5, 1};
  EXPECT_EQ(3, trace(m));
}



TEST_F(TestMatrix, Trace3x3)
{
  Mat3x3i m
  {
    2, 3, -5,
    1, -3, 4,
    7, 2, 9,
  };
  EXPECT_EQ(8, trace(m));
}



TEST_F(TestMatrix, Trace4x4)
{
  Mat4x4i m
  {
    2, 3, -5, 2,
    1, -3, 4, 0,
    7, 2, 9, 7,
    2, -1, -3, -5,
  };
  EXPECT_EQ(3, trace(m));
}



TEST_F(TestMatrix, NormMat3x1f)
{
  Mat3x1f m{3.f, 4.f, 12.f};
  EXPECT_FLOAT_EQ(169.f, squareNorm(m));
  EXPECT_FLOAT_EQ(13.f, norm(m));
}



TEST_F(TestMatrix, NormalizationMat3x1f)
{
  Mat3x1f m{3.f, 4.f, 12.f};

  Mat3x1f mNorm = normalized(m);
  HOU_EXPECT_FLOAT_CLOSE(m / 13.f, mNorm);
  EXPECT_FLOAT_EQ(1.f, squareNorm(mNorm));
  EXPECT_FLOAT_EQ(1.f, norm(mNorm));

  m.normalize();
  HOU_EXPECT_FLOAT_CLOSE(mNorm, m);
  EXPECT_FLOAT_EQ(1.f, squareNorm(m));
  EXPECT_FLOAT_EQ(1.f, norm(m));
}



TEST_F(TestMatrix, NormalizationFailureNullNorm)
{
  HOU_EXPECT_ERROR(normalized(Mat3x1f::zero()), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestMatrix, Identity)
{
  EXPECT_EQ(Mat3x3i({1, 0, 0, 0, 1, 0, 0, 0, 1}), Mat3x3i::identity());
}



TEST_F(TestMatrix, Zero)
{
  EXPECT_EQ(Mat3x2i({0, 0, 0, 0, 0, 0}), Mat3x2i::zero());
}



TEST_F(TestMatrix, Filled)
{
  EXPECT_EQ(Mat3x2i({2, 2, 2, 2, 2, 2}), Mat3x2i::filled(2));
}



TEST_F(TestMatrix, Diagonal)
{
  Mat3x3i mRef{1, 0, 0, 0, 2, 0, 0, 0, 3};
  EXPECT_EQ(mRef, Mat3x3i::diagonal(Vec3i(1, 2, 3)));
  EXPECT_EQ(mRef, Mat3x3i::diagonal(1, 2, 3));
}



TEST_F(TestMatrix, OutputStreamOperator)
{
  HOU_EXPECT_OUTPUT("(0)\n(1)", Mat2x1i(0, 1));
  HOU_EXPECT_OUTPUT("(0, 1)\n(2, 3)\n(4, 5)", Mat3x2i(0, 1, 2, 3, 4, 5));
}

