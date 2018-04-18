#include "hou/Test.hpp"

#include "hou/cor/CorError.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/MathFunctions.hpp"
#include "hou/mth/Rotation2.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestRotation2 : public Test {};
class TestRotation2DeathTest : public TestRotation2{};

}



TEST_F(TestRotation2, DefaultConstructor)
{
  Rot2f r;
  HOU_EXPECT_FLOAT_CLOSE(0.f, r.getAngle());
  HOU_EXPECT_FLOAT_CLOSE(Mat2x2f::identity(), r.getMatrix());
}



TEST_F(TestRotation2, ConstructorAngle)
{
  float angleRef = PI_F / 2.f;
  Mat2x2f mRef(0.f, -1.f, 1.f, 0.f);
  Rot2f r(angleRef);
  HOU_EXPECT_FLOAT_CLOSE(angleRef, r.getAngle());
  HOU_EXPECT_FLOAT_CLOSE(mRef, r.getMatrix());
}



TEST_F(TestRotation2, ConstructorAngleOverflow)
{
  float angleRef = -PI_F / 2.f;
  Mat2x2f mRef(0.f, 1.f, -1.f, 0.f);
  Rot2f r(3.f * PI_F / 2.f);
  HOU_EXPECT_CLOSE(angleRef, r.getAngle(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.getMatrix(), 1.e-6f);
}



TEST_F(TestRotation2, ConstructorAngleUnderflow)
{
  float angleRef = PI_F / 2.f;
  Mat2x2f mRef(0.f, -1.f, 1.f, 0.f);
  Rot2f r(-3.f * PI_F / 2.f);
  HOU_EXPECT_CLOSE(angleRef, r.getAngle(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.getMatrix(), 1.e-6f);
}



TEST_F(TestRotation2, ConstructorMatrix)
{
  float angleRef = PI_F / 2.f;
  Mat2x2f mRef(0.f, -1.f, 1.f, 0.f);
  Rot2f r(mRef);
  HOU_EXPECT_FLOAT_CLOSE(angleRef, r.getAngle());
  HOU_EXPECT_FLOAT_CLOSE(mRef, r.getMatrix());
}



TEST_F(TestRotation2DeathTest, ConstructorMatrixFailureInvalidMatrix)
{
  HOU_EXPECT_ERROR(Rot2f(Mat2x2f::zero()), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestRotation2, ConversionConstructor)
{
  Rot2d rd;
  Rot2f rf;
  HOU_EXPECT_FLOAT_CLOSE(0.f, rf.getAngle());
  HOU_EXPECT_FLOAT_CLOSE(Mat2x2f::identity(), rf.getMatrix());
}



TEST_F(TestRotation2, ComparisonOperators)
{
  Rot2f r1(PI_F / 6.f);
  Rot2f r2(r1);
  Rot2f r3(-PI_F / 3.f);

  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 == r3);
  EXPECT_FALSE(r1 != r2);
  EXPECT_TRUE(r1 != r3);
}



TEST_F(TestRotation2, FloatingPointComparison)
{
  Rot2f r1(0.23456f);
  Rot2f r2(r1);
  Rot2f r3(0.234561f);
  Rot2f r4(0.23556f);

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
  Rot2f r1(PI_F / 4.f);
  Rot2f r2(PI_F);
  Rot2f rRef(-3.f * PI_F / 4.f);
  HOU_EXPECT_FLOAT_CLOSE(rRef, r1 * r2);
  r1 *= r2;
  HOU_EXPECT_FLOAT_CLOSE(rRef, r1);
}



TEST_F(TestRotation2, Inversion)
{
  Rot2f r(PI_F / 4.f);
  Rot2f rInvRef(-PI_F / 4.f);
  Rot2f rInv = inverse(r);
  HOU_EXPECT_FLOAT_CLOSE(rInvRef, rInv);
  HOU_EXPECT_FLOAT_CLOSE(Rot2f::identity(), rInv * r);
  r.invert();
  HOU_EXPECT_FLOAT_CLOSE(rInvRef, r);
}



TEST_F(TestRotation2, OutputStreamOperator)
{
  Rot2f r(0.5f);
  HOU_EXPECT_OUTPUT("0.5", r);
}

