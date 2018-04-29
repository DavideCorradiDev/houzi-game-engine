// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlMultipleContexts.hpp"

#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_framebuffer_handle.hpp"

using namespace hou;



namespace
{

class TestGlFramebufferHandle : public TestGlMultipleContexts {};
class TestGlFramebufferHandleDeathTest : public TestGlFramebufferHandle {};

}



TEST_F(TestGlFramebufferHandle, Creation)
{
  gl::framebuffer_handle fbh = gl::framebuffer_handle::create();
  EXPECT_NE(0u, fbh.get_name());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlFramebufferHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlFramebufferHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::framebuffer_handle::create(), std::logic_error
    , get_text(gl_error::context_existence));
}



TEST_F(TestGlFramebufferHandle, Tracking)
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
  EXPECT_EQ(fbh1.get_name(), gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
  EXPECT_EQ(0u, gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
  EXPECT_TRUE(gl::is_framebuffer_bound(fbh1, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh1, GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(fbh2, GL_READ_FRAMEBUFFER));
  EXPECT_TRUE(gl::is_framebuffer_bound(GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::is_framebuffer_bound(GL_READ_FRAMEBUFFER));

  {
    setSharingContextCurrent();
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
    EXPECT_EQ(fbh4.get_name(), gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(fbh4.get_name(), gl::get_bound_framebuffer_name(GL_READ_FRAMEBUFFER));
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

    setContextCurrent();
    EXPECT_EQ(fbh1.get_name(), gl::get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER));
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

    setSharingContextCurrent();
  }
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlFramebufferHandleDeathTest, SharingContextBinding)
#else
TEST_F(TestGlFramebufferHandleDeathTest, DISABLED_SharingContextBinding)
#endif
{
  gl::framebuffer_handle fbh = gl::framebuffer_handle::create();
  setSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bind_framebuffer(fbh, GL_DRAW_FRAMEBUFFER)
    , std::logic_error, get_text(gl_error::invalid_ownership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlFramebufferHandleDeathTest, NonSharingContextBinding)
#else
TEST_F(TestGlFramebufferHandleDeathTest, DISABLED_NonSharingContextBinding)
#endif
{
  gl::framebuffer_handle fbh = gl::framebuffer_handle::create();
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bind_framebuffer(fbh, GL_DRAW_FRAMEBUFFER)
    , std::logic_error, get_text(gl_error::invalid_ownership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlFramebufferHandleDeathTest, NoContextBinding)
#else
TEST_F(TestGlFramebufferHandleDeathTest, DISABLED_NoContextBinding)
#endif
{
  gl::framebuffer_handle fbh = gl::framebuffer_handle::create();
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::bind_framebuffer(fbh, GL_DRAW_FRAMEBUFFER)
    , std::logic_error, get_text(gl_error::context_existence));
  setContextCurrent();
}

