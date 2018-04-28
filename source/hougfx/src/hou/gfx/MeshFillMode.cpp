// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/MeshFillMode.hpp"

#include "hou/cor/error.hpp"

#define MESH_FILL_MODE_CASE(mfm, os) \
  case MeshFillMode::mfm:            \
    return (os) << #mfm



namespace hou
{

std::ostream& operator<<(std::ostream& os, MeshFillMode mfm)
{
  switch(mfm)
  {
    MESH_FILL_MODE_CASE(Point, os);
    MESH_FILL_MODE_CASE(Line, os);
    MESH_FILL_MODE_CASE(Fill, os);
  default:
    return os;
  }
}

}  // namespace hou
