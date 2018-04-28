// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/ImageFormat.hpp"

#define IMAGE_FORMAT_CASE(format, os) \
  case ImageFormat::format: return (os) << #format



namespace hou
{

std::ostream& operator<<(std::ostream& os, ImageFormat format)
{
  switch(format)
  {
    IMAGE_FORMAT_CASE(r, os);
    IMAGE_FORMAT_CASE(rg, os);
    IMAGE_FORMAT_CASE(rgb, os);
    IMAGE_FORMAT_CASE(rgba, os);
    default: return os;
  }
}

}

