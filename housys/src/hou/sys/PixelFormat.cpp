// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/PixelFormat.hpp"

#define PIXEL_FORMAT_CASE(format, os) \
  case PixelFormat::format:           \
    return (os) << #format



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
  default:
    HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(format));
    return os;
  }
}

}  // namespace hou
