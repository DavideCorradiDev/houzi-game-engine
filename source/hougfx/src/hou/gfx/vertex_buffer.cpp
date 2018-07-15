// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/vertex_buffer.hpp"

#include "hou/cor/narrow_cast.hpp"



namespace hou
{

void vertex_buffer::bind(
  const vertex_buffer& buffer, vertex_buffer_target target)
{
  gl::bind_buffer(buffer.m_handle, static_cast<GLenum>(target));
}



void vertex_buffer::unbind(vertex_buffer_target target)
{
  gl::unbind_buffer(static_cast<GLenum>(target));
}



vertex_buffer::vertex_buffer(size_t byte_count, bool dynamic_storage)
  : non_copyable()
  , m_handle(gl::buffer_handle::create())
  , m_byte_count(byte_count)
{
  std::vector<uint8_t> data(byte_count, 0u);
  gl::set_buffer_storage(m_handle, narrow_cast<GLsizei>(data.size()),
    reinterpret_cast<const GLvoid*>(data.data()),
    dynamic_storage ? GL_DYNAMIC_STORAGE_BIT : 0);
}



vertex_buffer::vertex_buffer(
  size_t byte_count, const void* data, bool dynamic_storage)
  : non_copyable()
  , m_handle(gl::buffer_handle::create())
  , m_byte_count(byte_count)
{
  gl::set_buffer_storage(m_handle, narrow_cast<GLsizei>(byte_count),
    reinterpret_cast<const GLvoid*>(data),
    dynamic_storage ? GL_DYNAMIC_STORAGE_BIT : 0);
}



const gl::buffer_handle& vertex_buffer::get_handle() const noexcept
{
  return m_handle;
}



bool vertex_buffer::is_bound(vertex_buffer_target target) const
{
  return gl::is_buffer_bound(m_handle, static_cast<GLenum>(target));
}



size_t vertex_buffer::get_byte_count() const
{
  return m_byte_count;
}

}  // namespace hou
