// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

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



VertexBuffer::VertexBuffer(uint byteCount, bool dynamicStorage)
  : NonCopyable()
  , mHandle(gl::BufferHandle::create())
  , mByteCount(byteCount)
{
  std::vector<uint8_t> data(byteCount, 0u);
  gl::setBufferStorage(mHandle, static_cast<GLsizei>(data.size()),
    reinterpret_cast<const GLvoid*>(data.data()),
    dynamicStorage ? GL_DYNAMIC_STORAGE_BIT : 0);
}



VertexBuffer::VertexBuffer(uint size, const void* data, bool dynamicStorage)
  : NonCopyable()
  , mHandle(gl::BufferHandle::create())
  , mByteCount(size)
{
  gl::setBufferStorage(mHandle, static_cast<GLsizei>(size),
    reinterpret_cast<const GLvoid*>(data),
    dynamicStorage ? GL_DYNAMIC_STORAGE_BIT : 0);
}



VertexBuffer::VertexBuffer(VertexBuffer&& other)
  : NonCopyable()
  , mHandle(std::move(other.mHandle))
  , mByteCount(std::move(other.mByteCount))
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

}  // namespace hou
