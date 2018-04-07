// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/PixelFormat.hpp"

#define PIXEL_FORMAT_CASE(format, os) \
  case PixelFormat::format: return (os) << #format



namespace hou
{

std::ostream& operator<<(std::ostream& os, PixelFormat format)
{
  switch(format)
  {
    PIXEL_FORMAT_CASE(R, os);
    PIXEL_FORMAT_CASE(RG, os);
    PIXEL_FORMAT_CASE(RGB, os);
    PIXEL_FORMAT_CASE(RGBA, os);
    default: return os;
  }
}

}


