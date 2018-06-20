// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_texture_handle.hpp"

using namespace hou;



namespace
{

class test_gl_texture_handle : public test_gl_multiple_contexts
{};

class test_gl_texture_handle_death_test : public test_gl_texture_handle
{};

}  // namespace



TEST_F(test_gl_texture_handle, creation)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  EXPECT_NE(0u, th.get_name());
  EXPECT_EQ(static_cast<GLenum>(GL_TEXTURE_2D), th.get_target());
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_texture_handle_death_test, no_context_creation)
#else
TEST_F(test_gl_texture_handle_death_test, DISABLED_no_context_creation)
#endif
{
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::texture_handle::create(GL_TEXTURE_2D), gl::missing_context_error);
}



TEST_F(test_gl_texture_handle, tracking)
{
  gl::texture_handle th1 = gl::texture_handle::create(GL_TEXTURE_2D);
  gl::texture_handle th2 = gl::texture_handle::create(GL_TEXTURE_1D);

  gl::set_active_texture(0u);
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(0u, gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::set_active_texture(1u);
  EXPECT_EQ(1u, gl::get_active_texture());
  EXPECT_EQ(0u, gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::set_active_texture(0u);
  gl::bind_texture(th1);
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(th1.get_name(), gl::get_bound_texture_name());
  EXPECT_TRUE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::set_active_texture(1u);
  gl::bind_texture(th2);
  EXPECT_EQ(1u, gl::get_active_texture());
  EXPECT_EQ(th2.get_name(), gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_TRUE(gl::is_texture_bound(th2));

  set_sharing_context_current();
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(0u, gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::bind_texture(th2);
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(th2.get_name(), gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_TRUE(gl::is_texture_bound(th2));

  set_context_current();
  EXPECT_EQ(1u, gl::get_active_texture());
  EXPECT_EQ(th2.get_name(), gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_TRUE(gl::is_texture_bound(th2));

  gl::unbind_texture();
  EXPECT_EQ(1u, gl::get_active_texture());
  EXPECT_EQ(0u, gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::set_active_texture(0u);
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(th1.get_name(), gl::get_bound_texture_name());
  EXPECT_TRUE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));
}



TEST_F(test_gl_texture_handle, unit_tracking)
{
  gl::texture_handle th1 = gl::texture_handle::create(GL_TEXTURE_2D);
  gl::texture_handle th2 = gl::texture_handle::create(GL_TEXTURE_1D);

  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_FALSE(gl::is_texture_bound(th2, 2));

  gl::bind_texture(th1, 0);
  EXPECT_TRUE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_FALSE(gl::is_texture_bound(th2, 2));

  gl::bind_texture(th2, 2);
  EXPECT_TRUE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));

  set_sharing_context_current();
  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_FALSE(gl::is_texture_bound(th2, 2));

  gl::bind_texture(th2, 2);
  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));

  set_context_current();
  EXPECT_TRUE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));

  gl::bind_texture(th2, 0);
  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_TRUE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));

  gl::unbind_texture(0);
  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));
}



TEST_F(test_gl_texture_handle, sharing_context_binding)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_1D);
  set_sharing_context_current();
  gl::bind_texture(th);
  EXPECT_TRUE(is_texture_bound(th));
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_texture_handle_death_test, non_sharing_context_binding)
#else
TEST_F(test_gl_texture_handle_death_test, DISABLED_non_sharing_context_binding)
#endif
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_1D);
  set_non_sharing_context_current();
  EXPECT_ERROR_0(gl::bind_texture(th), gl::invalid_context_error);
  set_context_current();
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_texture_handle_death_test, no_context_binding)
#else
TEST_F(test_gl_texture_handle_death_test, DISABLED_no_context_binding)
#endif
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_1D);
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::bind_texture(th), gl::missing_context_error);
  set_context_current();
}



TEST_F(test_gl_texture_handle, min_filter)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  gl::set_texture_min_filter(th, static_cast<GLenum>(GL_NEAREST));
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST), gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_LINEAR);
  EXPECT_EQ(static_cast<GLenum>(GL_LINEAR), gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_NEAREST_MIPMAP_NEAREST);
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST_MIPMAP_NEAREST),
    gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_NEAREST_MIPMAP_LINEAR);
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST_MIPMAP_LINEAR),
    gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_LINEAR_MIPMAP_NEAREST);
  EXPECT_EQ(static_cast<GLenum>(GL_LINEAR_MIPMAP_NEAREST),
    gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_LINEAR_MIPMAP_LINEAR);
  EXPECT_EQ(static_cast<GLenum>(GL_LINEAR_MIPMAP_LINEAR),
    gl::get_texture_min_filter(th));
}



TEST_F(test_gl_texture_handle, mag_filter)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  gl::set_texture_mag_filter(th, GL_NEAREST);
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST), gl::get_texture_mag_filter(th));

  gl::set_texture_mag_filter(th, GL_LINEAR);
  EXPECT_EQ(static_cast<GLenum>(GL_LINEAR), gl::get_texture_mag_filter(th));
}



TEST_F(test_gl_texture_handle, swizzle_r)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_RED), gl::get_texture_swizzle_r(th));
  gl::set_texture_swizzle_r(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_texture_swizzle_r(th));
}



TEST_F(test_gl_texture_handle, swizzle_g)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_GREEN), gl::get_texture_swizzle_g(th));
  gl::set_texture_swizzle_g(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_texture_swizzle_g(th));
}



TEST_F(test_gl_texture_handle, swizzle_b)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_BLUE), gl::get_texture_swizzle_b(th));
  gl::set_texture_swizzle_b(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_texture_swizzle_b(th));
}



TEST_F(test_gl_texture_handle, swizzle_a)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_ALPHA), gl::get_texture_swizzle_a(th));
  gl::set_texture_swizzle_a(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_texture_swizzle_a(th));
}



TEST_F(test_gl_texture_handle, swizzle_rgba)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  std::array<GLenum, 4u> swizzle;
  std::array<GLenum, 4u> swizzle_ref;

  swizzle_ref = {
    GL_RED,
    GL_GREEN,
    GL_BLUE,
    GL_ALPHA,
  };
  gl::get_texture_swizzle(th, swizzle.data());
  EXPECT_EQ(swizzle_ref, swizzle);

  swizzle_ref = {
    GL_ONE,
    GL_GREEN,
    GL_ZERO,
    GL_RED,
  };
  gl::set_texture_swizzle(th, swizzle_ref.data());
  gl::get_texture_swizzle(th, swizzle.data());
  EXPECT_EQ(swizzle_ref, swizzle);
}



TEST_F(test_gl_texture_handle, texture_wrap_mode_s)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::get_texture_wrap_mode_s(th));
  gl::set_texture_wrap_mode_s(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(
    static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::get_texture_wrap_mode_s(th));
}



TEST_F(test_gl_texture_handle, texture_wrap_mode_t)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::get_texture_wrap_mode_t(th));
  gl::set_texture_wrap_mode_t(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(
    static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::get_texture_wrap_mode_t(th));
}



TEST_F(test_gl_texture_handle, texture_wrap_mode_r)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::get_texture_wrap_mode_r(th));
  gl::set_texture_wrap_mode_r(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(
    static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::get_texture_wrap_mode_r(th));
}
