// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/TextureFormat.hpp"

#define TEXTURE_FORMAT_CASE(format, os) \
  case TextureFormat::format:           \
    return (os) << #format

namespace hou
{

std::ostream &operator<<(std::ostream &os, TextureFormat format)
{
  switch(format)
  {
    TEXTURE_FORMAT_CASE(R, os);
    TEXTURE_FORMAT_CASE(RG, os);
    TEXTURE_FORMAT_CASE(RGB, os);
    TEXTURE_FORMAT_CASE(RGBA, os);
    TEXTURE_FORMAT_CASE(Depth, os);
    TEXTURE_FORMAT_CASE(Stencil, os);
    TEXTURE_FORMAT_CASE(DepthStencil, os);
  default:
    return os;
  }
}

}  // namespace hou
