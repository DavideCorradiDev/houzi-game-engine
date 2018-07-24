// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_exceptions.hpp"

using namespace hou;



namespace
{

class test_gl_exceptions : public test_gl_single_context
{};

using test_gl_exceptions_death_test = test_gl_exceptions;

}  // namespace



TEST_F(test_gl_exceptions, vsync_error)
{
  gl::vsync_error ex("foo.cpp", 42u, "Unsupported.");
  EXPECT_STREQ(
    "foo.cpp:42 - Failed to set the vertical sync mode.\nUnsupported.",
    ex.what());
}



TEST_F(test_gl_exceptions, shader_compiler_error)
{
  gl::shader_compiler_error ex_vertex(
    "foo.cpp", 42u, GL_VERTEX_SHADER, "Error.");
  EXPECT_STREQ("foo.cpp:42 - Error compiling OpenGL vertex shader:\nError.",
    ex_vertex.what());

  gl::shader_compiler_error ex_geometry(
    "foo.cpp", 42u, GL_GEOMETRY_SHADER, "Error.");
  EXPECT_STREQ("foo.cpp:42 - Error compiling OpenGL geometry shader:\nError.",
    ex_geometry.what());

  gl::shader_compiler_error ex_fragment(
    "foo.cpp", 42u, GL_FRAGMENT_SHADER, "Error.");
  EXPECT_STREQ("foo.cpp:42 - Error compiling OpenGL fragment shader:\nError.",
    ex_fragment.what());

  gl::shader_compiler_error ex_compute(
    "foo.cpp", 42u, GL_COMPUTE_SHADER, "Error.");
  EXPECT_STREQ("foo.cpp:42 - Error compiling OpenGL compute shader:\nError.",
    ex_compute.what());

  gl::shader_compiler_error ex_tess_control(
    "foo.cpp", 42u, GL_TESS_CONTROL_SHADER, "Error.");
  EXPECT_STREQ(
    "foo.cpp:42 - Error compiling OpenGL tesselation control shader:\nError.",
    ex_tess_control.what());

  gl::shader_compiler_error ex_tess_evaluation(
    "foo.cpp", 42u, GL_TESS_EVALUATION_SHADER, "Error.");
  EXPECT_STREQ(
    "foo.cpp:42 - Error compiling OpenGL tesselation evaluation "
    "shader:\nError.",
    ex_tess_evaluation.what());
}



TEST_F(test_gl_exceptions, shader_linker_error)
{
  gl::shader_linker_error ex("foo.cpp", 42u, "Error.");
  EXPECT_STREQ(
    "foo.cpp:42 - Error linking OpenGL shader program:\nError.", ex.what());
}



TEST_F(test_gl_exceptions, invalid_uniform_error)
{
  gl::invalid_uniform_error ex("foo.cpp", 42u, "uniform_name");
  EXPECT_STREQ(
    "foo.cpp:42 - The uniform 'uniform_name' was not defined in the shader "
    "program.",
    ex.what());
}



TEST_F(test_gl_exceptions, call_error)
{
  gl::call_error ex0("foo.cpp", 42u, GL_CONTEXT_LOST);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 1287: context lost.", ex0.what());

  gl::call_error ex1("foo.cpp", 42u, GL_INVALID_ENUM);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 1280: invalid enum.", ex1.what());

  gl::call_error ex2("foo.cpp", 42u, GL_INVALID_FRAMEBUFFER_OPERATION);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 1286: invalid framebuffer operation.",
    ex2.what());

  gl::call_error ex3("foo.cpp", 42u, GL_INVALID_OPERATION);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 1282: invalid operation.", ex3.what());

  gl::call_error ex4("foo.cpp", 42u, GL_INVALID_VALUE);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 1281: invalid value.", ex4.what());

  gl::call_error ex5("foo.cpp", 42u, GL_OUT_OF_MEMORY);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 1285: out of memory.", ex5.what());

  gl::call_error ex6("foo.cpp", 42u, GL_STACK_OVERFLOW);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 1283: stack overflow.", ex6.what());

  gl::call_error ex7("foo.cpp", 42u, GL_STACK_UNDERFLOW);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 1284: stack underflow.", ex7.what());

  gl::call_error ex9("foo.cpp", 42u, 0);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenGL error with code 0: unknown error.", ex9.what());
}



TEST_F(test_gl_exceptions, gl_check_error_function_success)
{
  glClear(GL_COLOR_BUFFER_BIT);
  EXPECT_NO_ERROR(gl::check_error("", 0));
}



TEST_F(test_gl_exceptions_death_test, gl_check_error_function_failure)
{
  glClear(GL_COLOR);
  EXPECT_ERROR_N(gl::check_error("", 0), gl::call_error, GL_INVALID_VALUE);
}



TEST_F(test_gl_exceptions, gl_check_error_macro_success)
{
  glClear(GL_COLOR_BUFFER_BIT);
  EXPECT_NO_ERROR(HOU_GL_CHECK_ERROR());
}



TEST_F(test_gl_exceptions_death_test, gl_check_error_macro_failure)
{
  glClear(GL_COLOR);
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  EXPECT_ERROR_N(HOU_GL_CHECK_ERROR(), gl::call_error, GL_INVALID_VALUE);
#else
  EXPECT_NO_ERROR(HOU_GL_CHECK_ERROR());
#endif
}
