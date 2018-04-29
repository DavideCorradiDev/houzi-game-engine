// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/VertexArray.hpp"

#include "hou/gfx/VertexBuffer.hpp"
#include "hou/gfx/VertexFormat.hpp"



namespace hou
{

void VertexArray::bind(const VertexArray& vertexArray)
{
  gl::bind_vertex_array(vertexArray.m_handle);
}



void VertexArray::unbind()
{
  gl::unbind_vertex_array();
}



uint VertexArray::getMaxBindingIndex()
{
  return gl::get_max_vertex_attrib_bindings() - 1u;
}



VertexArray::VertexArray()
  : non_copyable()
  , m_handle(gl::vertex_array_handle::create())
{}



VertexArray::VertexArray(VertexArray&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
{}



const gl::vertex_array_handle& VertexArray::get_handle() const
{
  return m_handle;
}



bool VertexArray::isBound() const
{
  return gl::is_vertex_array_bound(m_handle);
}



void VertexArray::setVertexData(
  const VertexBuffer& vb, uint bindingIndex, const VertexFormat& vf)
{
  HOU_EXPECT(bindingIndex <= getMaxBindingIndex());

  gl::set_vertex_array_vertex_buffer(m_handle, static_cast<GLuint>(bindingIndex),
    vb.get_handle(), static_cast<GLintptr>(vf.getOffset()),
    static_cast<GLsizei>(vf.getStride()));

  const std::vector<VertexAttribFormat>& vafs = vf.getVertexAttribFormats();
  for(GLuint i = 0; i < vafs.size(); ++i)
  {
    gl::set_vertex_array_attrib_format(m_handle, static_cast<GLuint>(i),
      static_cast<GLint>(vafs[i].getElementCount()),
      static_cast<GLenum>(vafs[i].get_type()),
      static_cast<GLboolean>(vafs[i].mustBeNormalized()),
      static_cast<GLuint>(vafs[i].getByteOffset()));
    gl::set_vertex_array_attrib_binding(
      m_handle, static_cast<GLuint>(i), static_cast<GLuint>(bindingIndex));
    gl::enable_vertex_array_attrib(m_handle, static_cast<GLuint>(i));
  }
}



void VertexArray::setElementData(const VertexBuffer& eb)
{
  gl::setVertexArrayElementBuffer(m_handle, eb.get_handle());
}

}  // namespace hou
