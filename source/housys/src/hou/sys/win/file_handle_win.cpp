// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_handle.hpp"

#include "hou/cor/character_encodings.hpp"
#include "hou/cor/narrow_cast.hpp"

#include "hou/sys/win/win.hpp"

#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>



namespace hou
{

FILE* open_file(const std::string& path, const std::string& mode) noexcept
{
  return _wfopen(convert_encoding<wide, utf8>(path).c_str(),
    convert_encoding<wide, utf8>(mode).c_str());
}



bool check_dir(const std::string& path) noexcept
{
  DWORD attr = GetFileAttributesW(convert_encoding<wide, utf8>(path).c_str());
  return attr != INVALID_FILE_ATTRIBUTES;
}



bool remove_dir(const std::string& path) noexcept
{
  return (_wremove(convert_encoding<wide, utf8>(path).c_str()) == 0);
}



bool rename_dir(
  const std::string& old_path, const std::string& new_path) noexcept
{
  return (_wrename(convert_encoding<wide, utf8>(old_path).c_str(),
    convert_encoding<wide, utf8>(new_path).c_str()) == 0);
}



size_t get_dir_byte_size(const std::string& path) noexcept
{
  struct _stat64 buf;
  int retval = _wstat64(convert_encoding<wide, utf8>(path).c_str(), &buf);
  if(retval == 0)
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
  return _fileno(file);
}



size_t get_file_byte_size(int file_descriptor) noexcept
{
  long length = _filelength(file_descriptor);
  return length == -1L ? std::numeric_limits<size_t>::max()
                       : static_cast<size_t>(length);
}

}  // namespace hou
