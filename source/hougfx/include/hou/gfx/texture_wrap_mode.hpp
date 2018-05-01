// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_WRAP_MODE_HPP
#define HOU_GFX_TEXTURE_WRAP_MODE_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the clamp mode of a texture. */
enum class texture_wrap_mode : GLenum
{
  /** Pixels sampled outside the texture will have the color of the
   * corresponding edge pixel. */
  clamp_to_edge = GL_CLAMP_TO_EDGE,
  /** Pixels sampled outside the texture  will have the color of the mirrored
   *  edge pixel. */
  mirror_clamp_to_edge = GL_MIRROR_CLAMP_TO_EDGE,
  /** Pixels sampled outside the texture will have the border color. */
  clamp_to_border = GL_CLAMP_TO_BORDER,
  /** The texture will be repeated. */
  repeat = GL_REPEAT,
  /** The texture will be mirrored and repeated. */
  mirrored_repeat = GL_MIRRORED_REPEAT,
};

/** Writes a texture_wrap_mode enum into a stream.
 *
 *  \param os the stream.
 *
 *  \param twm the texture_wrap_mode enum.
 *
 *  \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, texture_wrap_mode twm);

}  // namespace hou

#endif
