// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/test_gl_shader_sources.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_program_handle.hpp"
#include "hou/gl/gl_shader_handle.hpp"

using namespace hou;



namespace
{

class test_gl_program_handle : public test_gl_multiple_contexts
{};

using test_gl_program_handle_death_test = test_gl_program_handle;

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

  return ph;
}

}  // namespace



TEST_F(test_gl_program_handle, creation)
{
  gl::program_handle vah = gl::program_handle::create();
  EXPECT_NE(0u, vah.get_name());
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_program_handle, no_context_creation)
#else
TEST_F(test_gl_program_handle, DISABLED_no_context_creation)
#endif
{
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::program_handle::create(), gl::missing_context_error);
}



TEST_F(test_gl_program_handle, tracking)
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



TEST_F(test_gl_program_handle, sharing_context_binding)
{
  gl::program_handle ph = create_program();
  set_sharing_context_current();
  gl::bind_program(ph);
  EXPECT_TRUE(is_program_bound(ph));
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_program_handle_death_test, non_sharing_context_binding)
#else
TEST_F(test_gl_program_handle_death_test, DISABLED_non_sharing_context_binding)
#endif
{
  gl::program_handle ph = create_program();
  set_non_sharing_context_current();
  EXPECT_ERROR_0(gl::bind_program(ph), gl::invalid_context_error);
  set_context_current();
}



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
TEST_F(test_gl_program_handle_death_test, no_context_binding)
#else
TEST_F(test_gl_program_handle_death_test, DISABLED_no_context_binding)
#endif
{
  gl::program_handle ph = create_program();
  gl::context::unset_current();
  EXPECT_ERROR_0(gl::bind_program(ph), gl::missing_context_error);
  set_context_current();
}



TEST_F(test_gl_program_handle, link_program)
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



TEST_F(test_gl_program_handle_death_test, link_program_failure)
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
  EXPECT_ERROR_N(gl::link_program(ph), gl::shader_linker_error,
    "Geometry info\n"
    "-------------\n"
    "(0) : error C6022: No input primitive type\n"
    "(0) : error C6029: No output primitive type\n");
}



TEST_F(test_gl_program_handle, get_uniform_location)
{
  gl::program_handle ph = create_program();
  EXPECT_EQ(0, gl::get_program_uniform_location(ph, "colorUni"));
}



TEST_F(test_gl_program_handle_death_test, get_uniform_location_invalid_name)
{
  gl::program_handle ph = create_program();
  EXPECT_ERROR_N(gl::get_program_uniform_location(ph, "invalidName"),
    gl::invalid_uniform_error, "invalidName");
}
