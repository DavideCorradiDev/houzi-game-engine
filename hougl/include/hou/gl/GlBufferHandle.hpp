// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_BUFFER_HANDLE_HPP
#define HOU_GL_GL_BUFFER_HANDLE_HPP

#include "hou/gl/GlExport.hpp"
#include "hou/gl/GlObjectHandle.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API BufferHandle
  : public SharedObjectHandle
{
public:
  static BufferHandle create();

  BufferHandle(BufferHandle&& other);
  virtual ~BufferHandle();

private:
  BufferHandle(GLuint name);
};

HOU_GL_API void bindBuffer(const BufferHandle& buffer, GLenum target);
HOU_GL_API void unbindBuffer(GLenum target);
HOU_GL_API bool isBufferBound(const BufferHandle& buffer, GLenum target);
HOU_GL_API bool isBufferBound(GLenum target);
HOU_GL_API GLuint getBoundBufferName(GLenum target);

HOU_GL_API void setBufferStorage(const BufferHandle& buffer, GLsizei size
  , const GLvoid* data, GLbitfield flags);
HOU_GL_API void setBufferSubData(const BufferHandle& buffer, GLintptr offset
  , GLsizei size, const GLvoid* data);
HOU_GL_API void getBufferSubData(const BufferHandle& buffer, GLintptr offset
  , GLsizei size, GLvoid* data);

}

}

#endif

