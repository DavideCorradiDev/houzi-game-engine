// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/RenderBufferTarget.hpp"

#define GFX_RENDER_BUFFER_TARGET(vbt, os) \
  case RenderBufferTarget::vbt:           \
    return (os) << #vbt



namespace hou
{

std::ostream& operator<<(std::ostream& os, RenderBufferTarget vbt)
{
  switch(vbt)
  {
    GFX_RENDER_BUFFER_TARGET(Array, os);
    GFX_RENDER_BUFFER_TARGET(ElementArray, os);
  default:
    return os;
  }
}

}  // namespace hou
