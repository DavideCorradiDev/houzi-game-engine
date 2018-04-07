// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/ImageFormat.hpp"

#define IMAGE_FORMAT_CASE(format, os) \
  case ImageFormat::format: return (os) << #format



namespace hou
{

std::ostream& operator<<(std::ostream& os, ImageFormat format)
{
  switch(format)
  {
    IMAGE_FORMAT_CASE(R, os);
    IMAGE_FORMAT_CASE(RG, os);
    IMAGE_FORMAT_CASE(RGB, os);
    IMAGE_FORMAT_CASE(RGBA, os);
    default: return os;
  }
}

}

