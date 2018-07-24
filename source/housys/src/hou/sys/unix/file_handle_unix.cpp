// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_handle.hpp"

#include "hou/cor/narrow_cast.hpp"

#include <limits>
#include <sys/stat.h>



namespace hou
{

FILE* open_file(const std::string& path, const std::string& mode) noexcept
{
  return fopen(path.c_str(), mode.c_str());
}



bool check_dir(const std::string& path) noexcept
{
  struct stat buf;
  return stat(path.c_str(), &buf) == 0;
}



bool remove_dir(const std::string& path) noexcept
{
  return std::remove(path.c_str()) == 0u;
}



bool rename_dir(
  const std::string& old_path, const std::string& new_path) noexcept
{
  return std::rename(old_path.c_str(), new_path.c_str()) == 0u;
}



size_t get_dir_byte_size(const std::string& path) noexcept
{
  struct stat buf;
  if(stat(path.c_str(), &buf) == 0)
  {
    return narrow_cast<size_t>(buf.st_size);
  }
  else
  {
    return std::numeric_limits<size_t>::max();
  }
}



int get_file_descriptor(FILE* file) noexcept
{
  return file == nullptr ? -1 : fileno(file);
}



size_t get_file_byte_size(int file_descriptor) noexcept
{
  struct stat buf;
  if(fstat(file_descriptor, &buf) == 0u)
  {
    return narrow_cast<size_t>(buf.st_size);
  }
  else
  {
    return std::numeric_limits<size_t>::max();
  }
}

}  // namespace hou
