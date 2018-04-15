// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/Shader.hpp"

#include "hou/gl/GlError.hpp"

using namespace hou;



namespace
{

class TestShader : public TestGfxBase {};
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
  VertexShader vs(getVsSource());
  SUCCEED();
}



TEST_F(TestShader, GlVertexShaderMoveConstructor)
{
  VertexShader vsDummy = VertexShader(getVsSource());
  VertexShader vs = std::move(vsDummy);
  SUCCEED();
}



TEST_F(TestShaderDeathTest, GlVertexShaderCreation)
{
  const char vertexShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(VertexShader vs(vertexShaderSrc), std::runtime_error
    , formatString(getText(GlError::ShaderCompilation)
    , toString(ShaderType::Vertex).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(TestShader, GlFragmentShaderCreation)
{
  FragmentShader fs(getFsSource());
  SUCCEED();
}



TEST_F(TestShader, GlFragmentShaderMoveConstructor)
{
  FragmentShader fsDummy = FragmentShader(getFsSource());
  FragmentShader fs = std::move(fsDummy);
  SUCCEED();
}



TEST_F(TestShaderDeathTest, GlFragmentShaderCreation)
{
  const char fragShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(FragmentShader vs(fragShaderSrc), std::runtime_error
    , formatString(getText(GlError::ShaderCompilation)
    , toString(ShaderType::Fragment).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(TestShader, GlGeometryShaderCreation)
{
  GeometryShader gs(getGsSource());
  SUCCEED();
}



TEST_F(TestShader, GlGeometryShaderMoveConstructor)
{
  GeometryShader gsDummy = GeometryShader(getGsSource());
  GeometryShader gs = std::move(gsDummy);
  SUCCEED();
}



TEST_F(TestShaderDeathTest, GlGeometryShaderCreation)
{
  const char geometryShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(GeometryShader vs(geometryShaderSrc), std::runtime_error
    , formatString(getText(GlError::ShaderCompilation)
    , toString(ShaderType::Geometry).c_str()
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}

