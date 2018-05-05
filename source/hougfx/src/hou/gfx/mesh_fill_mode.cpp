// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/mesh_fill_mode.hpp"

#include "hou/cor/assertions.hpp"

#define MESH_FILL_MODE_CASE(mfm, os) \
  case mesh_fill_mode::mfm: \
    return (os) << #mfm



namespace hou
{

std::ostream& operator<<(std::ostream& os, mesh_fill_mode mfm)
{
  switch(mfm)
  {
    MESH_FILL_MODE_CASE(point, os);
    MESH_FILL_MODE_CASE(line, os);
    MESH_FILL_MODE_CASE(fill, os);
    default:
      return os;
  }
}

}  // namespace hou
