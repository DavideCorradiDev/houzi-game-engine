// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/SysError.hpp"



namespace hou
{

std::string get_text(SysError ec)
{
  switch(ec)
  {
    case SysError::FileClose:
      return u8"Error closing file (fid = %d).";
    case SysError::FileFlush:
      return u8"Error flushing file buffer.";
    case SysError::FileOpen:
      return u8"Error opening file: '%s'.";
    case SysError::FileRead:
      return u8"Error reading from file.";
    case SysError::FileSeek:
      return u8"Error setting file cursor.";
    case SysError::FileTell:
      return u8"Error getting file cursor.";
    case SysError::FileWrite:
      return u8"Error writing to file.";
    case SysError::ImageBmpRead:
      return u8"Error reading BMP image from path '%s'.";
    case SysError::ImageBmpWrite:
      return u8"Error writing BMP image to path '%s'.";
    case SysError::ImagePngRead:
      return u8"Error reading PNG image from path '%s'.";
    case SysError::ImageJpgRead:
      return u8"Error reading JPG image from path '%s'.";
    default:
      return u8"";
  }
}

}

