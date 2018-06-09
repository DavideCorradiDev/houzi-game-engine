// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/display_mode.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_display_mode : public Test
{};

}  // namespace



TEST_F(test_display_mode, default_constructor)
{
  display::mode v;
  EXPECT_EQ(vec2u::zero(), v.get_size());
  EXPECT_EQ(display::pixel_format(), v.get_pixel_format());
  EXPECT_EQ(0u, v.get_refresh_rate());
}



TEST_F(test_display_mode, constructor)
{
  display::mode v(vec2u(1200u, 400u), display::pixel_format::rgba(), 40u);
  EXPECT_EQ(vec2u(1200u, 400u), v.get_size());
  EXPECT_EQ(display::pixel_format::rgba(), v.get_pixel_format());
  EXPECT_EQ(40u, v.get_refresh_rate());
}



TEST_F(test_display_mode, set_size)
{
  vec2u val_ref(800u, 600u);
  display::mode v(vec2u(1200u, 400u), display::pixel_format::rgba(), 40u);
  v.set_size(val_ref);
  EXPECT_EQ(val_ref, v.get_size());
}



TEST_F(test_display_mode, set_pixel_format)
{
  display::pixel_format val_ref = display::pixel_format::rgb();
  display::mode v(vec2u(1200u, 400u), display::pixel_format::rgba(), 40u);
  v.set_pixel_format(val_ref);
  EXPECT_EQ(val_ref, v.get_pixel_format());
}



TEST_F(test_display_mode, set_refresh_rate)
{
  uint val_ref = 60u;
  display::mode v(vec2u(1200u, 400u), display::pixel_format::rgba(), 40u);
  v.set_refresh_rate(val_ref);
  EXPECT_EQ(val_ref, v.get_refresh_rate());
}



TEST_F(test_display_mode, lower_than_operator)
{
  uint x0 = 320u;
  uint x1 = 640u;

  uint y0 = 320u;
  uint y1 = 640u;

  display::pixel_format pf0 = display::pixel_format::rgb();
  display::pixel_format pf1 = display::pixel_format::rgba();

  uint r0 = 24u;
  uint r1 = 40u;

  display::mode v0000(vec2u(x0, y0), pf0, r0);
  display::mode v0001(vec2u(x0, y0), pf0, r1);
  display::mode v0010(vec2u(x0, y0), pf1, r0);
  display::mode v0011(vec2u(x0, y0), pf1, r1);

  display::mode v0100(vec2u(x0, y1), pf0, r0);
  display::mode v0101(vec2u(x0, y1), pf0, r1);
  display::mode v0110(vec2u(x0, y1), pf1, r0);
  display::mode v0111(vec2u(x0, y1), pf1, r1);

  display::mode v1000(vec2u(x1, y0), pf0, r0);
  display::mode v1001(vec2u(x1, y0), pf0, r1);
  display::mode v1010(vec2u(x1, y0), pf1, r0);
  display::mode v1011(vec2u(x1, y0), pf1, r1);

  display::mode v1100(vec2u(x1, y1), pf0, r0);
  display::mode v1101(vec2u(x1, y1), pf0, r1);
  display::mode v1110(vec2u(x1, y1), pf1, r0);
  display::mode v1111(vec2u(x1, y1), pf1, r1);

  EXPECT_FALSE(v0000 < v0000);
  EXPECT_TRUE(v0000 < v0001);
  EXPECT_TRUE(v0000 < v0010);
  EXPECT_TRUE(v0000 < v0011);
  EXPECT_TRUE(v0000 < v0100);
  EXPECT_TRUE(v0000 < v0101);
  EXPECT_TRUE(v0000 < v0110);
  EXPECT_TRUE(v0000 < v0111);
  EXPECT_TRUE(v0000 < v1000);
  EXPECT_TRUE(v0000 < v1001);
  EXPECT_TRUE(v0000 < v1010);
  EXPECT_TRUE(v0000 < v1011);
  EXPECT_TRUE(v0000 < v1100);
  EXPECT_TRUE(v0000 < v1101);
  EXPECT_TRUE(v0000 < v1110);
  EXPECT_TRUE(v0000 < v1111);

  EXPECT_FALSE(v0001 < v0000);
  EXPECT_FALSE(v0001 < v0001);
  EXPECT_TRUE(v0001 < v0010);
  EXPECT_TRUE(v0001 < v0011);
  EXPECT_TRUE(v0001 < v0100);
  EXPECT_TRUE(v0001 < v0101);
  EXPECT_TRUE(v0001 < v0110);
  EXPECT_TRUE(v0001 < v0111);
  EXPECT_TRUE(v0001 < v1000);
  EXPECT_TRUE(v0001 < v1001);
  EXPECT_TRUE(v0001 < v1010);
  EXPECT_TRUE(v0001 < v1011);
  EXPECT_TRUE(v0001 < v1100);
  EXPECT_TRUE(v0001 < v1101);
  EXPECT_TRUE(v0001 < v1110);
  EXPECT_TRUE(v0001 < v1111);

  EXPECT_FALSE(v0010 < v0000);
  EXPECT_FALSE(v0010 < v0001);
  EXPECT_FALSE(v0010 < v0010);
  EXPECT_TRUE(v0010 < v0011);
  EXPECT_TRUE(v0010 < v0100);
  EXPECT_TRUE(v0010 < v0101);
  EXPECT_TRUE(v0010 < v0110);
  EXPECT_TRUE(v0010 < v0111);
  EXPECT_TRUE(v0010 < v1000);
  EXPECT_TRUE(v0010 < v1001);
  EXPECT_TRUE(v0010 < v1010);
  EXPECT_TRUE(v0010 < v1011);
  EXPECT_TRUE(v0010 < v1100);
  EXPECT_TRUE(v0010 < v1101);
  EXPECT_TRUE(v0010 < v1110);
  EXPECT_TRUE(v0010 < v1111);

  EXPECT_FALSE(v0011 < v0000);
  EXPECT_FALSE(v0011 < v0001);
  EXPECT_FALSE(v0011 < v0010);
  EXPECT_FALSE(v0011 < v0011);
  EXPECT_TRUE(v0011 < v0100);
  EXPECT_TRUE(v0011 < v0101);
  EXPECT_TRUE(v0011 < v0110);
  EXPECT_TRUE(v0011 < v0111);
  EXPECT_TRUE(v0011 < v1000);
  EXPECT_TRUE(v0011 < v1001);
  EXPECT_TRUE(v0011 < v1010);
  EXPECT_TRUE(v0011 < v1011);
  EXPECT_TRUE(v0011 < v1100);
  EXPECT_TRUE(v0011 < v1101);
  EXPECT_TRUE(v0011 < v1110);
  EXPECT_TRUE(v0011 < v1111);

  EXPECT_FALSE(v0100 < v0000);
  EXPECT_FALSE(v0100 < v0001);
  EXPECT_FALSE(v0100 < v0010);
  EXPECT_FALSE(v0100 < v0011);
  EXPECT_FALSE(v0100 < v0100);
  EXPECT_TRUE(v0100 < v0101);
  EXPECT_TRUE(v0100 < v0110);
  EXPECT_TRUE(v0100 < v0111);
  EXPECT_TRUE(v0100 < v1000);
  EXPECT_TRUE(v0100 < v1001);
  EXPECT_TRUE(v0100 < v1010);
  EXPECT_TRUE(v0100 < v1011);
  EXPECT_TRUE(v0100 < v1100);
  EXPECT_TRUE(v0100 < v1101);
  EXPECT_TRUE(v0100 < v1110);
  EXPECT_TRUE(v0100 < v1111);

  EXPECT_FALSE(v0101 < v0000);
  EXPECT_FALSE(v0101 < v0001);
  EXPECT_FALSE(v0101 < v0010);
  EXPECT_FALSE(v0101 < v0011);
  EXPECT_FALSE(v0101 < v0100);
  EXPECT_FALSE(v0101 < v0101);
  EXPECT_TRUE(v0101 < v0110);
  EXPECT_TRUE(v0101 < v0111);
  EXPECT_TRUE(v0101 < v1000);
  EXPECT_TRUE(v0101 < v1001);
  EXPECT_TRUE(v0101 < v1010);
  EXPECT_TRUE(v0101 < v1011);
  EXPECT_TRUE(v0101 < v1100);
  EXPECT_TRUE(v0101 < v1101);
  EXPECT_TRUE(v0101 < v1110);
  EXPECT_TRUE(v0101 < v1111);

  EXPECT_FALSE(v0110 < v0000);
  EXPECT_FALSE(v0110 < v0001);
  EXPECT_FALSE(v0110 < v0010);
  EXPECT_FALSE(v0110 < v0011);
  EXPECT_FALSE(v0110 < v0100);
  EXPECT_FALSE(v0110 < v0101);
  EXPECT_FALSE(v0110 < v0110);
  EXPECT_TRUE(v0110 < v0111);
  EXPECT_TRUE(v0110 < v1000);
  EXPECT_TRUE(v0110 < v1001);
  EXPECT_TRUE(v0110 < v1010);
  EXPECT_TRUE(v0110 < v1011);
  EXPECT_TRUE(v0110 < v1100);
  EXPECT_TRUE(v0110 < v1101);
  EXPECT_TRUE(v0110 < v1110);
  EXPECT_TRUE(v0110 < v1111);

  EXPECT_FALSE(v0111 < v0000);
  EXPECT_FALSE(v0111 < v0001);
  EXPECT_FALSE(v0111 < v0010);
  EXPECT_FALSE(v0111 < v0011);
  EXPECT_FALSE(v0111 < v0100);
  EXPECT_FALSE(v0111 < v0101);
  EXPECT_FALSE(v0111 < v0110);
  EXPECT_FALSE(v0111 < v0111);
  EXPECT_TRUE(v0111 < v1000);
  EXPECT_TRUE(v0111 < v1001);
  EXPECT_TRUE(v0111 < v1010);
  EXPECT_TRUE(v0111 < v1011);
  EXPECT_TRUE(v0111 < v1100);
  EXPECT_TRUE(v0111 < v1101);
  EXPECT_TRUE(v0111 < v1110);
  EXPECT_TRUE(v0111 < v1111);

  EXPECT_FALSE(v1000 < v0000);
  EXPECT_FALSE(v1000 < v0001);
  EXPECT_FALSE(v1000 < v0010);
  EXPECT_FALSE(v1000 < v0011);
  EXPECT_FALSE(v1000 < v0100);
  EXPECT_FALSE(v1000 < v0101);
  EXPECT_FALSE(v1000 < v0110);
  EXPECT_FALSE(v1000 < v0111);
  EXPECT_FALSE(v1000 < v1000);
  EXPECT_TRUE(v1000 < v1001);
  EXPECT_TRUE(v1000 < v1010);
  EXPECT_TRUE(v1000 < v1011);
  EXPECT_TRUE(v1000 < v1100);
  EXPECT_TRUE(v1000 < v1101);
  EXPECT_TRUE(v1000 < v1110);
  EXPECT_TRUE(v1000 < v1111);

  EXPECT_FALSE(v1001 < v0000);
  EXPECT_FALSE(v1001 < v0001);
  EXPECT_FALSE(v1001 < v0010);
  EXPECT_FALSE(v1001 < v0011);
  EXPECT_FALSE(v1001 < v0100);
  EXPECT_FALSE(v1001 < v0101);
  EXPECT_FALSE(v1001 < v0110);
  EXPECT_FALSE(v1001 < v0111);
  EXPECT_FALSE(v1001 < v1000);
  EXPECT_FALSE(v1001 < v1001);
  EXPECT_TRUE(v1001 < v1010);
  EXPECT_TRUE(v1001 < v1011);
  EXPECT_TRUE(v1001 < v1100);
  EXPECT_TRUE(v1001 < v1101);
  EXPECT_TRUE(v1001 < v1110);
  EXPECT_TRUE(v1001 < v1111);

  EXPECT_FALSE(v1010 < v0000);
  EXPECT_FALSE(v1010 < v0001);
  EXPECT_FALSE(v1010 < v0010);
  EXPECT_FALSE(v1010 < v0011);
  EXPECT_FALSE(v1010 < v0100);
  EXPECT_FALSE(v1010 < v0101);
  EXPECT_FALSE(v1010 < v0110);
  EXPECT_FALSE(v1010 < v0111);
  EXPECT_FALSE(v1010 < v1000);
  EXPECT_FALSE(v1010 < v1001);
  EXPECT_FALSE(v1010 < v1010);
  EXPECT_TRUE(v1010 < v1011);
  EXPECT_TRUE(v1010 < v1100);
  EXPECT_TRUE(v1010 < v1101);
  EXPECT_TRUE(v1010 < v1110);
  EXPECT_TRUE(v1010 < v1111);

  EXPECT_FALSE(v1011 < v0000);
  EXPECT_FALSE(v1011 < v0001);
  EXPECT_FALSE(v1011 < v0010);
  EXPECT_FALSE(v1011 < v0011);
  EXPECT_FALSE(v1011 < v0100);
  EXPECT_FALSE(v1011 < v0101);
  EXPECT_FALSE(v1011 < v0110);
  EXPECT_FALSE(v1011 < v0111);
  EXPECT_FALSE(v1011 < v1000);
  EXPECT_FALSE(v1011 < v1001);
  EXPECT_FALSE(v1011 < v1010);
  EXPECT_FALSE(v1011 < v1011);
  EXPECT_TRUE(v1011 < v1100);
  EXPECT_TRUE(v1011 < v1101);
  EXPECT_TRUE(v1011 < v1110);
  EXPECT_TRUE(v1011 < v1111);

  EXPECT_FALSE(v1100 < v0000);
  EXPECT_FALSE(v1100 < v0001);
  EXPECT_FALSE(v1100 < v0010);
  EXPECT_FALSE(v1100 < v0011);
  EXPECT_FALSE(v1100 < v0100);
  EXPECT_FALSE(v1100 < v0101);
  EXPECT_FALSE(v1100 < v0110);
  EXPECT_FALSE(v1100 < v0111);
  EXPECT_FALSE(v1100 < v1000);
  EXPECT_FALSE(v1100 < v1001);
  EXPECT_FALSE(v1100 < v1010);
  EXPECT_FALSE(v1100 < v1011);
  EXPECT_FALSE(v1100 < v1100);
  EXPECT_TRUE(v1100 < v1101);
  EXPECT_TRUE(v1100 < v1110);
  EXPECT_TRUE(v1100 < v1111);

  EXPECT_FALSE(v1101 < v0000);
  EXPECT_FALSE(v1101 < v0001);
  EXPECT_FALSE(v1101 < v0010);
  EXPECT_FALSE(v1101 < v0011);
  EXPECT_FALSE(v1101 < v0100);
  EXPECT_FALSE(v1101 < v0101);
  EXPECT_FALSE(v1101 < v0110);
  EXPECT_FALSE(v1101 < v0111);
  EXPECT_FALSE(v1101 < v1000);
  EXPECT_FALSE(v1101 < v1001);
  EXPECT_FALSE(v1101 < v1010);
  EXPECT_FALSE(v1101 < v1011);
  EXPECT_FALSE(v1101 < v1100);
  EXPECT_FALSE(v1101 < v1101);
  EXPECT_TRUE(v1101 < v1110);
  EXPECT_TRUE(v1101 < v1111);

  EXPECT_FALSE(v1110 < v0000);
  EXPECT_FALSE(v1110 < v0001);
  EXPECT_FALSE(v1110 < v0010);
  EXPECT_FALSE(v1110 < v0011);
  EXPECT_FALSE(v1110 < v0100);
  EXPECT_FALSE(v1110 < v0101);
  EXPECT_FALSE(v1110 < v0110);
  EXPECT_FALSE(v1110 < v0111);
  EXPECT_FALSE(v1110 < v1000);
  EXPECT_FALSE(v1110 < v1001);
  EXPECT_FALSE(v1110 < v1010);
  EXPECT_FALSE(v1110 < v1011);
  EXPECT_FALSE(v1110 < v1100);
  EXPECT_FALSE(v1110 < v1101);
  EXPECT_FALSE(v1110 < v1110);
  EXPECT_TRUE(v1110 < v1111);

  EXPECT_FALSE(v1111 < v0000);
  EXPECT_FALSE(v1111 < v0001);
  EXPECT_FALSE(v1111 < v0010);
  EXPECT_FALSE(v1111 < v0011);
  EXPECT_FALSE(v1111 < v0100);
  EXPECT_FALSE(v1111 < v0101);
  EXPECT_FALSE(v1111 < v0110);
  EXPECT_FALSE(v1111 < v0111);
  EXPECT_FALSE(v1111 < v1000);
  EXPECT_FALSE(v1111 < v1001);
  EXPECT_FALSE(v1111 < v1010);
  EXPECT_FALSE(v1111 < v1011);
  EXPECT_FALSE(v1111 < v1100);
  EXPECT_FALSE(v1111 < v1101);
  EXPECT_FALSE(v1111 < v1110);
  EXPECT_FALSE(v1111 < v1111);
}



TEST_F(test_display_mode, comparison_operators)
{
  uint x0 = 320u;
  uint x1 = 640u;

  uint y0 = 320u;
  uint y1 = 640u;

  display::pixel_format pf0 = display::pixel_format::rgb();
  display::pixel_format pf1 = display::pixel_format::rgba();

  uint r0 = 24u;
  uint r1 = 40u;

  std::vector<display::mode> modes;

  modes.push_back(display::mode(vec2u(x0, y0), pf0, r0));
  modes.push_back(display::mode(vec2u(x0, y0), pf0, r1));
  modes.push_back(display::mode(vec2u(x0, y0), pf1, r0));
  modes.push_back(display::mode(vec2u(x0, y0), pf1, r1));

  modes.push_back(display::mode(vec2u(x1, y0), pf0, r0));
  modes.push_back(display::mode(vec2u(x1, y0), pf0, r1));
  modes.push_back(display::mode(vec2u(x1, y0), pf1, r0));
  modes.push_back(display::mode(vec2u(x1, y0), pf1, r1));

  modes.push_back(display::mode(vec2u(x0, y1), pf0, r0));
  modes.push_back(display::mode(vec2u(x0, y1), pf0, r1));
  modes.push_back(display::mode(vec2u(x0, y1), pf1, r0));
  modes.push_back(display::mode(vec2u(x0, y1), pf1, r1));

  modes.push_back(display::mode(vec2u(x1, y1), pf0, r0));
  modes.push_back(display::mode(vec2u(x1, y1), pf0, r1));
  modes.push_back(display::mode(vec2u(x1, y1), pf1, r0));
  modes.push_back(display::mode(vec2u(x1, y1), pf1, r1));

  // Test all comparison operators based on operator <.
  for(const auto& lhs : modes)
  {
    for(const auto& rhs : modes)
    {
      EXPECT_TRUE((!(lhs == rhs) && (lhs < rhs || rhs < lhs))
        || (lhs == rhs && (!(lhs < rhs) && !(rhs < lhs))));
      EXPECT_TRUE((!(lhs != rhs) && (!(lhs < rhs) && !(rhs < lhs)))
        || (lhs != rhs && (lhs < rhs || rhs < lhs)));
      EXPECT_TRUE(
        (!(lhs <= rhs) && rhs < lhs) || (lhs <= rhs && (!(rhs < lhs))));
      EXPECT_TRUE((!(lhs > rhs) && !(rhs < lhs)) || (lhs > rhs && rhs < lhs));
      EXPECT_TRUE(
        (!(lhs >= rhs) && lhs < rhs) || (lhs >= rhs && (!(lhs < rhs))));
    }
  }
}



TEST_F(test_display_mode, output_stream_operator)
{
  display::mode vm(vec2u(300u, 400u), display::pixel_format::rgba(), 45u);

  const char* output_ref
    = "{size = (300, 400), pixel_format = {bbp = 32, red_bit_mask = "
      "0xff000000, green_bit_mask = 0x00ff0000, blue_bit_mask = 0x0000ff00, "
      "alpha_bit_mask = 0x000000ff}, refresh_rate = 45}";
  EXPECT_OUTPUT(output_ref, vm);
}
