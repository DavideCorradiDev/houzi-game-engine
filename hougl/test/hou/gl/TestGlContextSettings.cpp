// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gl/GlContextSettings.hpp"

using namespace hou;



TEST(TestGlContextSettings, Creation)
{
  gl::ContextSettings cs(
    gl::Version(4u, 5u), gl::ContextProfile::Core, 3u, 1u, 0u);

  EXPECT_EQ(gl::Version(4u, 5u), cs.getVersion());
  EXPECT_EQ(gl::ContextProfile::Core, cs.getProfile());
  EXPECT_EQ(3u, cs.getDepthByteCount());
  EXPECT_EQ(1u, cs.getStencilByteCount());
  EXPECT_EQ(0u, cs.getAntialiasingLevel());
}



TEST(TestGlContextSettings, SettersAndGetters)
{
  gl::ContextSettings cs(
    gl::Version(4u, 5u), gl::ContextProfile::Core, 3u, 1u, 0u);

  cs.setVersion(gl::Version(3u, 4u));
  EXPECT_EQ(gl::Version(3u, 4u), cs.getVersion());

  cs.setProfile(gl::ContextProfile::Compatibility);
  EXPECT_EQ(gl::ContextProfile::Compatibility, cs.getProfile());

  cs.setDepthByteCount(2u);
  EXPECT_EQ(2u, cs.getDepthByteCount());

  cs.setStencilByteCount(2u);
  EXPECT_EQ(2u, cs.getStencilByteCount());

  cs.setAntialiasingLevel(4u);
  EXPECT_EQ(4u, cs.getAntialiasingLevel());
}



TEST(TestGlContextSettings, Comparison)
{
  gl::ContextSettings cs1(
    gl::Version(4u, 5u), gl::ContextProfile::Core, 3u, 1u, 0u);
  gl::ContextSettings cs2(
    gl::Version(3u, 5u), gl::ContextProfile::Core, 3u, 1u, 0u);
  gl::ContextSettings cs3(
    gl::Version(4u, 5u), gl::ContextProfile::Compatibility, 3u, 1u, 0u);
  gl::ContextSettings cs4(
    gl::Version(4u, 5u), gl::ContextProfile::Core, 32, 1u, 0u);
  gl::ContextSettings cs5(
    gl::Version(4u, 5u), gl::ContextProfile::Core, 3u, 0u, 0u);
  gl::ContextSettings cs6(
    gl::Version(4u, 5u), gl::ContextProfile::Core, 3u, 1u, 4u);
  gl::ContextSettings cs7(
    gl::Version(4u, 5u), gl::ContextProfile::Core, 3u, 1u, 0u);

  EXPECT_TRUE(cs1 != cs2);
  EXPECT_TRUE(cs1 != cs3);
  EXPECT_TRUE(cs1 != cs4);
  EXPECT_TRUE(cs1 != cs5);
  EXPECT_TRUE(cs1 != cs6);
  EXPECT_TRUE(cs1 == cs7);

  EXPECT_FALSE(cs1 == cs2);
  EXPECT_FALSE(cs1 == cs3);
  EXPECT_FALSE(cs1 == cs4);
  EXPECT_FALSE(cs1 == cs5);
  EXPECT_FALSE(cs1 == cs6);
  EXPECT_FALSE(cs1 != cs7);
}



TEST(TestGlContextSettings, DefaultSettings)
{
  gl::ContextSettings csRef(
    gl::Version::Default, gl::ContextProfile::Core, 3u, 1u, 0u);
  EXPECT_EQ(csRef, gl::ContextSettings::Default);
}
