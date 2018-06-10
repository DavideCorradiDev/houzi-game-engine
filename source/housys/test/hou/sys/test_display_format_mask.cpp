// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/display_format_mask.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_display_format_mask : public Test
{};

}  // namespace



TEST_F(test_display_format_mask, test_rgba8888)
{
  display::format_mask m(display::format::rgba8888);
  EXPECT_EQ(display::format::rgba8888, m.get_format());
  EXPECT_EQ(32u, m.get_bpp());
  EXPECT_EQ(0xff000000u, m.get_red_bit_mask());
  EXPECT_EQ(0x00ff0000u, m.get_green_bit_mask());
  EXPECT_EQ(0x0000ff00u, m.get_blue_bit_mask());
  EXPECT_EQ(0x000000ffu, m.get_alpha_bit_mask());
}



TEST_F(test_display_format_mask, comparison)
{
  display::format_mask m0(display::format::rgba8888);
  display::format_mask m1(display::format::rgba8888);
  display::format_mask m2(display::format::rgb888);

  EXPECT_TRUE(m0 == m1);
  EXPECT_FALSE(m0 == m2);

  EXPECT_FALSE(m0 != m1);
  EXPECT_TRUE(m0 != m2);
}



TEST_F(test_display_format_mask, output_stream_operator)
{
  display::format_mask m(display::format::rgba8888);
  const char* out_ref
    = "{bpp = 32, red_bit_mask = 0xff000000, green_bit_mask = 0x00ff0000, "
      "blue_bit_mask = 0x0000ff00, alpha_bit_mask = 0x000000ff}";
  EXPECT_OUTPUT(out_ref, m);
}
