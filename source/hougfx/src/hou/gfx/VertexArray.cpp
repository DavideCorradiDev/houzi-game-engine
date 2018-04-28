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
  gl::bindVertexArray(vertexArray.m_handle);
}



void VertexArray::unbind()
{
  gl::unbindVertexArray();
}



uint VertexArray::getMaxBindingIndex()
{
  return gl::getMaxVertexAttribBindings() - 1u;
}



VertexArray::VertexArray()
  : non_copyable()
  , m_handle(gl::VertexArrayHandle::create())
{}



VertexArray::VertexArray(VertexArray&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
{}



const gl::VertexArrayHandle& VertexArray::getHandle() const
{
  return m_handle;
}



bool VertexArray::isBound() const
{
  return gl::isVertexArrayBound(m_handle);
}



void VertexArray::setVertexData(
  const VertexBuffer& vb, uint bindingIndex, const VertexFormat& vf)
{
  HOU_EXPECT(bindingIndex <= getMaxBindingIndex());

  gl::setVertexArrayVertexBuffer(m_handle, static_cast<GLuint>(bindingIndex),
    vb.getHandle(), static_cast<GLintptr>(vf.getOffset()),
    static_cast<GLsizei>(vf.getStride()));

  const std::vector<VertexAttribFormat>& vafs = vf.getVertexAttribFormats();
  for(GLuint i = 0; i < vafs.size(); ++i)
  {
    gl::setVertexArrayAttribFormat(m_handle, static_cast<GLuint>(i),
      static_cast<GLint>(vafs[i].getElementCount()),
      static_cast<GLenum>(vafs[i].get_type()),
      static_cast<GLboolean>(vafs[i].mustBeNormalized()),
      static_cast<GLuint>(vafs[i].getByteOffset()));
    gl::setVertexArrayAttribBinding(
      m_handle, static_cast<GLuint>(i), static_cast<GLuint>(bindingIndex));
    gl::enableVertexArrayAttrib(m_handle, static_cast<GLuint>(i));
  }
}



void VertexArray::setElementData(const VertexBuffer& eb)
{
  gl::setVertexArrayElementBuffer(m_handle, eb.getHandle());
}

}  // namespace hou
