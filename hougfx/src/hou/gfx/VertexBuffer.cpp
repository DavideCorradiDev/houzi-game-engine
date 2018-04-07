// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/VertexBuffer.hpp"



namespace hou
{

void VertexBuffer::bind(const VertexBuffer& buffer, VertexBufferTarget target)
{
  gl::bindBuffer(buffer.mHandle, static_cast<GLenum>(target));
}



void VertexBuffer::unbind(VertexBufferTarget target)
{
  gl::unbindBuffer(static_cast<GLenum>(target));
}



VertexBuffer::VertexBuffer(uint byteCount, VertexBufferAttributes attributes)
  : VertexBuffer(std::vector<uint8_t>(byteCount, 0u), attributes)
{}



VertexBuffer::VertexBuffer(VertexBuffer&& other)
  : NonCopyable()
  , mHandle(std::move(other.mHandle))
  , mByteCount(other.mByteCount)
{}



const gl::BufferHandle& VertexBuffer::getHandle() const
{
  return mHandle;
}



bool VertexBuffer::isBound(VertexBufferTarget target) const
{
  return gl::isBufferBound(mHandle, static_cast<GLenum>(target));
}



uint VertexBuffer::getByteCount() const
{
  return mByteCount;
}



VertexBuffer::VertexBuffer(
  uint byteCount, const void* data, VertexBufferAttributes attributes)
  : NonCopyable()
  , mHandle(gl::BufferHandle::create())
  , mByteCount(byteCount)
{
  gl::setBufferStorage(mHandle, static_cast<GLsizei>(byteCount),
    reinterpret_cast<const GLvoid*>(data), static_cast<GLbitfield>(attributes));
}

}  // namespace hou
