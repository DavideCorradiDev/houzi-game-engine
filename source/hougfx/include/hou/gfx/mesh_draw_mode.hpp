// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_DRAW_MODE_HPP
#define HOU_GFX_MESH_DRAW_MODE_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the draw mode of a ph_mesh. */
enum class mesh_draw_mode : GLenum
{
  /** Single points draw mode. */
  points = GL_POINTS,
  /** line strip draw mode. */
  line_strip = GL_LINE_STRIP,
  /** line loop draw mode. */
  line_loop = GL_LINE_LOOP,
  /** lines draw mode. */
  lines = GL_LINES,
  /** Adjacency line strip draw mode, */
  line_strip_adjacency = GL_LINE_STRIP_ADJACENCY,
  /** Adjacency lines draw mode. */
  line_adjacency = GL_LINES_ADJACENCY,
  /** Triangle strip draw mode. */
  triangle_strip = GL_TRIANGLE_STRIP,
  /** Triangle fan draw mode. */
  triangle_fan = GL_TRIANGLE_FAN,
  /** triangles draw mode. */
  triangles = GL_TRIANGLES,
  /** Adjacency triangle strip draw mode. */
  triangle_strip_adjacency = GL_TRIANGLE_STRIP_ADJACENCY,
  /** patches draw mode. */
  patches = GL_PATCHES,
};

/** Writes a mesh_draw_mode enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param mdm the mesh_draw_mode enum.
 *  \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, mesh_draw_mode mdm);

}  // namespace hou

#endif
