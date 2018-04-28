// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlMultipleContexts.hpp"

#include "hou/gl/GlVertexArrayHandle.hpp"
#include "hou/gl/GlError.hpp"

using namespace hou;



namespace
{

class TestGlVertexArrayHandle: public TestGlMultipleContexts {};
class TestGlVertexArrayHandleDeathTest : public TestGlVertexArrayHandle {};

}



TEST_F(TestGlVertexArrayHandle, Creation)
{
  gl::VertexArrayHandle vah = gl::VertexArrayHandle::create();
  EXPECT_NE(0u, vah.getName());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlVertexArrayHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlVertexArrayHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::VertexArrayHandle::create(), std::logic_error
    , get_text(GlError::ContextExistence));
}



TEST_F(TestGlVertexArrayHandle, Tracking)
{
  gl::VertexArrayHandle vah1 = gl::VertexArrayHandle::create();

  {
    setSharingContextCurrent();
    gl::VertexArrayHandle vah2 = gl::VertexArrayHandle::create();

    setContextCurrent();
    EXPECT_EQ(0u, gl::getBoundVertexArrayName());
    EXPECT_FALSE(gl::isVertexArrayBound(vah1));
    EXPECT_FALSE(gl::isVertexArrayBound());

    gl::bindVertexArray(vah1);
    EXPECT_EQ(vah1.getName(), gl::getBoundVertexArrayName());
    EXPECT_TRUE(gl::isVertexArrayBound(vah1));
    EXPECT_TRUE(gl::isVertexArrayBound());

    setSharingContextCurrent();
    EXPECT_EQ(0u, gl::getBoundVertexArrayName());
    EXPECT_FALSE(gl::isVertexArrayBound(vah2));
    EXPECT_FALSE(gl::isVertexArrayBound());

    gl::bindVertexArray(vah2);
    EXPECT_EQ(vah2.getName(), gl::getBoundVertexArrayName());
    EXPECT_TRUE(gl::isVertexArrayBound(vah2));
    EXPECT_TRUE(gl::isVertexArrayBound());

    setContextCurrent();
    EXPECT_EQ(vah1.getName(), gl::getBoundVertexArrayName());
    EXPECT_TRUE(gl::isVertexArrayBound(vah1));
    EXPECT_TRUE(gl::isVertexArrayBound());

    gl::unbindVertexArray();
    EXPECT_EQ(0u, gl::getBoundVertexArrayName());
    EXPECT_FALSE(gl::isVertexArrayBound(vah1));
    EXPECT_FALSE(gl::isVertexArrayBound());

    setSharingContextCurrent();
  }
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlVertexArrayHandleDeathTest, SharingContextBinding)
#else
TEST_F(TestGlVertexArrayHandleDeathTest, DISABLED_SharingContextBinding)
#endif
{
  gl::VertexArrayHandle vah = gl::VertexArrayHandle::create();
  setSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bindVertexArray(vah), std::logic_error
    , get_text(GlError::InvalidOwnership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlVertexArrayHandleDeathTest, NonSharingContextBinding)
#else
TEST_F(TestGlVertexArrayHandleDeathTest, DISABLED_NonSharingContextBinding)
#endif
{
  gl::VertexArrayHandle vah = gl::VertexArrayHandle::create();
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bindVertexArray(vah), std::logic_error
    , get_text(GlError::InvalidOwnership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlVertexArrayHandleDeathTest, NoContextBinding)
#else
TEST_F(TestGlVertexArrayHandleDeathTest, DISABLED_NoContextBinding)
#endif
{
  gl::VertexArrayHandle vah = gl::VertexArrayHandle::create();
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::bindVertexArray(vah), std::logic_error
    , get_text(GlError::ContextExistence));
  setContextCurrent();
}

