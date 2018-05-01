// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_BUFFER_TARGET_HPP
#define HOU_GFX_VERTEX_BUFFER_TARGET_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Target for vertex buffer binding.
 */
enum class vertex_buffer_target : GLenum
{
  /** Array buffer. */
  array_buffer = GL_ARRAY_BUFFER,
  /** Element array buffer. */
  element_array_buffer = GL_ELEMENT_ARRAY_BUFFER,
};

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param vbt the vertex_buffer_target enum.
 *
 * \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(
  std::ostream& os, vertex_buffer_target vbt);

}  // namespace hou

#endif
