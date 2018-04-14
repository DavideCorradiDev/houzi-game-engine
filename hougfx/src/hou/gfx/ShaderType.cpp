// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/ShaderType.hpp"

#define GFX_SHADER_TYPE_CASE(st, os) \
  case ShaderType::st:               \
    return (os) << #st



namespace hou
{

std::ostream& operator<<(std::ostream& os, ShaderType st)
{
  switch(st)
  {
    GFX_SHADER_TYPE_CASE(Fragment, os);
    GFX_SHADER_TYPE_CASE(Geometry, os);
    GFX_SHADER_TYPE_CASE(Vertex, os);
  default:
    return os;
  }
}

}  // namespace hou
