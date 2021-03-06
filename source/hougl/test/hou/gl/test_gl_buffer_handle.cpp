// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/gl_buffer_handle.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"

using namespace hou;



namespace
{

class test_gl_buffer_handle : public test_gl_multiple_contexts
{};

using test_gl_buffer_handle_death_test = test_gl_buffer_handle;

}  // namespace



TEST_F(test_gl_buffer_handle, creation)
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  EXPECT_NE(0u, bh.get_name());
}



TEST_F(test_gl_buffer_handle_death_test, no_context_creation)
{
#if !defined(HOU_ENABLE_GL_ERROR_CHECKS)
  SKIP("GL error checks are disabled in this build.");
#endif
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multiple GL contexts are not supported on Emscripten.");
#endif
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::buffer_handle::create(), gl::missing_context_error);
}



TEST_F(test_gl_buffer_handle, binding)
{
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multiple GL contexts are not supported on Emscripten.");
#endif
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

  set_sharing_context_current();
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

  set_context_current();
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



TEST_F(test_gl_buffer_handle, sharing_context_binding)
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  set_sharing_context_current();
  gl::bind_buffer(bh, GL_ARRAY_BUFFER);
  EXPECT_TRUE(gl::is_buffer_bound(bh, GL_ARRAY_BUFFER));
}



TEST_F(test_gl_buffer_handle_death_test, non_sharing_context_binding)
{
#if !defined(HOU_ENABLE_GL_ERROR_CHECKS)
  SKIP("GL error checks are disabled in this build.");
#endif
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multiple GL contexts are not supported on Emscripten.");
#endif
  gl::buffer_handle bh = gl::buffer_handle::create();
  set_non_sharing_context_current();
  EXPECT_ERROR_0(
    gl::bind_buffer(bh, GL_ARRAY_BUFFER), gl::invalid_context_error);
  set_context_current();
}



TEST_F(test_gl_buffer_handle_death_test, no_context_binding)
{
#if !defined(HOU_ENABLE_GL_ERROR_CHECKS)
  SKIP("GL error checks are disabled in this build.");
#endif
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multiple GL contexts are not supported on Emscripten.");
#endif
  gl::buffer_handle bh = gl::buffer_handle::create();
  gl::context::unset_current();
  EXPECT_ERROR_0(
    gl::bind_buffer(bh, GL_ARRAY_BUFFER), gl::missing_context_error);
  set_context_current();
}
