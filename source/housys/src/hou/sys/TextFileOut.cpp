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



text_file_out::text_file_out(text_file_out&& other)
  : text_stream_out(std::move(other))
  , m_file(std::move(other.m_file))
  , m_byte_count(std::move(other.m_byte_count))
  , m_element_count(std::move(other.m_element_count))
{}



text_file_out::~text_file_out()
{}



bool text_file_out::eof() const
{
  return m_file.eof();
}



bool text_file_out::error() const
{
  return m_file.error();
}



size_t text_file_out::get_byte_count() const
{
  return m_file.get_byte_count();
}



size_t text_file_out::get_write_byte_count() const
{
  return m_byte_count;
}



size_t text_file_out::get_write_element_count() const
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



void text_file_out::on_write(const void* buf, size_t elementSize, size_t bufSize)
{
  m_file.write(buf, elementSize, bufSize);
  m_element_count = bufSize;
  m_byte_count = elementSize * bufSize;
}

}

