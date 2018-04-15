// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/mth/Rotation3.hpp"
#include "hou/mth/Matrix.hpp"
#include "hou/mth/MthUtils.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestRotation3 : public Test {};

class TestRotation3Paramf
  : public TestRotation3
  , public WithParamInterface<float> {};

class TestRotation3DeathTest : public TestRotation3 {};

}



TEST_F(TestRotation3, DefaultConstructor)
{
  Rot3f r;
  HOU_EXPECT_FLOAT_CLOSE(Quatf::identity(), r.getQuaternion());
  HOU_EXPECT_FLOAT_CLOSE(Vec3f::zero(), r.getVector());
  HOU_EXPECT_FLOAT_CLOSE(Mat3x3f::identity(), r.getMatrix());
}



TEST_F(TestRotation3, ConstructorQuaternion)
{
  Quatf quatRef(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  Vec3f vecRef(0.4275166f, -0.4275166f, 0.8550332f);
  Mat3x3f matRef
    ( 0.5833333f, -0.7904401f, -0.1868867f
    , 0.6237735f, 0.5833333f, -0.52022f
    , 0.52022f, 0.1868867f, 0.8333333f);

  Rot3f rQuat(quatRef);
  HOU_EXPECT_CLOSE(quatRef, rQuat.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rQuat.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rQuat.getMatrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorNonUnitQuaternion)
{
  Quatf quat(2.f, 4.f, 5.f, -6.f);
  EXPECT_FLOAT_EQ(9.f, norm(quat));

  Rot3f r(quat);
  HOU_EXPECT_FLOAT_CLOSE(normalized(quat), r.getQuaternion());
}



TEST_F(TestRotation3DeathTest, ConstructorFailureZeroQuaternion)
{
  HOU_EXPECT_ERROR(Rot3f(Quatf::zero()), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestRotation3, ConstructorVector)
{
  Quatf quatRef(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  Vec3f vecRef(0.4275166f, -0.4275166f, 0.8550332f);
  Mat3x3f matRef
    ( 0.5833333f, -0.7904401f, -0.1868867f
    , 0.6237735f, 0.5833333f, -0.52022f
    , 0.52022f, 0.1868867f, 0.8333333f);

  Rot3f rVec(vecRef);
  HOU_EXPECT_CLOSE(quatRef, rVec.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rVec.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rVec.getMatrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorMatrix)
{
  Quatf quatRef(0.f, 0.f, -0.7071068f, 0.7071068f);
  Vec3f vecRef(0.f, 0.f, -1.5707963f);
  Mat3x3f matRef(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f);

  Rot3f rMat(matRef);
  HOU_EXPECT_CLOSE(quatRef, rMat.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.getMatrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorMatrixNullRootFunction)
{
  Quatf quatRef(0.f, 1.f, 0.f, 0.f);
  Vec3f vecRef(0.f, PI_F, 0.f);
  Mat3x3f matRef(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f);

  Rot3f rMat(matRef);
  HOU_EXPECT_CLOSE(quatRef, rMat.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.getMatrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorMatrixSmallRootFunction)
{
  Quatf quatRef(0.707107f, 0.707107f, 0.f, 0.f);
  Vec3f vecRef(2.2214417f, 2.2214417f, 0.f);
  Mat3x3f matRef(0.f, 1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f);

  Rot3f rMat(matRef);
  HOU_EXPECT_CLOSE(quatRef, rMat.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.getMatrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorMatrixLowPrecision)
{
  Rot3f rotRef = Rot3f::x(PI_F / 3.f) * Rot3f::z(PI_F / 4.f) * Rot3f::y(PI_F / 2.f);
  Rot3f rot(rotRef.getMatrix());
  HOU_EXPECT_FLOAT_CLOSE(rotRef, rot);
}



TEST_F(TestRotation3, ConstructorNonRotationMatrix)
{
  Quatf quatRef(0.119523f, -0.239046f, 0.119523f, 0.956183f);
  Vec3f vecRef(0.2426f, -0.485199f, 0.2426f);
  Mat3x3f matRef
  {
    0.857143f, -0.285714f, -0.428571f,
    0.171429f, 0.942857f, -0.285714f,
    0.485714f, 0.171429f, 0.857143f,
  };

  Rot3f rMat(Mat3x3f{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f});
  HOU_EXPECT_CLOSE(quatRef, rMat.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.getMatrix(), 1.e-6f);

  HOU_EXPECT_CLOSE(1.f, norm(rMat.getQuaternion()), 1.e-6f);
  HOU_EXPECT_CLOSE(Mat3x3f::identity(), rMat.getMatrix()
    * transpose(rMat.getMatrix()), 1.e-6f);
  HOU_EXPECT_CLOSE(1.f, det(rMat.getMatrix()), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorZeroMatrix)
{
  Quatf quatRef(0.f, 0.f, 1.f, 0.f);
  Vec3f vecRef(0.f, 0.f, PI_F);
  Mat3x3f matRef(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f);

  Rot3f rMat(Mat3x3f::zero());
  HOU_EXPECT_CLOSE(quatRef, rMat.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.getMatrix(), 1.e-6f);

  HOU_EXPECT_CLOSE(1.f, norm(rMat.getQuaternion()), 1.e-6f);
  HOU_EXPECT_CLOSE(Mat3x3f::identity(), rMat.getMatrix()
    * transpose(rMat.getMatrix()), 1.e-6f);
  HOU_EXPECT_CLOSE(1.f, det(rMat.getMatrix()), 1.e-6f);
}



TEST_F(TestRotation3, ConversionConstructor)
{
  Quatd qd(1., 2., 3., 4.);
  Rot3d rd(qd);
  Quatf qfRef(rd.getQuaternion());
  Rot3f rf(rd);

  HOU_EXPECT_FLOAT_CLOSE(qfRef, rf.getQuaternion());
}



TEST_F(TestRotation3, ComparisonOperators)
{
  Quatf q1(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  Quatf q2(q1);
  Quatf q3(Quatf::identity());

  Rot3f r1(q1);
  Rot3f r2(q2);
  Rot3f r3(q3);

  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 == r3);

  EXPECT_FALSE(r1 != r2);
  EXPECT_TRUE(r1 != r3);
}



TEST_F(TestRotation3, FloatComparison)
{
  Quatf q1(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  Quatf q2(q1);
  Quatf q3(0.204124101f, -0.2041241f, 0.4082483f, 0.8660254f);
  Quatf q4(0.2041241f, -0.2141241f, 0.4082483f, 0.8660254f);
  Quatf q5(0.3041241f, -0.2141241f, 0.4082483f, 0.8660254f);

  Rot3f r1(q1);
  Rot3f r2(q2);
  Rot3f r3(q3);
  Rot3f r4(q4);
  Rot3f r5(q5);

  EXPECT_TRUE(close(r1, r2));
  EXPECT_TRUE(close(r1, r3));
  EXPECT_FALSE(close(r1, r4));
  EXPECT_FALSE(close(r1, r5));

  EXPECT_TRUE(close(r1, r2, 1.e-2f));
  EXPECT_TRUE(close(r1, r3, 1.e-2f));
  EXPECT_TRUE(close(r1, r4, 1.e-2f));
  EXPECT_FALSE(close(r1, r5, 1.e-2f));
}



TEST_F(TestRotation3, Multiplication)
{
  Quatf q1(1.f, 2.f, 3.f, 4.f);
  q1.normalize();
  Quatf q2(-3.f, 7.f, -1.f, 3.f);
  q2.normalize();
  Quatf qRef = q1 * q2;

  Rot3f r1(q1);
  Rot3f r2(q2);
  Rot3f rRef(qRef);
  HOU_EXPECT_FLOAT_CLOSE(rRef, r1 * r2);
  r1 *= r2;
  HOU_EXPECT_FLOAT_CLOSE(rRef, r1);
}



TEST_F(TestRotation3, Inversion)
{
  Quatf q(1.f, 2.f, 3.f, 4.f);
  q.normalize();
  Quatf qRef = inverse(q);

  Rot3f r(q);
  Rot3f rRef(qRef);
  HOU_EXPECT_FLOAT_CLOSE(rRef, inverse(r));
  r.invert();
  HOU_EXPECT_FLOAT_CLOSE(rRef, r);
}



TEST_F(TestRotation3, OutputStreamOperator)
{
  Quatf quatRef(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  Rot3f r(quatRef);
  HOU_EXPECT_OUTPUT("(0.204124,-0.204124,0.408248,0.866025)", r);
}



TEST_P(TestRotation3Paramf, RotationX)
{
  Rot3f r = Rot3f::x(GetParam());
  Quatf qRef(std::sin(GetParam() / 2.f), 0.f, 0.f, std::cos(GetParam() / 2.f));
  Vec3f vRef(GetParam(), 0.f, 0.f);
  Mat3x3f mRef =
  {
    1.f, 0.f, 0.f,
    0.f, std::cos(GetParam()), -std::sin(GetParam()),
    0.f, std::sin(GetParam()), std::cos(GetParam()),
  };
  HOU_EXPECT_CLOSE(qRef, r.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vRef, r.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.getMatrix(), 1.e-6f);
}



TEST_P(TestRotation3Paramf, RotationY)
{
  Rot3f r = Rot3f::y(GetParam());
  Quatf qRef(0.f, std::sin(GetParam() / 2.f), 0.f, std::cos(GetParam() / 2.f));
  Vec3f vRef(0.f, GetParam(), 0.f);
  Mat3x3f mRef =
  {
    std::cos(GetParam()), 0.f, std::sin(GetParam()),
    0.f, 1.f, 0.f,
    -std::sin(GetParam()), 0.f, std::cos(GetParam()),
  };
  HOU_EXPECT_CLOSE(qRef, r.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vRef, r.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.getMatrix(), 1.e-6f);
}



TEST_P(TestRotation3Paramf, RotationZ)
{
  Rot3f r = Rot3f::z(GetParam());
  Quatf qRef(0.f, 0.f, std::sin(GetParam() / 2.f), std::cos(GetParam() / 2.f));
  Vec3f vRef(0.f, 0.f, GetParam());
  Mat3x3f mRef =
  {
    std::cos(GetParam()), -std::sin(GetParam()), 0.f,
    std::sin(GetParam()), std::cos(GetParam()), 0.f,
    0.f, 0.f, 1.f,
  };
  HOU_EXPECT_CLOSE(qRef, r.getQuaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vRef, r.getVector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.getMatrix(), 1.e-6f);
}



INSTANTIATE_TEST_CASE_P
  ( TestRotation3Paramf
  , TestRotation3Paramf
  , Values(PI_F / 2.f, PI_F / 6.f),);

