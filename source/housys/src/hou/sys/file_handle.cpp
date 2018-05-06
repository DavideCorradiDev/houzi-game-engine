// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_handle.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/assertions.hpp"



namespace hou
{

file_handle::file_handle(
  const std::string& path, file_open_mode mode, file_type type)
  : non_copyable()
  , m_file(open_file(path, get_file_mode_string(mode, type)))
{
  HOU_CHECK_N(m_file != nullptr, file_open_error, path);
}



file_handle::file_handle(file_handle&& other)
  : non_copyable()
  , m_file(std::move(other.m_file))
{
  other.m_file = nullptr;
}



file_handle::~file_handle()
{
  if(m_file != nullptr)
  {
    HOU_DISABLE_EXCEPTIONS_BEGIN
    HOU_CHECK_0(fclose(m_file) != EOF, file_close_error);
    HOU_DISABLE_EXCEPTIONS_END
  }
}



file_handle::operator FILE*() const
{
  return m_file;
}



std::string get_file_mode_string(file_open_mode mode, file_type type)
{
  switch(mode)
  {
    case file_open_mode::read:
      return type == file_type::binary ? "rb" : "r";
    case file_open_mode::write:
      return type == file_type::binary ? "wb" : "w";
    case file_open_mode::append:
      return type == file_type::binary ? "ab" : "a";
    default:
      return "";
  }
}



std::string get_filename_extension(const std::string& path)
{
  std::vector<std::string> point_separated_strings;
  split_string(path, '.', std::back_inserter(point_separated_strings));
  // If filename is empty, or if there is no point, return empty extension.
  if(point_separated_strings.size() < 2u)
  {
    return std::string();
  }
  return point_separated_strings.back();
}

}  // namespace hou
