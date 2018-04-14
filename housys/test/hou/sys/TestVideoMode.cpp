// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/sys/VideoMode.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestVideoMode : public Test {};

}



TEST_F(TestVideoMode, Constructor)
{
  VideoMode v(Vec2u(1200u, 400u), 8u);
  EXPECT_EQ(8u, v.getBytesPerPixel());
  EXPECT_EQ(Vec2u(1200u, 400u), v.getResolution());
}



TEST_F(TestVideoMode, FullscreenModeCheck)
{
  std::vector<VideoMode> vmodes = VideoMode::getFullscreenModes();
  for(const auto& mode : vmodes)
  {
    EXPECT_TRUE(mode.isFullscreenMode());
  }
  VideoMode notFullscreenMode(Vec2u(0u, 0u), 0u);
  EXPECT_FALSE(notFullscreenMode.isFullscreenMode());
}



TEST_F(TestVideoMode, DesktopModeIsFullscreen)
{
  EXPECT_TRUE(VideoMode::getDesktopMode().isFullscreenMode());
}



TEST_F(TestVideoMode, ComparisonOperators)
{
  VideoMode v0(Vec2u(640u, 320u), 4u);
  VideoMode v1(Vec2u(640u, 320u), 4u);
  VideoMode v2(Vec2u(800u, 320u), 4u);
  VideoMode v3(Vec2u(640u, 320u), 8u);

  EXPECT_TRUE(v0 == v1);
  EXPECT_FALSE(v0 == v2);
  EXPECT_FALSE(v0 == v3);

  EXPECT_FALSE(v0 != v1);
  EXPECT_TRUE(v0 != v2);
  EXPECT_TRUE(v0 != v3);
}



TEST_F(TestVideoMode, OrderingOperators)
{
  VideoMode v0(Vec2u(640u, 320u), 4u);
  VideoMode v1(Vec2u(640u, 600u), 4u);
  VideoMode v2(Vec2u(800u, 320u), 4u);
  VideoMode v3(Vec2u(800u, 600u), 4u);
  VideoMode v4(Vec2u(640u, 320u), 8u);
  VideoMode v5(Vec2u(640u, 600u), 8u);
  VideoMode v6(Vec2u(800u, 320u), 8u);
  VideoMode v7(Vec2u(800u, 600u), 8u);
  VideoMode v8(v0);

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



TEST_F(TestVideoMode, OutputStreamOperator)
{
  VideoMode vm(Vec2u(300u, 400u), 8u);
  const char* outputRef = "{Resolution = (300, 400), BytesPerPixel = 64}";
  HOU_EXPECT_OUTPUT(outputRef, vm);
}

