// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_MESH_FILL_MODE_HPP
#define HOU_GFX_MESH_FILL_MODE_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the mesh fill mode of a mesh. */
enum class MeshFillMode : GLenum
{
  /** Single points. */
  Point = GL_POINT,
  /** Polygon outlines. */
  Line = GL_LINE,
  /** Filled polygons. */
  Fill = GL_FILL,
};

/** Writes a MeshFillMode enum into a stream.
 *
 *  \param os the stream.
 *  \param mfm the MeshFillMode enum.
 *  \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, MeshFillMode mfm);

}  // namespace hou

#endif
