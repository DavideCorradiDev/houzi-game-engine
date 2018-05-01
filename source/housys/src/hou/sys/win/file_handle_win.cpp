// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_handle.hpp"

#include "hou/cor/character_encodings.hpp"

#include "hou/sys/win/win.hpp"

#include <sys/stat.h>
#include <sys/types.h>



namespace hou
{

FILE* open_file(const std::string& path, const std::string& mode)
{
  return _wfopen(convert_encoding<utf8, wide>(path).c_str(),
    convert_encoding<utf8, wide>(mode).c_str());
}



bool check_dir(const std::string& path)
{
  DWORD attr = GetFileAttributesW(convert_encoding<utf8, wide>(path).c_str());
  return attr != INVALID_FILE_ATTRIBUTES;
}



bool remove_dir(const std::string& path)
{
  return _wremove(convert_encoding<utf8, wide>(path).c_str()) == 0;
}



bool rename_dir(const std::string& old_path, const std::string& new_path)
{
  return _wrename(convert_encoding<utf8, wide>(old_path).c_str(),
           convert_encoding<utf8, wide>(new_path).c_str())
    == 0;
}



size_t get_dir_byte_size(const std::string& path)
{
  struct _stat64 buf;
  int retval = _wstat64(convert_encoding<utf8, wide>(path).c_str(), &buf);
  if(retval == 0)
  {
    return buf.st_size;
  }
  else
  {
    return std::numeric_limits<size_t>::max();
  }
}



int get_file_descriptor(not_null<FILE*> file)
{
  return _fileno(file.get());
}



size_t get_file_byte_size(int file_descriptor)
{
  return static_cast<size_t>(_filelength(file_descriptor));
}

}  // namespace hou
