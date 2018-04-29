// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_CHANNEL_HPP
#define HOU_GFX_TEXTURE_CHANNEL_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the texture channel. */
enum class TextureChannel : GLenum
{
  /** red channel. */
  r = GL_RED,
  /** green channel. */
  G = GL_GREEN,
  /** blue channel. */
  B = GL_BLUE,
  /** Alpha channel. */
  A = GL_ALPHA,
  /** Constant zero channel. */
  Zero = GL_ZERO,
  /** Constant one channel. */
  One = GL_ONE,
};

/** Writes a TextureChannel enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param tc the TextureChannel enum.
 *  \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureChannel tc);

}  // namespace hou

#endif
