// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlBufferHandle.hpp"

#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlContext.hpp"



namespace hou
{

namespace gl
{

namespace
{

GLenum toGetGLenum(GLenum target);



GLenum toGetGLenum(GLenum target)
{
  switch(target)
  {
    case GL_ARRAY_BUFFER:
      return GL_ARRAY_BUFFER_BINDING;
    break;
    case GL_ELEMENT_ARRAY_BUFFER:
      return GL_ELEMENT_ARRAY_BUFFER_BINDING;
    default:
      return 0u;
  }
}

}



BufferHandle BufferHandle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name;
  glCreateBuffers(1, &name);
  HOU_GL_CHECK_ERROR();
  return BufferHandle(name);
}



BufferHandle::BufferHandle(BufferHandle&& other)
  : SharedObjectHandle(std::move(other))
{}



BufferHandle::~BufferHandle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = getName();
  glDeleteBuffers(1, &name);
  HOU_GL_CHECK_ERROR();
}



BufferHandle::BufferHandle(GLuint name)
  : SharedObjectHandle(name)
{}



void bindBuffer(const BufferHandle& buffer, GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  if(!isBufferBound(buffer, target))
  {
    glBindBuffer(target, buffer.getName());
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundBuffer(buffer.getUid()
      , target);
  }
}



void unbindBuffer(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(isBufferBound(target))
  {
    glBindBuffer(target, 0u);
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundBuffer(0u, target);
  }
}



bool isBufferBound(const BufferHandle& buffer, GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  return Context::getCurrent()->mTrackingData.getBoundBuffer(target)
    == buffer.getUid();
}



bool isBufferBound(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return Context::getCurrent()->mTrackingData.getBoundBuffer(target) != 0u;
}



GLuint getBoundBufferName(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint name;
  glGetIntegerv(toGetGLenum(target), &name);
  HOU_GL_CHECK_ERROR();
  return static_cast<GLuint>(name);
}



void setBufferStorage(const BufferHandle& buffer, GLsizei size
  , const GLvoid* data, GLbitfield flags)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glNamedBufferStorage(buffer.getName(), size, data, flags);
  HOU_GL_CHECK_ERROR();
}



void setBufferSubData(const BufferHandle& buffer, GLintptr offset, GLsizei size
  , const GLvoid* data)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glNamedBufferSubData(buffer.getName(), offset, size, data);
  HOU_GL_CHECK_ERROR();
}



void getBufferSubData(const BufferHandle& buffer, GLintptr offset, GLsizei size
  , GLvoid* data)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glGetNamedBufferSubData(buffer.getName(), offset, size, data);
  HOU_GL_CHECK_ERROR();
}

}

}

