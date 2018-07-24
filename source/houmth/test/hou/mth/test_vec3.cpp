// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/mth/matrix.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_vec3 : public Test
{};

}  // namespace



TEST_F(test_vec3, construction)
{
  vec3i vi1;
  vec3i vi2(1, 2, 3);
  vec3i vi3{4, 5, 6};
  vec3i vi4(vi2);
  vec3i vi5(vec3f(7.f, 8.f, 9.f));

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



TEST_F(test_vec3, construction_frommatrix)
{
  vec3i vi1(mat3x1i{1, 2, 3});
  vec3i vi2(mat3x1f{1.f, 2.f, 3.f});

  EXPECT_EQ(1, vi1(0));
  EXPECT_EQ(2, vi1(1));
  EXPECT_EQ(3, vi1(2));
  EXPECT_EQ(1, vi2(0));
  EXPECT_EQ(2, vi2(1));
  EXPECT_EQ(3, vi2(2));
}



TEST_F(test_vec3, element_access_operators)
{
  vec3i v1(1, 2, 3);

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



TEST_F(test_vec3, crossmatrix)
{
  vec3f v(1.f, 2.f, 3.f);
  // clang-format off
  mat3x3f m =
  {
    0.f, -3.f, 2.f,
    3.f, 0.f, -1.f,
    -2.f, 1.f, 0.f
  };
  // clang-format on

  EXPECT_FLOAT_CLOSE(m, cross_matrix(v));
}



TEST_F(test_vec3, cross_product)
{
  vec3i v1(1, 3, -5);
  vec3i v2(-2, 7, 6);
  EXPECT_EQ(vec3i(53, 4, 13), cross(v1, v2));
  EXPECT_EQ(vec3i(-53, -4, -13), cross(v2, v1));
  EXPECT_EQ(cross_matrix(v1) * v2, cross(v1, v2));
  EXPECT_EQ(cross_matrix(v2) * v1, cross(v2, v1));
  EXPECT_EQ(0, dot(cross(v1, v2), v1));
  EXPECT_EQ(0, dot(cross(v1, v2), v2));
}



TEST_F(test_vec3, outer_product)
{
  vec3i v1(-1, 2, 3);
  vec3i v2(5, 7, 11);
  // clang-format off
  mat3x3i m =
  {
    -5, -7, -11,
    10, 14, 22,
    15, 21, 33
  };
  // clang-format on

  EXPECT_EQ(m, outer_product(v1, v2));
}



TEST_F(test_vec3, dot_product)
{
  vec3i v1(2, 3, 5);
  vec3i v2(-1, 7, 4);
  EXPECT_EQ(0, dot(vec3i::zero(), v1));
  EXPECT_EQ(39, dot(v1, v2));
  EXPECT_EQ(39, dot(v2, v1));
}



TEST_F(test_vec3, output_stream_operator)
{
  vec3i v(1, 2, 3);
  EXPECT_OUTPUT("(1)\n(2)\n(3)", v);
}
