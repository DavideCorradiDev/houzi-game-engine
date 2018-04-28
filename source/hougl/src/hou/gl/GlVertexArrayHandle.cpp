// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlVertexArrayHandle.hpp"

#include "hou/gl/GlBufferHandle.hpp"
#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlFunctions.hpp"



namespace hou
{

namespace gl
{

VertexArrayHandle VertexArrayHandle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name;
  glCreateVertexArrays(1, &name);
  HOU_GL_CHECK_ERROR();
  return VertexArrayHandle(name);
}



VertexArrayHandle::VertexArrayHandle(VertexArrayHandle&& other)
  : NonSharedObjectHandle(std::move(other))
{}



VertexArrayHandle::~VertexArrayHandle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  GLuint name = getName();
  glDeleteVertexArrays(1, &name);
  HOU_GL_CHECK_ERROR();
}



VertexArrayHandle::VertexArrayHandle(GLuint name)
  : NonSharedObjectHandle(name)
{}



void bindVertexArray(const VertexArrayHandle& vertexArray)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  if(!isVertexArrayBound(vertexArray))
  {
    glBindVertexArray(vertexArray.getName());
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundVertexArray
      (vertexArray.getUid());
  }
}



void unbindVertexArray()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(isVertexArrayBound())
  {
    glBindVertexArray(0u);
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundVertexArray(0u);
  }
}



bool isVertexArrayBound(const VertexArrayHandle& vertexArray)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  return Context::getCurrent()->mTrackingData.getBoundVertexArray()
    == vertexArray.getUid();
}



bool isVertexArrayBound()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return Context::getCurrent()->mTrackingData.getBoundVertexArray() != 0u;
}



GLuint getBoundVertexArrayName()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint name;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &name);
  HOU_GL_CHECK_ERROR();
  return static_cast<GLuint>(name);
}



void setVertexArrayVertexBuffer(const VertexArrayHandle& vertexArray
  , GLuint bindingIndex, const BufferHandle& buffer, GLintptr offset
  , GLsizei stride)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glVertexArrayVertexBuffer(vertexArray.getName(), bindingIndex
    , buffer.getName(), offset, stride);
  HOU_GL_CHECK_ERROR();
}



void setVertexArrayAttribFormat(const VertexArrayHandle& vertexArray
  , GLuint attribIndex, GLint size, GLenum type, GLboolean normalized
  , GLuint relativeOffset)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  glVertexArrayAttribFormat(vertexArray.getName(), attribIndex, size
    , type, normalized, relativeOffset);
  HOU_GL_CHECK_ERROR();
}



void setVertexArrayAttribBinding(const VertexArrayHandle& vertexArray
  , GLuint attribIndex, GLuint bindingIndex)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  glVertexArrayAttribBinding(vertexArray.getName(), attribIndex, bindingIndex);
  HOU_GL_CHECK_ERROR();
}



void enableVertexArrayAttrib(const VertexArrayHandle& vertexArray
  , GLuint index)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  glEnableVertexArrayAttrib(vertexArray.getName(), index);
  HOU_GL_CHECK_ERROR();
}



void setVertexArrayElementBuffer(const VertexArrayHandle& vertexArray
  , const BufferHandle& buffer)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glVertexArrayElementBuffer(vertexArray.getName(), buffer.getName());
  HOU_GL_CHECK_ERROR();
}



GLint getMaxVertexAttribs()
{
  return getInteger(GL_MAX_VERTEX_ATTRIBS);
}



GLint getMaxVertexAttribBindings()
{
  return getInteger(GL_MAX_VERTEX_ATTRIB_BINDINGS);
}

}

}

