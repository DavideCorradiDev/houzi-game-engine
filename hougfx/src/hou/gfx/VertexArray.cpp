// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/VertexArray.hpp"

#include "hou/gfx/VertexBuffer.hpp"
#include "hou/gfx/VertexFormat.hpp"



namespace hou
{

void VertexArray::bind(const VertexArray& vertexArray)
{
  gl::bindVertexArray(vertexArray.mHandle);
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
  : NonCopyable()
  , mHandle(gl::VertexArrayHandle::create())
{}



VertexArray::VertexArray(VertexArray&& other)
  : NonCopyable()
  , mHandle(std::move(other.mHandle))
{}



const gl::VertexArrayHandle& VertexArray::getHandle() const
{
  return mHandle;
}



bool VertexArray::isBound() const
{
  return gl::isVertexArrayBound(mHandle);
}



void VertexArray::setVertexData(
  const VertexBuffer& vb, uint bindingIndex, const VertexFormat& vf)
{
  HOU_EXPECT(bindingIndex <= getMaxBindingIndex());

  gl::setVertexArrayVertexBuffer(mHandle, static_cast<GLuint>(bindingIndex),
    vb.getHandle(), static_cast<GLintptr>(vf.getOffset()),
    static_cast<GLsizei>(vf.getStride()));

  const std::vector<VertexAttribFormat>& vafs = vf.getVertexAttribFormats();
  for(GLuint i = 0; i < vafs.size(); ++i)
  {
    gl::setVertexArrayAttribFormat(mHandle, static_cast<GLuint>(i),
      static_cast<GLint>(vafs[i].getElementCount()),
      static_cast<GLenum>(vafs[i].getType()),
      static_cast<GLboolean>(vafs[i].mustBeNormalized()),
      static_cast<GLuint>(vafs[i].getByteOffset()));
    gl::setVertexArrayAttribBinding(
      mHandle, static_cast<GLuint>(i), static_cast<GLuint>(bindingIndex));
    gl::enableVertexArrayAttrib(mHandle, static_cast<GLuint>(i));
  }
}



void VertexArray::setElementData(const VertexBuffer& eb)
{
  gl::setVertexArrayElementBuffer(mHandle, eb.getHandle());
}

}  // namespace hou
