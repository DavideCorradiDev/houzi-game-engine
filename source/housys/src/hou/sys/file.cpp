// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/narrow_cast.hpp"
#include "hou/cor/std_string.hpp"

#include <cstdio>
#include <vector>



namespace hou
{

namespace
{

const std::string assert_msg_file_tell
  = u8"Could not read a file cursor position.";

}  // namespace



file::file(const std::string& filename, file_open_mode mode, file_type type)
  : non_copyable()
  , m_handle(filename, mode, type)
  , m_eof(false)
  , m_error(false)
{}



bool file::eof() const noexcept
{
  return m_eof;
}



bool file::error() const noexcept
{
  return m_error;
}



size_t file::get_byte_count() const noexcept
{
  return get_file_byte_size(get_file_descriptor(m_handle));
}



long file::tell() const
{
  long pos = ftell(m_handle);
  HOU_CHECK_0(pos != -1L, cursor_error);
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
  HOU_CHECK_0(fflush(m_handle) != EOF, write_error);
}



bool file::getc(char& c)
{
  int retval = fgetc(m_handle);
  update_flags();
  c = narrow_cast<char>(retval);
  if(retval == EOF)
  {
    HOU_CHECK_0(!error(), read_error);
    return false;
  }
  return true;
}



void file::putc(char c)
{
  int retval = fputc(c, m_handle);
  update_flags();
  HOU_CHECK_0(retval != EOF, write_error);
}



size_t file::gets(std::string& str)
{
  const char* retval = fgets(
    const_cast<char*>(str.data()), narrow_cast<int>(str.size()), m_handle);
  update_flags();
  if(retval == nullptr)
  {
    HOU_CHECK_0(!error(), read_error);
    return 0u;
  }
  return std::char_traits<char>::length(retval);
}



void file::puts(const std::string& str)
{
  int retval = fputs(str.c_str(), m_handle);
  update_flags();
  HOU_CHECK_0(retval != EOF, write_error);
}



size_t file::read(void* buf, size_t element_size, size_t buf_size)
{
  size_t count = fread(buf, element_size, buf_size, m_handle);
  update_flags();
  HOU_CHECK_0(count == buf_size || !error(), read_error);
  return count;
}



void file::write(const void* buf, size_t element_size, size_t buf_size)
{
  size_t count = fwrite(buf, element_size, buf_size, m_handle);
  update_flags();
  HOU_CHECK_0(count == buf_size, write_error);
}



void file::seek(long pos, int origin) const
{
  HOU_CHECK_0(fseek(m_handle, pos, origin) == 0, cursor_error);
}



void file::update_flags() noexcept
{
  m_eof = (feof(m_handle) != 0);
  m_error = (ferror(m_handle) != 0);
}

}  // namespace hou
