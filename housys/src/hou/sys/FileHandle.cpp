// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/FileHandle.hpp"

#include "hou/sys/SysError.hpp"

#include "hou/cor/Error.hpp"



namespace hou
{

FileHandle::FileHandle(const std::string& path, FileOpenMode mode, FileType type)
  : NonCopyable()
  , mFile(openFile(path, getFileModeString(mode, type)))
{
  HOU_RUNTIME_CHECK(mFile != nullptr, getText(SysError::FileOpen), path.c_str());
}



FileHandle::FileHandle(FileHandle&& other)
  : NonCopyable()
  , mFile(std::move(other.mFile))
{
  other.mFile = nullptr;
}



FileHandle::~FileHandle()
{
  if(mFile != nullptr)
  {
    HOU_FATAL_CHECK(fclose(mFile) != EOF, getText(SysError::FileClose)
      , getFileDescriptor(mFile));
  }
}



FileHandle::operator FILE*() const
{
  return mFile;
}



std::string getFileModeString(FileOpenMode mode, FileType type)
{
  switch(mode)
  {
    case FileOpenMode::Read:
      return type == FileType::Binary ? "rb" : "r";
    case FileOpenMode::Write:
      return type == FileType::Binary ? "wb" : "w";
    case FileOpenMode::Append:
      return type == FileType::Binary ? "ab" : "a";
    default:
      return "";
  }
}



std::string getFilenameExtension(const std::string& path)
{
  std::vector<std::string> pointSeparatedStrings;
  splitString(path, '.', std::back_inserter(pointSeparatedStrings));
  // If filename is empty, or if there is no point, return empty extension.
  if(pointSeparatedStrings.size() < 2u)
  {
    return std::string();
  }
  return pointSeparatedStrings.back();
}

}

