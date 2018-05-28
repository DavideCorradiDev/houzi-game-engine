// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/mth/matrix.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_vec2 : public Test
{};

}  // namespace



TEST_F(test_vec2, construction)
{
  vec2i vi1;
  vec2i vi2(1, 2);
  vec2i vi3{3, 4};
  vec2i vi4(vi2);
  vec2i vi5(vec2f(5.f, 6.f));

  EXPECT_EQ(0, vi1(0));
  EXPECT_EQ(0, vi1(1));
  EXPECT_EQ(1, vi2(0));
  EXPECT_EQ(2, vi2(1));
  EXPECT_EQ(3, vi3(0));
  EXPECT_EQ(4, vi3(1));
  EXPECT_EQ(1, vi4(0));
  EXPECT_EQ(2, vi4(1));
  EXPECT_EQ(5, vi5(0));
  EXPECT_EQ(6, vi5(1));
}



TEST_F(test_vec2, construction_frommatrix)
{
  vec2i vi1(mat2x1i{1, 2});
  vec2i vi2(mat2x1f{1.f, 2.f});

  EXPECT_EQ(1, vi1(0));
  EXPECT_EQ(2, vi1(1));
  EXPECT_EQ(1, vi2(0));
  EXPECT_EQ(2, vi2(1));
}



TEST_F(test_vec2, element_access_operators)
{
  vec2i v1(1, 2);

  EXPECT_EQ(1, v1.x());
  EXPECT_EQ(2, v1.y());

  v1.x() = 3;
  v1.y() = 4;

  EXPECT_EQ(3, v1.x());
  EXPECT_EQ(4, v1.y());
}



TEST_F(test_vec2, cross_product)
{
  vec2i v(3, 2);
  EXPECT_EQ(vec2i(2, -3), cross(v));
  EXPECT_EQ(0, dot(cross(v), v));
}



TEST_F(test_vec2, dot_product)
{
  vec2i v1(2, 3);
  vec2i v2(-5, 7);
  EXPECT_EQ(0, dot(vec2i::zero(), v1));
  EXPECT_EQ(11, dot(v1, v2));
  EXPECT_EQ(11, dot(v2, v1));
}



TEST_F(test_vec2, output_stream_operator)
{
  vec2i v(1, 2);
  EXPECT_OUTPUT("(1)\n(2)", v);
}
