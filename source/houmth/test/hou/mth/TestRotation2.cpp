#include "hou/Test.hpp"

#include "hou/cor/cor_error.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/math_functions.hpp"
#include "hou/mth/rotation2.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestRotation2 : public Test {};
class TestRotation2DeathTest : public TestRotation2{};

}



TEST_F(TestRotation2, DefaultConstructor)
{
  rot2f r;
  HOU_EXPECT_FLOAT_CLOSE(0.f, r.get_angle());
  HOU_EXPECT_FLOAT_CLOSE(Mat2x2f::identity(), r.get_matrix());
}



TEST_F(TestRotation2, ConstructorAngle)
{
  float angleRef = pi_f / 2.f;
  Mat2x2f mRef(0.f, -1.f, 1.f, 0.f);
  rot2f r(angleRef);
  HOU_EXPECT_FLOAT_CLOSE(angleRef, r.get_angle());
  HOU_EXPECT_FLOAT_CLOSE(mRef, r.get_matrix());
}



TEST_F(TestRotation2, ConstructorAngleOverflow)
{
  float angleRef = -pi_f / 2.f;
  Mat2x2f mRef(0.f, 1.f, -1.f, 0.f);
  rot2f r(3.f * pi_f / 2.f);
  HOU_EXPECT_CLOSE(angleRef, r.get_angle(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.get_matrix(), 1.e-6f);
}



TEST_F(TestRotation2, ConstructorAngleUnderflow)
{
  float angleRef = pi_f / 2.f;
  Mat2x2f mRef(0.f, -1.f, 1.f, 0.f);
  rot2f r(-3.f * pi_f / 2.f);
  HOU_EXPECT_CLOSE(angleRef, r.get_angle(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.get_matrix(), 1.e-6f);
}



TEST_F(TestRotation2, ConstructorMatrix)
{
  float angleRef = pi_f / 2.f;
  Mat2x2f mRef(0.f, -1.f, 1.f, 0.f);
  rot2f r(mRef);
  HOU_EXPECT_FLOAT_CLOSE(angleRef, r.get_angle());
  HOU_EXPECT_FLOAT_CLOSE(mRef, r.get_matrix());
}



TEST_F(TestRotation2DeathTest, ConstructorMatrixFailureInvalidMatrix)
{
  HOU_EXPECT_ERROR(rot2f(Mat2x2f::zero()), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestRotation2, ConversionConstructor)
{
  rot2d rd;
  rot2f rf;
  HOU_EXPECT_FLOAT_CLOSE(0.f, rf.get_angle());
  HOU_EXPECT_FLOAT_CLOSE(Mat2x2f::identity(), rf.get_matrix());
}



TEST_F(TestRotation2, ComparisonOperators)
{
  rot2f r1(pi_f / 6.f);
  rot2f r2(r1);
  rot2f r3(-pi_f / 3.f);

  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 == r3);
  EXPECT_FALSE(r1 != r2);
  EXPECT_TRUE(r1 != r3);
}



TEST_F(TestRotation2, FloatingPointComparison)
{
  rot2f r1(0.23456f);
  rot2f r2(r1);
  rot2f r3(0.234561f);
  rot2f r4(0.23556f);

  EXPECT_TRUE(close(r1, r2));
  EXPECT_FALSE(close(r1, r3));
  EXPECT_FALSE(close(r1, r4));
  EXPECT_TRUE(close(r1, r2, 1.e-5f));
  EXPECT_TRUE(close(r1, r3, 1.e-5f));
  EXPECT_FALSE(close(r1, r4, 1.e-5f));
  EXPECT_TRUE(close(r1, r2, 1.e-2f));
  EXPECT_TRUE(close(r1, r3, 1.e-2f));
  EXPECT_TRUE(close(r1, r4, 1.e-2f));
}



TEST_F(TestRotation2, Multiplication)
{
  rot2f r1(pi_f / 4.f);
  rot2f r2(pi_f);
  rot2f rRef(-3.f * pi_f / 4.f);
  HOU_EXPECT_FLOAT_CLOSE(rRef, r1 * r2);
  r1 *= r2;
  HOU_EXPECT_FLOAT_CLOSE(rRef, r1);
}



TEST_F(TestRotation2, Inversion)
{
  rot2f r(pi_f / 4.f);
  rot2f rInvRef(-pi_f / 4.f);
  rot2f rInv = inverse(r);
  HOU_EXPECT_FLOAT_CLOSE(rInvRef, rInv);
  HOU_EXPECT_FLOAT_CLOSE(rot2f::identity(), rInv * r);
  r.invert();
  HOU_EXPECT_FLOAT_CLOSE(rInvRef, r);
}



TEST_F(TestRotation2, OutputStreamOperator)
{
  rot2f r(0.5f);
  HOU_EXPECT_OUTPUT("0.5", r);
}

