// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_VERTEX_ARRAY_HANDLE_HPP
#define HOU_GL_GL_VERTEX_ARRAY_HANDLE_HPP

#include "hou/gl/GlExport.hpp"
#include "hou/gl/GlObjectHandle.hpp"



namespace hou
{

namespace gl
{

class BufferHandle;

class HOU_GL_API VertexArrayHandle
  : public NonSharedObjectHandle
{
public:
  static VertexArrayHandle create();

  VertexArrayHandle(VertexArrayHandle&& other);
  virtual ~VertexArrayHandle();

private:
  VertexArrayHandle(GLuint name);
};

HOU_GL_API void bindVertexArray(const VertexArrayHandle& vertexArray);
HOU_GL_API void unbindVertexArray();
HOU_GL_API bool isVertexArrayBound(const VertexArrayHandle& vertexArray);
HOU_GL_API bool isVertexArrayBound();
HOU_GL_API GLuint getBoundVertexArrayName();

HOU_GL_API void setVertexArrayVertexBuffer(const VertexArrayHandle& vertexArray
  , GLuint bindingIndex, const BufferHandle& buffer, GLintptr offset
  , GLsizei stride);
HOU_GL_API void setVertexArrayAttribFormat(const VertexArrayHandle& vertexArray
  , GLuint attribIndex, GLint size, GLenum type, GLboolean normalized
  , GLuint relativeOffset);
HOU_GL_API void setVertexArrayAttribBinding
  (const VertexArrayHandle& vertexArray, GLuint attribIndex
  , GLuint bindingIndex);
HOU_GL_API void enableVertexArrayAttrib(const VertexArrayHandle& vertexArray
  , GLuint index);
HOU_GL_API void setVertexArrayElementBuffer
  (const VertexArrayHandle& vertexArray, const BufferHandle& buffer);
HOU_GL_API GLint getMaxVertexAttribs();
HOU_GL_API GLint getMaxVertexAttribBindings();



}

}

#endif

