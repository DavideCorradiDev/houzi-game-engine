// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_functions.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_exceptions.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "hou/mth/rectangle.hpp"

#include "hou/sys/system_window.hpp"
#include "hou/sys/video_mode.hpp"

#if defined(HOU_SYSTEM_WINDOWS)
#include "hou/sys/win/win_error.hpp"
#endif

#include <mutex>



namespace hou
{

namespace gl
{

namespace
{
void enable(GLenum val);
void disable(GLenum val);
GLboolean is_enabed(GLenum val);

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



GLboolean is_enabed(GLenum val)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLboolean retval = glIsEnabled(val);
  HOU_GL_CHECK_ERROR();
  return retval;
}
}  // namespace

void init_extensions()
{
  static bool extensionsInitialized = false;
  static std::mutex extensionsMutex;

  std::lock_guard<std::mutex> lock(extensionsMutex);
  // Initialize only once.
  if(extensionsInitialized)
  {
    return;
  }

  // Create temporary dummy context, needed to call any GL function.
  system_window w("", vec2u(1u, 1u));
  gl::context c(gl::context_settings::get_basic(), w);
  gl::context::set_current(c, w);
  HOU_GL_CHECK_CONTEXT_EXISTENCE();

  int glad_init = gladLoadGLLoader(SDL_GL_GetProcAddress);
  HOU_CHECK_N(glad_init != 0, extension_initialization_error, glad_init);

  //   // Initialize extenstions through GLAD.
  //   int glad_init_retval = gladLoadGL();
  //   HOU_CHECK_N(
  //     glad_init_retval != 0, extension_initialization_error,
  //     glad_init_retval);
  //
  // #if defined(HOU_SYSTEM_WINDOWS)
  //   int wgl_glad_init_retval = gladLoadWGL(GetDC(w.get_handle()));
  //   HOU_CHECK_N(wgl_glad_init_retval != 0, extension_initialization_error,
  //     wgl_glad_init_retval);
  // #elif defined(HOU_SYSTEM_LINUX)
  //   int glx_glad_init_retval = gladLoadWGL(GetDC(w.get_handle()));
  //   HOU_CHECK_N(glx_glad_init_retval != 0, extension_initialization_error,
  //     glx_glad_init_retval);
  // #endif

  extensionsInitialized = true;
}



const GLubyte* get_gl_version_string()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  const GLubyte* str = glGetString(GL_VERSION);
  HOU_GL_CHECK_ERROR();
  return str;
}



void set_vertical_sync_mode(vertical_sync_mode mode)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
#if defined(HOU_SYSTEM_WINDOWS)
  if(wglSwapIntervalEXT)
  {
    HOU_CHECK_0(wglSwapIntervalEXT(static_cast<int>(mode)) != 0, vsync_error);
  }
#else
  HOU_UNREACHABLE();
#endif
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



void enable_blending()
{
  enable(GL_BLEND);
}



void disable_blending()
{
  disable(GL_BLEND);
}



GLboolean is_blending_enabled()
{
  return is_enabed(GL_BLEND);
}



void set_blending(GLenum sfactor, GLenum dfactor)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glBlendFunc(sfactor, dfactor);
  HOU_GL_CHECK_ERROR();
}



GLenum get_source_blending()
{
  return get_integer(GL_BLEND_SRC_ALPHA);
}



GLenum get_destination_blending()
{
  return get_integer(GL_BLEND_DST_ALPHA);
}



void enable_multisampling()
{
  enable(GL_MULTISAMPLE);
}



void disable_multisampling()
{
  disable(GL_MULTISAMPLE);
}



GLboolean is_multisampling_enabled()
{
  return is_enabed(GL_MULTISAMPLE);
}



void set_unpack_alignment(GLint value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glPixelStorei(GL_UNPACK_ALIGNMENT, value);
  HOU_GL_CHECK_ERROR();
}



GLint get_unpack_alignment()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint value;
  glGetIntegerv(GL_UNPACK_ALIGNMENT, &value);
  HOU_GL_CHECK_ERROR();
  return value;
}



void set_pack_alignment(GLint value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glPixelStorei(GL_PACK_ALIGNMENT, value);
  HOU_GL_CHECK_ERROR();
}



GLint get_pack_alignment()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint value;
  glGetIntegerv(GL_PACK_ALIGNMENT, &value);
  HOU_GL_CHECK_ERROR();
  return value;
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



void bind_window(window& w)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  gl::context::set_current(*gl::context::get_current(), w);
}



GLsizei get_pixel_size_bytes(GLenum format)
{
  switch(format)
  {
    case GL_RED:
      return 1u;
    case GL_RG:
      return 2u;
    case GL_RGB:
    case GL_BGR:
      return 3u;
    case GL_RGBA:
    case GL_BGRA:
      return 4u;
    default:
      return 1u;
  }
}



GLsizei compute_texture_size_bytes(
  GLsizei width, GLsizei height, GLsizei depth, GLenum format)
{
  GLsizei unpack_alignment = narrow_cast<GLsizei>(gl::get_unpack_alignment());
  GLsizei pixel_size = get_pixel_size_bytes(format);
  GLsizei row_size = pixel_size * width;
  GLsizei offset = row_size % unpack_alignment;
  row_size += (unpack_alignment - offset) % unpack_alignment;
  return row_size * height * depth;
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

}  // namespace gl

}  // namespace hou
