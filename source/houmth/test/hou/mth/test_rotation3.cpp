// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/mth/rotation3.hpp"
#include "hou/mth/matrix.hpp"
#include "hou/mth/math_functions.hpp"

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
  HOU_EXPECT_FLOAT_CLOSE(quatf::identity(), r.get_quaternion());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), r.get_vector());
  HOU_EXPECT_FLOAT_CLOSE(mat3x3f::identity(), r.get_matrix());
}



TEST_F(TestRotation3, ConstructorQuaternion)
{
  quatf quatRef(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  vec3f vecRef(0.4275166f, -0.4275166f, 0.8550332f);
  mat3x3f matRef
    ( 0.5833333f, -0.7904401f, -0.1868867f
    , 0.6237735f, 0.5833333f, -0.52022f
    , 0.52022f, 0.1868867f, 0.8333333f);

  Rot3f rQuat(quatRef);
  HOU_EXPECT_CLOSE(quatRef, rQuat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rQuat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rQuat.get_matrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorNonUnitQuaternion)
{
  quatf quat(2.f, 4.f, 5.f, -6.f);
  EXPECT_FLOAT_EQ(9.f, norm(quat));

  Rot3f r(quat);
  HOU_EXPECT_FLOAT_CLOSE(normalized(quat), r.get_quaternion());
}



TEST_F(TestRotation3DeathTest, ConstructorFailureZeroQuaternion)
{
  HOU_EXPECT_ERROR(Rot3f(quatf::zero()), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestRotation3, ConstructorVector)
{
  quatf quatRef(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  vec3f vecRef(0.4275166f, -0.4275166f, 0.8550332f);
  mat3x3f matRef
    ( 0.5833333f, -0.7904401f, -0.1868867f
    , 0.6237735f, 0.5833333f, -0.52022f
    , 0.52022f, 0.1868867f, 0.8333333f);

  Rot3f rVec(vecRef);
  HOU_EXPECT_CLOSE(quatRef, rVec.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rVec.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rVec.get_matrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorMatrix)
{
  quatf quatRef(0.f, 0.f, -0.7071068f, 0.7071068f);
  vec3f vecRef(0.f, 0.f, -1.5707963f);
  mat3x3f matRef(0.f, 1.f, 0.f, -1.f, 0.f, 0.f, 0.f, 0.f, 1.f);

  Rot3f rMat(matRef);
  HOU_EXPECT_CLOSE(quatRef, rMat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.get_matrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorMatrixNullRootFunction)
{
  quatf quatRef(0.f, 1.f, 0.f, 0.f);
  vec3f vecRef(0.f, pi_f, 0.f);
  mat3x3f matRef(-1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f);

  Rot3f rMat(matRef);
  HOU_EXPECT_CLOSE(quatRef, rMat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.get_matrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorMatrixSmallRootFunction)
{
  quatf quatRef(0.707107f, 0.707107f, 0.f, 0.f);
  vec3f vecRef(2.2214417f, 2.2214417f, 0.f);
  mat3x3f matRef(0.f, 1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f);

  Rot3f rMat(matRef);
  HOU_EXPECT_CLOSE(quatRef, rMat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.get_matrix(), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorMatrixLowPrecision)
{
  Rot3f rotRef = Rot3f::x(pi_f / 3.f) * Rot3f::z(pi_f / 4.f) * Rot3f::y(pi_f / 2.f);
  Rot3f rot(rotRef.get_matrix());
  HOU_EXPECT_FLOAT_CLOSE(rotRef, rot);
}



TEST_F(TestRotation3, ConstructorNonRotationMatrix)
{
  quatf quatRef(0.119523f, -0.239046f, 0.119523f, 0.956183f);
  vec3f vecRef(0.2426f, -0.485199f, 0.2426f);
  mat3x3f matRef
  {
    0.857143f, -0.285714f, -0.428571f,
    0.171429f, 0.942857f, -0.285714f,
    0.485714f, 0.171429f, 0.857143f,
  };

  Rot3f rMat(mat3x3f{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f});
  HOU_EXPECT_CLOSE(quatRef, rMat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.get_matrix(), 1.e-6f);

  HOU_EXPECT_CLOSE(1.f, norm(rMat.get_quaternion()), 1.e-6f);
  HOU_EXPECT_CLOSE(mat3x3f::identity(), rMat.get_matrix()
    * transpose(rMat.get_matrix()), 1.e-6f);
  HOU_EXPECT_CLOSE(1.f, det(rMat.get_matrix()), 1.e-6f);
}



TEST_F(TestRotation3, ConstructorZeroMatrix)
{
  quatf quatRef(0.f, 0.f, 1.f, 0.f);
  vec3f vecRef(0.f, 0.f, pi_f);
  mat3x3f matRef(-1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f, 0.f, 1.f);

  Rot3f rMat(mat3x3f::zero());
  HOU_EXPECT_CLOSE(quatRef, rMat.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vecRef, rMat.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(matRef, rMat.get_matrix(), 1.e-6f);

  HOU_EXPECT_CLOSE(1.f, norm(rMat.get_quaternion()), 1.e-6f);
  HOU_EXPECT_CLOSE(mat3x3f::identity(), rMat.get_matrix()
    * transpose(rMat.get_matrix()), 1.e-6f);
  HOU_EXPECT_CLOSE(1.f, det(rMat.get_matrix()), 1.e-6f);
}



TEST_F(TestRotation3, ConversionConstructor)
{
  quatd qd(1., 2., 3., 4.);
  Rot3d rd(qd);
  quatf qfRef(rd.get_quaternion());
  Rot3f rf(rd);

  HOU_EXPECT_FLOAT_CLOSE(qfRef, rf.get_quaternion());
}



TEST_F(TestRotation3, ComparisonOperators)
{
  quatf q1(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  quatf q2(q1);
  quatf q3(quatf::identity());

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
  quatf q1(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  quatf q2(q1);
  quatf q3(0.204124101f, -0.2041241f, 0.4082483f, 0.8660254f);
  quatf q4(0.2041241f, -0.2141241f, 0.4082483f, 0.8660254f);
  quatf q5(0.3041241f, -0.2141241f, 0.4082483f, 0.8660254f);

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
  quatf q1(1.f, 2.f, 3.f, 4.f);
  q1.normalize();
  quatf q2(-3.f, 7.f, -1.f, 3.f);
  q2.normalize();
  quatf qRef = q1 * q2;

  Rot3f r1(q1);
  Rot3f r2(q2);
  Rot3f rRef(qRef);
  HOU_EXPECT_FLOAT_CLOSE(rRef, r1 * r2);
  r1 *= r2;
  HOU_EXPECT_FLOAT_CLOSE(rRef, r1);
}



TEST_F(TestRotation3, Inversion)
{
  quatf q(1.f, 2.f, 3.f, 4.f);
  q.normalize();
  quatf qRef = inverse(q);

  Rot3f r(q);
  Rot3f rRef(qRef);
  HOU_EXPECT_FLOAT_CLOSE(rRef, inverse(r));
  r.invert();
  HOU_EXPECT_FLOAT_CLOSE(rRef, r);
}



TEST_F(TestRotation3, OutputStreamOperator)
{
  quatf quatRef(0.2041241f, -0.2041241f, 0.4082483f, 0.8660254f);
  Rot3f r(quatRef);
  HOU_EXPECT_OUTPUT("(0.204124,-0.204124,0.408248,0.866025)", r);
}



TEST_P(TestRotation3Paramf, RotationX)
{
  Rot3f r = Rot3f::x(GetParam());
  quatf qRef(std::sin(GetParam() / 2.f), 0.f, 0.f, std::cos(GetParam() / 2.f));
  vec3f vRef(GetParam(), 0.f, 0.f);
  mat3x3f mRef =
  {
    1.f, 0.f, 0.f,
    0.f, std::cos(GetParam()), -std::sin(GetParam()),
    0.f, std::sin(GetParam()), std::cos(GetParam()),
  };
  HOU_EXPECT_CLOSE(qRef, r.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vRef, r.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.get_matrix(), 1.e-6f);
}



TEST_P(TestRotation3Paramf, RotationY)
{
  Rot3f r = Rot3f::y(GetParam());
  quatf qRef(0.f, std::sin(GetParam() / 2.f), 0.f, std::cos(GetParam() / 2.f));
  vec3f vRef(0.f, GetParam(), 0.f);
  mat3x3f mRef =
  {
    std::cos(GetParam()), 0.f, std::sin(GetParam()),
    0.f, 1.f, 0.f,
    -std::sin(GetParam()), 0.f, std::cos(GetParam()),
  };
  HOU_EXPECT_CLOSE(qRef, r.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vRef, r.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.get_matrix(), 1.e-6f);
}



TEST_P(TestRotation3Paramf, RotationZ)
{
  Rot3f r = Rot3f::z(GetParam());
  quatf qRef(0.f, 0.f, std::sin(GetParam() / 2.f), std::cos(GetParam() / 2.f));
  vec3f vRef(0.f, 0.f, GetParam());
  mat3x3f mRef =
  {
    std::cos(GetParam()), -std::sin(GetParam()), 0.f,
    std::sin(GetParam()), std::cos(GetParam()), 0.f,
    0.f, 0.f, 1.f,
  };
  HOU_EXPECT_CLOSE(qRef, r.get_quaternion(), 1.e-6f);
  HOU_EXPECT_CLOSE(vRef, r.get_vector(), 1.e-6f);
  HOU_EXPECT_CLOSE(mRef, r.get_matrix(), 1.e-6f);
}



INSTANTIATE_TEST_CASE_P
  ( TestRotation3Paramf
  , TestRotation3Paramf
  , Values(pi_f / 2.f, pi_f / 6.f),);

