// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/FileOpenMode.hpp"

#define FILE_OPEN_MODE_CASE(fom, os) \
  case FileOpenMode::fom: return (os) << #fom



namespace hou
{

std::ostream& operator<<(std::ostream& os, FileOpenMode fom)
{
  switch(fom)
  {
    FILE_OPEN_MODE_CASE(Read, os);
    FILE_OPEN_MODE_CASE(Write, os);
    FILE_OPEN_MODE_CASE(Append, os);
    default: return os;
  }
}

}



