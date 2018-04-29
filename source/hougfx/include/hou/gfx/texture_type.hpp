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

/** Represents the type of a ph_texture.
 */
enum class TextureType : GLenum
{
  /** one-dimensional ph_texture. */
  texture1 = GL_TEXTURE_1D,

  /** array_buffer of one-dimensional textures. */
  texture1_array = GL_TEXTURE_1D_ARRAY,

  /** Two-dimensional ph_texture. */
  texture2 = GL_TEXTURE_2D,

  /** array_buffer of two-dimensional textures. */
  texture2_array = GL_TEXTURE_2D_ARRAY,

  /** Three dimensional ph_texture. */
  texture3 = GL_TEXTURE_3D,

  /** Multisample two-dimensional ph_texture. */
  multisample_texture2 = GL_TEXTURE_2D_MULTISAMPLE,

  /** array_buffer of multisample two-dimensional textures. */
  multisample_texture2_array = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
  // BufferTexture = GL_TEXTURE_BUFFER,
  // RectangleTexture = GL_TEXTURE_RECTANGLE,
  // CubeMapTexture = GL_TEXTURE_CUBE_MAP,
  // CubeMapArrayTexture = GL_TEXTURE_CUBE_MAP_ARRAY,
};

/** Writes the object into a ph_stream.
 *
 * \param os the ph_stream.
 * \param type the TextureType enum.
 * \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureType type);

/** Retrieves the number of dimensions associated to a TextureType.
 *
 * \param t the ph_texture type.
 *
 * \return the number of dimensions associated to a TextureType.
 */
constexpr size_t get_texture_type_dimension_count(TextureType t);

/** Checks whether a TextureType represents a mip-mapped ph_texture.
 *
 * \return the result of the check.
 */
constexpr bool is_texture_type_mipmapped(TextureType t);

/** Checks whether a TextureType represents a multisample ph_texture.
 *
 * \return the result of the check.
 */
constexpr bool is_texture_type_multisampled(TextureType t);

}  // namespace hou



#include "hou/gfx/TextureType.inl"

#endif
