// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlSingleContext.hpp"

#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_functions.hpp"

#include "hou/sys/video_mode.hpp"
#include "hou/sys/system_window.hpp"

using namespace hou;



namespace
{

class TestGlFunctions : public TestGlSingleContext
{};
class TestGlFunctionsDeathTest : public TestGlFunctions
{};

}  // namespace



TEST_F(TestGlFunctions, VerticalSync)
{
  gl::set_vertical_sync_mode(gl::vertical_sync_mode::disabled);
  gl::set_vertical_sync_mode(gl::vertical_sync_mode::enabled);
  SUCCEED();
}



TEST_F(TestGlFunctions, UnpackAlignment)
{
  gl::set_unpack_alignment(1);
  EXPECT_EQ(1, gl::get_unpack_alignment());
  gl::set_unpack_alignment(4);
  EXPECT_EQ(4, gl::get_unpack_alignment());
}



TEST_F(TestGlFunctionsDeathTest, InvalidUnpackAlignment)
{
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  HOU_EXPECT_ERROR(gl::set_unpack_alignment(3), std::logic_error,
    get_text(gl_error::invalid_value));
#else
  SUCCEED();
#endif
}



TEST_F(TestGlFunctions, PackAlignment)
{
  gl::set_pack_alignment(1);
  EXPECT_EQ(1, gl::get_pack_alignment());
  gl::set_pack_alignment(4);
  EXPECT_EQ(4, gl::get_pack_alignment());
}



TEST_F(TestGlFunctionsDeathTest, InvalidPackAlignment)
{
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  HOU_EXPECT_ERROR(
    gl::set_pack_alignment(3), std::logic_error, get_text(gl_error::invalid_value));
#else
  SUCCEED();
#endif
}



TEST_F(TestGlFunctions, get_pixel_size_bytes)
{
  EXPECT_EQ(1, gl::get_pixel_size_bytes(GL_RED));
  EXPECT_EQ(2, gl::get_pixel_size_bytes(GL_RG));
  EXPECT_EQ(3, gl::get_pixel_size_bytes(GL_RGB));
  EXPECT_EQ(3, gl::get_pixel_size_bytes(GL_BGR));
  EXPECT_EQ(4, gl::get_pixel_size_bytes(GL_RGBA));
  EXPECT_EQ(4, gl::get_pixel_size_bytes(GL_BGRA));
}



TEST_F(TestGlFunctions, ComputeTextureSizeBytes)
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



TEST_F(TestGlFunctions, BindWindow)
{
  ASSERT_TRUE(mContext.is_current());
  system_window w("Test", video_mode(vec2u(40u, 30u), 32u), window_style::windowed);
  gl::bind_window(w);
  EXPECT_TRUE(mContext.is_current());
}



TEST_F(TestGlFunctions, EnableBlending)
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



TEST_F(TestGlFunctions, GetBlendingFactors)
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



TEST_F(TestGlFunctions, EnableMultisampling)
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
