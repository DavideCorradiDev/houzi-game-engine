// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/RenderBuffer.hpp"



namespace hou
{

void RenderBuffer::bind(const RenderBuffer& buffer, RenderBufferTarget target)
{
  gl::bindBuffer(buffer.mHandle, static_cast<GLenum>(target));
}



void RenderBuffer::unbind(RenderBufferTarget target)
{
  gl::unbindBuffer(static_cast<GLenum>(target));
}



RenderBuffer::RenderBuffer(uint size, bool dynamicStorage)
  : NonCopyable()
  , mHandle(gl::BufferHandle::create())
  , mByteCount(size)
{
  std::vector<uint8_t> data(size, 0u);
  gl::setBufferStorage(mHandle, static_cast<GLsizei>(data.size()),
    reinterpret_cast<const GLvoid*>(data.data()),
    dynamicStorage ? GL_DYNAMIC_STORAGE_BIT : 0);
}



RenderBuffer::RenderBuffer(uint size, const void* data, bool dynamicStorage)
  : NonCopyable()
  , mHandle(gl::BufferHandle::create())
  , mByteCount(size)
{
  gl::setBufferStorage(mHandle, static_cast<GLsizei>(size),
    reinterpret_cast<const GLvoid*>(data),
    dynamicStorage ? GL_DYNAMIC_STORAGE_BIT : 0);
}



RenderBuffer::RenderBuffer(RenderBuffer&& other)
  : NonCopyable()
  , mHandle(std::move(other.mHandle))
  , mByteCount(std::move(other.mByteCount))
{}



const gl::BufferHandle& RenderBuffer::getHandle() const
{
  return mHandle;
}



bool RenderBuffer::isBound(RenderBufferTarget target) const
{
  return gl::isBufferBound(mHandle, static_cast<GLenum>(target));
}



uint RenderBuffer::getByteCount() const
{
  return mByteCount;
}

}  // namespace hou
