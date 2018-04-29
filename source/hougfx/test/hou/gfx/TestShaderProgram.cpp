// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/Shader.hpp"
#include "hou/gfx/ShaderProgram.hpp"

#include "hou/gl/gl_error.hpp"

using namespace hou;



namespace
{

class TestShaderProgram : public TestGfxBase
{};

class TestShaderProgramDeathTest : public TestShaderProgram
{};

class ConcreteShaderProgram
  : public ShaderProgram
{
public:
  using ShaderProgram::ShaderProgram;
};




std::string getFsSource();
std::string getGsSource();
std::string getVsSource();



std::string getFsSource()
{
  return "#ph_version 330 core\n"
         "uniform vec4 colorUni;"
         "out vec4 outColor;"
         "void main()"
         "{"
         "    outColor = colorUni;"
         "}";
}



std::string getGsSource()
{
  return "#ph_version 330 core\n"
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
  return "#ph_version 330 core\n"
         "in vec2 pos;"
         "void main()"
         "{"
         "    gl_Position = vec4(pos, 0.0, 1.0);"
         "}";
}

}  // namespace



TEST_F(TestShaderProgram, Binding)
{
  VertexShader vs(getVsSource());
  FragmentShader fs(getFsSource());
  ConcreteShaderProgram p1(vs, fs);
  ConcreteShaderProgram p2(vs, fs);

  EXPECT_FALSE(p1.isBound());
  EXPECT_FALSE(p2.isBound());

  ConcreteShaderProgram::bind(p1);
  EXPECT_TRUE(p1.isBound());
  EXPECT_FALSE(p2.isBound());

  ConcreteShaderProgram::bind(p2);
  EXPECT_FALSE(p1.isBound());
  EXPECT_TRUE(p2.isBound());

  ConcreteShaderProgram::unbind();
  EXPECT_FALSE(p1.isBound());
  EXPECT_FALSE(p2.isBound());
}



TEST_F(TestShaderProgram, ConstructorWithoutGlGeometryShader)
{
  VertexShader vs(getVsSource());
  FragmentShader fs(getFsSource());
  ConcreteShaderProgram p(vs, fs);
  EXPECT_NE(0u, p.getHandle().get_name());
}



TEST_F(TestShaderProgram, ConstructorWithGlGeometryShader)
{
  VertexShader vs(getVsSource());
  GeometryShader gs(getGsSource());
  FragmentShader fs(getFsSource());
  ConcreteShaderProgram p(vs, fs, gs);
  EXPECT_NE(0u, p.getHandle().get_name());
}



TEST_F(TestShaderProgram, MoveConstructor)
{
  VertexShader vs(getVsSource());
  GeometryShader gs(getGsSource());
  FragmentShader fs(getFsSource());
  ConcreteShaderProgram pDummy(vs, fs, gs);
  uint programId = pDummy.getHandle().get_name();
  ConcreteShaderProgram p = std::move(pDummy);
  EXPECT_EQ(programId, p.getHandle().get_name());
  EXPECT_EQ(0u, pDummy.getHandle().get_name());
}



TEST_F(TestShaderProgram, GetUniformLocation)
{
  VertexShader vs(getVsSource());
  GeometryShader gs(getGsSource());
  FragmentShader fs(getFsSource());
  ConcreteShaderProgram p(vs, fs, gs);
  EXPECT_EQ(0u, p.getUniformLocation("colorUni"));
}



TEST_F(TestShaderProgramDeathTest, GetUniformLocationInvalidName)
{
  VertexShader vs(getVsSource());
  GeometryShader gs(getGsSource());
  FragmentShader fs(getFsSource());
  ConcreteShaderProgram p(vs, fs, gs);
  std::string invalidName = "trololol";
  HOU_EXPECT_ERROR(p.getUniformLocation(invalidName), std::runtime_error,
    format_string(get_text(gl_error::program_invalid_uniform), invalidName.c_str()));
}



TEST_F(TestShaderProgramDeathTest, ConstructorErrorLinkFailure)
{
  VertexShader vs(getVsSource());
  GeometryShader gs(getVsSource());
  FragmentShader fs(getFsSource());
  HOU_EXPECT_ERROR(ConcreteShaderProgram(vs, fs, gs), std::runtime_error,
    format_string(get_text(gl_error::program_linking),
      "Geometry info\n"
      "-------------\n"
      "(0) : error C6022: No input primitive type\n"
      "(0) : error C6029: No output primitive type\n"));
}
