// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/binary_file_in.hpp"



namespace hou
{

binary_file_in::binary_file_in(const std::string& path)
  : non_copyable()
  , binary_stream_in()
  , m_file(path, file_open_mode::read, file_type::binary)
  , m_byte_count(0u)
  , m_element_count(0u)
{}



binary_file_in::binary_file_in(binary_file_in&& other)
  : binary_stream_in(std::move(other))
  , m_file(std::move(other.m_file))
  , m_byte_count(std::move(other.m_byte_count))
  , m_element_count(std::move(other.m_element_count))
{}



binary_file_in::~binary_file_in()
{}



bool binary_file_in::eof() const
{
  return m_file.eof();
}



bool binary_file_in::error() const
{
  return m_file.error();
}



size_t binary_file_in::get_byte_count() const
{
  return m_file.get_byte_count();
}



size_t binary_file_in::get_read_byte_count() const
{
  return m_byte_count;
}



size_t binary_file_in::get_read_element_count() const
{
  return m_element_count;
}



binary_file_in::byte_position binary_file_in::get_byte_pos() const
{
  return m_file.tell();
}



binary_stream& binary_file_in::set_byte_pos(binary_file_in::byte_position pos)
{
  m_file.seek_set(pos);
  return *this;
}



binary_stream& binary_file_in::move_byte_pos(binary_file_in::byte_offset offset)
{
  m_file.seek_offset(offset);
  return *this;
}



void binary_file_in::on_read(void* buf, size_t element_size, size_t buf_size)
{
  m_element_count = m_file.read(buf, element_size, buf_size);
  m_byte_count = m_element_count * element_size;
}

}  // namespace hou
