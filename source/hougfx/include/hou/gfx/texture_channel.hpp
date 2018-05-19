// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_CHANNEL_HPP
#define HOU_GFX_TEXTURE_CHANNEL_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the texture channel. */
enum class texture_channel : GLenum
{
  /** red channel. */
  r = GL_RED,
  /** green channel. */
  g = GL_GREEN,
  /** blue channel. */
  b = GL_BLUE,
  /** alpha channel. */
  a = GL_ALPHA,
  /** Constant zero channel. */
  zero = GL_ZERO,
  /** Constant one channel. */
  one = GL_ONE,
};

/** Writes a texture_channel enum into a stream.
 *
 * \param os the stream.
 *
 * \param tc the texture_channel enum.
 *
 * \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, texture_channel tc);

}  // namespace hou

#endif
