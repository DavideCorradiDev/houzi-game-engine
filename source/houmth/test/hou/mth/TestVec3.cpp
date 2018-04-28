// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/cor_error.hpp"

#include "hou/mth/Matrix.hpp"

using namespace hou;
using namespace testing;



namespace 
{

class TestVec3 : public Test {};

}



TEST_F(TestVec3, Construction)
{
  Vec3i vi1;
  Vec3i vi2(1, 2, 3);
  Vec3i vi3{4, 5, 6};
  Vec3i vi4(vi2);
  Vec3i vi5(Vec3f(7.f, 8.f, 9.f));

  EXPECT_EQ(0, vi1(0));
  EXPECT_EQ(0, vi1(1));
  EXPECT_EQ(0, vi1(2));
  EXPECT_EQ(1, vi2(0));
  EXPECT_EQ(2, vi2(1));
  EXPECT_EQ(3, vi2(2));
  EXPECT_EQ(4, vi3(0));
  EXPECT_EQ(5, vi3(1));
  EXPECT_EQ(6, vi3(2));
  EXPECT_EQ(1, vi4(0));
  EXPECT_EQ(2, vi4(1));
  EXPECT_EQ(3, vi4(2));
  EXPECT_EQ(7, vi5(0));
  EXPECT_EQ(8, vi5(1));
  EXPECT_EQ(9, vi5(2));
}



TEST_F(TestVec3, ConstructionFromMatrix)
{
  Vec3i vi1(Mat3x1i{1, 2, 3});
  Vec3i vi2(Mat3x1f{1.f, 2.f, 3.f});

  EXPECT_EQ(1, vi1(0));
  EXPECT_EQ(2, vi1(1));
  EXPECT_EQ(3, vi1(2));
  EXPECT_EQ(1, vi2(0));
  EXPECT_EQ(2, vi2(1));
  EXPECT_EQ(3, vi2(2));
}



TEST_F(TestVec3, ElementAccessOperators)
{
  Vec3i v1(1, 2, 3);

  EXPECT_EQ(1, v1.x());
  EXPECT_EQ(2, v1.y());
  EXPECT_EQ(3, v1.z());

  v1.x() = 4;
  v1.y() = 5;
  v1.z() = 6;

  EXPECT_EQ(4, v1.x());
  EXPECT_EQ(5, v1.y());
  EXPECT_EQ(6, v1.z());
}



TEST_F(TestVec3, CrossMatrix)
{
  Vec3f v(1.f, 2.f, 3.f);
  Mat3x3f m =
  {
    0.f, -3.f, 2.f,
    3.f, 0.f, -1.f,
    -2.f, 1.f, 0.f
  };

  HOU_EXPECT_FLOAT_CLOSE(m, crossMatrix(v));
}



TEST_F(TestVec3, CrossProduct)
{
  Vec3i v1(1, 3, -5);
  Vec3i v2(-2, 7, 6);
  EXPECT_EQ(Vec3i(53, 4, 13), cross(v1, v2));
  EXPECT_EQ(Vec3i(-53, -4, -13), cross(v2, v1));
  EXPECT_EQ(crossMatrix(v1) * v2, cross(v1, v2));
  EXPECT_EQ(crossMatrix(v2) * v1, cross(v2, v1));
  EXPECT_EQ(0, dot(cross(v1, v2), v1));
  EXPECT_EQ(0, dot(cross(v1, v2), v2));
}



TEST_F(TestVec3, OuterProduct)
{
  Vec3i v1(-1, 2, 3);
  Vec3i v2(5, 7, 11);
  Mat3x3i m =
  {
    -5, -7, -11,
    10, 14, 22,
    15, 21, 33
  };

  EXPECT_EQ(m, outerProduct(v1, v2));
}



TEST_F(TestVec3, DotProduct)
{
  Vec3i v1(2, 3, 5);
  Vec3i v2(-1, 7, 4);
  EXPECT_EQ(0, dot(Vec3i::zero(), v1));
  EXPECT_EQ(39, dot(v1, v2));
  EXPECT_EQ(39, dot(v2, v1));
}



TEST_F(TestVec3, OutputStreamOperator)
{
  Vec3i v(1, 2, 3);
  HOU_EXPECT_OUTPUT("(1)\n(2)\n(3)", v);
}

