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
enum class TextureType : GLenum
{
  /** One-dimensional texture. */
  Texture1 = GL_TEXTURE_1D,

  /** Array of one-dimensional textures. */
  Texture1Array = GL_TEXTURE_1D_ARRAY,

  /** Two-dimensional texture. */
  Texture2 = GL_TEXTURE_2D,

  /** Array of two-dimensional textures. */
  Texture2Array = GL_TEXTURE_2D_ARRAY,

  /** Three dimensional texture. */
  Texture3 = GL_TEXTURE_3D,

  /** Multisample two-dimensional texture. */
  MultisampleTexture2 = GL_TEXTURE_2D_MULTISAMPLE,

  /** Array of multisample two-dimensional textures. */
  MultisampleTexture2Array = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
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
 * \param t the texture type.
 *
 * \return the number of dimensions associated to a TextureType.
 */
constexpr size_t getTextureTypeDimensionCount(TextureType t);

/** Checks whether a TextureType represents a mip-mapped texture.
 *
 * \return the result of the check.
 */
constexpr bool isTextureTypeMipMapped(TextureType t);

/** Checks whether a TextureType represents a multisample texture.
 *
 * \return the result of the check.
 */
constexpr bool isTextureTypeMultisampled(TextureType t);

}  // namespace hou



#include "hou/gfx/TextureType.inl"

#endif
