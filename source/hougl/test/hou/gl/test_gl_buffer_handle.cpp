// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/gl_buffer_handle.hpp"
#include "hou/gl/gl_error.hpp"

using namespace hou;



namespace
{

class TestGlBufferHandle: public test_gl_multiple_contexts {};
class TestGlBufferHandleDeathTest : public TestGlBufferHandle {};

}



TEST_F(TestGlBufferHandle, Creation)
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  EXPECT_NE(0u, bh.get_name());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlBufferHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlBufferHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::buffer_handle::create(), std::logic_error
    , get_text(gl_error::context_existence));
}



TEST_F(TestGlBufferHandle, Tracking)
{
  gl::buffer_handle bh1 = gl::buffer_handle::create();
  gl::buffer_handle bh2 = gl::buffer_handle::create();

  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ELEMENT_ARRAY_BUFFER));

  gl::bind_buffer(bh1, GL_ARRAY_BUFFER);
  EXPECT_EQ(bh1.get_name(), gl::get_bound_buffer_name(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_TRUE(gl::is_buffer_bound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_TRUE(gl::is_buffer_bound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ELEMENT_ARRAY_BUFFER));

  setSharingContextCurrent();
  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ELEMENT_ARRAY_BUFFER));

  gl::bind_buffer(bh2, GL_ELEMENT_ARRAY_BUFFER);
  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ARRAY_BUFFER));
  EXPECT_EQ(bh2.get_name(), gl::get_bound_buffer_name(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ARRAY_BUFFER));
  EXPECT_TRUE(gl::is_buffer_bound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ARRAY_BUFFER));
  EXPECT_TRUE(gl::is_buffer_bound(GL_ELEMENT_ARRAY_BUFFER));

  setContextCurrent();
  EXPECT_EQ(bh1.get_name(), gl::get_bound_buffer_name(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_TRUE(gl::is_buffer_bound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_TRUE(gl::is_buffer_bound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ELEMENT_ARRAY_BUFFER));

  gl::unbind_buffer(GL_ARRAY_BUFFER);
  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ARRAY_BUFFER));
  EXPECT_EQ(0u, gl::get_bound_buffer_name(GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh1, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(bh2, GL_ELEMENT_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ARRAY_BUFFER));
  EXPECT_FALSE(gl::is_buffer_bound(GL_ELEMENT_ARRAY_BUFFER));
}



TEST_F(TestGlBufferHandle, SharingContextBinding)
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  setSharingContextCurrent();
  gl::bind_buffer(bh, GL_ARRAY_BUFFER);
  EXPECT_TRUE(gl::is_buffer_bound(bh, GL_ARRAY_BUFFER));
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlBufferHandleDeathTest, NonSharingContextBinding)
#else
TEST_F(TestGlBufferHandleDeathTest, DISABLED_NonSharingContextBinding)
#endif
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bind_buffer(bh, GL_ARRAY_BUFFER)
    , std::logic_error, get_text(gl_error::invalid_ownership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlBufferHandleDeathTest, NoContextBinding)
#else
TEST_F(TestGlBufferHandleDeathTest, DISABLED_NoContextBinding)
#endif
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::bind_buffer(bh, GL_ARRAY_BUFFER)
    , std::logic_error, get_text(gl_error::context_existence));
  setContextCurrent();
}




