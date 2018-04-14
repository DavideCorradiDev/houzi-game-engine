// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GL_UTILS_HPP
#define HOU_GL_UTILS_HPP

#include "hou/gl/GlExport.hpp"

#include "hou/gl/GlVerticalSyncMode.hpp"
#include "hou/gl/OpenGl.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/mth/RectangleFwd.hpp"



namespace hou
{

class Window;

namespace gl
{

HOU_GL_API void initExtensions();
HOU_GL_API const GLubyte* getGlVersionString();

HOU_GL_API void setVerticalSyncMode(VerticalSyncMode mode);

HOU_GL_API void setClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
HOU_GL_API void setClearDepth(GLfloat depth);
HOU_GL_API void setClearStencil(GLint stencil);
HOU_GL_API void clear(GLenum mask);

HOU_GL_API void enableBlending();
HOU_GL_API void disableBlending();
HOU_GL_API GLboolean isBlendingEnabled();
HOU_GL_API void setBlending(GLenum sfactor, GLenum dfactor);
HOU_GL_API GLenum getSourceBlending();
HOU_GL_API GLenum getDestinationBlending();

HOU_GL_API void enableMultisampling();
HOU_GL_API void disableMultisampling();
HOU_GL_API GLboolean isMultisamplingEnabled();

HOU_GL_API void setUnpackAlignment(GLint value);
HOU_GL_API GLint getUnpackAlignment();
HOU_GL_API void setPackAlignment(GLint value);
HOU_GL_API GLint getPackAlignment();

HOU_GL_API void setViewport(GLint x, GLint y, GLsizei w, GLsizei h);
HOU_GL_API void setPolygonMode(GLenum polygonFace, GLenum polygonMode);
HOU_GL_API void drawArrays(GLenum drawMode, GLint first, GLsizei count);
HOU_GL_API void bindWindow(Window& w);

HOU_GL_API GLsizei getPixelSizeBytes(GLenum format);
HOU_GL_API GLsizei computeTextureSizeBytes(
  GLsizei width, GLsizei height, GLsizei depth, GLenum format);

HOU_GL_API void getIntegerv(GLenum variable, GLint* value);
HOU_GL_API GLint getInteger(GLenum variable);

}  // namespace gl

}  // namespace hou

#endif
