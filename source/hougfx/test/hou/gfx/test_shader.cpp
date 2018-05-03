// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/shader.hpp"

#include "hou/gl/gl_error.hpp"

using namespace hou;



namespace
{

class test_shader : public test_gfx_base {};

class test_shader_death_test : public test_shader {};

std::string get_fs_source();
std::string get_gs_source();
std::string get_vs_source();



// clang-format off
std::string get_fs_source()
{
  return
    "#version 330 core\n"
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
  return
    "#version 330 core\n"
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
  return
    "#version 330 core\n"
    "in vec2 pos;"
    "void main()"
    "{"
    "    gl_Position = vec4(pos, 0.0, 1.0);"
    "}";
}
// clang-format on

}



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
  const char vs_src[] = "I like trains.";
  DEPRECATED_HOU_EXPECT_ERROR(vertex_shader vs(vs_src), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , to_string(shader_type::vertex).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
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
  const char fs_src[] = "I like trains.";
  DEPRECATED_HOU_EXPECT_ERROR(fragment_shader vs(fs_src), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , to_string(shader_type::fragment).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(test_shader, gl_geometry_shader_creation)
{
  geometry_shader gs(get_gs_source());
  SUCCEED();
}



TEST_F(test_shader, gl_geometry_shader_move_constructor)
{
  geometry_shader gs_dummy = geometry_shader(get_gs_source());
  geometry_shader gs = std::move(gs_dummy);
  SUCCEED();
}



TEST_F(test_shader_death_test, gl_geometry_shader_creation)
{
  const char gs_src[] = "I like trains.";
  DEPRECATED_HOU_EXPECT_ERROR(geometry_shader vs(gs_src), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , to_string(shader_type::geometry).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}

