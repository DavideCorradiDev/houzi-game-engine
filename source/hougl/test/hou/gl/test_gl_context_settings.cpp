// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_settings.hpp"
#include "hou/test.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_gl_context_settings : public Test
{};

}  // namespace



TEST_F(test_gl_context_settings, constructor)
{
  gl::context_settings cs(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

  EXPECT_EQ(gl::version(4u, 5u), cs.get_version());
  EXPECT_EQ(gl::context_profile::core, cs.get_profile());
  EXPECT_EQ(3u, cs.get_depth_bit_count());
  EXPECT_EQ(1u, cs.get_stencil_bit_count());
  EXPECT_EQ(0u, cs.get_sample_count());
}



TEST_F(test_gl_context_settings, set_version)
{
  gl::context_settings cs(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

  cs.set_version(gl::version(3u, 4u));
  EXPECT_EQ(gl::version(3u, 4u), cs.get_version());
}



TEST_F(test_gl_context_settings, set_profile)
{
  gl::context_settings cs(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

  cs.set_profile(gl::context_profile::compatibility);
  EXPECT_EQ(gl::context_profile::compatibility, cs.get_profile());
}



TEST_F(test_gl_context_settings, set_depth_bit_count)
{
  gl::context_settings cs(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

  cs.set_depth_bit_count(2u);
  EXPECT_EQ(2u, cs.get_depth_bit_count());
}



TEST_F(test_gl_context_settings, set_stencil_bit_count)
{
  gl::context_settings cs(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

  cs.set_stencil_bit_count(2u);
  EXPECT_EQ(2u, cs.get_stencil_bit_count());
}



TEST_F(test_gl_context_settings, set_sample_count)
{
  gl::context_settings cs(
    gl::version(4u, 5u), gl::context_profile::core, 3u, 1u, 0u);

  cs.set_sample_count(4u);
  EXPECT_EQ(4u, cs.get_sample_count());
}



TEST_F(test_gl_context_settings, comparison)
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



TEST_F(test_gl_context_settings, output_stream_operator)
{
  gl::context_settings cs(
    gl::version(3u, 4u), gl::context_profile::compatibility, 24u, 8u, 2u);
  const char* out_ref
    = "{gl_version = 3.4, gl_profile = compatibility, depth_bit_count = 24, "
      "stencil_bit_count = 8, sample_count = 2}";
  EXPECT_OUTPUT(out_ref, cs);
}



TEST_F(test_gl_context_settings, get_basic)
{
  gl::context_settings cs_ref(
    gl::version(1u, 0u), gl::context_profile::compatibility, 24u, 8u, 0u);
  EXPECT_EQ(cs_ref, gl::context_settings::get_basic());
}



TEST_F(test_gl_context_settings, get_default)
{
  gl::context_settings cs_ref(
    gl::version(4u, 5u), gl::context_profile::core, 24u, 8u, 0u);
  EXPECT_EQ(cs_ref, gl::context_settings::get_default());
}
