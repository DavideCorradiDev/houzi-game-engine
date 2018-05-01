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

class test_gl_buffer_handle: public test_gl_multiple_contexts {};

class test_gl_buffer_handle_death_test : public test_gl_buffer_handle {};

}



TEST_F(test_gl_buffer_handle, creation)
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  EXPECT_NE(0u, bh.get_name());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(test_gl_buffer_handle_death_test, no_context_creation)
#else
TEST_F(test_gl_buffer_handle_death_test, DISABLED_no_context_creation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::buffer_handle::create(), std::logic_error
    , get_text(gl_error::context_existence));
}



TEST_F(test_gl_buffer_handle, tracking)
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



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(test_gl_buffer_handle_death_test, non_sharing_context_binding)
#else
TEST_F(test_gl_buffer_handle_death_test, DISABLED_non_sharing_context_binding)
#endif
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  set_non_sharing_context_current();
  HOU_EXPECT_ERROR(gl::bind_buffer(bh, GL_ARRAY_BUFFER)
    , std::logic_error, get_text(gl_error::invalid_ownership));
  set_context_current();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(test_gl_buffer_handle_death_test, no_context_binding)
#else
TEST_F(test_gl_buffer_handle_death_test, DISABLED_no_context_binding)
#endif
{
  gl::buffer_handle bh = gl::buffer_handle::create();
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::bind_buffer(bh, GL_ARRAY_BUFFER)
    , std::logic_error, get_text(gl_error::context_existence));
  set_context_current();
}




