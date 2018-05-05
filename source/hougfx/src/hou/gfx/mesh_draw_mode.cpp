// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/mesh_draw_mode.hpp"

#include "hou/cor/assertions.hpp"

#define MESH_DRAW_MODE_CASE(mdm, os) \
  case mesh_draw_mode::mdm: \
    return (os) << #mdm



namespace hou
{

std::ostream& operator<<(std::ostream& os, mesh_draw_mode mdm)
{
  switch(mdm)
  {
    MESH_DRAW_MODE_CASE(points, os);
    MESH_DRAW_MODE_CASE(line_strip, os);
    MESH_DRAW_MODE_CASE(line_loop, os);
    MESH_DRAW_MODE_CASE(lines, os);
    MESH_DRAW_MODE_CASE(line_strip_adjacency, os);
    MESH_DRAW_MODE_CASE(line_adjacency, os);
    MESH_DRAW_MODE_CASE(triangle_strip, os);
    MESH_DRAW_MODE_CASE(triangle_fan, os);
    MESH_DRAW_MODE_CASE(triangles, os);
    MESH_DRAW_MODE_CASE(triangle_strip_adjacency, os);
    MESH_DRAW_MODE_CASE(patches, os);
    default:
      return os;
  }
}

}  // namespace hou
