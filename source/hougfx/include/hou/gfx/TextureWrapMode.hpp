// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_WRAP_MODE_HPP
#define HOU_GFX_TEXTURE_WRAP_MODE_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the clamp mode of a texture. */
enum class TextureWrapMode : GLenum
{
  /** Pixels sampled outside the texture will have the ph_color of the
   * corresponding edge ph_pixel. */
  ClampToEdge = GL_CLAMP_TO_EDGE,
  /** Pixels sampled outside the texture  will have the ph_color of the mirrored
   *  edge ph_pixel. */
  MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE,
  /** Pixels sampled outside the texture will have the border ph_color. */
  ClampToBorder = GL_CLAMP_TO_BORDER,
  /** The texture will be repeated. */
  Repeat = GL_REPEAT,
  /** The texture will be mirrored and repeated. */
  MirroredRepeat = GL_MIRRORED_REPEAT,
};

/** Writes a TextureWrapMode enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param twm the TextureWrapMode enum.
 *  \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureWrapMode twm);

}  // namespace hou

#endif
