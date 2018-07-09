// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_buffer_handle.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"



namespace hou
{

namespace gl
{

namespace
{

class scoped_buffer_binding
{
public:
  scoped_buffer_binding(GLenum target, GLuint name);
  ~scoped_buffer_binding();

private:
  GLenum m_target_bkp;
  GLuint m_name_bkp;
};

GLenum toGetGLenum(GLenum target);



scoped_buffer_binding::scoped_buffer_binding(GLenum target, GLuint name)
  : m_target_bkp(target)
  , m_name_bkp(get_bound_buffer_name(target))
{
  glBindBuffer(m_target_bkp, name);
  HOU_GL_CHECK_ERROR();
}



scoped_buffer_binding::~scoped_buffer_binding()
{
  glBindBuffer(m_target_bkp, m_name_bkp);
  HOU_GL_CHECK_ERROR();
}



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
      HOU_UNREACHABLE();
      return 0u;
  }
}

}  // namespace



buffer_handle buffer_handle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = 0u;
#if defined(HOU_GL_ES)
  glGenBuffers(1, &name);
#else
  glCreateBuffers(1, &name);
#endif
  HOU_GL_CHECK_ERROR();
  return buffer_handle(name);
}



buffer_handle::~buffer_handle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  GLuint name = get_name();
  glDeleteBuffers(1, &name);
  HOU_GL_CHECK_ERROR();
}



buffer_handle::buffer_handle(GLuint name)
  : shared_object_handle(name)
{}



void bind_buffer(const buffer_handle& buffer, GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  if(!is_buffer_bound(buffer, target))
  {
    glBindBuffer(target, buffer.get_name());
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_buffer(
      buffer.get_uid(), target);
  }
}



void unbind_buffer(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(is_buffer_bound(target))
  {
    glBindBuffer(target, 0u);
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_buffer(0u, target);
  }
}



bool is_buffer_bound(const buffer_handle& buffer, GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  return context::get_current()->m_tracking_data.get_bound_buffer(target)
    == buffer.get_uid();
}



bool is_buffer_bound(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return context::get_current()->m_tracking_data.get_bound_buffer(target) != 0u;
}



GLuint get_bound_buffer_name(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint name;
  glGetIntegerv(toGetGLenum(target), &name);
  HOU_GL_CHECK_ERROR();
  return static_cast<GLuint>(name);
}



void set_buffer_storage(const buffer_handle& buffer, GLsizei size,
  const GLvoid* data, GLbitfield flags)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
#if defined(HOU_GL_ES)
  {
    scoped_buffer_binding(GL_ARRAY_BUFFER, buffer.get_name());
    glBufferStorage(GL_ARRAY_BUFFER, size, data, flags);
  }
#else
  glNamedBufferStorage(buffer.get_name(), size, data, flags);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_buffer_sub_data(const buffer_handle& buffer, GLintptr offset,
  GLsizei size, const GLvoid* data)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
#if defined(HOU_GL_ES)
  {
    scoped_buffer_binding(GL_ARRAY_BUFFER, buffer.get_name());
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
  }
#else
  glNamedBufferSubData(buffer.get_name(), offset, size, data);
#endif
  HOU_GL_CHECK_ERROR();
}



void get_buffer_sub_data(
  const buffer_handle& buffer, GLintptr offset, GLsizei size, GLvoid* data)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
#if defined(HOU_GL_ES)
  {
    scoped_buffer_binding(GL_ARRAY_BUFFER, buffer.get_name());
    glGetBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
  }
#else
  glGetNamedBufferSubData(buffer.get_name(), offset, size, data);
#endif
  HOU_GL_CHECK_ERROR();
}

}  // namespace gl

}  // namespace hou
