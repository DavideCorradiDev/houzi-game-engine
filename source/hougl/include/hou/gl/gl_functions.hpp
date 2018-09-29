// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_UTILS_HPP
#define HOU_GL_UTILS_HPP

#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_config.hpp"

#include "hou/mth/rectangle_fwd.hpp"



namespace hou
{

class window;

namespace gl
{

HOU_GL_API const GLubyte* get_gl_version_string();

HOU_GL_API GLboolean is_enabled(GLenum val);
HOU_GL_API void enable(GLenum val);
HOU_GL_API void disable(GLenum val);

HOU_GL_API void get_float_v(GLenum variable, GLfloat* value);
HOU_GL_API void get_integer_v(GLenum variable, GLint* value);
HOU_GL_API GLint get_integer(GLenum variable);

HOU_GL_API void set_clear_color(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
HOU_GL_API void set_clear_depth(GLfloat depth);
HOU_GL_API void set_clear_stencil(GLint stencil);
HOU_GL_API void clear(GLenum mask);

HOU_GL_API void set_blend_func(GLenum sfactor, GLenum dfactor);
HOU_GL_API void set_blend_equation(GLenum mode);
HOU_GL_API void set_blend_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

HOU_GL_API void set_viewport(GLint x, GLint y, GLsizei w, GLsizei h);
HOU_GL_API void set_polygon_mode(GLenum polygon_face, GLenum polygon_mode);
HOU_GL_API void draw_arrays(GLenum draw_mode, GLint first, GLsizei count);

}  // namespace gl

}  // namespace hou

#endif
