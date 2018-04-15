// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlMultipleContexts.hpp"

#include "hou/gl/TestGlShaderSources.hpp"

#include "hou/gl/GlError.hpp"
#include "hou/gl/GlProgramHandle.hpp"
#include "hou/gl/GlShaderHandle.hpp"

using namespace hou;



namespace
{

class TestGlProgramHandle: public TestGlMultipleContexts {};
class TestGlProgramHandleDeathTest : public TestGlProgramHandle {};

gl::ProgramHandle createProgram();



gl::ProgramHandle createProgram()
{
  gl::ShaderHandle vsh = gl::ShaderHandle::create(GL_VERTEX_SHADER);
  compileShader(vsh, getVsSource().c_str());

  gl::ShaderHandle fsh = gl::ShaderHandle::create(GL_FRAGMENT_SHADER);
  compileShader(fsh, getFsSource().c_str());

  gl::ProgramHandle ph = gl::ProgramHandle::create();
  attachShader(ph, vsh);
  attachShader(ph, fsh);
  linkProgram(ph);

  return std::move(ph);
}

}



TEST_F(TestGlProgramHandle, Creation)
{
  gl::ProgramHandle vah = gl::ProgramHandle::create();
  EXPECT_NE(0u, vah.getName());
}



#if defined(HOU_DISABLE_GL_CONTEXT_EXISTENCE_CHECKS)
TEST_F(TestGlProgramHandle, DISABLED_NoContextCreation)
#else
TEST_F(TestGlProgramHandle, NoContextCreation)
#endif
{
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::ProgramHandle::create(), std::logic_error
    , getText(GlError::ContextExistence));
}



TEST_F(TestGlProgramHandle, Tracking)
{
  gl::ProgramHandle ph1 = createProgram();
  gl::ProgramHandle ph2 = createProgram();

  setContextCurrent();
  EXPECT_EQ(0u, gl::getBoundProgramName());
  EXPECT_FALSE(gl::isProgramBound(ph1));
  EXPECT_FALSE(gl::isProgramBound());

  gl::bindProgram(ph1);
  EXPECT_EQ(ph1.getName(), gl::getBoundProgramName());
  EXPECT_TRUE(gl::isProgramBound(ph1));
  EXPECT_TRUE(gl::isProgramBound());

  setSharingContextCurrent();
  EXPECT_EQ(0u, gl::getBoundProgramName());
  EXPECT_FALSE(gl::isProgramBound(ph2));
  EXPECT_FALSE(gl::isProgramBound());

  gl::bindProgram(ph2);
  EXPECT_EQ(ph2.getName(), gl::getBoundProgramName());
  EXPECT_TRUE(gl::isProgramBound(ph2));
  EXPECT_TRUE(gl::isProgramBound());

  setContextCurrent();
  EXPECT_EQ(ph1.getName(), gl::getBoundProgramName());
  EXPECT_TRUE(gl::isProgramBound(ph1));
  EXPECT_TRUE(gl::isProgramBound());

  gl::unbindProgram();
  EXPECT_EQ(0u, gl::getBoundProgramName());
  EXPECT_FALSE(gl::isProgramBound(ph1));
  EXPECT_FALSE(gl::isProgramBound());
}



TEST_F(TestGlProgramHandle, SharingContextBinding)
{
  gl::ProgramHandle ph = createProgram();
  setSharingContextCurrent();
  gl::bindProgram(ph);
  EXPECT_TRUE(isProgramBound(ph));
}



#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
TEST_F(TestGlProgramHandleDeathTest, DISABLED_NonSharingContextBinding)
#else
TEST_F(TestGlProgramHandleDeathTest, NonSharingContextBinding)
#endif
{
  gl::ProgramHandle ph = createProgram();
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bindProgram(ph), std::logic_error
    , getText(GlError::InvalidOwnership));
  setContextCurrent();
}



#if defined(HOU_DISABLE_GL_CONTEXT_EXISTENCE_CHECKS)
TEST_F(TestGlProgramHandleDeathTest, DISABLED_NoContextBinding)
#else
TEST_F(TestGlProgramHandleDeathTest, NoContextBinding)
#endif
{
  gl::ProgramHandle ph = createProgram();
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::bindProgram(ph), std::logic_error
    , getText(GlError::ContextExistence));
  setContextCurrent();
}



TEST_F(TestGlProgramHandle, LinkProgram)
{
  gl::ShaderHandle vsh = gl::ShaderHandle::create(GL_VERTEX_SHADER);
  gl::compileShader(vsh, getVsSource().c_str());
  gl::ShaderHandle gsh = gl::ShaderHandle::create(GL_GEOMETRY_SHADER);
  gl::compileShader(gsh, getGsSource().c_str());
  gl::ShaderHandle fsh = gl::ShaderHandle::create(GL_FRAGMENT_SHADER);
  gl::compileShader(fsh, getFsSource().c_str());
  gl::ProgramHandle ph = gl::ProgramHandle::create();
  gl::attachShader(ph, vsh);
  gl::attachShader(ph, gsh);
  gl::attachShader(ph, fsh);
  gl::linkProgram(ph);
  SUCCEED();
}



TEST_F(TestGlProgramHandleDeathTest, LinkProgramFailure)
{
  gl::ShaderHandle vsh = gl::ShaderHandle::create(GL_VERTEX_SHADER);
  gl::compileShader(vsh, getVsSource().c_str());
  gl::ShaderHandle gsh = gl::ShaderHandle::create(GL_GEOMETRY_SHADER);
  // Vertex shader source here to trigger the error!
  gl::compileShader(gsh, getVsSource().c_str());
  gl::ShaderHandle fsh = gl::ShaderHandle::create(GL_FRAGMENT_SHADER);
  gl::compileShader(fsh, getFsSource().c_str());
  gl::ProgramHandle ph = gl::ProgramHandle::create();
  gl::attachShader(ph, vsh);
  gl::attachShader(ph, gsh);
  gl::attachShader(ph, fsh);
  HOU_EXPECT_ERROR(gl::linkProgram(ph), std::runtime_error
    , formatString(getText(GlError::ProgramLinking)
    , "Geometry info\n"
    "-------------\n"
    "(0) : error C6022: No input primitive type\n"
    "(0) : error C6029: No output primitive type\n"));
}



TEST_F(TestGlProgramHandle, GetUniformLocation)
{
  gl::ProgramHandle ph = createProgram();
  EXPECT_EQ(0, gl::getProgramUniformLocation(ph, "colorUni"));
}



TEST_F(TestGlProgramHandleDeathTest, GetUniformLocationInvalidName)
{
  gl::ProgramHandle ph = createProgram();
  HOU_EXPECT_ERROR(gl::getProgramUniformLocation(ph, "invalidName")
    , std::runtime_error, formatString(getText(GlError::ProgramInvalidUniform)
    , "invalidName"));

}

