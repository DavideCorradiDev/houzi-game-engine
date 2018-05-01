// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_UTILS_HPP
#define HOU_GL_UTILS_HPP

#include "hou/gl/gl_export.hpp"

#include "hou/gl/gl_vertical_sync_mode.hpp"
#include "hou/gl/open_gl.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/mth/rectangle_fwd.hpp"



namespace hou
{

class window;

namespace gl
{

HOU_GL_API void init_extensions();
HOU_GL_API const GLubyte* get_gl_version_string();

HOU_GL_API void set_vertical_sync_mode(vertical_sync_mode mode);

HOU_GL_API void set_clear_color(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
HOU_GL_API void set_clear_depth(GLfloat depth);
HOU_GL_API void set_clear_stencil(GLint stencil);
HOU_GL_API void clear(GLenum mask);

HOU_GL_API void enable_blending();
HOU_GL_API void disable_blending();
HOU_GL_API GLboolean is_blending_enabled();
HOU_GL_API void set_blending(GLenum sfactor, GLenum dfactor);
HOU_GL_API GLenum get_source_blending();
HOU_GL_API GLenum get_destination_blending();

HOU_GL_API void enable_multisampling();
HOU_GL_API void disable_multisampling();
HOU_GL_API GLboolean is_multisampling_enabled();

HOU_GL_API void set_unpack_alignment(GLint value);
HOU_GL_API GLint get_unpack_alignment();
HOU_GL_API void set_pack_alignment(GLint value);
HOU_GL_API GLint get_pack_alignment();

HOU_GL_API void set_viewport(GLint x, GLint y, GLsizei w, GLsizei h);
HOU_GL_API void set_polygon_mode(GLenum polygon_face, GLenum polygon_mode);
HOU_GL_API void draw_arrays(GLenum draw_mode, GLint first, GLsizei count);
HOU_GL_API void bind_window(window& w);

HOU_GL_API GLsizei get_pixel_size_bytes(GLenum format);
HOU_GL_API GLsizei compute_texture_size_bytes(
  GLsizei width, GLsizei height, GLsizei depth, GLenum format);

HOU_GL_API void get_integer_v(GLenum variable, GLint* value);
HOU_GL_API GLint get_integer(GLenum variable);

}  // namespace gl

}  // namespace hou

#endif
