// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/FileType.hpp"

#define FILE_TYPE_CASE(fom, os) \
  case FileType::fom: return (os) << #fom



namespace hou
{

std::ostream& operator<<(std::ostream& os, FileType fom)
{
  switch(fom)
  {
    FILE_TYPE_CASE(Binary, os);
    FILE_TYPE_CASE(Text, os);
    default: return os;
  }
}

}




