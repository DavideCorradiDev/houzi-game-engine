// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/shader_type.hpp"

#include "hou/cor/core_functions.hpp"

#define GFX_SHADER_TYPE_CASE(st, os) \
  case shader_type::st:               \
    return (os) << #st



namespace hou
{

std::ostream& operator<<(std::ostream& os, shader_type st)
{
  switch(st)
  {
    GFX_SHADER_TYPE_CASE(fragment, os);
    GFX_SHADER_TYPE_CASE(geometry, os);
    GFX_SHADER_TYPE_CASE(vertex, os);
  }
  return STREAM_VALUE(os, shader_type, st);
}

}  // namespace hou
