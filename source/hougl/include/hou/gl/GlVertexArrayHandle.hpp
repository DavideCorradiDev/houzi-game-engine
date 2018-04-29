// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_VERTEX_ARRAY_HANDLE_HPP
#define HOU_GL_GL_VERTEX_ARRAY_HANDLE_HPP

#include "hou/gl/gl_export.hpp"
#include "hou/gl/gl_object_handle.hpp"



namespace hou
{

namespace gl
{

class buffer_handle;

class HOU_GL_API vertex_array_handle
  : public non_shared_object_handle
{
public:
  static vertex_array_handle create();

  vertex_array_handle(vertex_array_handle&& other);
  virtual ~vertex_array_handle();

private:
  vertex_array_handle(GLuint name);
};

HOU_GL_API void bind_vertex_array(const vertex_array_handle& vertexArray);
HOU_GL_API void unbind_vertex_array();
HOU_GL_API bool is_vertex_array_bound(const vertex_array_handle& vertexArray);
HOU_GL_API bool is_vertex_array_bound();
HOU_GL_API GLuint get_bound_vertex_array_name();

HOU_GL_API void set_vertex_array_vertex_buffer(const vertex_array_handle& vertexArray
  , GLuint bindingIndex, const buffer_handle& buffer, GLintptr offset
  , GLsizei stride);
HOU_GL_API void set_vertex_array_attrib_format(const vertex_array_handle& vertexArray
  , GLuint attribIndex, GLint size, GLenum type, GLboolean normalized
  , GLuint relativeOffset);
HOU_GL_API void set_vertex_array_attrib_binding
  (const vertex_array_handle& vertexArray, GLuint attribIndex
  , GLuint bindingIndex);
HOU_GL_API void enable_vertex_array_attrib(const vertex_array_handle& vertexArray
  , GLuint index);
HOU_GL_API void setVertexArrayElementBuffer
  (const vertex_array_handle& vertexArray, const buffer_handle& buffer);
HOU_GL_API GLint get_max_vertex_attribs();
HOU_GL_API GLint get_max_vertex_attrib_bindings();



}

}

#endif

