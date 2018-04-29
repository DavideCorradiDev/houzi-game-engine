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

class TestShaderProgram : public test_gfx_base
{};

class TestShaderProgramDeathTest : public TestShaderProgram
{};

class ConcreteShaderProgram
  : public shader_program
{
public:
  using shader_program::shader_program;
};




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

}  // namespace



TEST_F(TestShaderProgram, Binding)
{
  vertex_shader vs(getVsSource());
  fragment_shader fs(getFsSource());
  ConcreteShaderProgram p1(vs, fs);
  ConcreteShaderProgram p2(vs, fs);

  EXPECT_FALSE(p1.is_bound());
  EXPECT_FALSE(p2.is_bound());

  ConcreteShaderProgram::bind(p1);
  EXPECT_TRUE(p1.is_bound());
  EXPECT_FALSE(p2.is_bound());

  ConcreteShaderProgram::bind(p2);
  EXPECT_FALSE(p1.is_bound());
  EXPECT_TRUE(p2.is_bound());

  ConcreteShaderProgram::unbind();
  EXPECT_FALSE(p1.is_bound());
  EXPECT_FALSE(p2.is_bound());
}



TEST_F(TestShaderProgram, ConstructorWithoutGlGeometryShader)
{
  vertex_shader vs(getVsSource());
  fragment_shader fs(getFsSource());
  ConcreteShaderProgram p(vs, fs);
  EXPECT_NE(0u, p.get_handle().get_name());
}



TEST_F(TestShaderProgram, ConstructorWithGlGeometryShader)
{
  vertex_shader vs(getVsSource());
  geometry_shader gs(getGsSource());
  fragment_shader fs(getFsSource());
  ConcreteShaderProgram p(vs, fs, gs);
  EXPECT_NE(0u, p.get_handle().get_name());
}



TEST_F(TestShaderProgram, MoveConstructor)
{
  vertex_shader vs(getVsSource());
  geometry_shader gs(getGsSource());
  fragment_shader fs(getFsSource());
  ConcreteShaderProgram pDummy(vs, fs, gs);
  uint programId = pDummy.get_handle().get_name();
  ConcreteShaderProgram p = std::move(pDummy);
  EXPECT_EQ(programId, p.get_handle().get_name());
  EXPECT_EQ(0u, pDummy.get_handle().get_name());
}



TEST_F(TestShaderProgram, GetUniformLocation)
{
  vertex_shader vs(getVsSource());
  geometry_shader gs(getGsSource());
  fragment_shader fs(getFsSource());
  ConcreteShaderProgram p(vs, fs, gs);
  EXPECT_EQ(0u, p.get_uniform_location("colorUni"));
}



TEST_F(TestShaderProgramDeathTest, GetUniformLocationInvalidName)
{
  vertex_shader vs(getVsSource());
  geometry_shader gs(getGsSource());
  fragment_shader fs(getFsSource());
  ConcreteShaderProgram p(vs, fs, gs);
  std::string invalidName = "trololol";
  HOU_EXPECT_ERROR(p.get_uniform_location(invalidName), std::runtime_error,
    format_string(get_text(gl_error::program_invalid_uniform), invalidName.c_str()));
}



TEST_F(TestShaderProgramDeathTest, ConstructorErrorLinkFailure)
{
  vertex_shader vs(getVsSource());
  geometry_shader gs(getVsSource());
  fragment_shader fs(getFsSource());
  HOU_EXPECT_ERROR(ConcreteShaderProgram(vs, fs, gs), std::runtime_error,
    format_string(get_text(gl_error::program_linking),
      "Geometry info\n"
      "-------------\n"
      "(0) : error C6022: No input primitive type\n"
      "(0) : error C6029: No output primitive type\n"));
}
