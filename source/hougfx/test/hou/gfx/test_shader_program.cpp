// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/shader.hpp"
#include "hou/gfx/shader_program.hpp"

#include "hou/gl/gl_error.hpp"

using namespace hou;



namespace
{

class test_shader_program : public test_gfx_base
{};

class test_shader_program_death_test : public test_shader_program
{};

class concrete_shader_program : public shader_program
{
public:
  using shader_program::shader_program;
};



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

}  // namespace



TEST_F(test_shader_program, binding)
{
  vertex_shader vs(get_vs_source());
  fragment_shader fs(get_fs_source());
  concrete_shader_program p1(vs, fs);
  concrete_shader_program p2(vs, fs);

  EXPECT_FALSE(p1.is_bound());
  EXPECT_FALSE(p2.is_bound());

  concrete_shader_program::bind(p1);
  EXPECT_TRUE(p1.is_bound());
  EXPECT_FALSE(p2.is_bound());

  concrete_shader_program::bind(p2);
  EXPECT_FALSE(p1.is_bound());
  EXPECT_TRUE(p2.is_bound());

  concrete_shader_program::unbind();
  EXPECT_FALSE(p1.is_bound());
  EXPECT_FALSE(p2.is_bound());
}



TEST_F(test_shader_program, constructor_without_gl_geometry_shader)
{
  vertex_shader vs(get_vs_source());
  fragment_shader fs(get_fs_source());
  concrete_shader_program p(vs, fs);
  EXPECT_NE(0u, p.get_handle().get_name());
}



TEST_F(test_shader_program, constructor_with_gl_geometry_shader)
{
  vertex_shader vs(get_vs_source());
  geometry_shader gs(get_gs_source());
  fragment_shader fs(get_fs_source());
  concrete_shader_program p(vs, fs, gs);
  EXPECT_NE(0u, p.get_handle().get_name());
}



TEST_F(test_shader_program, move_constructor)
{
  vertex_shader vs(get_vs_source());
  geometry_shader gs(get_gs_source());
  fragment_shader fs(get_fs_source());
  concrete_shader_program p_dummy(vs, fs, gs);
  uint programId = p_dummy.get_handle().get_name();
  concrete_shader_program p = std::move(p_dummy);
  EXPECT_EQ(programId, p.get_handle().get_name());
  EXPECT_EQ(0u, p_dummy.get_handle().get_name());
}



TEST_F(test_shader_program, get_uniform_location)
{
  vertex_shader vs(get_vs_source());
  geometry_shader gs(get_gs_source());
  fragment_shader fs(get_fs_source());
  concrete_shader_program p(vs, fs, gs);
  EXPECT_EQ(0u, p.get_uniform_location("colorUni"));
}



TEST_F(test_shader_program_death_test, get_uniform_location_invalid_name)
{
  vertex_shader vs(get_vs_source());
  geometry_shader gs(get_gs_source());
  fragment_shader fs(get_fs_source());
  concrete_shader_program p(vs, fs, gs);
  std::string invalidName = "trololol";
  DEPRECATED_HOU_EXPECT_ERROR(p.get_uniform_location(invalidName), std::runtime_error,
    format_string(
      get_text(gl_error::program_invalid_uniform), invalidName.c_str()));
}



TEST_F(test_shader_program_death_test, constructor_error_link_failure)
{
  vertex_shader vs(get_vs_source());
  geometry_shader gs(get_vs_source());
  fragment_shader fs(get_fs_source());
  DEPRECATED_HOU_EXPECT_ERROR(concrete_shader_program(vs, fs, gs), std::runtime_error,
    format_string(get_text(gl_error::program_linking),
      "Geometry info\n"
      "-------------\n"
      "(0) : error C6022: No input primitive type\n"
      "(0) : error C6029: No output primitive type\n"));
}
