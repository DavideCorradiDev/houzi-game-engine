// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/video_mode.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_video_mode : public Test
{};

}  // namespace



TEST_F(test_video_mode, constructor)
{
  video_mode v(vec2u(1200u, 400u), 8u);
  EXPECT_EQ(8u, v.get_bytes_per_pixel());
  EXPECT_EQ(vec2u(1200u, 400u), v.get_resolution());
}



TEST_F(test_video_mode, fullscreen_mode_check)
{
  std::vector<video_mode> vmodes = video_mode::get_fullscreen_modes();
  for(const auto& mode : vmodes)
  {
    EXPECT_TRUE(mode.is_fullscreen_mode());
  }
  video_mode notFullscreenMode(vec2u(0u, 0u), 0u);
  EXPECT_FALSE(notFullscreenMode.is_fullscreen_mode());
}



TEST_F(test_video_mode, desktop_mode_is_fullscreen)
{
  EXPECT_TRUE(video_mode::get_desktop_mode().is_fullscreen_mode());
}



TEST_F(test_video_mode, comparison_operators)
{
  video_mode v0(vec2u(640u, 320u), 4u);
  video_mode v1(vec2u(640u, 320u), 4u);
  video_mode v2(vec2u(800u, 320u), 4u);
  video_mode v3(vec2u(640u, 320u), 8u);

  EXPECT_TRUE(v0 == v1);
  EXPECT_FALSE(v0 == v2);
  EXPECT_FALSE(v0 == v3);

  EXPECT_FALSE(v0 != v1);
  EXPECT_TRUE(v0 != v2);
  EXPECT_TRUE(v0 != v3);
}



TEST_F(test_video_mode, ordering_operators)
{
  video_mode v0(vec2u(640u, 320u), 4u);
  video_mode v1(vec2u(640u, 600u), 4u);
  video_mode v2(vec2u(800u, 320u), 4u);
  video_mode v3(vec2u(800u, 600u), 4u);
  video_mode v4(vec2u(640u, 320u), 8u);
  video_mode v5(vec2u(640u, 600u), 8u);
  video_mode v6(vec2u(800u, 320u), 8u);
  video_mode v7(vec2u(800u, 600u), 8u);
  video_mode v8(v0);

  EXPECT_TRUE(v0 < v1);
  EXPECT_TRUE(v1 < v2);
  EXPECT_TRUE(v2 < v3);
  EXPECT_TRUE(v3 < v4);
  EXPECT_TRUE(v4 < v5);
  EXPECT_TRUE(v5 < v6);
  EXPECT_TRUE(v6 < v7);
  EXPECT_FALSE(v7 < v6);
  EXPECT_FALSE(v6 < v5);
  EXPECT_FALSE(v5 < v4);
  EXPECT_FALSE(v4 < v3);
  EXPECT_FALSE(v3 < v2);
  EXPECT_FALSE(v2 < v1);
  EXPECT_FALSE(v1 < v0);
  EXPECT_FALSE(v0 < v8);
  EXPECT_FALSE(v8 < v0);

  EXPECT_TRUE(v0 <= v1);
  EXPECT_TRUE(v1 <= v2);
  EXPECT_TRUE(v2 <= v3);
  EXPECT_TRUE(v3 <= v4);
  EXPECT_TRUE(v4 <= v5);
  EXPECT_TRUE(v5 <= v6);
  EXPECT_TRUE(v6 <= v7);
  EXPECT_FALSE(v7 <= v6);
  EXPECT_FALSE(v6 <= v5);
  EXPECT_FALSE(v5 <= v4);
  EXPECT_FALSE(v4 <= v3);
  EXPECT_FALSE(v3 <= v2);
  EXPECT_FALSE(v2 <= v1);
  EXPECT_FALSE(v1 <= v0);
  EXPECT_TRUE(v0 <= v8);
  EXPECT_TRUE(v8 <= v0);

  EXPECT_FALSE(v0 > v1);
  EXPECT_FALSE(v1 > v2);
  EXPECT_FALSE(v2 > v3);
  EXPECT_FALSE(v3 > v4);
  EXPECT_FALSE(v4 > v5);
  EXPECT_FALSE(v5 > v6);
  EXPECT_FALSE(v6 > v7);
  EXPECT_TRUE(v7 > v6);
  EXPECT_TRUE(v6 > v5);
  EXPECT_TRUE(v5 > v4);
  EXPECT_TRUE(v4 > v3);
  EXPECT_TRUE(v3 > v2);
  EXPECT_TRUE(v2 > v1);
  EXPECT_TRUE(v1 > v0);
  EXPECT_FALSE(v0 > v8);
  EXPECT_FALSE(v8 > v0);

  EXPECT_FALSE(v0 >= v1);
  EXPECT_FALSE(v1 >= v2);
  EXPECT_FALSE(v2 >= v3);
  EXPECT_FALSE(v3 >= v4);
  EXPECT_FALSE(v4 >= v5);
  EXPECT_FALSE(v5 >= v6);
  EXPECT_FALSE(v6 >= v7);
  EXPECT_TRUE(v7 >= v6);
  EXPECT_TRUE(v6 >= v5);
  EXPECT_TRUE(v5 >= v4);
  EXPECT_TRUE(v4 >= v3);
  EXPECT_TRUE(v3 >= v2);
  EXPECT_TRUE(v2 >= v1);
  EXPECT_TRUE(v1 >= v0);
  EXPECT_TRUE(v0 >= v8);
  EXPECT_TRUE(v8 >= v0);
}



TEST_F(test_video_mode, output_stream_operator)
{
  video_mode vm(vec2u(300u, 400u), 8u);
  const char* output_ref = "{resolution = (300, 400), bytes_per_pixel = 8}";
  EXPECT_OUTPUT(output_ref, vm);
}
