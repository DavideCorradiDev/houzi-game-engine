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

class test_gl_program_handle : public test_gl_multiple_contexts
{};

class test_gl_program_handle_death_test : public test_gl_program_handle
{};

gl::program_handle create_program();



gl::program_handle create_program()
{
  gl::shader_handle vsh = gl::shader_handle::create(GL_VERTEX_SHADER);
  compile_shader(vsh, get_vs_source().c_str());

  gl::shader_handle fsh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  compile_shader(fsh, get_fs_source().c_str());

  gl::program_handle ph = gl::program_handle::create();
  attach_shader(ph, vsh);
  attach_shader(ph, fsh);
  link_program(ph);

  return std::move(ph);
}

}  // namespace



TEST_F(test_gl_program_handle, Creation)
{
  gl::program_handle vah = gl::program_handle::create();
  EXPECT_NE(0u, vah.get_name());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(test_gl_program_handle, NoContextCreation)
#else
TEST_F(test_gl_program_handle, DISABLED_NoContextCreation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::program_handle::create(), std::logic_error,
    get_text(gl_error::context_existence));
}



TEST_F(test_gl_program_handle, Tracking)
{
  gl::program_handle ph1 = create_program();
  gl::program_handle ph2 = create_program();

  set_context_current();
  EXPECT_EQ(0u, gl::get_bound_program_name());
  EXPECT_FALSE(gl::is_program_bound(ph1));
  EXPECT_FALSE(gl::is_program_bound());

  gl::bind_program(ph1);
  EXPECT_EQ(ph1.get_name(), gl::get_bound_program_name());
  EXPECT_TRUE(gl::is_program_bound(ph1));
  EXPECT_TRUE(gl::is_program_bound());

  set_sharing_context_current();
  EXPECT_EQ(0u, gl::get_bound_program_name());
  EXPECT_FALSE(gl::is_program_bound(ph2));
  EXPECT_FALSE(gl::is_program_bound());

  gl::bind_program(ph2);
  EXPECT_EQ(ph2.get_name(), gl::get_bound_program_name());
  EXPECT_TRUE(gl::is_program_bound(ph2));
  EXPECT_TRUE(gl::is_program_bound());

  set_context_current();
  EXPECT_EQ(ph1.get_name(), gl::get_bound_program_name());
  EXPECT_TRUE(gl::is_program_bound(ph1));
  EXPECT_TRUE(gl::is_program_bound());

  gl::unbind_program();
  EXPECT_EQ(0u, gl::get_bound_program_name());
  EXPECT_FALSE(gl::is_program_bound(ph1));
  EXPECT_FALSE(gl::is_program_bound());
}



TEST_F(test_gl_program_handle, SharingContextBinding)
{
  gl::program_handle ph = create_program();
  set_sharing_context_current();
  gl::bind_program(ph);
  EXPECT_TRUE(is_program_bound(ph));
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(test_gl_program_handle_death_test, NonSharingContextBinding)
#else
TEST_F(test_gl_program_handle_death_test, DISABLED_NonSharingContextBinding)
#endif
{
  gl::program_handle ph = create_program();
  set_non_sharing_context_current();
  HOU_EXPECT_ERROR(gl::bind_program(ph), std::logic_error,
    get_text(gl_error::invalid_ownership));
  set_context_current();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(test_gl_program_handle_death_test, NoContextBinding)
#else
TEST_F(test_gl_program_handle_death_test, DISABLED_NoContextBinding)
#endif
{
  gl::program_handle ph = create_program();
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::bind_program(ph), std::logic_error,
    get_text(gl_error::context_existence));
  set_context_current();
}



TEST_F(test_gl_program_handle, LinkProgram)
{
  gl::shader_handle vsh = gl::shader_handle::create(GL_VERTEX_SHADER);
  gl::compile_shader(vsh, get_vs_source().c_str());
  gl::shader_handle gsh = gl::shader_handle::create(GL_GEOMETRY_SHADER);
  gl::compile_shader(gsh, get_gs_source().c_str());
  gl::shader_handle fsh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  gl::compile_shader(fsh, get_fs_source().c_str());
  gl::program_handle ph = gl::program_handle::create();
  gl::attach_shader(ph, vsh);
  gl::attach_shader(ph, gsh);
  gl::attach_shader(ph, fsh);
  gl::link_program(ph);
  SUCCEED();
}



TEST_F(test_gl_program_handle_death_test, LinkProgramFailure)
{
  gl::shader_handle vsh = gl::shader_handle::create(GL_VERTEX_SHADER);
  gl::compile_shader(vsh, get_vs_source().c_str());
  gl::shader_handle gsh = gl::shader_handle::create(GL_GEOMETRY_SHADER);
  // vertex shader source here to trigger the error!
  gl::compile_shader(gsh, get_vs_source().c_str());
  gl::shader_handle fsh = gl::shader_handle::create(GL_FRAGMENT_SHADER);
  gl::compile_shader(fsh, get_fs_source().c_str());
  gl::program_handle ph = gl::program_handle::create();
  gl::attach_shader(ph, vsh);
  gl::attach_shader(ph, gsh);
  gl::attach_shader(ph, fsh);
  HOU_EXPECT_ERROR(gl::link_program(ph), std::runtime_error,
    format_string(get_text(gl_error::program_linking),
      "Geometry info\n"
      "-------------\n"
      "(0) : error C6022: No input primitive type\n"
      "(0) : error C6029: No output primitive type\n"));
}



TEST_F(test_gl_program_handle, GetUniformLocation)
{
  gl::program_handle ph = create_program();
  EXPECT_EQ(0, gl::get_program_uniform_location(ph, "colorUni"));
}



TEST_F(test_gl_program_handle_death_test, GetUniformLocationInvalidName)
{
  gl::program_handle ph = create_program();
  HOU_EXPECT_ERROR(gl::get_program_uniform_location(ph, "invalidName"),
    std::runtime_error,
    format_string(get_text(gl_error::program_invalid_uniform), "invalidName"));
}
