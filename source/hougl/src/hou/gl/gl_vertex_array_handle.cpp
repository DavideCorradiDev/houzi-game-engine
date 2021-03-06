// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_vertex_array_handle.hpp"

#include "hou/gl/gl_buffer_handle.hpp"
#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_missing_context_error.hpp"

#include <memory>



namespace hou
{

namespace gl
{

namespace
{

class scoped_vertex_array_binding
{
public:
  scoped_vertex_array_binding(GLuint name);
  ~scoped_vertex_array_binding();

private:
  GLuint m_name_bkp;
};



scoped_vertex_array_binding::scoped_vertex_array_binding(GLuint name)
  : m_name_bkp(get_bound_vertex_array_name())
{
  glBindVertexArray(name);
  HOU_GL_CHECK_ERROR();
}



scoped_vertex_array_binding::~scoped_vertex_array_binding()
{
  glBindVertexArray(m_name_bkp);
  HOU_GL_CHECK_ERROR();
}

}



vertex_array_handle vertex_array_handle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = 0u;
#if defined(HOU_GL_ES)
  glGenVertexArrays(1, &name);
#else
  glCreateVertexArrays(1, &name);
#endif
  HOU_GL_CHECK_ERROR();
  return vertex_array_handle(name);
}



vertex_array_handle::~vertex_array_handle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  GLuint name = get_name();
  glDeleteVertexArrays(1, &name);
  HOU_GL_CHECK_ERROR();
}



vertex_array_handle::vertex_array_handle(GLuint name)
  : non_shared_object_handle(name)
{}



void bind_vertex_array(const vertex_array_handle& vertex_array)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertex_array);
  if(!is_vertex_array_bound(vertex_array))
  {
    glBindVertexArray(vertex_array.get_name());
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_vertex_array(
      vertex_array.get_uid());
  }
}



void unbind_vertex_array()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(is_vertex_array_bound())
  {
    glBindVertexArray(0u);
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_vertex_array(0u);
  }
}



bool is_vertex_array_bound(const vertex_array_handle& vertex_array)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertex_array);
  return context::get_current()->m_tracking_data.get_bound_vertex_array()
    == vertex_array.get_uid();
}



bool is_vertex_array_bound()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return context::get_current()->m_tracking_data.get_bound_vertex_array() != 0u;
}



GLuint get_bound_vertex_array_name()
{
  return static_cast<GLuint>(get_integer(GL_VERTEX_ARRAY_BINDING));
}



GLint get_max_vertex_attribs()
{
  return get_integer(GL_MAX_VERTEX_ATTRIBS);
}



GLint get_max_vertex_attrib_bindings()
{
#if defined(HOU_GL_ES)
  // The binding index can't really be specified, so it makes sense to
  // specify 1 as the maximum.
  return 1;
#else
  return get_integer(GL_MAX_VERTEX_ATTRIB_BINDINGS);
#endif
}



#if defined(HOU_GL_ES)

void enable_vertex_array_attrib(GLuint index)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glEnableVertexAttribArray(index);
  HOU_GL_CHECK_ERROR();
}



void set_vertex_attrib_pointer(GLuint index, GLint size, GLenum type,
  GLboolean normalized, GLsizei stride, GLvoid* offset)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glVertexAttribPointer(index, size, type, normalized, stride, offset);
  HOU_GL_CHECK_ERROR();
}

#else

void set_vertex_array_vertex_buffer(const vertex_array_handle& vertex_array,
  GLuint binding_index, const buffer_handle& buffer, GLintptr offset,
  GLsizei stride)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertex_array);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glVertexArrayVertexBuffer(
    vertex_array.get_name(), binding_index, buffer.get_name(), offset, stride);
  HOU_GL_CHECK_ERROR();
}



void set_vertex_array_attrib_format(const vertex_array_handle& vertex_array,
  GLuint attrib_index, GLint size, GLenum type, GLboolean normalized,
  GLuint relative_offset)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertex_array);
  glVertexArrayAttribFormat(vertex_array.get_name(), attrib_index, size, type,
    normalized, relative_offset);
  HOU_GL_CHECK_ERROR();
}



void set_vertex_array_attrib_binding(const vertex_array_handle& vertex_array,
  GLuint attrib_index, GLuint binding_index)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertex_array);
  glVertexArrayAttribBinding(
    vertex_array.get_name(), attrib_index, binding_index);
  HOU_GL_CHECK_ERROR();
}



void enable_vertex_array_attrib(
  const vertex_array_handle& vertex_array, GLuint index)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertex_array);
  glEnableVertexArrayAttrib(vertex_array.get_name(), index);
  HOU_GL_CHECK_ERROR();
}



void set_vertex_array_element_buffer(
  const vertex_array_handle& vertex_array, const buffer_handle& buffer)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertex_array);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glVertexArrayElementBuffer(vertex_array.get_name(), buffer.get_name());
  HOU_GL_CHECK_ERROR();
}

#endif

}  // namespace gl

}  // namespace hou
