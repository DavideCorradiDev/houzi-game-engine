// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/gl_context_settings.hpp"

using namespace hou;



TEST(TestGlContextSettings, Creation)
{
  gl::context_settings cs(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

  EXPECT_EQ(gl::version(4u, 5u), cs.get_version());
  EXPECT_EQ(gl::context_profile::core, cs.get_profile());
  EXPECT_EQ(3u, cs.get_depth_byte_count());
  EXPECT_EQ(1u, cs.get_stencil_byte_count());
  EXPECT_EQ(0u, cs.get_sample_count());
}



TEST(TestGlContextSettings, SettersAndGetters)
{
  gl::context_settings cs(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

  cs.set_version(gl::version(3u, 4u));
  EXPECT_EQ(gl::version(3u, 4u), cs.get_version());

  cs.set_profile(gl::context_profile::compatibility);
  EXPECT_EQ(gl::context_profile::compatibility, cs.get_profile());

  cs.set_depth_byte_count(2u);
  EXPECT_EQ(2u, cs.get_depth_byte_count());

  cs.set_stencil_byte_count(2u);
  EXPECT_EQ(2u, cs.get_stencil_byte_count());

  cs.set_sample_count(4u);
  EXPECT_EQ(4u, cs.get_sample_count());
}



TEST(TestGlContextSettings, Comparison)
{
  gl::context_settings cs1(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);
  gl::context_settings cs2(
    gl::version(3u, 5u), gl::context_profile::core, 3u, 1u, 0u);
  gl::context_settings cs3(
    gl::version(4u, 5u), gl::context_profile::compatibility, 3u, 1u, 0u);
  gl::context_settings cs4(
    gl::version(4u, 5u), gl::context_profile::core, 32, 1u, 0u);
  gl::context_settings cs5(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 0u, 0u);
  gl::context_settings cs6(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 4u);
  gl::context_settings cs7(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

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
  gl::context_settings cs_ref(
    gl::version::standard, gl::context_profile::core, 3u, 1u, 0u);
  EXPECT_EQ(cs_ref, gl::context_settings::standard);
}
