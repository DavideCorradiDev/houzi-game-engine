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
  gl::context_settings cs;

  EXPECT_EQ(gl::version(4u, 5u), cs.get_version());
  EXPECT_EQ(gl::context_profile::core, cs.get_profile());
  EXPECT_EQ(gl::color_format(8u, 8u, 8u, 0u), cs.get_color_format());
  EXPECT_EQ(24u, cs.get_depth_bit_count());
  EXPECT_EQ(8u, cs.get_stencil_bit_count());
  EXPECT_EQ(0u, cs.get_multisample_buffer_count());
  EXPECT_EQ(0u, cs.get_sample_count());
  EXPECT_TRUE(cs.double_buffer());
  EXPECT_TRUE(cs.srgb_capable());
  EXPECT_FALSE(cs.stereo());
  EXPECT_FALSE(cs.debug_mode());
  EXPECT_FALSE(cs.forward_compatibility_mode());
  EXPECT_FALSE(cs.robust_access());
  EXPECT_FALSE(cs.reset_isolation());
}



TEST_F(test_gl_context_settings, set_version)
{
  gl::context_settings cs;
  EXPECT_EQ(gl::version(4u, 5u), cs.get_version());
  cs.set_version(gl::version(3u, 4u));
  EXPECT_EQ(gl::version(3u, 4u), cs.get_version());
}



TEST_F(test_gl_context_settings, set_profile)
{
  gl::context_settings cs;
  EXPECT_EQ(gl::context_profile::core, cs.get_profile());
  cs.set_profile(gl::context_profile::compatibility);
  EXPECT_EQ(gl::context_profile::compatibility, cs.get_profile());
}



TEST_F(test_gl_context_settings, set_color_format)
{
  gl::context_settings cs;
  EXPECT_EQ(gl::color_format(8u, 8u, 8u, 0u), cs.get_color_format());
  cs.set_color_format(gl::color_format(1u, 2u, 3u, 4u));
  EXPECT_EQ(gl::color_format(1u, 2u, 3u, 4u), cs.get_color_format());
}



TEST_F(test_gl_context_settings, set_depth_bit_count)
{
  gl::context_settings cs;
  EXPECT_EQ(24u, cs.get_depth_bit_count());
  cs.set_depth_bit_count(2u);
  EXPECT_EQ(2u, cs.get_depth_bit_count());
}



TEST_F(test_gl_context_settings, set_stencil_bit_count)
{
  gl::context_settings cs;
  EXPECT_EQ(8u, cs.get_stencil_bit_count());
  cs.set_stencil_bit_count(2u);
  EXPECT_EQ(2u, cs.get_stencil_bit_count());
}



TEST_F(test_gl_context_settings, set_multisample_buffer_count)
{
  gl::context_settings cs;
  cs.set_multisample_buffer_count(4u);
  EXPECT_EQ(4u, cs.get_multisample_buffer_count());
}



TEST_F(test_gl_context_settings, set_sample_count)
{
  gl::context_settings cs;
  cs.set_sample_count(4u);
  EXPECT_EQ(4u, cs.get_sample_count());
}



TEST_F(test_gl_context_settings, set_double_buffer)
{
  gl::context_settings cs;
  EXPECT_TRUE(cs.double_buffer());
  cs.set_double_buffer(false);
  EXPECT_FALSE(cs.double_buffer());
}



TEST_F(test_gl_context_settings, set_srgb_capable)
{
  gl::context_settings cs;
  EXPECT_TRUE(cs.srgb_capable());
  cs.set_srgb_capable(false);
  EXPECT_FALSE(cs.srgb_capable());
}



TEST_F(test_gl_context_settings, set_stereo)
{
  gl::context_settings cs;
  EXPECT_FALSE(cs.stereo());
  cs.set_stereo(true);
  EXPECT_TRUE(cs.stereo());
}




TEST_F(test_gl_context_settings, set_forward_compatibility_mode)
{
  gl::context_settings cs;
  EXPECT_FALSE(cs.forward_compatibility_mode());
  cs.set_forward_compatibility_mode(true);
  EXPECT_TRUE(cs.forward_compatibility_mode());
}



TEST_F(test_gl_context_settings, set_robust_access)
{
  gl::context_settings cs;
  EXPECT_FALSE(cs.robust_access());
  cs.set_robust_access(true);
  EXPECT_TRUE(cs.robust_access());
}



TEST_F(test_gl_context_settings, set_reset_isolation)
{
  gl::context_settings cs;
  EXPECT_FALSE(cs.reset_isolation());
  cs.set_reset_isolation(true);
  EXPECT_TRUE(cs.reset_isolation());
}



TEST_F(test_gl_context_settings, comparison)
{
  gl::context_settings cs0;
  gl::context_settings cs1;
  gl::context_settings cs2;
  cs2.set_version(gl::version(1u, 0u));
  gl::context_settings cs3;
  cs3.set_profile(gl::context_profile::compatibility);
  gl::context_settings cs4;
  cs4.set_color_format(gl::color_format(1u, 2u, 3u, 4u));
  gl::context_settings cs5;
  cs5.set_depth_bit_count(8u);
  gl::context_settings cs6;
  cs6.set_stencil_bit_count(4u);
  gl::context_settings cs7;
  cs7.set_multisample_buffer_count(2u);
  gl::context_settings cs8;
  cs8.set_sample_count(1u);
  gl::context_settings cs9;
  cs9.set_double_buffer(false);
  gl::context_settings cs10;
  cs10.set_srgb_capable(false);
  gl::context_settings cs11;
  cs11.set_stereo(true);
  gl::context_settings cs12;
  cs12.set_debug_mode(true);
  gl::context_settings cs13;
  cs13.set_forward_compatibility_mode(true);
  gl::context_settings cs14;
  cs14.set_robust_access(true);
  gl::context_settings cs15;
  cs15.set_reset_isolation(true);

  EXPECT_TRUE(cs0 == cs1);
  EXPECT_FALSE(cs0 == cs2);
  EXPECT_FALSE(cs0 == cs3);
  EXPECT_FALSE(cs0 == cs4);
  EXPECT_FALSE(cs0 == cs6);
  EXPECT_FALSE(cs0 == cs7);
  EXPECT_FALSE(cs0 == cs8);
  EXPECT_FALSE(cs0 == cs9);
  EXPECT_FALSE(cs0 == cs10);
  EXPECT_FALSE(cs0 == cs11);
  EXPECT_FALSE(cs0 == cs12);
  EXPECT_FALSE(cs0 == cs12);
  EXPECT_FALSE(cs0 == cs13);
  EXPECT_FALSE(cs0 == cs14);
  EXPECT_FALSE(cs0 == cs15);

  EXPECT_FALSE(cs0 != cs1);
  EXPECT_TRUE(cs0 != cs2);
  EXPECT_TRUE(cs0 != cs3);
  EXPECT_TRUE(cs0 != cs4);
  EXPECT_TRUE(cs0 != cs6);
  EXPECT_TRUE(cs0 != cs7);
  EXPECT_TRUE(cs0 != cs8);
  EXPECT_TRUE(cs0 != cs9);
  EXPECT_TRUE(cs0 != cs10);
  EXPECT_TRUE(cs0 != cs11);
  EXPECT_TRUE(cs0 != cs12);
  EXPECT_TRUE(cs0 != cs12);
  EXPECT_TRUE(cs0 != cs13);
  EXPECT_TRUE(cs0 != cs14);
  EXPECT_TRUE(cs0 != cs15);
}



TEST_F(test_gl_context_settings, output_stream_operator)
{
  gl::context_settings cs;
  const char* out_ref
    = "{gl_version = 4.5, "
      "gl_profile = core, "
      "color_format = {red_bit_count = 8, green_bit_count = 8, blue_bit_count "
      "= 8, alpha_bit_count = 0}, "
      "depth_bit_count = 24, "
      "stencil_bit_count = 8, "
      "multisample_buffer_count = 0, "
      "sample_count = 0, "
      "double_buffer = true, "
      "srgb_capable = true, "
      "stereo = false, "
      "debug_mode = false, "
      "forward_compatibility_mode = false, "
      "robust_access = false, "
      "reset_isolation = false}";
  EXPECT_OUTPUT(out_ref, cs);
}



TEST_F(test_gl_context_settings, get_basic)
{
  gl::context_settings cs = gl::context_settings::get_basic();
  EXPECT_EQ(gl::version(1u, 0u), cs.get_version());
  EXPECT_EQ(gl::context_profile::any, cs.get_profile());
  EXPECT_EQ(gl::color_format(3u, 3u, 2u, 0u), cs.get_color_format());
  EXPECT_EQ(16u, cs.get_depth_bit_count());
  EXPECT_EQ(0u, cs.get_stencil_bit_count());
  EXPECT_EQ(0u, cs.get_multisample_buffer_count());
  EXPECT_EQ(0u, cs.get_sample_count());
  EXPECT_TRUE(cs.double_buffer());
  EXPECT_FALSE(cs.srgb_capable());
  EXPECT_FALSE(cs.stereo());
  EXPECT_FALSE(cs.debug_mode());
  EXPECT_FALSE(cs.forward_compatibility_mode());
  EXPECT_FALSE(cs.robust_access());
  EXPECT_FALSE(cs.reset_isolation());
}



TEST_F(test_gl_context_settings, get_default_core)
{
  gl::context_settings cs = gl::context_settings::get_default_core();
  EXPECT_EQ(gl::version(4u, 5u), cs.get_version());
  EXPECT_EQ(gl::context_profile::core, cs.get_profile());
  EXPECT_EQ(gl::color_format(8u, 8u, 8u, 0u), cs.get_color_format());
  EXPECT_EQ(24u, cs.get_depth_bit_count());
  EXPECT_EQ(8u, cs.get_stencil_bit_count());
  EXPECT_EQ(0u, cs.get_multisample_buffer_count());
  EXPECT_EQ(0u, cs.get_sample_count());
  EXPECT_TRUE(cs.double_buffer());
  EXPECT_TRUE(cs.srgb_capable());
  EXPECT_FALSE(cs.stereo());
  EXPECT_FALSE(cs.debug_mode());
  EXPECT_FALSE(cs.forward_compatibility_mode());
  EXPECT_FALSE(cs.robust_access());
  EXPECT_FALSE(cs.reset_isolation());
}



TEST_F(test_gl_context_settings, get_default_es)
{
  gl::context_settings cs = gl::context_settings::get_default_es();
  EXPECT_EQ(gl::version(3u, 2u), cs.get_version());
  EXPECT_EQ(gl::context_profile::es, cs.get_profile());
  EXPECT_EQ(gl::color_format(8u, 8u, 8u, 0u), cs.get_color_format());
  EXPECT_EQ(24u, cs.get_depth_bit_count());
  EXPECT_EQ(8u, cs.get_stencil_bit_count());
  EXPECT_EQ(0u, cs.get_multisample_buffer_count());
  EXPECT_EQ(0u, cs.get_sample_count());
  EXPECT_TRUE(cs.double_buffer());
  EXPECT_FALSE(cs.srgb_capable());
  EXPECT_FALSE(cs.stereo());
  EXPECT_FALSE(cs.debug_mode());
  EXPECT_FALSE(cs.forward_compatibility_mode());
  EXPECT_FALSE(cs.robust_access());
  EXPECT_FALSE(cs.reset_isolation());
}



TEST_F(test_gl_context_settings, get_default)
{
#if defined(HOU_GL_ES)
  EXPECT_EQ(gl::context_settings::get_default_es(),
    gl::context_settings::get_default());
#else
  EXPECT_EQ(gl::context_settings::get_default_core(),
    gl::context_settings::get_default());
#endif
}
