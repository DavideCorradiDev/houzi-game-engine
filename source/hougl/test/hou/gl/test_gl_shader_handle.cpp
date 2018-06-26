// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/test_gl_shader_sources.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_shader_handle.hpp"

using namespace hou;



namespace
{

class test_gl_shader_handle : public test_gl_multiple_contexts
{};

using test_gl_shader_handle_death_test = test_gl_shader_handle;

}  // namespace



TEST_F(test_gl_shader_handle, creation)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_VERTEX_SHADER);
  EXPECT_NE(0u, sh.get_name());
  EXPECT_EQ(static_cast<GLenum>(GL_VERTEX_SHADER), sh.get_type());
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_shader_handle_death_test, no_context_creation)
#else
TEST_F(test_gl_shader_handle_death_test, DISABLED_no_context_creation)
#endif
{
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::shader_handle::create(GL_VERTEX_SHADER),
    gl::missing_context_error);
}



TEST_F(test_gl_shader_handle, compile_fragment_shader)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  compile_shader(sh, get_fs_source().c_str());
  SUCCEED();
}



TEST_F(test_gl_shader_handle_death_test, compile_fragment_shader_failure)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  const char fragmentGlShaderSrc[] = "I like trains.";
  EXPECT_ERROR_N(compile_shader(sh, fragmentGlShaderSrc),
    gl::shader_compiler_error, GL_FRAGMENT_SHADER,
    "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n");
}



TEST_F(test_gl_shader_handle, compile_geometry_shader)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_GEOMETRY_SHADER);
  compile_shader(sh, get_gs_source().c_str());
  SUCCEED();
}



TEST_F(test_gl_shader_handle_death_test, compile_geometry_shader_failure)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_GEOMETRY_SHADER);
  const char geometryGlShaderSrc[] = "I like trains.";
  EXPECT_ERROR_N(compile_shader(sh, geometryGlShaderSrc),
    gl::shader_compiler_error, GL_GEOMETRY_SHADER,
    "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n");
}



TEST_F(test_gl_shader_handle, compile_vertex_shader)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_VERTEX_SHADER);
  compile_shader(sh, get_vs_source().c_str());
  SUCCEED();
}



TEST_F(test_gl_shader_handle_death_test, compile_vertex_shader_failure)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_VERTEX_SHADER);
  const char vertexGlShaderSrc[] = "I like trains.";
  EXPECT_ERROR_N(compile_shader(sh, vertexGlShaderSrc),
    gl::shader_compiler_error, GL_VERTEX_SHADER,
    "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n");
}
