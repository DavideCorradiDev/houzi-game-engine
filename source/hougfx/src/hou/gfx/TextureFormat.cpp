// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

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
    TEXTURE_FORMAT_CASE(r, os);
    TEXTURE_FORMAT_CASE(rg, os);
    TEXTURE_FORMAT_CASE(rgb, os);
    TEXTURE_FORMAT_CASE(rgba, os);
    TEXTURE_FORMAT_CASE(depth, os);
    TEXTURE_FORMAT_CASE(stencil, os);
    TEXTURE_FORMAT_CASE(DepthStencil, os);
  default:
    return os;
  }
}

}  // namespace hou
