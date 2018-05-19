// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_vertex_array_handle.hpp"

using namespace hou;



namespace
{

class test_gl_vertex_array_handle : public test_gl_multiple_contexts
{};

class test_gl_vertex_array_handle_death_test
  : public test_gl_vertex_array_handle
{};

}  // namespace



TEST_F(test_gl_vertex_array_handle, Creation)
{
  gl::vertex_array_handle vah = gl::vertex_array_handle::create();
  EXPECT_NE(0u, vah.get_name());
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_vertex_array_handle_death_test, no_context_creation)
#else
TEST_F(test_gl_vertex_array_handle_death_test, DISABLED_no_context_creation)
#endif
{
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::vertex_array_handle::create(), gl::missing_context_error);
}



TEST_F(test_gl_vertex_array_handle, tracking)
{
  gl::vertex_array_handle vah1 = gl::vertex_array_handle::create();

  {
    set_sharing_context_current();
    gl::vertex_array_handle vah2 = gl::vertex_array_handle::create();

    set_context_current();
    EXPECT_EQ(0u, gl::get_bound_vertex_array_name());
    EXPECT_FALSE(gl::is_vertex_array_bound(vah1));
    EXPECT_FALSE(gl::is_vertex_array_bound());

    gl::bind_vertex_array(vah1);
    EXPECT_EQ(vah1.get_name(), gl::get_bound_vertex_array_name());
    EXPECT_TRUE(gl::is_vertex_array_bound(vah1));
    EXPECT_TRUE(gl::is_vertex_array_bound());

    set_sharing_context_current();
    EXPECT_EQ(0u, gl::get_bound_vertex_array_name());
    EXPECT_FALSE(gl::is_vertex_array_bound(vah2));
    EXPECT_FALSE(gl::is_vertex_array_bound());

    gl::bind_vertex_array(vah2);
    EXPECT_EQ(vah2.get_name(), gl::get_bound_vertex_array_name());
    EXPECT_TRUE(gl::is_vertex_array_bound(vah2));
    EXPECT_TRUE(gl::is_vertex_array_bound());

    set_context_current();
    EXPECT_EQ(vah1.get_name(), gl::get_bound_vertex_array_name());
    EXPECT_TRUE(gl::is_vertex_array_bound(vah1));
    EXPECT_TRUE(gl::is_vertex_array_bound());

    gl::unbind_vertex_array();
    EXPECT_EQ(0u, gl::get_bound_vertex_array_name());
    EXPECT_FALSE(gl::is_vertex_array_bound(vah1));
    EXPECT_FALSE(gl::is_vertex_array_bound());

    set_sharing_context_current();
  }
  set_context_current();
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_vertex_array_handle_death_test, sharing_context_binding)
#else
TEST_F(test_gl_vertex_array_handle_death_test, DISABLED_sharing_context_binding)
#endif
{
  gl::vertex_array_handle vah = gl::vertex_array_handle::create();
  set_sharing_context_current();
  EXPECT_ERROR_0(gl::bind_vertex_array(vah), gl::invalid_context_error);
  set_context_current();
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_vertex_array_handle_death_test, non_sharing_context_binding)
#else
TEST_F(
  test_gl_vertex_array_handle_death_test, DISABLED_non_sharing_context_binding)
#endif
{
  gl::vertex_array_handle vah = gl::vertex_array_handle::create();
  set_non_sharing_context_current();
  EXPECT_ERROR_0(gl::bind_vertex_array(vah), gl::invalid_context_error);
  set_context_current();
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_vertex_array_handle_death_test, no_context_binding)
#else
TEST_F(test_gl_vertex_array_handle_death_test, DISABLED_no_context_binding)
#endif
{
  gl::vertex_array_handle vah = gl::vertex_array_handle::create();
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::bind_vertex_array(vah), gl::missing_context_error);
  set_context_current();
}
