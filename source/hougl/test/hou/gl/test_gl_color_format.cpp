// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gl/gl_color_format.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_gl_color_format : public Test
{};

}  // namespace



TEST_F(test_gl_color_format, constructor)
{
  gl::color_format cf(1u, 2u, 3u, 4u);

  EXPECT_EQ(1u, cf.get_red_bit_count());
  EXPECT_EQ(2u, cf.get_green_bit_count());
  EXPECT_EQ(3u, cf.get_blue_bit_count());
  EXPECT_EQ(4u, cf.get_alpha_bit_count());
  EXPECT_EQ(10u, cf.get_bit_count());
}



TEST_F(test_gl_color_format, comparison_operators)
{
  gl::color_format cf0(1u, 2u, 3u, 4u);
  gl::color_format cf1(cf0);
  gl::color_format cf2(5u, 2u, 3u, 4u);
  gl::color_format cf3(1u, 5u, 3u, 4u);
  gl::color_format cf4(1u, 2u, 5u, 4u);
  gl::color_format cf5(1u, 2u, 3u, 5u);

  EXPECT_TRUE(cf0 == cf1);
  EXPECT_FALSE(cf0 == cf2);
  EXPECT_FALSE(cf0 == cf3);
  EXPECT_FALSE(cf0 == cf4);
  EXPECT_FALSE(cf0 == cf5);

  EXPECT_FALSE(cf0 != cf1);
  EXPECT_TRUE(cf0 != cf2);
  EXPECT_TRUE(cf0 != cf3);
  EXPECT_TRUE(cf0 != cf4);
  EXPECT_TRUE(cf0 != cf5);
}



TEST_F(test_gl_color_format, output_stream_operator)
{
  gl::color_format cf(1u, 2u, 3u, 4u);
  const char* out_ref
    = "{red_bit_count = 1, green_bit_count = 2, blue_bit_count = 3, "
      "alpha_bit_count = 4}";
  EXPECT_OUTPUT(out_ref, cf);
}
