// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlMultipleContexts.hpp"

#include "hou/gl/TestGlShaderSources.hpp"

#include "hou/gl/GlError.hpp"
#include "hou/gl/GlShaderHandle.hpp"

using namespace hou;



namespace
{

class TestGlShaderHandle: public TestGlMultipleContexts {};
class TestGlShaderHandleDeathTest : public TestGlShaderHandle {};

}



TEST_F(TestGlShaderHandle, Creation)
{
  gl::ShaderHandle sh = gl::ShaderHandle::create(GL_VERTEX_SHADER);
  EXPECT_NE(0u, sh.getName());
  EXPECT_EQ(static_cast<GLenum>(GL_VERTEX_SHADER), sh.get_type());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlShaderHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlShaderHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::ShaderHandle::create(GL_VERTEX_SHADER)
    , std::logic_error, get_text(GlError::ContextExistence));
}



TEST_F(TestGlShaderHandle, CompileFragmentShader)
{
  gl::ShaderHandle sh = gl::ShaderHandle::create(GL_FRAGMENT_SHADER);
  compileShader(sh, getFsSource().c_str());
  SUCCEED();
}



TEST_F(TestGlShaderHandleDeathTest, CompileFragmentShaderFailure)
{
  gl::ShaderHandle sh = gl::ShaderHandle::create(GL_FRAGMENT_SHADER);
  const char fragmentGlShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(compileShader(sh, fragmentGlShaderSrc), std::runtime_error
    , format_string(get_text(GlError::ShaderCompilation)
    , "Fragment"
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(TestGlShaderHandle, CompileGeometryShader)
{
  gl::ShaderHandle sh = gl::ShaderHandle::create(GL_GEOMETRY_SHADER);
  compileShader(sh, getGsSource().c_str());
  SUCCEED();
}



TEST_F(TestGlShaderHandleDeathTest, CompileGeometryShaderFailure)
{
  gl::ShaderHandle sh = gl::ShaderHandle::create(GL_GEOMETRY_SHADER);
  const char geometryGlShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(compileShader(sh, geometryGlShaderSrc), std::runtime_error
    , format_string(get_text(GlError::ShaderCompilation)
    , "Geometry"
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}



TEST_F(TestGlShaderHandle, CompileVertexShader)
{
  gl::ShaderHandle sh = gl::ShaderHandle::create(GL_VERTEX_SHADER);
  compileShader(sh, getVsSource().c_str());
  SUCCEED();
}



TEST_F(TestGlShaderHandleDeathTest, CompileVertexShaderFailure)
{
  gl::ShaderHandle sh = gl::ShaderHandle::create(GL_VERTEX_SHADER);
  const char vertexGlShaderSrc[] = "I like trains.";
  HOU_EXPECT_ERROR(compileShader(sh, vertexGlShaderSrc), std::runtime_error
    , format_string(get_text(GlError::ShaderCompilation)
    , "Vertex"
    , "0(1) : error C0000: syntax error, "
    "unexpected '.', expecting \"::\" at token \".\"\n"));
}

