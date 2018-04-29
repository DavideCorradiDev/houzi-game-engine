// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_vertex_array_handle.hpp"

#include "hou/gl/gl_buffer_handle.hpp"
#include "hou/gl/GlCheck.hpp"
#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_functions.hpp"



namespace hou
{

namespace gl
{

vertex_array_handle vertex_array_handle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name;
  glCreateVertexArrays(1, &name);
  HOU_GL_CHECK_ERROR();
  return vertex_array_handle(name);
}



vertex_array_handle::vertex_array_handle(vertex_array_handle&& other)
  : non_shared_object_handle(std::move(other))
{}



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



void bind_vertex_array(const vertex_array_handle& vertexArray)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  if(!is_vertex_array_bound(vertexArray))
  {
    glBindVertexArray(vertexArray.get_name());
    HOU_GL_CHECK_ERROR();
    context::getCurrent()->mTrackingData.set_bound_vertex_array
      (vertexArray.get_uid());
  }
}



void unbind_vertex_array()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(is_vertex_array_bound())
  {
    glBindVertexArray(0u);
    HOU_GL_CHECK_ERROR();
    context::getCurrent()->mTrackingData.set_bound_vertex_array(0u);
  }
}



bool is_vertex_array_bound(const vertex_array_handle& vertexArray)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  return context::getCurrent()->mTrackingData.get_bound_vertex_array()
    == vertexArray.get_uid();
}



bool is_vertex_array_bound()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return context::getCurrent()->mTrackingData.get_bound_vertex_array() != 0u;
}



GLuint get_bound_vertex_array_name()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint name;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &name);
  HOU_GL_CHECK_ERROR();
  return static_cast<GLuint>(name);
}



void set_vertex_array_vertex_buffer(const vertex_array_handle& vertexArray
  , GLuint bindingIndex, const buffer_handle& buffer, GLintptr offset
  , GLsizei stride)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glVertexArrayVertexBuffer(vertexArray.get_name(), bindingIndex
    , buffer.get_name(), offset, stride);
  HOU_GL_CHECK_ERROR();
}



void set_vertex_array_attrib_format(const vertex_array_handle& vertexArray
  , GLuint attribIndex, GLint size, GLenum type, GLboolean normalized
  , GLuint relativeOffset)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  glVertexArrayAttribFormat(vertexArray.get_name(), attribIndex, size
    , type, normalized, relativeOffset);
  HOU_GL_CHECK_ERROR();
}



void set_vertex_array_attrib_binding(const vertex_array_handle& vertexArray
  , GLuint attribIndex, GLuint bindingIndex)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  glVertexArrayAttribBinding(vertexArray.get_name(), attribIndex, bindingIndex);
  HOU_GL_CHECK_ERROR();
}



void enable_vertex_array_attrib(const vertex_array_handle& vertexArray
  , GLuint index)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  glEnableVertexArrayAttrib(vertexArray.get_name(), index);
  HOU_GL_CHECK_ERROR();
}



void setVertexArrayElementBuffer(const vertex_array_handle& vertexArray
  , const buffer_handle& buffer)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(vertexArray);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(buffer);
  glVertexArrayElementBuffer(vertexArray.get_name(), buffer.get_name());
  HOU_GL_CHECK_ERROR();
}



GLint get_max_vertex_attribs()
{
  return get_integer(GL_MAX_VERTEX_ATTRIBS);
}



GLint get_max_vertex_attrib_bindings()
{
  return get_integer(GL_MAX_VERTEX_ATTRIB_BINDINGS);
}

}

}

