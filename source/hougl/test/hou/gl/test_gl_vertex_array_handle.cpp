// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/gl_vertex_array_handle.hpp"
#include "hou/gl/gl_error.hpp"

using namespace hou;



namespace
{

class TestGlVertexArrayHandle: public test_gl_multiple_contexts {};
class TestGlVertexArrayHandleDeathTest : public TestGlVertexArrayHandle {};

}



TEST_F(TestGlVertexArrayHandle, Creation)
{
  gl::vertex_array_handle vah = gl::vertex_array_handle::create();
  EXPECT_NE(0u, vah.get_name());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlVertexArrayHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlVertexArrayHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::vertex_array_handle::create(), std::logic_error
    , get_text(gl_error::context_existence));
}



TEST_F(TestGlVertexArrayHandle, Tracking)
{
  gl::vertex_array_handle vah1 = gl::vertex_array_handle::create();

  {
    setSharingContextCurrent();
    gl::vertex_array_handle vah2 = gl::vertex_array_handle::create();

    setContextCurrent();
    EXPECT_EQ(0u, gl::get_bound_vertex_array_name());
    EXPECT_FALSE(gl::is_vertex_array_bound(vah1));
    EXPECT_FALSE(gl::is_vertex_array_bound());

    gl::bind_vertex_array(vah1);
    EXPECT_EQ(vah1.get_name(), gl::get_bound_vertex_array_name());
    EXPECT_TRUE(gl::is_vertex_array_bound(vah1));
    EXPECT_TRUE(gl::is_vertex_array_bound());

    setSharingContextCurrent();
    EXPECT_EQ(0u, gl::get_bound_vertex_array_name());
    EXPECT_FALSE(gl::is_vertex_array_bound(vah2));
    EXPECT_FALSE(gl::is_vertex_array_bound());

    gl::bind_vertex_array(vah2);
    EXPECT_EQ(vah2.get_name(), gl::get_bound_vertex_array_name());
    EXPECT_TRUE(gl::is_vertex_array_bound(vah2));
    EXPECT_TRUE(gl::is_vertex_array_bound());

    setContextCurrent();
    EXPECT_EQ(vah1.get_name(), gl::get_bound_vertex_array_name());
    EXPECT_TRUE(gl::is_vertex_array_bound(vah1));
    EXPECT_TRUE(gl::is_vertex_array_bound());

    gl::unbind_vertex_array();
    EXPECT_EQ(0u, gl::get_bound_vertex_array_name());
    EXPECT_FALSE(gl::is_vertex_array_bound(vah1));
    EXPECT_FALSE(gl::is_vertex_array_bound());

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
  gl::vertex_array_handle vah = gl::vertex_array_handle::create();
  setSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bind_vertex_array(vah), std::logic_error
    , get_text(gl_error::invalid_ownership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlVertexArrayHandleDeathTest, NonSharingContextBinding)
#else
TEST_F(TestGlVertexArrayHandleDeathTest, DISABLED_NonSharingContextBinding)
#endif
{
  gl::vertex_array_handle vah = gl::vertex_array_handle::create();
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bind_vertex_array(vah), std::logic_error
    , get_text(gl_error::invalid_ownership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlVertexArrayHandleDeathTest, NoContextBinding)
#else
TEST_F(TestGlVertexArrayHandleDeathTest, DISABLED_NoContextBinding)
#endif
{
  gl::vertex_array_handle vah = gl::vertex_array_handle::create();
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::bind_vertex_array(vah), std::logic_error
    , get_text(gl_error::context_existence));
  setContextCurrent();
}

