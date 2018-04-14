// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/MeshDrawMode.hpp"

#include "hou/cor/Error.hpp"

#define MESH_DRAW_MODE_CASE(mdm, os) \
  case MeshDrawMode::mdm:            \
    return (os) << #mdm



namespace hou
{

std::ostream& operator<<(std::ostream& os, MeshDrawMode mdm)
{
  switch(mdm)
  {
    MESH_DRAW_MODE_CASE(Points, os);
    MESH_DRAW_MODE_CASE(LineStrip, os);
    MESH_DRAW_MODE_CASE(LineLoop, os);
    MESH_DRAW_MODE_CASE(Lines, os);
    MESH_DRAW_MODE_CASE(LineStripAdjacency, os);
    MESH_DRAW_MODE_CASE(LinesAdjacency, os);
    MESH_DRAW_MODE_CASE(TriangleStrip, os);
    MESH_DRAW_MODE_CASE(TriangleFan, os);
    MESH_DRAW_MODE_CASE(Triangles, os);
    MESH_DRAW_MODE_CASE(TriangleStripAdjacency, os);
    MESH_DRAW_MODE_CASE(Patches, os);
  default:
    return os;
  }
}

}  // namespace hou
