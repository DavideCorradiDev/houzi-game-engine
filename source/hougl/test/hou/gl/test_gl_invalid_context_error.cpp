// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_object_handle.hpp"

using namespace hou;



namespace
{

class test_gl_invalid_context_error : public test_gl_single_context
{};

using test_gl_invalid_context_error_death_test = test_gl_invalid_context_error;



class concrete_gl_shared_object_handle : public gl::shared_object_handle
{
public:
  concrete_gl_shared_object_handle(GLuint name)
    : gl::shared_object_handle(name)
  {}
};



class concrete_non_shared_object_handle : public gl::non_shared_object_handle
{
public:
  concrete_non_shared_object_handle(GLuint name)
    : gl::non_shared_object_handle(name)
  {}
};

}  // namespace



TEST_F(test_gl_invalid_context_error, invalid_context_error)
{
  gl::invalid_context_error ex("foo.cpp", 42u);
  EXPECT_STREQ(
    "foo.cpp:42 - The current OpenGL context does not own the object.",
    ex.what());
}



TEST_F(
  test_gl_invalid_context_error, gl_context_ownership_shared_function_success)
{
  system_window w("test", vec2u(1u, 1u));
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_gl_shared_object_handle o1(0u);

  gl::context::set_current(c2, w);
  concrete_gl_shared_object_handle o2(0u);

  gl::context::set_current(c3, w);
  concrete_gl_shared_object_handle o3(0u);

  gl::context::set_current(c1, w);
  EXPECT_NO_ERROR(gl::check_context_ownership(o1, "", 0));
  EXPECT_NO_ERROR(gl::check_context_ownership(o2, "", 0));

  gl::context::set_current(c2, w);
  EXPECT_NO_ERROR(gl::check_context_ownership(o1, "", 0));
  EXPECT_NO_ERROR(gl::check_context_ownership(o2, "", 0));

  gl::context::set_current(c3, w);
  EXPECT_NO_ERROR(gl::check_context_ownership(o3, "", 0));
}



TEST_F(test_gl_invalid_context_error_death_test,
  gl_context_ownership_shared_function_failure)
{
  system_window w("test", vec2u(1u, 1u));
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_gl_shared_object_handle o1(0u);

  gl::context::set_current(c2, w);
  concrete_gl_shared_object_handle o2(0u);

  gl::context::set_current(c3, w);
  concrete_gl_shared_object_handle o3(0u);

  gl::context::set_current(c1, w);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o3, "", 0), gl::invalid_context_error);

  gl::context::set_current(c2, w);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o3, "", 0), gl::invalid_context_error);

  gl::context::set_current(c3, w);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o1, "", 0), gl::invalid_context_error);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o2, "", 0), gl::invalid_context_error);
}



TEST_F(test_gl_invalid_context_error, gl_context_ownership_shared_macro_success)
{
  system_window w("test", vec2u(1u, 1u));
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_gl_shared_object_handle o1(0u);

  gl::context::set_current(c2, w);
  concrete_gl_shared_object_handle o2(0u);

  gl::context::set_current(c3, w);
  concrete_gl_shared_object_handle o3(0u);

  gl::context::set_current(c1, w);
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1));
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2));

  gl::context::set_current(c2, w);
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1));
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2));

  gl::context::set_current(c3, w);
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3));
}



TEST_F(test_gl_invalid_context_error_death_test,
  gl_context_ownership_shared_macro_failure)
{
  system_window w("test", vec2u(1u, 1u));
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_gl_shared_object_handle o1(0u);

  gl::context::set_current(c2, w);
  concrete_gl_shared_object_handle o2(0u);

  gl::context::set_current(c3, w);
  concrete_gl_shared_object_handle o3(0u);

  gl::context::set_current(c1, w);
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), gl::invalid_context_error);
#else
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3));
#endif

  gl::context::set_current(c2, w);
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), gl::invalid_context_error);
#else
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3));
#endif

  gl::context::set_current(c3, w);
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), gl::invalid_context_error);
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), gl::invalid_context_error);
#else
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1));
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2));
#endif
}



TEST_F(test_gl_invalid_context_error,
  gl_context_ownership_non_shared_function_success)
{
  system_window w("test", vec2u(1u, 1u));
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_non_shared_object_handle o1(0u);

  gl::context::set_current(c2, w);
  concrete_non_shared_object_handle o2(0u);

  gl::context::set_current(c3, w);
  concrete_non_shared_object_handle o3(0u);

  gl::context::set_current(c1, w);
  EXPECT_NO_ERROR(gl::check_context_ownership(o1, "", 0));

  gl::context::set_current(c2, w);
  EXPECT_NO_ERROR(gl::check_context_ownership(o2, "", 0));

  gl::context::set_current(c3, w);
  EXPECT_NO_ERROR(gl::check_context_ownership(o3, "", 0));
}



TEST_F(test_gl_invalid_context_error_death_test,
  gl_context_ownership_non_shared_function_failure)
{
  system_window w("test", vec2u(1u, 1u));
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_non_shared_object_handle o1(0u);

  gl::context::set_current(c2, w);
  concrete_non_shared_object_handle o2(0u);

  gl::context::set_current(c3, w);
  concrete_non_shared_object_handle o3(0u);

  gl::context::set_current(c1, w);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o2, "", 0), gl::invalid_context_error);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o3, "", 0), gl::invalid_context_error);

  gl::context::set_current(c2, w);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o1, "", 0), gl::invalid_context_error);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o3, "", 0), gl::invalid_context_error);

  gl::context::set_current(c3, w);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o1, "", 0), gl::invalid_context_error);
  EXPECT_ERROR_0(
    gl::check_context_ownership(o2, "", 0), gl::invalid_context_error);
}



TEST_F(
  test_gl_invalid_context_error, gl_context_ownership_non_shared_macro_success)
{
  system_window w("test", vec2u(1u, 1u));
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_non_shared_object_handle o1(0u);

  gl::context::set_current(c2, w);
  concrete_non_shared_object_handle o2(0u);

  gl::context::set_current(c3, w);
  concrete_non_shared_object_handle o3(0u);

  gl::context::set_current(c1, w);
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1));

  gl::context::set_current(c2, w);
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2));

  gl::context::set_current(c3, w);
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3));
}



TEST_F(test_gl_invalid_context_error_death_test,
  gl_context_ownership_non_shared_macro_failure)
{
  system_window w("test", vec2u(1u, 1u));
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w, c1);
  gl::context c3(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  concrete_non_shared_object_handle o1(0u);

  gl::context::set_current(c2, w);
  concrete_non_shared_object_handle o2(0u);

  gl::context::set_current(c3, w);
  concrete_non_shared_object_handle o3(0u);

  gl::context::set_current(c1, w);
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), gl::invalid_context_error);
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), gl::invalid_context_error);
#else
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2));
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3));
#endif

  gl::context::set_current(c2, w);
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), gl::invalid_context_error);
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), gl::invalid_context_error);
#else
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1));
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3));
#endif

  gl::context::set_current(c3, w);
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), gl::invalid_context_error);
  EXPECT_ERROR_0(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), gl::invalid_context_error);
#else
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1));
  EXPECT_NO_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2));
#endif
}
