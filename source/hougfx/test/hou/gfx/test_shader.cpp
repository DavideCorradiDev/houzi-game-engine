// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/shader.hpp"

#include "hou/gl/gl_exceptions.hpp"

using namespace hou;



namespace
{

class test_shader : public test_gfx_base
{};

using test_shader_death_test = test_shader;

std::string get_gl_version_shader_string();
std::string get_fs_source();
std::string get_gs_source();
std::string get_vs_source();



std::string get_gl_version_shader_string()
{
  if(gl::context::get_current()->get_settings().get_profile()
    == hou::gl::context_profile::es)
  {
    return "#version 300 es\n"
           "precision highp float;\n";
  }
  else
  {
    return "#version 450 core\n";
  }
}




// clang-format off
std::string get_fs_source()
{
  return get_gl_version_shader_string() +
    "uniform vec4 colorUni;"
    "out vec4 outColor;"
    "void main()"
    "{"
    "    outColor = colorUni;"
    "}";
}
// clang-format on



// clang-format off
std::string get_gs_source()
{
  return get_gl_version_shader_string() +
    "layout(points) in;"
    "layout(line_strip, max_vertices = 2) out;"
    "void main()"
    "{"
    "  gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);"
    "  EmitVertex();"
    "  gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);"
    "  EmitVertex();"
    "  EndPrimitive();"
    "}";
}
// clang-format on



// clang-format off
std::string get_vs_source()
{
  return get_gl_version_shader_string() +
    "in vec2 pos;"
    "void main()"
    "{"
    "    gl_Position = vec4(pos, 0.0, 1.0);"
    "}";
}
// clang-format on

}  // namespace



TEST_F(test_shader, gl_vertex_shader_creation)
{
  vertex_shader vs(get_vs_source());
  SUCCEED();
}



TEST_F(test_shader, gl_vertex_shader_move_constructor)
{
  vertex_shader vs_dummy = vertex_shader(get_vs_source());
  vertex_shader vs = std::move(vs_dummy);
  SUCCEED();
}



TEST_F(test_shader_death_test, gl_vertex_shader_creation)
{
#if defined(HOU_GL_ES)
  const char error_msg[] = "ERROR: 0:1: 'I' : syntax error\n";
#else
  const char error_msg[] = "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n";
#endif
  const char vs_src[] = "I like trains.";
  EXPECT_ERROR_N(vertex_shader vs(vs_src), gl::shader_compiler_error,
    static_cast<GLenum>(shader_type::vertex), error_msg);
}



TEST_F(test_shader, gl_fragment_shader_creation)
{
  fragment_shader fs(get_fs_source());
  SUCCEED();
}



TEST_F(test_shader, gl_fragment_shader_move_constructor)
{
  fragment_shader fs_dummy = fragment_shader(get_fs_source());
  fragment_shader fs = std::move(fs_dummy);
  SUCCEED();
}



TEST_F(test_shader_death_test, gl_fragment_shader_creation)
{
#if defined(HOU_GL_ES)
  const char error_msg[] = "ERROR: 0:1: 'I' : syntax error\n";
#else
  const char error_msg[] = "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n";
#endif
  const char fs_src[] = "I like trains.";
  EXPECT_ERROR_N(fragment_shader vs(fs_src), gl::shader_compiler_error,
    static_cast<GLenum>(shader_type::fragment), error_msg);
}



TEST_F(test_shader, gl_geometry_shader_creation)
{
  SKIP_IF(gl::context::get_current()->get_settings().get_profile()
      == gl::context_profile::es,
    "Geometry shaders are not supported in GLES.");

  geometry_shader gs(get_gs_source());
  SUCCEED();
}



TEST_F(test_shader, gl_geometry_shader_move_constructor)
{
  SKIP_IF(gl::context::get_current()->get_settings().get_profile()
      == gl::context_profile::es,
    "Geometry shaders are not supported in GLES.");

  geometry_shader gs_dummy = geometry_shader(get_gs_source());
  geometry_shader gs = std::move(gs_dummy);
  SUCCEED();
}



TEST_F(test_shader_death_test, gl_geometry_shader_creation)
{
  SKIP_IF(gl::context::get_current()->get_settings().get_profile()
      == gl::context_profile::es,
    "Geometry shaders are not supported in GLES.");

  const char gs_src[] = "I like trains.";
  EXPECT_ERROR_N(geometry_shader vs(gs_src), gl::shader_compiler_error,
    static_cast<GLenum>(shader_type::geometry),
    "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n");
}
