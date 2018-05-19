// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/text_file_out.hpp"



namespace hou
{

text_file_out::text_file_out(const std::string& path)
  : non_copyable()
  , text_stream_out()
  , m_file(path, file_open_mode::write, file_type::binary)
  , m_byte_count(0u)
  , m_element_count(0u)
{}



bool text_file_out::eof() const noexcept
{
  return m_file.eof();
}



bool text_file_out::error() const noexcept
{
  return m_file.error();
}



size_t text_file_out::get_byte_count() const noexcept
{
  return m_file.get_byte_count();
}



size_t text_file_out::get_write_byte_count() const noexcept
{
  return m_byte_count;
}



size_t text_file_out::get_write_element_count() const noexcept
{
  return m_element_count;
}



text_file_out::text_position text_file_out::get_text_pos() const
{
  return create_position_object(m_file.tell());
}



text_stream& text_file_out::set_text_pos(text_file_out::text_position pos)
{
  m_file.seek_set(convert_position_object(pos));
  return *this;
}



void text_file_out::on_write(
  const void* buf, size_t element_size, size_t buf_size)
{
  m_file.write(buf, element_size, buf_size);
  m_element_count = buf_size;
  m_byte_count = element_size * buf_size;
}

}  // namespace hou
