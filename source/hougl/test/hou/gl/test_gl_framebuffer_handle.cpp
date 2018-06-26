// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_framebuffer_handle.hpp"

using namespace hou;



namespace
{

class test_gl_framebuffer_handle : public test_gl_multiple_contexts
{};

using test_gl_framebuffer_handle_death_test = test_gl_framebuffer_handle;

}  // namespace



TEST_F(test_gl_framebuffer_handle, creation)
{
  gl::framebuffer_handle fbh = gl::framebuffer_handle::create();
  EXPECT_NE(0u, fbh.get_name());
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_framebuffer_handle_death_test, no_context_creation)
#else
TEST_F(test_gl_framebuffer_handle_death_test, DISABLED_no_context_creation)
#endif
{
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::framebuffer_handle::create(), gl::missing_context_error);
}



TEST_F(test_gl_framebuffer_handle, binding)
{
  gl::framebuffer_handle fbh1 = gl::framebuffer_handle::create();
  gl::framebuffer_handle fbh2 = gl::framebuffer_handle::create();

  EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
  EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh1, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh1, GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(GL_READ_FRAMEBUFFER));

  gl::bind_framebuffer(fbh1, GL_DRAW_FRAMEBUFFER);
  EXPECT_EQ(
    fbh1.get_name(), gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
  EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
  EXPECT_TRUE(gl::is_framebuffer_bound(fbh1, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh1, GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_READ_FRAMEBUFFER));
  EXPECT_TRUE(gl::is_framebuffer_bound(GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(GL_READ_FRAMEBUFFER));

  {
    set_sharing_context_current();
    gl::framebuffer_handle fbh3 = gl::framebuffer_handle::create();
    gl::framebuffer_handle fbh4 = gl::framebuffer_handle::create();

    EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh3, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh3, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh4, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh4, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(GL_READ_FRAMEBUFFER));

    gl::bind_framebuffer(fbh4);
    EXPECT_EQ(
      fbh4.get_name(), gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(
      fbh4.get_name(), gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh3, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh3, GL_READ_FRAMEBUFFER));
    EXPECT_TRUE(gl::is_framebuffer_bound(fbh4, GL_DRAW_FRAMEBUFFER));
    EXPECT_TRUE(gl::is_framebuffer_bound(fbh4, GL_READ_FRAMEBUFFER));
    EXPECT_TRUE(gl::is_framebuffer_bound(GL_DRAW_FRAMEBUFFER));
    EXPECT_TRUE(gl::is_framebuffer_bound(GL_READ_FRAMEBUFFER));

    gl::unbind_framebuffer();
    EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh3, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh3, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh4, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh4, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(GL_READ_FRAMEBUFFER));

    set_context_current();
    EXPECT_EQ(
      fbh1.get_name(), gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
    EXPECT_TRUE(gl::is_framebuffer_bound(fbh1, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh1, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_READ_FRAMEBUFFER));
    EXPECT_TRUE(gl::is_framebuffer_bound(GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(GL_READ_FRAMEBUFFER));

    gl::unbind_framebuffer(GL_DRAW_FRAMEBUFFER);
    EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh1, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh1, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::is_framebuffer_bound(GL_READ_FRAMEBUFFER));

    set_sharing_context_current();
  }
  set_context_current();
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_framebuffer_handle_death_test, sharing_context_binding)
#else
TEST_F(test_gl_framebuffer_handle_death_test, DISABLED_sharing_context_binding)
#endif
{
  gl::framebuffer_handle fbh = gl::framebuffer_handle::create();
  set_sharing_context_current();
  EXPECT_ERROR_0(
    gl::bind_framebuffer(fbh, GL_DRAW_FRAMEBUFFER), gl::invalid_context_error);
  set_context_current();
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_framebuffer_handle_death_test, non_sharing_context_binding)
#else
TEST_F(
  test_gl_framebuffer_handle_death_test, DISABLED_non_sharing_context_binding)
#endif
{
  gl::framebuffer_handle fbh = gl::framebuffer_handle::create();
  set_non_sharing_context_current();
  EXPECT_ERROR_0(
    gl::bind_framebuffer(fbh, GL_DRAW_FRAMEBUFFER), gl::invalid_context_error);
  set_context_current();
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_framebuffer_handle_death_test, no_context_binding)
#else
TEST_F(test_gl_framebuffer_handle_death_test, DISABLED_no_context_binding)
#endif
{
  gl::framebuffer_handle fbh = gl::framebuffer_handle::create();
  gl::context::unset_current();
  EXPECT_ERROR_0(
    gl::bind_framebuffer(fbh, GL_DRAW_FRAMEBUFFER), gl::missing_context_error);
  set_context_current();
}
