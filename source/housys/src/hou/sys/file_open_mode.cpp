// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_open_mode.hpp"

#define FILE_OPEN_MODE_CASE(fom, os) \
  case file_open_mode::fom: return (os) << #fom



namespace hou
{

std::ostream& operator<<(std::ostream& os, file_open_mode fom)
{
  switch(fom)
  {
    FILE_OPEN_MODE_CASE(read, os);
    FILE_OPEN_MODE_CASE(write, os);
    FILE_OPEN_MODE_CASE(append, os);
    default: return os;
  }
}

}



