// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/sys/color.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_color : public Test
{};

}  // namespace



TEST_F(test_color, value_constructor)
{
  color c(20u, 30u, 40u, 50u);
  EXPECT_EQ(20u, c.get_red());
  EXPECT_EQ(30u, c.get_green());
  EXPECT_EQ(40u, c.get_blue());
  EXPECT_EQ(50u, c.get_alpha());
  EXPECT_EQ(20u, static_cast<uint8_t>(255.f * c.get_red_f()));
  EXPECT_EQ(30u, static_cast<uint8_t>(255.f * c.get_green_f()));
  EXPECT_EQ(40u, static_cast<uint8_t>(255.f * c.get_blue_f()));
  EXPECT_EQ(50u, static_cast<uint8_t>(255.f * c.get_alpha_f()));
}



TEST_F(test_color, set_red)
{
  color c(20u, 30u, 40u, 50u);
  c.set_red(100u);
  EXPECT_EQ(100u, c.get_red());
  EXPECT_EQ(100u, static_cast<uint8_t>(c.get_red_f() * 255.f));
  c.set_red_f(0.5f);
  EXPECT_EQ(127, c.get_red());
  EXPECT_EQ(127, static_cast<uint8_t>(c.get_red_f() * 255.f));
}



TEST_F(test_color, set_green)
{
  color c(20u, 30u, 40u, 50u);
  c.set_green(100u);
  EXPECT_EQ(100u, c.get_green());
  EXPECT_EQ(100u, static_cast<uint8_t>(c.get_green_f() * 255.f));
  c.set_green_f(0.5f);
  EXPECT_EQ(127, c.get_green());
  EXPECT_EQ(127, static_cast<uint8_t>(c.get_green_f() * 255.f));
}



TEST_F(test_color, set_blue)
{
  color c(20u, 30u, 40u, 50u);
  c.set_blue(100u);
  EXPECT_EQ(100u, c.get_blue());
  EXPECT_EQ(100u, static_cast<uint8_t>(c.get_blue_f() * 255.f));
  c.set_blue_f(0.5f);
  EXPECT_EQ(127, c.get_blue());
  EXPECT_EQ(127, static_cast<uint8_t>(c.get_blue_f() * 255.f));
}



TEST_F(test_color, set_alpha)
{
  color c(20u, 30u, 40u, 50u);
  c.set_alpha(100u);
  EXPECT_EQ(100u, c.get_alpha());
  EXPECT_EQ(100u, static_cast<uint8_t>(c.get_alpha_f() * 255.f));
  c.set_alpha_f(0.5f);
  EXPECT_EQ(127, c.get_alpha());
  EXPECT_EQ(127, static_cast<uint8_t>(c.get_alpha_f() * 255.f));
}



TEST_F(test_color, float_conversion)
{
  color c(0u, 0u, 0u, 0u);
  for(uint i = 0; i < 256; ++i)
  {
    c.set_red(i);
    EXPECT_EQ(i, static_cast<uint8_t>(255.f * c.get_red_f()));
    c.set_red_f(c.get_red_f());
    EXPECT_EQ(i, c.get_red());
  }
}



TEST_F(test_color, float_value_thresholds)
{
  color c(0u, 0u, 0u, 0u);
  c.set_red_f(1.1f);
  EXPECT_FLOAT_EQ(1.f, c.get_red_f());
  EXPECT_EQ(255u, c.get_red());
  c.set_red_f(-0.1f);
  EXPECT_FLOAT_EQ(0.f, c.get_red_f());
  EXPECT_EQ(0u, c.get_red());
}



TEST_F(test_color, comparison)
{
  color c1(100u, 100u, 100u, 100u);
  color c2(110u, 100u, 100u, 100u);
  color c3(100u, 110u, 100u, 100u);
  color c4(100u, 100u, 110u, 100u);
  color c5(100u, 100u, 100u, 110u);
  color c6(100u, 100u, 100u, 100u);

  EXPECT_FALSE(c1 == c2);
  EXPECT_FALSE(c1 == c3);
  EXPECT_FALSE(c1 == c4);
  EXPECT_FALSE(c1 == c5);
  EXPECT_TRUE(c1 == c6);

  EXPECT_TRUE(c1 != c2);
  EXPECT_TRUE(c1 != c3);
  EXPECT_TRUE(c1 != c4);
  EXPECT_TRUE(c1 != c5);
  EXPECT_FALSE(c1 != c6);
}



TEST_F(test_color, output_stream_operator)
{
  HOU_EXPECT_OUTPUT(
    "{red = 1, green = 2, blue = 3, alpha = 4}", color(1u, 2u, 3u, 4u));
}
