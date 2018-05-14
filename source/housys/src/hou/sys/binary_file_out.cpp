// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/binary_file_out.hpp"



namespace hou
{

binary_file_out::binary_file_out(const std::string& path)
  : non_copyable()
  , binary_stream_out()
  , m_file(path, file_open_mode::write, file_type::binary)
  , m_byte_count(0u)
  , m_element_count(0u)
{}



binary_file_out::binary_file_out(binary_file_out&& other) noexcept
  : binary_stream_out(std::move(other))
  , m_file(std::move(other.m_file))
  , m_byte_count(std::move(other.m_byte_count))
  , m_element_count(std::move(other.m_element_count))
{}



bool binary_file_out::eof() const noexcept
{
  return m_file.eof();
}



bool binary_file_out::error() const noexcept
{
  return m_file.error();
}



size_t binary_file_out::get_byte_count() const noexcept
{
  return m_file.get_byte_count();
}



size_t binary_file_out::get_write_byte_count() const noexcept
{
  return m_byte_count;
}



size_t binary_file_out::get_write_element_count() const noexcept
{
  return m_element_count;
}



binary_file_out::byte_position binary_file_out::get_byte_pos() const
{
  return m_file.tell();
}



binary_stream& binary_file_out::set_byte_pos(binary_file_out::byte_position pos)
{
  m_file.seek_set(pos);
  return *this;
}



binary_stream& binary_file_out::move_byte_pos(
  binary_file_out::byte_offset offset)
{
  m_file.seek_offset(offset);
  return *this;
}



void binary_file_out::on_write(
  const void* buf, size_t element_size, size_t buf_size)
{
  m_file.write(buf, element_size, buf_size);
  m_element_count = buf_size;
  m_byte_count = element_size * buf_size;
}

}  // namespace hou
