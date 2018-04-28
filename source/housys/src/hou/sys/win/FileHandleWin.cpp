// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/FileHandle.hpp"

#include "hou/cor/CharacterEncodings.hpp"

#include "hou/sys/win/Win.hpp"

#include <sys/stat.h>
#include <sys/types.h>



namespace hou
{

FILE* openFile(const std::string& path, const std::string& mode)
{
  return _wfopen(convertEncoding<Utf8, Wide>(path).c_str()
    , convertEncoding<Utf8, Wide>(mode).c_str());
}



bool checkDir(const std::string& path)
{
  DWORD attr = GetFileAttributesW(convertEncoding<Utf8, Wide>(path).c_str());
  return attr != INVALID_FILE_ATTRIBUTES;
}



bool removeDir(const std::string& path)
{
  return _wremove(convertEncoding<Utf8, Wide>(path).c_str()) == 0;
}



bool renameDir(const std::string& oldPath, const std::string& newPath)
{
  return _wrename(convertEncoding<Utf8, Wide>(oldPath).c_str()
    , convertEncoding<Utf8, Wide>(newPath).c_str()) == 0;
}



size_t getDirByteSize(const std::string& path)
{
  struct _stat64 buf;
  int retval = _wstat64(convertEncoding<Utf8, Wide>(path).c_str(), &buf);
  if(retval == 0)
  {
    return buf.st_size;
  }
  else
  {
    return std::numeric_limits<size_t>::max();
  }
}



int getFileDescriptor(NotNull<FILE*> file)
{
  return _fileno(file.get());
}



size_t getFileByteSize(int fileDescriptor)
{
  return static_cast<size_t>(_filelength(fileDescriptor));
}

}

