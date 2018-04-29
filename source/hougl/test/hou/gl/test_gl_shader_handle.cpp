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

class TestGlShaderHandle: public test_gl_multiple_contexts {};
class TestGlShaderHandleDeathTest : public TestGlShaderHandle {};

}



TEST_F(TestGlShaderHandle, Creation)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_VERTEX_SHADER);
  EXPECT_NE(0u, sh.get_name());
  EXPECT_EQ(static_cast<GLenum>(GL_VERTEX_SHADER), sh.get_type());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlShaderHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlShaderHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::shader_handle::create(GL_VERTEX_SHADER)
    , std::logic_error, get_text(gl_error::context_existence));
}



TEST_F(TestGlShaderHandle, CompileFragmentShader)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  compile_shader(sh, getFsSource().c_str());
  SUCCEED();
}



TEST_F(TestGlShaderHandleDeathTest, CompileFragmentShaderFailure)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  const char fragmentGlShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(compile_shader(sh, fragmentGlShaderSrc), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , "Fragment"
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(TestGlShaderHandle, CompileGeometryShader)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_GEOMETRY_SHADER);
  compile_shader(sh, getGsSource().c_str());
  SUCCEED();
}



TEST_F(TestGlShaderHandleDeathTest, CompileGeometryShaderFailure)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_GEOMETRY_SHADER);
  const char geometryGlShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(compile_shader(sh, geometryGlShaderSrc), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , "Geometry"
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(TestGlShaderHandle, CompileVertexShader)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_VERTEX_SHADER);
  compile_shader(sh, getVsSource().c_str());
  SUCCEED();
}



TEST_F(TestGlShaderHandleDeathTest, CompileVertexShaderFailure)
{
  gl::shader_handle sh = gl::shader_handle::create(GL_VERTEX_SHADER);
  const char vertexGlShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(compile_shader(sh, vertexGlShaderSrc), std::runtime_error
    , format_string(get_text(gl_error::shader_compilation)
    , "Vertex"
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}

