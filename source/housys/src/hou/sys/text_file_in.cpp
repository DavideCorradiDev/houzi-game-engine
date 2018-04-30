// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/text_file_in.hpp"

#include "hou/cor/error.hpp"



namespace hou
{

text_file_in::text_file_in(const std::string& path)
  : non_copyable()
  , text_stream_in()
  , m_file(path, file_open_mode::read, file_type::text)
  , m_byte_count(0u)
  , m_element_count(0u)
{}



text_file_in::text_file_in(text_file_in&& other)
  : text_stream_in(std::move(other))
  , m_file(std::move(other.m_file))
  , m_byte_count(std::move(other.m_byte_count))
  , m_element_count(std::move(other.m_element_count))
{}



text_file_in::~text_file_in()
{}



bool text_file_in::eof() const
{
  return m_file.eof();
}



bool text_file_in::error() const
{
  return m_file.error();
}



size_t text_file_in::get_byte_count() const
{
  return m_file.get_byte_count();
}



size_t text_file_in::get_read_byte_count() const
{
  return m_byte_count;
}



size_t text_file_in::get_read_element_count() const
{
  return m_element_count;
}



text_file_in::text_position text_file_in::get_text_pos() const
{
  return create_position_object(m_file.tell());
}



text_stream& text_file_in::set_text_pos(text_file_in::text_position pos)
{
  m_file.seek_set(convert_position_object(pos));
  return *this;
}



void text_file_in::on_read(void* buf, size_t element_size, size_t buf_size)
{
  m_element_count = m_file.read(buf, element_size, buf_size);
  m_byte_count = m_element_count * element_size;
}

}  // namespace hou
