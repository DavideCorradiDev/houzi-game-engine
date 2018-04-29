// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_functions.hpp"

#include "hou/gl/gl_check.hpp"
#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_error.hpp"

#include "hou/mth/rectangle.hpp"

#include "hou/sys/video_mode.hpp"
#include "hou/sys/system_window.hpp"

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
GLboolean isEnabled(GLenum val);

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



GLboolean isEnabled(GLenum val)
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
  if(!extensionsInitialized)
  {
    // Create temporary dummy ph_context, needed to call any GL function.
    system_window w("", video_mode(vec2u(0u, 0u), 32u), window_style::windowed);
    gl::context_settings cs(gl::context_settings::standard);
    gl::context c(cs, w);
    gl::context::set_current(c, w);
    HOU_GL_CHECK_CONTEXT_EXISTENCE();

    // Initialize extenstions through GLAD.
    int gladInitRetval = gladLoadGL();
    HOU_RUNTIME_CHECK(gladInitRetval != 0,
      get_text(gl_error::extensions_initialization), gladInitRetval);

#if defined(HOU_SYSTEM_WINDOWS)
    int wglGladInitRetval = gladLoadWGL(GetDC(w.get_handle()));
    HOU_RUNTIME_CHECK(wglGladInitRetval != 0,
      get_text(gl_error::extensions_initialization), wglGladInitRetval);
#endif

    extensionsInitialized = true;
  }
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
    HOU_WIN_RUNTIME_CHECK(wglSwapIntervalEXT(static_cast<int>(mode)) != 0,
      get_text(gl_error::vertical_sync_set));
  }
#else
  HOU_LOGIC_ERROR("Unsupported OS");
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
  return isEnabled(GL_BLEND);
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
  return isEnabled(GL_MULTISAMPLE);
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
    = context::getCurrent()->mTrackingData.get_current_viewport();
  if(x != currVp.x() || y != currVp.y() || w != currVp.w() || h != currVp.h())
  {
    glViewport(x, y, w, h);
    HOU_GL_CHECK_ERROR();
  }
}



void set_polygon_mode(GLenum polygonFace, GLenum polygonMode)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glPolygonMode(polygonFace, polygonMode);
  HOU_GL_CHECK_ERROR();
}



void draw_arrays(GLenum drawMode, GLint first, GLsizei count)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glDrawArrays(drawMode, first, count);
  HOU_GL_CHECK_ERROR();
}



void bind_window(window& w)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  gl::context::set_current(*gl::context::getCurrent(), w);
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
  GLsizei unpackAlignment = static_cast<GLsizei>(gl::get_unpack_alignment());
  GLsizei pixelSize = get_pixel_size_bytes(format);
  GLsizei rowSize = pixelSize * width;
  GLsizei offset = rowSize % unpackAlignment;
  rowSize += (unpackAlignment - offset) % unpackAlignment;
  return rowSize * height * depth;
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
