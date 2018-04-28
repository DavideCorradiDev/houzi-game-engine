// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlMultipleContexts.hpp"

#include "hou/gl/GlError.hpp"
#include "hou/gl/GlFramebufferHandle.hpp"

using namespace hou;



namespace
{

class TestGlFramebufferHandle : public TestGlMultipleContexts {};
class TestGlFramebufferHandleDeathTest : public TestGlFramebufferHandle {};

}



TEST_F(TestGlFramebufferHandle, Creation)
{
  gl::FramebufferHandle fbh = gl::FramebufferHandle::create();
  EXPECT_NE(0u, fbh.getName());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlFramebufferHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlFramebufferHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::FramebufferHandle::create(), std::logic_error
    , get_text(GlError::ContextExistence));
}



TEST_F(TestGlFramebufferHandle, Tracking)
{
  gl::FramebufferHandle fbh1 = gl::FramebufferHandle::create();
  gl::FramebufferHandle fbh2 = gl::FramebufferHandle::create();

  EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_DRAW_FRAMEBUFFER));
  EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(fbh1, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(fbh1, GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(fbh2, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(fbh2, GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(GL_READ_FRAMEBUFFER));

  gl::bindFramebuffer(fbh1, GL_DRAW_FRAMEBUFFER);
  EXPECT_EQ(fbh1.getName(), gl::getBoundFramebufferName(GL_DRAW_FRAMEBUFFER));
  EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_READ_FRAMEBUFFER));
  EXPECT_TRUE(gl::isFramebufferBound(fbh1, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(fbh1, GL_READ_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(fbh2, GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(fbh2, GL_READ_FRAMEBUFFER));
  EXPECT_TRUE(gl::isFramebufferBound(GL_DRAW_FRAMEBUFFER));
  EXPECT_FALSE(gl::isFramebufferBound(GL_READ_FRAMEBUFFER));

  {
    setSharingContextCurrent();
    gl::FramebufferHandle fbh3 = gl::FramebufferHandle::create();
    gl::FramebufferHandle fbh4 = gl::FramebufferHandle::create();

    EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh3, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh3, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh4, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh4, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(GL_READ_FRAMEBUFFER));

    gl::bindFramebuffer(fbh4);
    EXPECT_EQ(fbh4.getName(), gl::getBoundFramebufferName(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(fbh4.getName(), gl::getBoundFramebufferName(GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh3, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh3, GL_READ_FRAMEBUFFER));
    EXPECT_TRUE(gl::isFramebufferBound(fbh4, GL_DRAW_FRAMEBUFFER));
    EXPECT_TRUE(gl::isFramebufferBound(fbh4, GL_READ_FRAMEBUFFER));
    EXPECT_TRUE(gl::isFramebufferBound(GL_DRAW_FRAMEBUFFER));
    EXPECT_TRUE(gl::isFramebufferBound(GL_READ_FRAMEBUFFER));

    gl::unbindFramebuffer();
    EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh3, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh3, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh4, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh4, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(GL_READ_FRAMEBUFFER));

    setContextCurrent();
    EXPECT_EQ(fbh1.getName(), gl::getBoundFramebufferName(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_READ_FRAMEBUFFER));
    EXPECT_TRUE(gl::isFramebufferBound(fbh1, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh1, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh2, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh2, GL_READ_FRAMEBUFFER));
    EXPECT_TRUE(gl::isFramebufferBound(GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(GL_READ_FRAMEBUFFER));

    gl::unbindFramebuffer(GL_DRAW_FRAMEBUFFER);
    EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_DRAW_FRAMEBUFFER));
    EXPECT_EQ(0u, gl::getBoundFramebufferName(GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh1, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh1, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh2, GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(fbh2, GL_READ_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(GL_DRAW_FRAMEBUFFER));
    EXPECT_FALSE(gl::isFramebufferBound(GL_READ_FRAMEBUFFER));

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
  gl::FramebufferHandle fbh = gl::FramebufferHandle::create();
  setSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bindFramebuffer(fbh, GL_DRAW_FRAMEBUFFER)
    , std::logic_error, get_text(GlError::InvalidOwnership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlFramebufferHandleDeathTest, NonSharingContextBinding)
#else
TEST_F(TestGlFramebufferHandleDeathTest, DISABLED_NonSharingContextBinding)
#endif
{
  gl::FramebufferHandle fbh = gl::FramebufferHandle::create();
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bindFramebuffer(fbh, GL_DRAW_FRAMEBUFFER)
    , std::logic_error, get_text(GlError::InvalidOwnership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlFramebufferHandleDeathTest, NoContextBinding)
#else
TEST_F(TestGlFramebufferHandleDeathTest, DISABLED_NoContextBinding)
#endif
{
  gl::FramebufferHandle fbh = gl::FramebufferHandle::create();
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::bindFramebuffer(fbh, GL_DRAW_FRAMEBUFFER)
    , std::logic_error, get_text(GlError::ContextExistence));
  setContextCurrent();
}

