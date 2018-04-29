// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/VertexBuffer.hpp"



namespace hou
{

void VertexBuffer::bind(const VertexBuffer& buffer, VertexBufferTarget target)
{
  gl::bind_buffer(buffer.m_handle, static_cast<GLenum>(target));
}



void VertexBuffer::unbind(VertexBufferTarget target)
{
  gl::unbind_buffer(static_cast<GLenum>(target));
}



VertexBuffer::VertexBuffer(uint byteCount, bool dynamicStorage)
  : non_copyable()
  , m_handle(gl::buffer_handle::create())
  , m_byte_count(byteCount)
{
  std::vector<uint8_t> data(byteCount, 0u);
  gl::set_buffer_storage(m_handle, static_cast<GLsizei>(data.size()),
    reinterpret_cast<const GLvoid*>(data.data()),
    dynamicStorage ? GL_DYNAMIC_STORAGE_BIT : 0);
}



VertexBuffer::VertexBuffer(uint size, const void* data, bool dynamicStorage)
  : non_copyable()
  , m_handle(gl::buffer_handle::create())
  , m_byte_count(size)
{
  gl::set_buffer_storage(m_handle, static_cast<GLsizei>(size),
    reinterpret_cast<const GLvoid*>(data),
    dynamicStorage ? GL_DYNAMIC_STORAGE_BIT : 0);
}



VertexBuffer::VertexBuffer(VertexBuffer&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
  , m_byte_count(std::move(other.m_byte_count))
{}



const gl::buffer_handle& VertexBuffer::get_handle() const
{
  return m_handle;
}



bool VertexBuffer::isBound(VertexBufferTarget target) const
{
  return gl::is_buffer_bound(m_handle, static_cast<GLenum>(target));
}



uint VertexBuffer::get_byte_count() const
{
  return m_byte_count;
}

}  // namespace hou
