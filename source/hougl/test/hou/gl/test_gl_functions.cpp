// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_functions.hpp"

#include "hou/sys/video_mode.hpp"
#include "hou/sys/system_window.hpp"

using namespace hou;



namespace
{

class test_gl_functions : public test_gl_single_context
{};

class test_gl_functions_death_test : public test_gl_functions
{};

}  // namespace



TEST_F(test_gl_functions, vertical_sync)
{
  gl::set_vertical_sync_mode(gl::vertical_sync_mode::disabled);
  gl::set_vertical_sync_mode(gl::vertical_sync_mode::enabled);
  SUCCEED();
}



TEST_F(test_gl_functions, unpack_alignment)
{
  gl::set_unpack_alignment(1);
  EXPECT_EQ(1, gl::get_unpack_alignment());
  gl::set_unpack_alignment(4);
  EXPECT_EQ(4, gl::get_unpack_alignment());
}



TEST_F(test_gl_functions_death_test, invalid_unpack_alignment)
{
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  DEPRECATED_HOU_EXPECT_ERROR(gl::set_unpack_alignment(3), std::logic_error,
    get_text(gl_error::invalid_value));
#else
  SUCCEED();
#endif
}



TEST_F(test_gl_functions, pack_alignment)
{
  gl::set_pack_alignment(1);
  EXPECT_EQ(1, gl::get_pack_alignment());
  gl::set_pack_alignment(4);
  EXPECT_EQ(4, gl::get_pack_alignment());
}



TEST_F(test_gl_functions_death_test, invalid_pack_alignment)
{
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  DEPRECATED_HOU_EXPECT_ERROR(
    gl::set_pack_alignment(3), std::logic_error, get_text(gl_error::invalid_value));
#else
  SUCCEED();
#endif
}



TEST_F(test_gl_functions, get_pixel_size_bytes)
{
  EXPECT_EQ(1, gl::get_pixel_size_bytes(GL_RED));
  EXPECT_EQ(2, gl::get_pixel_size_bytes(GL_RG));
  EXPECT_EQ(3, gl::get_pixel_size_bytes(GL_RGB));
  EXPECT_EQ(3, gl::get_pixel_size_bytes(GL_BGR));
  EXPECT_EQ(4, gl::get_pixel_size_bytes(GL_RGBA));
  EXPECT_EQ(4, gl::get_pixel_size_bytes(GL_BGRA));
}



TEST_F(test_gl_functions, compute_texture_size_bytes)
{
  gl::set_unpack_alignment(4);
  EXPECT_EQ(48, gl::compute_texture_size_bytes(7, 3, 2, GL_RED));
  EXPECT_EQ(96, gl::compute_texture_size_bytes(7, 3, 2, GL_RG));
  EXPECT_EQ(144, gl::compute_texture_size_bytes(7, 3, 2, GL_RGB));
  EXPECT_EQ(144, gl::compute_texture_size_bytes(7, 3, 2, GL_BGR));
  EXPECT_EQ(168, gl::compute_texture_size_bytes(7, 3, 2, GL_RGBA));
  EXPECT_EQ(168, gl::compute_texture_size_bytes(7, 3, 2, GL_BGRA));

  gl::set_unpack_alignment(1);
  EXPECT_EQ(42, gl::compute_texture_size_bytes(7, 3, 2, GL_RED));
  EXPECT_EQ(84, gl::compute_texture_size_bytes(7, 3, 2, GL_RG));
  EXPECT_EQ(126, gl::compute_texture_size_bytes(7, 3, 2, GL_RGB));
  EXPECT_EQ(126, gl::compute_texture_size_bytes(7, 3, 2, GL_BGR));
  EXPECT_EQ(168, gl::compute_texture_size_bytes(7, 3, 2, GL_RGBA));
  EXPECT_EQ(168, gl::compute_texture_size_bytes(7, 3, 2, GL_BGRA));
}



TEST_F(test_gl_functions, bind_window)
{
  ASSERT_TRUE(m_context.is_current());
  system_window w("Test", video_mode(vec2u(40u, 30u), 32u), window_style::windowed);
  gl::bind_window(w);
  EXPECT_TRUE(m_context.is_current());
}



TEST_F(test_gl_functions, enable_blending)
{
  EXPECT_FALSE(gl::is_blending_enabled());
  gl::enable_blending();
  EXPECT_TRUE(gl::is_blending_enabled());
  gl::enable_blending();
  EXPECT_TRUE(gl::is_blending_enabled());
  gl::disable_blending();
  EXPECT_FALSE(gl::is_blending_enabled());
  gl::disable_blending();
  EXPECT_FALSE(gl::is_blending_enabled());
}



TEST_F(test_gl_functions, get_blending_factors)
{
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_source_blending());
  EXPECT_EQ(static_cast<GLenum>(GL_ZERO), gl::get_destination_blending());

  gl::set_blending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  EXPECT_EQ(static_cast<GLenum>(GL_SRC_ALPHA), gl::get_source_blending());
  EXPECT_EQ(
    static_cast<GLenum>(GL_ONE_MINUS_SRC_ALPHA), gl::get_destination_blending());

  gl::set_blending(GL_SRC_COLOR, GL_DST_ALPHA);
  EXPECT_EQ(static_cast<GLenum>(GL_SRC_COLOR), gl::get_source_blending());
  EXPECT_EQ(static_cast<GLenum>(GL_DST_ALPHA), gl::get_destination_blending());
}



TEST_F(test_gl_functions, enable_multisampling)
{
  EXPECT_TRUE(gl::is_multisampling_enabled());
  gl::enable_multisampling();
  EXPECT_TRUE(gl::is_multisampling_enabled());
  gl::enable_multisampling();
  EXPECT_TRUE(gl::is_multisampling_enabled());
  gl::disable_multisampling();
  EXPECT_FALSE(gl::is_multisampling_enabled());
  gl::disable_multisampling();
  EXPECT_FALSE(gl::is_multisampling_enabled());
}
