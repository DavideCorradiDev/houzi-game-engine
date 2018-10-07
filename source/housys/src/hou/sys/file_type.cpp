// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/file_type.hpp"

#include "hou/cor/core_functions.hpp"

#define FILE_TYPE_CASE(ft, os) \
  case file_type::ft: \
    return (os) << #ft



namespace hou
{

std::ostream& operator<<(std::ostream& os, file_type ft)
{
  switch(ft)
  {
    FILE_TYPE_CASE(binary, os);
    FILE_TYPE_CASE(text, os);
  }
  return STREAM_VALUE(os, file_type, ft);
}

}  // namespace hou
