// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_functions.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "hou/mth/rectangle.hpp"



namespace hou
{

namespace gl
{

const GLubyte* get_gl_version_string()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  const GLubyte* str = glGetString(GL_VERSION);
  HOU_GL_CHECK_ERROR();
  return str;
}



GLboolean is_enabled(GLenum val)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLboolean retval = glIsEnabled(val);
  HOU_GL_CHECK_ERROR();
  return retval;
}



void enable(GLenum val)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glEnable(val);
  HOU_GL_CHECK_ERROR();
}



void disable(GLenum val)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glDisable(val);
  HOU_GL_CHECK_ERROR();
}



void get_float_v(GLenum variable, GLfloat* value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glGetFloatv(variable, value);
  HOU_GL_CHECK_ERROR();
}



void get_integer_v(GLenum variable, GLint* value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glGetIntegerv(variable, value);
  HOU_GL_CHECK_ERROR();
}



GLint get_integer(GLenum variable)
{
  GLint value;
  get_integer_v(variable, &value);
  return value;
}



void set_clear_color(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glClearColor(r, g, b, a);
  HOU_GL_CHECK_ERROR();
}



void set_clear_depth(GLfloat depth)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glClearDepth(depth);
  HOU_GL_CHECK_ERROR();
}



void set_clear_stencil(GLint stencil)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glClearDepth(stencil);
  HOU_GL_CHECK_ERROR();
}



void clear(GLenum mask)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glClear(mask);
  HOU_GL_CHECK_ERROR();
}



void set_blend_func(GLenum sfactor, GLenum dfactor)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glBlendFunc(sfactor, dfactor);
  HOU_GL_CHECK_ERROR();
}




void set_blend_equation(GLenum mode)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glBlendEquation(mode);
  HOU_GL_CHECK_ERROR();
}



void set_blend_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glBlendColor(r, g, b, a);
  HOU_GL_CHECK_ERROR();
}



void set_viewport(GLint x, GLint y, GLsizei w, GLsizei h)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  const recti& currVp
    = context::get_current()->m_tracking_data.get_current_viewport();
  if(x != currVp.x() || y != currVp.y() || w != currVp.w() || h != currVp.h())
  {
    glViewport(x, y, w, h);
    HOU_GL_CHECK_ERROR();
  }
}



void set_polygon_mode(GLenum polygon_face, GLenum polygon_mode)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glPolygonMode(polygon_face, polygon_mode);
  HOU_GL_CHECK_ERROR();
}



void draw_arrays(GLenum draw_mode, GLint first, GLsizei count)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glDrawArrays(draw_mode, first, count);
  HOU_GL_CHECK_ERROR();
}

}  // namespace gl

}  // namespace hou
