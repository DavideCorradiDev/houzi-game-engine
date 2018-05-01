// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_TYPE_HPP
#define HOU_GFX_TEXTURE_TYPE_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Represents the type of a texture.
 */
enum class texture_type : GLenum
{
  /** one-dimensional texture. */
  texture1 = GL_TEXTURE_1D,

  /** array_buffer of one-dimensional textures. */
  texture1_array = GL_TEXTURE_1D_ARRAY,

  /** Two-dimensional texture. */
  texture2 = GL_TEXTURE_2D,

  /** array_buffer of two-dimensional textures. */
  texture2_array = GL_TEXTURE_2D_ARRAY,

  /** Three dimensional texture. */
  texture3 = GL_TEXTURE_3D,

  /** Multisample two-dimensional texture. */
  multisample_texture2 = GL_TEXTURE_2D_MULTISAMPLE,

  /** array_buffer of multisample two-dimensional textures. */
  multisample_texture2_array = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,

  // buffer_texture = GL_TEXTURE_BUFFER,
  // rectangle_texture = GL_TEXTURE_RECTANGLE,
  // cube_map_texture = GL_TEXTURE_CUBE_MAP,
  // cube_map_array_texture = GL_TEXTURE_CUBE_MAP_ARRAY,
};

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param type the texture_type enum.
 *
 * \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, texture_type type);

/** Retrieves the number of dimensions associated to a texture_type.
 *
 * \param t the texture type.
 *
 * \return the number of dimensions associated to a texture_type.
 */
constexpr size_t get_texture_type_dimension_count(texture_type t);

/** Checks whether a texture_type represents a mip-mapped texture.
 *
 * \return the result of the check.
 */
constexpr bool is_texture_type_mipmapped(texture_type t);

/** Checks whether a texture_type represents a multisample texture.
 *
 * \return the result of the check.
 */
constexpr bool is_texture_type_multisampled(texture_type t);

}  // namespace hou



#include "hou/gfx/texture_type.inl"

#endif
