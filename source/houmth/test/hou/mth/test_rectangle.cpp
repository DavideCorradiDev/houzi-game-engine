// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/checked_variable.hpp"

#include "hou/mth/rectangle.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_rectangle : public Test
{};

}  // namespace



TEST_F(test_rectangle, default_constructor)
{
  recti r;
  EXPECT_EQ(0, r.x());
  EXPECT_EQ(0, r.y());
  EXPECT_EQ(0, r.w());
  EXPECT_EQ(0, r.h());
}



TEST_F(test_rectangle, non_negative_size_default_constructor)
{
  rectui r;
  EXPECT_EQ(0, r.x());
  EXPECT_EQ(0, r.y());
  EXPECT_EQ(0, r.w());
  EXPECT_EQ(0, r.h());
}



TEST_F(test_rectangle, element_constructor)
{
  recti r(1, 2, 3, 4);
  EXPECT_EQ(1, r.x());
  EXPECT_EQ(2, r.y());
  EXPECT_EQ(3, r.w());
  EXPECT_EQ(4, r.h());
}



TEST_F(test_rectangle, non_negative_element_constructor)
{
  rectui r(1, 2, 3, 4);
  EXPECT_EQ(1, r.x());
  EXPECT_EQ(2, r.y());
  EXPECT_EQ(3, r.w());
  EXPECT_EQ(4, r.h());
}



TEST_F(test_rectangle, position_size_constructor)
{
  recti r(vec2i(5, 6), vec2i(7, 8));
  EXPECT_EQ(5, r.x());
  EXPECT_EQ(6, r.y());
  EXPECT_EQ(7, r.w());
  EXPECT_EQ(8, r.h());
}



TEST_F(test_rectangle, non_negative_position_size_constructor)
{
  rectui r(vec2i(5, 6), vec2i(7, 8));
  EXPECT_EQ(5, r.x());
  EXPECT_EQ(6, r.y());
  EXPECT_EQ(7, r.w());
  EXPECT_EQ(8, r.h());
}



TEST_F(test_rectangle, conversion_constructor)
{
  rectf rf(1.1f, 2.2f, 3.3f, 4.4f);
  recti ri = static_cast<recti>(rf);

  EXPECT_EQ(1, ri.x());
  EXPECT_EQ(2, ri.y());
  EXPECT_EQ(3, ri.w());
  EXPECT_EQ(4, ri.h());
}



TEST_F(test_rectangle, non_negative_conversion_constructor)
{
  rectuf rf(1.1f, 2.2f, 3.3f, 4.4f);
  rectui ri = static_cast<recti>(rf);

  EXPECT_EQ(1, ri.x());
  EXPECT_EQ(2, ri.y());
  EXPECT_EQ(3, ri.w());
  EXPECT_EQ(4, ri.h());
}



TEST_F(test_rectangle, element_access)
{
  recti r(1, 2, 3, 5);

  EXPECT_EQ(vec2i(1, 2), r.get_position());
  EXPECT_EQ(vec2i(3, 5), r.get_size());
  EXPECT_EQ(1, r.x());
  EXPECT_EQ(2, r.y());
  EXPECT_EQ(3, r.w());
  EXPECT_EQ(5, r.h());

  r.x() = -7;
  EXPECT_EQ(vec2i(-7, 2), r.get_position());
  EXPECT_EQ(-7, r.x());

  r.y() = -11;
  EXPECT_EQ(vec2i(-7, -11), r.get_position());
  EXPECT_EQ(-11, r.y());

  r.w() = -13;
  EXPECT_EQ(vec2i(-13, 5), r.get_size());
  EXPECT_EQ(-13, r.w());

  r.h() = -17;
  EXPECT_EQ(vec2i(-13, -17), r.get_size());
  EXPECT_EQ(-17, r.h());

  r.set_position(vec2i(2, 3));
  EXPECT_EQ(vec2i(2, 3), r.get_position());
  EXPECT_EQ(2, r.x());
  EXPECT_EQ(3, r.y());

  r.set_size(vec2i(9, 7));
  EXPECT_EQ(vec2i(9, 7), r.get_size());
  EXPECT_EQ(9, r.w());
  EXPECT_EQ(7, r.h());
}



TEST_F(test_rectangle, non_negative_element_access)
{
  rectui r(1, 2, 3, 5);

  EXPECT_EQ(vec2i(1, 2), r.get_position());
  EXPECT_EQ(vec2ipz(3, 5), r.get_size());
  EXPECT_EQ(1, r.x());
  EXPECT_EQ(2, r.y());
  EXPECT_EQ(3, r.w());
  EXPECT_EQ(5, r.h());

  r.x() = -7;
  EXPECT_EQ(vec2i(-7, 2), r.get_position());
  EXPECT_EQ(-7, r.x());

  r.y() = -11;
  EXPECT_EQ(vec2i(-7, -11), r.get_position());
  EXPECT_EQ(-11, r.y());

  r.w() = 13;
  EXPECT_EQ(vec2ipz(13, 5), r.get_size());
  EXPECT_EQ(13, r.w());

  r.h() = 17;
  EXPECT_EQ(vec2ipz(13, 17), r.get_size());
  EXPECT_EQ(17, r.h());

  r.set_position(vec2i(2, 3));
  EXPECT_EQ(vec2i(2, 3), r.get_position());
  EXPECT_EQ(2, r.x());
  EXPECT_EQ(3, r.y());

  r.set_size(vec2i(9, 7));
  EXPECT_EQ(vec2ipz(9, 7), r.get_size());
  EXPECT_EQ(9, r.w());
  EXPECT_EQ(7, r.h());
}



TEST_F(test_rectangle, left)
{
  recti r(1, 2, 3, 4);
  EXPECT_EQ(1, r.l());

  r.x() = 5;
  r.w() = 6;
  EXPECT_EQ(5, r.l());

  r.x() = -2;
  r.w() = 6;
  EXPECT_EQ(-2, r.l());

  r.x() = -10;
  r.w() = 5;
  EXPECT_EQ(-10, r.l());

  r.x() = 2;
  r.w() = -5;
  EXPECT_EQ(-3, r.l());

  r.x() = -3;
  r.w() = -5;
  EXPECT_EQ(-8, r.l());
}



TEST_F(test_rectangle, right)
{
  recti r(1, 2, 3, 4);
  EXPECT_EQ(4, r.r());

  r.x() = 5;
  r.w() = 6;
  EXPECT_EQ(11, r.r());

  r.x() = -2;
  r.w() = 6;
  EXPECT_EQ(4, r.r());

  r.x() = -10;
  r.w() = 5;
  EXPECT_EQ(-5, r.r());

  r.x() = 2;
  r.w() = -5;
  EXPECT_EQ(2, r.r());

  r.x() = -3;
  r.w() = -5;
  EXPECT_EQ(-3, r.r());
}



TEST_F(test_rectangle, top)
{
  recti r(1, 2, 3, 4);
  EXPECT_EQ(2, r.t());

  r.y() = 5;
  r.h() = 6;
  EXPECT_EQ(5, r.t());

  r.y() = -2;
  r.h() = 6;
  EXPECT_EQ(-2, r.t());

  r.y() = -10;
  r.h() = 5;
  EXPECT_EQ(-10, r.t());

  r.y() = 2;
  r.h() = -5;
  EXPECT_EQ(-3, r.t());

  r.y() = -3;
  r.h() = -5;
  EXPECT_EQ(-8, r.t());
}



TEST_F(test_rectangle, bottom)
{
  recti r(1, 2, 3, 4);
  EXPECT_EQ(6, r.b());

  r.y() = 5;
  r.h() = 6;
  EXPECT_EQ(11, r.b());

  r.y() = -2;
  r.h() = 6;
  EXPECT_EQ(4, r.b());

  r.y() = -10;
  r.h() = 5;
  EXPECT_EQ(-5, r.b());

  r.y() = 2;
  r.h() = -5;
  EXPECT_EQ(2, r.b());

  r.y() = -3;
  r.h() = -5;
  EXPECT_EQ(-3, r.b());
}



TEST_F(test_rectangle, comparison_operators)
{
  recti r1(1, 2, 3, 4);
  recti r2(r1);
  recti r3(1, 2, 3, 0);
  recti r4(1, 2, 0, 4);
  recti r5(1, 0, 3, 4);
  recti r6(0, 2, 3, 4);

  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 == r3);
  EXPECT_FALSE(r1 == r4);
  EXPECT_FALSE(r1 == r5);
  EXPECT_FALSE(r1 == r6);
  EXPECT_FALSE(r1 != r2);
  EXPECT_TRUE(r1 != r3);
  EXPECT_TRUE(r1 != r4);
  EXPECT_TRUE(r1 != r5);
  EXPECT_TRUE(r1 != r6);
}



TEST_F(test_rectangle, non_negative_comparison_operators)
{
  rectui r1(1, 2, 3, 4);
  rectui r2(r1);
  rectui r3(1, 2, 3, 0);
  rectui r4(1, 2, 0, 4);
  rectui r5(1, 0, 3, 4);
  rectui r6(0, 2, 3, 4);

  EXPECT_TRUE(r1 == r2);
  EXPECT_FALSE(r1 == r3);
  EXPECT_FALSE(r1 == r4);
  EXPECT_FALSE(r1 == r5);
  EXPECT_FALSE(r1 == r6);
  EXPECT_FALSE(r1 != r2);
  EXPECT_TRUE(r1 != r3);
  EXPECT_TRUE(r1 != r4);
  EXPECT_TRUE(r1 != r5);
  EXPECT_TRUE(r1 != r6);
}



TEST_F(test_rectangle, floating_point_comparison)
{
  rectf r1(1.23456f, 2.34567f, 4.245678f, 5.894523f);
  rectf r2(r1);
  rectf r3(1.23458f, 2.34567f, 4.245678f, 5.894523f);
  rectf r4(1.23656f, 2.34567f, 4.245678f, 5.894523f);

  EXPECT_TRUE(close(r1, r2));
  EXPECT_FALSE(close(r1, r3));
  EXPECT_FALSE(close(r1, r4));
  EXPECT_TRUE(close(r1, r2, 1.e-6f));
  EXPECT_FALSE(close(r1, r3, 1.e-6f));
  EXPECT_FALSE(close(r1, r4, 1.e-6f));
  EXPECT_TRUE(close(r1, r2, 1.e-3f));
  EXPECT_TRUE(close(r1, r3, 1.e-3f));
  EXPECT_FALSE(close(r1, r4, 1.e-3f));
  EXPECT_TRUE(close(r1, r2, 1.e-2f));
  EXPECT_TRUE(close(r1, r3, 1.e-2f));
  EXPECT_TRUE(close(r1, r4, 1.e-2f));
}



TEST_F(test_rectangle, output_stream_operator)
{
  EXPECT_OUTPUT("{position = (1, 2), size = (3, 4)}", recti(1, 2, 3, 4));
}



TEST_F(test_rectangle, non_negative_output_stream_operator)
{
  EXPECT_OUTPUT("{position = (1, 2), size = (3, 4)}", rectui(1, 2, 3, 4));
}



TEST_F(test_rectangle, rect_contains_point)
{
  recti r(-2, 3, 5, 4);
  vec2i p0(1, 5);
  vec2i p1(-2, 5);
  vec2i p2(3, 5);
  vec2i p3(1, 3);
  vec2i p4(1, 7);
  vec2i p5(-3, 8);
  vec2i p6(-3, 5);
  vec2i p7(-3, 2);
  vec2i p8(1, 2);
  vec2i p9(4, 2);
  vec2i p10(4, 5);
  vec2i p11(4, 8);
  vec2i p12(1, 8);

  EXPECT_TRUE(is_point_in_rectangle(r, p0));
  EXPECT_TRUE(is_point_in_rectangle(r, p1));
  EXPECT_TRUE(is_point_in_rectangle(r, p2));
  EXPECT_TRUE(is_point_in_rectangle(r, p3));
  EXPECT_TRUE(is_point_in_rectangle(r, p4));
  EXPECT_FALSE(is_point_in_rectangle(r, p5));
  EXPECT_FALSE(is_point_in_rectangle(r, p6));
  EXPECT_FALSE(is_point_in_rectangle(r, p7));
  EXPECT_FALSE(is_point_in_rectangle(r, p8));
  EXPECT_FALSE(is_point_in_rectangle(r, p9));
  EXPECT_FALSE(is_point_in_rectangle(r, p10));
  EXPECT_FALSE(is_point_in_rectangle(r, p11));
  EXPECT_FALSE(is_point_in_rectangle(r, p12));
}



TEST_F(test_rectangle, non_negative_rect_contains_point)
{
  rectui r(-2, 3, 5, 4);
  vec2i p0(1, 5);
  vec2i p1(-2, 5);
  vec2i p2(3, 5);
  vec2i p3(1, 3);
  vec2i p4(1, 7);
  vec2i p5(-3, 8);
  vec2i p6(-3, 5);
  vec2i p7(-3, 2);
  vec2i p8(1, 2);
  vec2i p9(4, 2);
  vec2i p10(4, 5);
  vec2i p11(4, 8);
  vec2i p12(1, 8);

  EXPECT_TRUE(is_point_in_rectangle(r, p0));
  EXPECT_TRUE(is_point_in_rectangle(r, p1));
  EXPECT_TRUE(is_point_in_rectangle(r, p2));
  EXPECT_TRUE(is_point_in_rectangle(r, p3));
  EXPECT_TRUE(is_point_in_rectangle(r, p4));
  EXPECT_FALSE(is_point_in_rectangle(r, p5));
  EXPECT_FALSE(is_point_in_rectangle(r, p6));
  EXPECT_FALSE(is_point_in_rectangle(r, p7));
  EXPECT_FALSE(is_point_in_rectangle(r, p8));
  EXPECT_FALSE(is_point_in_rectangle(r, p9));
  EXPECT_FALSE(is_point_in_rectangle(r, p10));
  EXPECT_FALSE(is_point_in_rectangle(r, p11));
  EXPECT_FALSE(is_point_in_rectangle(r, p12));
}
