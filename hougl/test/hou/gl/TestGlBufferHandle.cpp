// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlMultipleContexts.hpp"

#include "hou/gl/GlBufferHandle.hpp"
#include "hou/gl/GlError.hpp"

using namespace hou;



namespace
{

class TestGlBufferHandle: public TestGlMultipleContexts {};
class TestGlBufferHandleDeathTest : public TestGlBufferHandle {};

}



TEST_F(TestGlBufferHandle, Creation)
{
  gl::BufferHandle bh = gl::BufferHandle::create();
  EXPECT_NE(0u, bh.getName());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlBufferHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlBufferHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::BufferHandle::create(), std::logic_error
    , getText(GlError::ContextExistence));
}



TEST_F(TestGlBufferHandle, Tracking)
{
  gl::BufferHandle bh1 = gl::BufferHandle::create();
  gl::BufferHandle bh2 = gl::BufferHandle::create();

  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ELEMENT_ARRAY_BUFFER));

  gl::bindBuffer(bh1, GL_ARRAY_BUFFER);
  EXPECT_EQ(bh1.getName(), gl::getBoundBufferName(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_TRUE(gl::isBufferBound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_TRUE(gl::isBufferBound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ELEMENT_ARRAY_BUFFER));

  setSharingContextCurrent();
  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ELEMENT_ARRAY_BUFFER));

  gl::bindBuffer(bh2, GL_ELEMENT_ARRAY_BUFFER);
  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ARRAY_BUFFER));
  EXPECT_EQ(bh2.getName(), gl::getBoundBufferName(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ARRAY_BUFFER));
  EXPECT_TRUE(gl::isBufferBound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ARRAY_BUFFER));
  EXPECT_TRUE(gl::isBufferBound(GL_ELEMENT_ARRAY_BUFFER));

  setContextCurrent();
  EXPECT_EQ(bh1.getName(), gl::getBoundBufferName(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_TRUE(gl::isBufferBound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_TRUE(gl::isBufferBound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ELEMENT_ARRAY_BUFFER));

  gl::unbindBuffer(GL_ARRAY_BUFFER);
  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::getBoundBufferName(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::isBufferBound(GL_ELEMENT_ARRAY_BUFFER));
}



TEST_F(TestGlBufferHandle, SharingContextBinding)
{
  gl::BufferHandle bh = gl::BufferHandle::create();
  setSharingContextCurrent();
  gl::bindBuffer(bh, GL_ARRAY_BUFFER);
  EXPECT_TRUE(gl::isBufferBound(bh, GL_ARRAY_BUFFER));
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlBufferHandleDeathTest, NonSharingContextBinding)
#else
TEST_F(TestGlBufferHandleDeathTest, DISABLED_NonSharingContextBinding)
#endif
{
  gl::BufferHandle bh = gl::BufferHandle::create();
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bindBuffer(bh, GL_ARRAY_BUFFER)
    , std::logic_error, getText(GlError::InvalidOwnership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlBufferHandleDeathTest, NoContextBinding)
#else
TEST_F(TestGlBufferHandleDeathTest, DISABLED_NoContextBinding)
#endif
{
  gl::BufferHandle bh = gl::BufferHandle::create();
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::bindBuffer(bh, GL_ARRAY_BUFFER)
    , std::logic_error, getText(GlError::ContextExistence));
  setContextCurrent();
}




