// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/test_gl_shader_sources.hpp"

#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_program_handle.hpp"
#include "hou/gl/gl_shader_handle.hpp"

using namespace hou;



namespace
{

class TestGlProgramHandle: public test_gl_multiple_contexts {};
class TestGlProgramHandleDeathTest : public TestGlProgramHandle {};

gl::program_handle createProgram();



gl::program_handle createProgram()
{
  gl::shader_handle vsh = gl::shader_handle::create(GL_VERTEX_SHADER);
  compile_shader(vsh, getVsSource().c_str());

  gl::shader_handle fsh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  compile_shader(fsh, getFsSource().c_str());

  gl::program_handle ph = gl::program_handle::create();
  attach_shader(ph, vsh);
  attach_shader(ph, fsh);
  link_program(ph);

  return std::move(ph);
}

}



TEST_F(TestGlProgramHandle, Creation)
{
  gl::program_handle vah = gl::program_handle::create();
  EXPECT_NE(0u, vah.get_name());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlProgramHandle, NoContextCreation)
#else
TEST_F(TestGlProgramHandle, DISABLED_NoContextCreation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::program_handle::create(), std::logic_error
    , get_text(gl_error::context_existence));
}



TEST_F(TestGlProgramHandle, Tracking)
{
  gl::program_handle ph1 = createProgram();
  gl::program_handle ph2 = createProgram();

  setContextCurrent();
  EXPECT_EQ(0u, gl::get_bound_program_name());
  EXPECT_FALSE(gl::is_program_bound(ph1));
  EXPECT_FALSE(gl::is_program_bound());

  gl::bind_program(ph1);
  EXPECT_EQ(ph1.get_name(), gl::get_bound_program_name());
  EXPECT_TRUE(gl::is_program_bound(ph1));
  EXPECT_TRUE(gl::is_program_bound());

  setSharingContextCurrent();
  EXPECT_EQ(0u, gl::get_bound_program_name());
  EXPECT_FALSE(gl::is_program_bound(ph2));
  EXPECT_FALSE(gl::is_program_bound());

  gl::bind_program(ph2);
  EXPECT_EQ(ph2.get_name(), gl::get_bound_program_name());
  EXPECT_TRUE(gl::is_program_bound(ph2));
  EXPECT_TRUE(gl::is_program_bound());

  setContextCurrent();
  EXPECT_EQ(ph1.get_name(), gl::get_bound_program_name());
  EXPECT_TRUE(gl::is_program_bound(ph1));
  EXPECT_TRUE(gl::is_program_bound());

  gl::unbind_program();
  EXPECT_EQ(0u, gl::get_bound_program_name());
  EXPECT_FALSE(gl::is_program_bound(ph1));
  EXPECT_FALSE(gl::is_program_bound());
}



TEST_F(TestGlProgramHandle, SharingContextBinding)
{
  gl::program_handle ph = createProgram();
  setSharingContextCurrent();
  gl::bind_program(ph);
  EXPECT_TRUE(is_program_bound(ph));
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlProgramHandleDeathTest, NonSharingContextBinding)
#else
TEST_F(TestGlProgramHandleDeathTest, DISABLED_NonSharingContextBinding)
#endif
{
  gl::program_handle ph = createProgram();
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(gl::bind_program(ph), std::logic_error
    , get_text(gl_error::invalid_ownership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlProgramHandleDeathTest, NoContextBinding)
#else
TEST_F(TestGlProgramHandleDeathTest, DISABLED_NoContextBinding)
#endif
{
  gl::program_handle ph = createProgram();
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::bind_program(ph), std::logic_error
    , get_text(gl_error::context_existence));
  setContextCurrent();
}



TEST_F(TestGlProgramHandle, LinkProgram)
{
  gl::shader_handle vsh = gl::shader_handle::create(GL_VERTEX_SHADER);
  gl::compile_shader(vsh, getVsSource().c_str());
  gl::shader_handle gsh = gl::shader_handle::create(GL_GEOMETRY_SHADER);
  gl::compile_shader(gsh, getGsSource().c_str());
  gl::shader_handle fsh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  gl::compile_shader(fsh, getFsSource().c_str());
  gl::program_handle ph = gl::program_handle::create();
  gl::attach_shader(ph, vsh);
  gl::attach_shader(ph, gsh);
  gl::attach_shader(ph, fsh);
  gl::link_program(ph);
  SUCCEED();
}



TEST_F(TestGlProgramHandleDeathTest, LinkProgramFailure)
{
  gl::shader_handle vsh = gl::shader_handle::create(GL_VERTEX_SHADER);
  gl::compile_shader(vsh, getVsSource().c_str());
  gl::shader_handle gsh = gl::shader_handle::create(GL_GEOMETRY_SHADER);
  // vertex ph_shader source here to trigger the error!
  gl::compile_shader(gsh, getVsSource().c_str());
  gl::shader_handle fsh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  gl::compile_shader(fsh, getFsSource().c_str());
  gl::program_handle ph = gl::program_handle::create();
  gl::attach_shader(ph, vsh);
  gl::attach_shader(ph, gsh);
  gl::attach_shader(ph, fsh);
  HOU_EXPECT_ERROR(gl::link_program(ph), std::runtime_error
    , format_string(get_text(gl_error::program_linking)
    , "Geometry info\n"
    "-------------\n"
    "(0) : error C6022: No input primitive type\n"
    "(0) : error C6029: No output primitive type\n"));
}



TEST_F(TestGlProgramHandle, GetUniformLocation)
{
  gl::program_handle ph = createProgram();
  EXPECT_EQ(0, gl::get_program_uniform_location(ph, "colorUni"));
}



TEST_F(TestGlProgramHandleDeathTest, GetUniformLocationInvalidName)
{
  gl::program_handle ph = createProgram();
  HOU_EXPECT_ERROR(gl::get_program_uniform_location(ph, "invalidName")
    , std::runtime_error, format_string(get_text(gl_error::program_invalid_uniform)
    , "invalidName"));

}

