// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/graphics_state.hpp"

#include "hou/gl/gl_functions.hpp"



namespace hou
{

bool is_multisampling_enabled()
{
  return gl::is_enabled(GL_MULTISAMPLE) == GL_TRUE;
}



void set_multisampling_enabled(bool value)
{
  if(value)
  {
    gl::enable(GL_MULTISAMPLE);
  }
  else
  {
    gl::disable(GL_MULTISAMPLE);
  }
}



bool is_blending_enabled()
{
  return gl::is_enabled(GL_BLEND) == GL_TRUE;
}



void set_blending_enabled(bool value)
{
  if(value)
  {
    gl::enable(GL_BLEND);
  }
  else
  {
    gl::disable(GL_BLEND);
  }
}



blending_factor get_source_blending_factor()
{
  return blending_factor(gl::get_integer(GL_BLEND_SRC_ALPHA));
}



void set_source_blending_factor(blending_factor f)
{
  gl::set_blend_func(
    static_cast<GLenum>(f), gl::get_integer(GL_BLEND_DST_ALPHA));
}



blending_factor get_destination_blending_factor()
{
  return blending_factor(gl::get_integer(GL_BLEND_DST_ALPHA));
}



void set_destination_blending_factor(blending_factor f)
{
  gl::set_blend_func(
    gl::get_integer(GL_BLEND_SRC_ALPHA), static_cast<GLenum>(f));
}



blending_equation get_blending_equation()
{
  return blending_equation(gl::get_integer(GL_BLEND_EQUATION_ALPHA));
}



void set_blending_equation(blending_equation eq)
{
  gl::set_blend_equation(static_cast<GLenum>(eq));
}



color get_blending_color()
{
  GLfloat color[4];
  gl::get_float_v(GL_BLEND_COLOR, color);
  return color_f(color[0], color[1], color[2], color[3]);
}



void set_blending_color(const color& c)
{
  gl::set_blend_color(
    c.get_red_f(), c.get_green_f(), c.get_blue_f(), c.get_alpha_f());
}

}  // namespace hou
