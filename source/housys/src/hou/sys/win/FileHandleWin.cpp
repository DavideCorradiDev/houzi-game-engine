// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/FileHandle.hpp"

#include "hou/cor/character_encodings.hpp"

#include "hou/sys/win/Win.hpp"

#include <sys/stat.h>
#include <sys/types.h>



namespace hou
{

FILE* openFile(const std::string& path, const std::string& mode)
{
  return _wfopen(convertEncoding<utf8, wide>(path).c_str()
    , convertEncoding<utf8, wide>(mode).c_str());
}



bool checkDir(const std::string& path)
{
  DWORD attr = GetFileAttributesW(convertEncoding<utf8, wide>(path).c_str());
  return attr != INVALID_FILE_ATTRIBUTES;
}



bool removeDir(const std::string& path)
{
  return _wremove(convertEncoding<utf8, wide>(path).c_str()) == 0;
}



bool renameDir(const std::string& oldPath, const std::string& newPath)
{
  return _wrename(convertEncoding<utf8, wide>(oldPath).c_str()
    , convertEncoding<utf8, wide>(newPath).c_str()) == 0;
}



size_t getDirByteSize(const std::string& path)
{
  struct _stat64 buf;
  int retval = _wstat64(convertEncoding<utf8, wide>(path).c_str(), &buf);
  if(retval == 0)
  {
    return buf.st_size;
  }
  else
  {
    return std::numeric_limits<size_t>::max();
  }
}



int getFileDescriptor(not_null<FILE*> file)
{
  return _fileno(file.get());
}



size_t getFileByteSize(int fileDescriptor)
{
  return static_cast<size_t>(_filelength(fileDescriptor));
}

}

