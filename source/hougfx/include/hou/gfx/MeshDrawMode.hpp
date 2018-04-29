// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_DRAW_MODE_HPP
#define HOU_GFX_MESH_DRAW_MODE_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the draw mode of a mesh. */
enum class MeshDrawMode : GLenum
{
  /** Single points draw mode. */
  Points = GL_POINTS,
  /** Line strip draw mode. */
  LineStrip = GL_LINE_STRIP,
  /** Line loop draw mode. */
  LineLoop = GL_LINE_LOOP,
  /** Lines draw mode. */
  Lines = GL_LINES,
  /** Adjacency line strip draw mode, */
  LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
  /** Adjacency lines draw mode. */
  LinesAdjacency = GL_LINES_ADJACENCY,
  /** Triangle strip draw mode. */
  TriangleStrip = GL_TRIANGLE_STRIP,
  /** Triangle fan draw mode. */
  TriangleFan = GL_TRIANGLE_FAN,
  /** Triangles draw mode. */
  Triangles = GL_TRIANGLES,
  /** Adjacency triangle strip draw mode. */
  TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
  /** Patches draw mode. */
  Patches = GL_PATCHES,
};

/** Writes a MeshDrawMode enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param mdm the MeshDrawMode enum.
 *  \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, MeshDrawMode mdm);

}  // namespace hou

#endif
