// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_vsync_mode.hpp"

using namespace hou;



namespace
{

class test_gl_vsync_mode : public test_gl_single_context
{};

using test_gl_vsync_mode_death_test = test_gl_vsync_mode;

}  // namespace



TEST_F(test_gl_vsync_mode, set_vsync_mode)
{
  EXPECT_EQ(gl::vsync_mode::disabled, gl::get_vsync_mode());

  EXPECT_TRUE(gl::set_vsync_mode(gl::vsync_mode::disabled));
  EXPECT_EQ(gl::vsync_mode::disabled, gl::get_vsync_mode());

  if(gl::set_vsync_mode(gl::vsync_mode::adaptive))
  {
    EXPECT_EQ(gl::vsync_mode::adaptive, gl::get_vsync_mode());
  }

  EXPECT_TRUE(gl::set_vsync_mode(gl::vsync_mode::enabled));
  EXPECT_EQ(gl::vsync_mode::enabled, gl::get_vsync_mode());
}
