// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_type.hpp"

#define FILE_TYPE_CASE(fom, os) \
  case file_type::fom: \
    return (os) << #fom



namespace hou
{

std::ostream& operator<<(std::ostream& os, file_type fom)
{
  switch(fom)
  {
    FILE_TYPE_CASE(binary, os);
    FILE_TYPE_CASE(text, os);
    default:
      return os;
  }
}

}  // namespace hou
