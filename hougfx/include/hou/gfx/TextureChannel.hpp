// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_TEXTURE_CHANNEL_HPP
#define HOU_GFX_TEXTURE_CHANNEL_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the texture channel. */
enum class TextureChannel : GLenum
{
  /** Red channel. */
  R = GL_RED,
  /** Green channel. */
  G = GL_GREEN,
  /** Blue channel. */
  B = GL_BLUE,
  /** Alpha channel. */
  A = GL_ALPHA,
  /** Constant zero channel. */
  Zero = GL_ZERO,
  /** Constant one channel. */
  One = GL_ONE,
};

/** Writes a TextureChannel enum into a stream.
 *
 *  \param os the stream.
 *  \param tc the TextureChannel enum.
 *  \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureChannel tc);

}  // namespace hou

#endif
