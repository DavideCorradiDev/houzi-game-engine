// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file.hpp"

#include "hou/sys/sys_error.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/std_string.hpp"

#include <cstdio>
#include <vector>



namespace hou
{

file::file(const std::string& filename, file_open_mode mode, file_type type)
  : non_copyable()
  , m_handle(filename, mode, type)
  , m_eof(false)
  , m_error(false)
{}



file::file(file&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
  , m_eof(std::move(other.m_eof))
  , m_error(std::move(other.m_error))
{}



bool file::eof() const
{
  return m_eof;
}



bool file::error() const
{
  return m_error;
}



size_t file::get_byte_count() const
{
  return get_file_byte_size(get_file_descriptor(m_handle));
}



long file::tell() const
{
  long pos = ftell(m_handle);
  DEPRECATED_HOU_RUNTIME_CHECK(pos != -1L, get_text(sys_error::file_tell));
  return pos;
}



void file::seek_set(long pos)
{
  seek(pos, SEEK_SET);
  update_flags();
}



void file::seek_from_end(long pos)
{
  seek(pos, SEEK_END);
  update_flags();
}



void file::seek_offset(long offset)
{
  seek(offset, SEEK_CUR);
  update_flags();
}



void file::flush() const
{
  DEPRECATED_HOU_RUNTIME_CHECK(fflush(m_handle) != EOF, get_text(sys_error::file_flush));
}



bool file::getc(char& c)
{
  int retval = fgetc(m_handle);
  update_flags();
  c = static_cast<char>(retval);
  if(retval == EOF)
  {
    DEPRECATED_HOU_RUNTIME_CHECK(!error(), get_text(sys_error::file_read));
    return false;
  }
  return true;
}



void file::putc(char c)
{
  int retval = fputc(c, m_handle);
  update_flags();
  DEPRECATED_HOU_RUNTIME_CHECK(retval != EOF, get_text(sys_error::file_write));
}



size_t file::gets(std::string& str)
{
  const char* retval
    = fgets(const_cast<char*>(str.data()), str.size(), m_handle);
  update_flags();
  if(retval == nullptr)
  {
    DEPRECATED_HOU_RUNTIME_CHECK(!error(), get_text(sys_error::file_read));
    return 0u;
  }
  return std::char_traits<char>::length(retval);
}



void file::puts(const std::string& str)
{
  int retval = fputs(str.c_str(), m_handle);
  update_flags();
  DEPRECATED_HOU_RUNTIME_CHECK(retval != EOF, get_text(sys_error::file_write));
}



size_t file::read(void* buf, size_t element_size, size_t buf_size)
{
  size_t count = fread(buf, element_size, buf_size, m_handle);
  update_flags();
  DEPRECATED_HOU_RUNTIME_CHECK(
    count == buf_size || !error(), get_text(sys_error::file_read));
  return count;
}



void file::write(const void* buf, size_t element_size, size_t buf_size)
{
  size_t count = fwrite(buf, element_size, buf_size, m_handle);
  update_flags();
  DEPRECATED_HOU_RUNTIME_CHECK(count == buf_size, get_text(sys_error::file_write));
}



void file::seek(long pos, int origin) const
{
  DEPRECATED_HOU_RUNTIME_CHECK(
    fseek(m_handle, pos, origin) == 0, get_text(sys_error::file_seek));
}



void file::update_flags()
{
  m_eof = (feof(m_handle) != 0);
  m_error = (ferror(m_handle) != 0);
}

}  // namespace hou
