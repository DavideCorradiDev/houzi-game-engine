// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/vertex_buffer_target.hpp"

#include "hou/cor/core_functions.hpp"

#define GFX_VERTEX_BUFFER_TARGET(vbt, os) \
  case vertex_buffer_target::vbt: \
    return (os) << #vbt



namespace hou
{

std::ostream& operator<<(std::ostream& os, vertex_buffer_target vbt)
{
  switch(vbt)
  {
    GFX_VERTEX_BUFFER_TARGET(array_buffer, os);
    GFX_VERTEX_BUFFER_TARGET(element_array_buffer, os);
  }
  return STREAM_VALUE(os, vertex_buffer_target, vbt);
}

}  // namespace hou
