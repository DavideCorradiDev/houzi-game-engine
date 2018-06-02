// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/test_sys_base.hpp"

#include "hou/sys/video_mode.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_video_mode : public test_sys_base
{};

}  // namespace



TEST_F(test_video_mode, constructor)
{
  video_mode v(vec2u(1200u, 400u), 8u, 40u);
  EXPECT_EQ(vec2u(1200u, 400u), v.get_resolution());
  EXPECT_EQ(8u, v.get_depth_byte_count());
  EXPECT_EQ(40u, v.get_refresh_rate());
}



TEST_F(test_video_mode, set_resolution)
{
  vec2u valRef(800u, 600u);
  video_mode v(vec2u(1200u, 400u), 8u, 40u);
  v.set_resolution(valRef);
  EXPECT_EQ(valRef, v.get_resolution());
}



TEST_F(test_video_mode, set_depth_byte_count)
{
  uint valRef = 4u;
  video_mode v(vec2u(1200u, 400u), 8u, 40u);
  v.set_depth_byte_count(valRef);
  EXPECT_EQ(valRef, v.get_depth_byte_count());
}



TEST_F(test_video_mode, set_refresh_rate)
{
  uint valRef = 60u;
  video_mode v(vec2u(1200u, 400u), 8u, 40u);
  v.set_refresh_rate(valRef);
  EXPECT_EQ(valRef, v.get_refresh_rate());
}



TEST_F(test_video_mode, lower_than_operator)
{
  uint x0 = 320u;
  uint x1 = 640u;

  uint y0 = 320u;
  uint y1 = 640u;

  uint d0 = 1u;
  uint d1 = 2u;

  uint r0 = 24u;
  uint r1 = 40u;

  video_mode v0000(vec2u(x0, y0), d0, r0);
  video_mode v0001(vec2u(x0, y0), d0, r1);
  video_mode v0010(vec2u(x0, y0), d1, r0);
  video_mode v0011(vec2u(x0, y0), d1, r1);

  video_mode v0100(vec2u(x1, y0), d0, r0);
  video_mode v0101(vec2u(x1, y0), d0, r1);
  video_mode v0110(vec2u(x1, y0), d1, r0);
  video_mode v0111(vec2u(x1, y0), d1, r1);

  video_mode v1000(vec2u(x0, y1), d0, r0);
  video_mode v1001(vec2u(x0, y1), d0, r1);
  video_mode v1010(vec2u(x0, y1), d1, r0);
  video_mode v1011(vec2u(x0, y1), d1, r1);

  video_mode v1100(vec2u(x1, y1), d0, r0);
  video_mode v1101(vec2u(x1, y1), d0, r1);
  video_mode v1110(vec2u(x1, y1), d1, r0);
  video_mode v1111(vec2u(x1, y1), d1, r1);

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
  EXPECT_FALSE(v0001 < v0010);
  EXPECT_TRUE(v0001 < v0011);
  EXPECT_FALSE(v0001 < v0100);
  EXPECT_TRUE(v0001 < v0101);
  EXPECT_FALSE(v0001 < v0110);
  EXPECT_TRUE(v0001 < v0111);
  EXPECT_FALSE(v0001 < v1000);
  EXPECT_TRUE(v0001 < v1001);
  EXPECT_FALSE(v0001 < v1010);
  EXPECT_TRUE(v0001 < v1011);
  EXPECT_FALSE(v0001 < v1100);
  EXPECT_TRUE(v0001 < v1101);
  EXPECT_FALSE(v0001 < v1110);
  EXPECT_TRUE(v0001 < v1111);

  EXPECT_FALSE(v0010 < v0000);
  EXPECT_TRUE(v0010 < v0001);
  EXPECT_FALSE(v0010 < v0010);
  EXPECT_TRUE(v0010 < v0011);
  EXPECT_FALSE(v0010 < v0100);
  EXPECT_TRUE(v0010 < v0101);
  EXPECT_TRUE(v0010 < v0110);
  EXPECT_TRUE(v0010 < v0111);
  EXPECT_FALSE(v0010 < v1000);
  EXPECT_TRUE(v0010 < v1001);
  EXPECT_TRUE(v0010 < v1010);
  EXPECT_TRUE(v0010 < v1011);
  EXPECT_FALSE(v0010 < v1100);
  EXPECT_TRUE(v0010 < v1101);
  EXPECT_TRUE(v0010 < v1110);
  EXPECT_TRUE(v0010 < v1111);

  EXPECT_FALSE(v0011 < v0000);
  EXPECT_FALSE(v0011 < v0001);
  EXPECT_FALSE(v0011 < v0010);
  EXPECT_FALSE(v0011 < v0011);
  EXPECT_FALSE(v0011 < v0100);
  EXPECT_FALSE(v0011 < v0101);
  EXPECT_FALSE(v0011 < v0110);
  EXPECT_TRUE(v0011 < v0111);
  EXPECT_FALSE(v0011 < v1000);
  EXPECT_FALSE(v0011 < v1001);
  EXPECT_FALSE(v0011 < v1010);
  EXPECT_TRUE(v0011 < v1011);
  EXPECT_FALSE(v0011 < v1100);
  EXPECT_FALSE(v0011 < v1101);
  EXPECT_FALSE(v0011 < v1110);
  EXPECT_TRUE(v0011 < v1111);

  EXPECT_FALSE(v0100 < v0000);
  EXPECT_TRUE(v0100 < v0001);
  EXPECT_TRUE(v0100 < v0010);
  EXPECT_TRUE(v0100 < v0011);
  EXPECT_FALSE(v0100 < v0100);
  EXPECT_TRUE(v0100 < v0101);
  EXPECT_TRUE(v0100 < v0110);
  EXPECT_TRUE(v0100 < v0111);
  EXPECT_FALSE(v0100 < v1000);
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
  EXPECT_TRUE(v0101 < v0011);
  EXPECT_FALSE(v0101 < v0100);
  EXPECT_FALSE(v0101 < v0101);
  EXPECT_FALSE(v0101 < v0110);
  EXPECT_TRUE(v0101 < v0111);
  EXPECT_FALSE(v0101 < v1000);
  EXPECT_FALSE(v0101 < v1001);
  EXPECT_FALSE(v0101 < v1010);
  EXPECT_TRUE(v0101 < v1011);
  EXPECT_FALSE(v0101 < v1100);
  EXPECT_TRUE(v0101 < v1101);
  EXPECT_FALSE(v0101 < v1110);
  EXPECT_TRUE(v0101 < v1111);

  EXPECT_FALSE(v0110 < v0000);
  EXPECT_TRUE(v0110 < v0001);
  EXPECT_FALSE(v0110 < v0010);
  EXPECT_TRUE(v0110 < v0011);
  EXPECT_FALSE(v0110 < v0100);
  EXPECT_TRUE(v0110 < v0101);
  EXPECT_FALSE(v0110 < v0110);
  EXPECT_TRUE(v0110 < v0111);
  EXPECT_FALSE(v0110 < v1000);
  EXPECT_TRUE(v0110 < v1001);
  EXPECT_FALSE(v0110 < v1010);
  EXPECT_TRUE(v0110 < v1011);
  EXPECT_FALSE(v0110 < v1100);
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
  EXPECT_FALSE(v0111 < v1000);
  EXPECT_FALSE(v0111 < v1001);
  EXPECT_FALSE(v0111 < v1010);
  EXPECT_FALSE(v0111 < v1011);
  EXPECT_FALSE(v0111 < v1100);
  EXPECT_FALSE(v0111 < v1101);
  EXPECT_FALSE(v0111 < v1110);
  EXPECT_TRUE(v0111 < v1111);

  EXPECT_FALSE(v1000 < v0000);
  EXPECT_TRUE(v1000 < v0001);
  EXPECT_TRUE(v1000 < v0010);
  EXPECT_TRUE(v1000 < v0011);
  EXPECT_TRUE(v1000 < v0100);
  EXPECT_TRUE(v1000 < v0101);
  EXPECT_TRUE(v1000 < v0110);
  EXPECT_TRUE(v1000 < v0111);
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
  EXPECT_TRUE(v1001 < v0011);
  EXPECT_FALSE(v1001 < v0100);
  EXPECT_TRUE(v1001 < v0101);
  EXPECT_FALSE(v1001 < v0110);
  EXPECT_TRUE(v1001 < v0111);
  EXPECT_FALSE(v1001 < v1000);
  EXPECT_FALSE(v1001 < v1001);
  EXPECT_FALSE(v1001 < v1010);
  EXPECT_TRUE(v1001 < v1011);
  EXPECT_FALSE(v1001 < v1100);
  EXPECT_TRUE(v1001 < v1101);
  EXPECT_FALSE(v1001 < v1110);
  EXPECT_TRUE(v1001 < v1111);

  EXPECT_FALSE(v1010 < v0000);
  EXPECT_TRUE(v1010 < v0001);
  EXPECT_FALSE(v1010 < v0010);
  EXPECT_TRUE(v1010 < v0011);
  EXPECT_FALSE(v1010 < v0100);
  EXPECT_TRUE(v1010 < v0101);
  EXPECT_TRUE(v1010 < v0110);
  EXPECT_TRUE(v1010 < v0111);
  EXPECT_FALSE(v1010 < v1000);
  EXPECT_TRUE(v1010 < v1001);
  EXPECT_FALSE(v1010 < v1010);
  EXPECT_TRUE(v1010 < v1011);
  EXPECT_FALSE(v1010 < v1100);
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
  EXPECT_TRUE(v1011 < v0111);
  EXPECT_FALSE(v1011 < v1000);
  EXPECT_FALSE(v1011 < v1001);
  EXPECT_FALSE(v1011 < v1010);
  EXPECT_FALSE(v1011 < v1011);
  EXPECT_FALSE(v1011 < v1100);
  EXPECT_FALSE(v1011 < v1101);
  EXPECT_FALSE(v1011 < v1110);
  EXPECT_TRUE(v1011 < v1111);

  EXPECT_FALSE(v1100 < v0000);
  EXPECT_TRUE(v1100 < v0001);
  EXPECT_TRUE(v1100 < v0010);
  EXPECT_TRUE(v1100 < v0011);
  EXPECT_FALSE(v1100 < v0100);
  EXPECT_TRUE(v1100 < v0101);
  EXPECT_TRUE(v1100 < v0110);
  EXPECT_TRUE(v1100 < v0111);
  EXPECT_FALSE(v1100 < v1000);
  EXPECT_TRUE(v1100 < v1001);
  EXPECT_TRUE(v1100 < v1010);
  EXPECT_TRUE(v1100 < v1011);
  EXPECT_FALSE(v1100 < v1100);
  EXPECT_TRUE(v1100 < v1101);
  EXPECT_TRUE(v1100 < v1110);
  EXPECT_TRUE(v1100 < v1111);

  EXPECT_FALSE(v1101 < v0000);
  EXPECT_FALSE(v1101 < v0001);
  EXPECT_FALSE(v1101 < v0010);
  EXPECT_TRUE(v1101 < v0011);
  EXPECT_FALSE(v1101 < v0100);
  EXPECT_FALSE(v1101 < v0101);
  EXPECT_FALSE(v1101 < v0110);
  EXPECT_TRUE(v1101 < v0111);
  EXPECT_FALSE(v1101 < v1000);
  EXPECT_FALSE(v1101 < v1001);
  EXPECT_FALSE(v1101 < v1010);
  EXPECT_TRUE(v1101 < v1011);
  EXPECT_FALSE(v1101 < v1100);
  EXPECT_FALSE(v1101 < v1101);
  EXPECT_FALSE(v1101 < v1110);
  EXPECT_TRUE(v1101 < v1111);

  EXPECT_FALSE(v1110 < v0000);
  EXPECT_TRUE(v1110 < v0001);
  EXPECT_FALSE(v1110 < v0010);
  EXPECT_TRUE(v1110 < v0011);
  EXPECT_FALSE(v1110 < v0100);
  EXPECT_TRUE(v1110 < v0101);
  EXPECT_FALSE(v1110 < v0110);
  EXPECT_TRUE(v1110 < v0111);
  EXPECT_FALSE(v1110 < v1000);
  EXPECT_TRUE(v1110 < v1001);
  EXPECT_FALSE(v1110 < v1010);
  EXPECT_TRUE(v1110 < v1011);
  EXPECT_FALSE(v1110 < v1100);
  EXPECT_TRUE(v1110 < v1101);
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



TEST_F(test_video_mode, comparison_operators)
{
  uint x0 = 320u;
  uint x1 = 640u;

  uint y0 = 320u;
  uint y1 = 640u;

  uint d0 = 1u;
  uint d1 = 2u;

  uint r0 = 24u;
  uint r1 = 40u;

  std::vector<video_mode> modes;

  modes.push_back(video_mode(vec2u(x0, y0), d0, r0));
  modes.push_back(video_mode(vec2u(x0, y0), d0, r1));
  modes.push_back(video_mode(vec2u(x0, y0), d1, r0));
  modes.push_back(video_mode(vec2u(x0, y0), d1, r1));

  modes.push_back(video_mode(vec2u(x1, y0), d0, r0));
  modes.push_back(video_mode(vec2u(x1, y0), d0, r1));
  modes.push_back(video_mode(vec2u(x1, y0), d1, r0));
  modes.push_back(video_mode(vec2u(x1, y0), d1, r1));

  modes.push_back(video_mode(vec2u(x0, y1), d0, r0));
  modes.push_back(video_mode(vec2u(x0, y1), d0, r1));
  modes.push_back(video_mode(vec2u(x0, y1), d1, r0));
  modes.push_back(video_mode(vec2u(x0, y1), d1, r1));

  modes.push_back(video_mode(vec2u(x1, y1), d0, r0));
  modes.push_back(video_mode(vec2u(x1, y1), d0, r1));
  modes.push_back(video_mode(vec2u(x1, y1), d1, r0));
  modes.push_back(video_mode(vec2u(x1, y1), d1, r1));

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



TEST_F(test_video_mode, output_stream_operator)
{
  video_mode vm(vec2u(300u, 400u), 8u, 45u);

  const char* output_ref
    = "{resolution = (300, 400), depth_byte_count = 8, refresh_rate = 45}";
  EXPECT_OUTPUT(output_ref, vm);
}
