// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/test_gl_shader_sources.hpp"

#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_shader_handle.hpp"

using namespace hou;



namespace
{

class test_gl_shader_handle : public test_gl_multiple_contexts
{};

class test_gl_shader_handle_death_test : public test_gl_shader_handle
{};

}  // namespace



TEST_F(test_gl_shader_handle, creation)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_VERTEX_SHADER);
  EXPECT_NE(0u, sh.get_name());
  EXPECT_EQ(static_cast<GLenum>(GL_VERTEX_SHADER), sh.get_type());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(test_gl_shader_handle_death_test, no_context_creation)
#else
TEST_F(test_gl_shader_handle_death_test, DISABLED_no_context_creation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::shader_handle::create(GL_VERTEX_SHADER),
    std::logic_error, get_text(gl_error::context_existence));
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
  HOU_EXPECT_ERROR(compile_shader(sh, fragmentGlShaderSrc), std::runtime_error,
    format_string(get_text(gl_error::shader_compilation), "fragment",
      "0(1) : error C0000: syntax error, "
      "unexpected '.', expecting \"::\" at token \".\"\n"));
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
  HOU_EXPECT_ERROR(compile_shader(sh, geometryGlShaderSrc), std::runtime_error,
    format_string(get_text(gl_error::shader_compilation), "geometry",
      "0(1) : error C0000: syntax error, "
      "unexpected '.', expecting \"::\" at token \".\"\n"));
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
  HOU_EXPECT_ERROR(compile_shader(sh, vertexGlShaderSrc), std::runtime_error,
    format_string(get_text(gl_error::shader_compilation), "vertex",
      "0(1) : error C0000: syntax error, "
      "unexpected '.', expecting \"::\" at token \".\"\n"));
}
