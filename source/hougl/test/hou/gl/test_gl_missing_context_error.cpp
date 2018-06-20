// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_missing_context_error.hpp"

#include "hou/sys/system_window.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_gl_missing_context_error : public Test
{};

using test_gl_missing_context_error_death_test = test_gl_missing_context_error;

}  // namespace



TEST_F(test_gl_missing_context_error, missing_context_error)
{
  gl::missing_context_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - No current OpenGL context.", ex.what());
}



TEST_F(test_gl_missing_context_error, gl_context_existence_function_success)
{
  system_window w("Test", vec2u(16u, 8u));
  gl::context ctx(gl::context_settings::get_default(), w);
  gl::context::set_current(ctx, w);
  EXPECT_NO_ERROR(gl::check_context_existence("", 0));
}



TEST_F(test_gl_missing_context_error_death_test,
  gl_context_existence_function_failure)
{
  EXPECT_ERROR_0(gl::check_context_existence("", 0), gl::missing_context_error);
}



TEST_F(test_gl_missing_context_error, gl_context_existence_macro_success)
{
  system_window w("Test", vec2u(16u, 8u));
  gl::context ctx(gl::context_settings::get_default(), w);
  gl::context::set_current(ctx, w);
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_EXISTENCE());
}



TEST_F(
  test_gl_missing_context_error_death_test, gl_context_existence_macro_failure)
{
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_EXISTENCE(), gl::missing_context_error);
#else
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_EXISTENCE());
#endif
}
