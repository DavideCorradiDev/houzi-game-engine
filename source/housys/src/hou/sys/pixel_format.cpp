// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/pixel_format.hpp"

#include "hou/cor/exception.hpp"

#define PIXEL_FORMAT_CASE(format, os)                                          \
  case pixel_format::format:                                                   \
    return (os) << #format



namespace hou
{

std::ostream& operator<<(std::ostream& os, pixel_format format)
{
  switch(format)
  {
    PIXEL_FORMAT_CASE(r, os);
    PIXEL_FORMAT_CASE(rg, os);
    PIXEL_FORMAT_CASE(rgb, os);
    PIXEL_FORMAT_CASE(rgba, os);
  }
  HOU_UNREACHABLE();
  return os;
}

}  // namespace hou
