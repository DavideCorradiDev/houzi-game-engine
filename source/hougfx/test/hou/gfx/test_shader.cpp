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

class TestShader : public test_gfx_base {};
class TestShaderDeathTest : public TestShader {};

std::string getFsSource();
std::string getGsSource();
std::string getVsSource();



std::string getFsSource()
{
  return "#version 330 core\n"
    "uniform vec4 colorUni;"
    "out vec4 outColor;"
    "void main()"
    "{"
    "    outColor = colorUni;"
    "}";
}



std::string getGsSource()
{
  return "#version 330 core\n"
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



std::string getVsSource()
{
  return "#version 330 core\n"
    "in vec2 pos;"
    "void main()"
    "{"
    "    gl_Position = vec4(pos, 0.0, 1.0);"
    "}";
}

}



TEST_F(TestShader, GlVertexShaderCreation)
{
  vertex_shader vs(getVsSource());
  SUCCEED();
}



TEST_F(TestShader, GlVertexShaderMoveConstructor)
{
  vertex_shader vsDummy = vertex_shader(getVsSource());
  vertex_shader vs = std::move(vsDummy);
  SUCCEED();
}



TEST_F(TestShaderDeathTest, GlVertexShaderCreation)
{
  const char vertexShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(vertex_shader vs(vertexShaderSrc), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , to_string(shader_type::vertex).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(TestShader, GlFragmentShaderCreation)
{
  fragment_shader fs(getFsSource());
  SUCCEED();
}



TEST_F(TestShader, GlFragmentShaderMoveConstructor)
{
  fragment_shader fsDummy = fragment_shader(getFsSource());
  fragment_shader fs = std::move(fsDummy);
  SUCCEED();
}



TEST_F(TestShaderDeathTest, GlFragmentShaderCreation)
{
  const char fragShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(fragment_shader vs(fragShaderSrc), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , to_string(shader_type::fragment).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(TestShader, GlGeometryShaderCreation)
{
  geometry_shader gs(getGsSource());
  SUCCEED();
}



TEST_F(TestShader, GlGeometryShaderMoveConstructor)
{
  geometry_shader gsDummy = geometry_shader(getGsSource());
  geometry_shader gs = std::move(gsDummy);
  SUCCEED();
}



TEST_F(TestShaderDeathTest, GlGeometryShaderCreation)
{
  const char geometryShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(geometry_shader vs(geometryShaderSrc), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , to_string(shader_type::geometry).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}

