// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_FILL_MODE_HPP
#define HOU_GFX_MESH_FILL_MODE_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the mesh fill mode of a mesh. */
enum class mesh_fill_mode : GLenum
{
  /** Single points. */
  point = GL_POINT,
  /** Polygon outlines. */
  line = GL_LINE,
  /** Filled polygons. */
  fill = GL_FILL,
};

/** Writes a mesh_fill_mode enum into a stream.
 *
 *  \param os the stream.
 *  \param mfm the mesh_fill_mode enum.
 *  \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, mesh_fill_mode mfm);

}  // namespace hou

#endif
