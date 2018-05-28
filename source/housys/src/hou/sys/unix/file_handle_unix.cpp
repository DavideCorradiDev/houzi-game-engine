// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_handle.hpp"

#include "hou/cor/exception.hpp"



namespace hou
{

FILE* open_file(const std::string& path, const std::string& mode) noexcept
{
  HOU_UNREACHABLE();
  return nullptr;
}



bool check_dir(const std::string& path) noexcept
{
  HOU_UNREACHABLE();
  return false;
}



bool remove_dir(const std::string& path) noexcept
{
  HOU_UNREACHABLE();
  return false;
}



bool rename_dir(
  const std::string& old_path, const std::string& new_path) noexcept
{
  HOU_UNREACHABLE();
  return false;
}



size_t get_dir_byte_size(const std::string& path) noexcept
{
  HOU_UNREACHABLE();
  return 0u;
}



int get_file_descriptor(FILE* file) noexcept
{
  HOU_UNREACHABLE();
  return 0;
}



size_t get_file_byte_size(int file_descriptor) noexcept
{
  HOU_UNREACHABLE();
  return 0u;
}

}
