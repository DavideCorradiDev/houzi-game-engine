// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlUtils.hpp"

#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlError.hpp"

#include "hou/mth/Rectangle.hpp"

#include "hou/sys/VideoMode.hpp"
#include "hou/sys/Window.hpp"

#if defined(HOU_SYSTEM_WINDOWS)
#include "hou/sys/win/WinError.hpp"
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

void initExtensions()
{
  static bool extensionsInitialized = false;
  static std::mutex extensionsMutex;

  std::lock_guard<std::mutex> lock(extensionsMutex);
  // Initialize only once.
  if(!extensionsInitialized)
  {
    // Create temporary dummy context, needed to call any GL function.
    Window w("", VideoMode(Vec2u(0u, 0u), 32u), WindowStyle::Windowed);
    gl::ContextSettings cs(gl::ContextSettings::Default);
    gl::Context c(cs, w);
    gl::Context::setCurrent(c, w);
    HOU_GL_CHECK_CONTEXT_EXISTENCE();

    // Initialize extenstions through GLAD.
    int gladInitRetval = gladLoadGL();
    HOU_RUNTIME_CHECK(gladInitRetval != 0,
      getText(GlError::ExtensionsInitialization), gladInitRetval);

#if defined(HOU_SYSTEM_WINDOWS)
    int wglGladInitRetval = gladLoadWGL(GetDC(w.getWindowHandle()));
    HOU_RUNTIME_CHECK(wglGladInitRetval != 0,
      getText(GlError::ExtensionsInitialization), wglGladInitRetval);
#endif

    extensionsInitialized = true;
  }
}



const GLubyte* getGlVersionString()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  const GLubyte* str = glGetString(GL_VERSION);
  HOU_GL_CHECK_ERROR();
  return str;
}



void setVerticalSyncMode(VerticalSyncMode mode)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
#if defined(HOU_SYSTEM_WINDOWS)
  if(wglSwapIntervalEXT)
  {
    HOU_WIN_RUNTIME_CHECK(wglSwapIntervalEXT(static_cast<int>(mode)) != 0,
      getText(GlError::VerticalSyncSet));
  }
#else
  HOU_LOGIC_ERROR("Unsupported OS");
#endif
}



void setClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glClearColor(r, g, b, a);
  HOU_GL_CHECK_ERROR();
}



void setClearDepth(GLfloat depth)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glClearDepth(depth);
  HOU_GL_CHECK_ERROR();
}



void setClearStencil(GLint stencil)
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



void enableBlending()
{
  enable(GL_BLEND);
}



void disableBlending()
{
  disable(GL_BLEND);
}



GLboolean isBlendingEnabled()
{
  return isEnabled(GL_BLEND);
}



void setBlending(GLenum sfactor, GLenum dfactor)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glBlendFunc(sfactor, dfactor);
  HOU_GL_CHECK_ERROR();
}



GLenum getSourceBlending()
{
  return getInteger(GL_BLEND_SRC_ALPHA);
}



GLenum getDestinationBlending()
{
  return getInteger(GL_BLEND_DST_ALPHA);
}



void enableMultisampling()
{
  enable(GL_MULTISAMPLE);
}



void disableMultisampling()
{
  disable(GL_MULTISAMPLE);
}



GLboolean isMultisamplingEnabled()
{
  return isEnabled(GL_MULTISAMPLE);
}



void setUnpackAlignment(GLint value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glPixelStorei(GL_UNPACK_ALIGNMENT, value);
  HOU_GL_CHECK_ERROR();
}



GLint getUnpackAlignment()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint value;
  glGetIntegerv(GL_UNPACK_ALIGNMENT, &value);
  HOU_GL_CHECK_ERROR();
  return value;
}



void setPackAlignment(GLint value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glPixelStorei(GL_PACK_ALIGNMENT, value);
  HOU_GL_CHECK_ERROR();
}



GLint getPackAlignment()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint value;
  glGetIntegerv(GL_PACK_ALIGNMENT, &value);
  HOU_GL_CHECK_ERROR();
  return value;
}



void setViewport(GLint x, GLint y, GLsizei w, GLsizei h)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  const Recti& currVp
    = Context::getCurrent()->mTrackingData.getCurrentViewport();
  if(x != currVp.x() || y != currVp.y() || w != currVp.w() || h != currVp.h())
  {
    glViewport(x, y, w, h);
    HOU_GL_CHECK_ERROR();
  }
}



void setPolygonMode(GLenum polygonFace, GLenum polygonMode)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glPolygonMode(polygonFace, polygonMode);
  HOU_GL_CHECK_ERROR();
}



void drawArrays(GLenum drawMode, GLint first, GLsizei count)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glDrawArrays(drawMode, first, count);
  HOU_GL_CHECK_ERROR();
}



void bindWindow(Window& w)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  gl::Context::setCurrent(*gl::Context::getCurrent(), w);
}



GLsizei getPixelSizeBytes(GLenum format)
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



GLsizei computeTextureSizeBytes(
  GLsizei width, GLsizei height, GLsizei depth, GLenum format)
{
  GLsizei unpackAlignment = static_cast<GLsizei>(gl::getUnpackAlignment());
  GLsizei pixelSize = getPixelSizeBytes(format);
  GLsizei rowSize = pixelSize * width;
  GLsizei offset = rowSize % unpackAlignment;
  rowSize += (unpackAlignment - offset) % unpackAlignment;
  return rowSize * height * depth;
}



void getIntegerv(GLenum variable, GLint* value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glGetIntegerv(variable, value);
  HOU_GL_CHECK_ERROR();
}



GLint getInteger(GLenum variable)
{
  GLint value;
  getIntegerv(variable, &value);
  return value;
}

}  // namespace gl

}  // namespace hou
