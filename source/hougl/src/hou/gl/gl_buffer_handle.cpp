// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_buffer_handle.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_missing_context_error.hpp"

#include "hou/cor/cor_exceptions.hpp"



namespace hou
{

namespace gl
{

namespace prv
{

scoped_buffer_binding::scoped_buffer_binding(GLenum target, GLuint name)
  : m_target_bkp(target)
  , m_name_bkp(get_bound_buffer_name(target))
{
  glBindBuffer(target, name);
  HOU_GL_CHECK_ERROR();
}



scoped_buffer_binding::~scoped_buffer_binding()
{
  glBindBuffer(m_target_bkp, m_name_bkp);
  HOU_GL_CHECK_ERROR();
}

}  // namespace prv

namespace
{

GLenum to_get_gl_enum(GLenum target);

GLenum to_get_gl_enum(GLenum target)
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

#if defined(HOU_GL_ES)
GLenum to_buffer_usage_enum(GLbitfield buffer_flags)
{
  if(buffer_flags & GL_DYNAMIC_STORAGE_BIT)
  {
    return GL_DYNAMIC_DRAW;
  }
  else
  {
    return GL_STATIC_DRAW;
  }
}
#endif

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
  return static_cast<GLuint>(get_integer(to_get_gl_enum(target)));
}



void set_buffer_storage(const buffer_handle& buffer, GLsizei size,
  const GLvoid* data, GLbitfield flags)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
#if defined(HOU_GL_ES)
  {
    prv::scoped_buffer_binding binding(GL_ARRAY_BUFFER, buffer.get_name());
    glBufferData(GL_ARRAY_BUFFER, size, data, to_buffer_usage_enum(flags));
    HOU_GL_CHECK_ERROR();
  }
#else
  glNamedBufferStorage(buffer.get_name(), size, data, flags);
  HOU_GL_CHECK_ERROR();
#endif
}



void set_buffer_sub_data(const buffer_handle& buffer, GLintptr offset,
  GLsizei size, const GLvoid* data)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
#if defined(HOU_GL_ES)
  {
    prv::scoped_buffer_binding binding(GL_ARRAY_BUFFER, buffer.get_name());
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    HOU_GL_CHECK_ERROR();
  }
#else
  glNamedBufferSubData(buffer.get_name(), offset, size, data);
  HOU_GL_CHECK_ERROR();
#endif
}



#if defined(HOU_GL_ES)
void get_buffer_sub_data(const buffer_handle&, GLintptr, GLsizei, GLvoid*)
{
  HOU_ERROR_N(unsupported_error,
    "Reading from a GL buffer is not supported on GLES");
}
#else
void get_buffer_sub_data(
  const buffer_handle& buffer, GLintptr offset, GLsizei size, GLvoid* data)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glGetNamedBufferSubData(buffer.get_name(), offset, size, data);
  HOU_GL_CHECK_ERROR();
}
#endif

}  // namespace gl

}  // namespace hou
