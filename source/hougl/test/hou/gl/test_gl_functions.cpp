// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"

#include "hou/sys/window.hpp"

using namespace hou;



namespace
{

class test_gl_functions : public test_gl_single_context
{};

using test_gl_functions_death_test = test_gl_functions;

}  // namespace



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
  EXPECT_ERROR_N(gl::set_unpack_alignment(3), gl::call_error, GL_INVALID_VALUE);
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
  EXPECT_ERROR_N(gl::set_pack_alignment(3), gl::call_error, GL_INVALID_VALUE);
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
