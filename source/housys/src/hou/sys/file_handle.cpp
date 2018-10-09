// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_handle.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/cor_exceptions.hpp"
#include "hou/cor/narrow_cast.hpp"



namespace hou
{

file_handle::file_handle(
  const std::string& path, file_open_mode mode, file_type type)
  : non_copyable()
  , m_file(open_file(path, get_file_mode_string(mode, type)))
{
  HOU_CHECK_N(m_file != nullptr, file_open_error, path);
}



file_handle::file_handle(file_handle&& other) noexcept
  : non_copyable()
  , m_file(std::move(other.m_file))
{
  other.m_file = nullptr;
}



void file_handle::close()
{
  HOU_CHECK_0(fflush(m_file) != EOF, write_error);
  HOU_CHECK_0(close_file(m_file), file_close_error);
  m_file = nullptr;
}



file_handle::~file_handle()
{
  if(m_file != nullptr)
  {
    close();
  }
}



file_handle::operator FILE*() const noexcept
{
  return m_file;
}



std::string get_file_mode_string(file_open_mode mode, file_type type) noexcept
{
  switch(mode)
  {
    case file_open_mode::read:
      return type == file_type::binary ? "rb" : "r";
    case file_open_mode::write:
      return type == file_type::binary ? "wb" : "w";
    case file_open_mode::append:
      return type == file_type::binary ? "ab" : "a";
  }
  HOU_ERROR_N(invalid_enum,
    narrow_cast<int>(static_cast<std::underlying_type<file_type>::type>(type)));
  return "";
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



bool close_file(FILE* f) noexcept
{
  return f == nullptr ? false : (fclose(f) != EOF);
}

}  // namespace hou
