// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_BLENDING_FACTOR_HPP
#define HOU_GFX_BLENDING_FACTOR_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/**
 * Enumeration for blending factors.
 */
enum class blending_factor
{
  /** Zero. */
  zero = GL_ZERO,
  /** One. */
  one = GL_ONE,
  /** Source color. */
  src_color = GL_SRC_COLOR,
  /** One minus source color. */
  one_minus_src_color = GL_ONE_MINUS_SRC_COLOR,
  /** Destination color. */
  dst_color = GL_DST_COLOR,
  /** One minus destination color. */
  one_minus_dst_color = GL_ONE_MINUS_DST_COLOR,
  /** Source alpha. */
  src_alpha = GL_SRC_ALPHA,
  /** One minus source alpha. */
  one_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA,
  /** Destination alpha. */
  dst_alpha = GL_DST_ALPHA,
  /** One minus destination alpha. */
  one_minus_dst_alpha = GL_ONE_MINUS_DST_ALPHA,
  /** Constant color. */
  constant_color = GL_CONSTANT_COLOR,
  /** One minus constant color. */
  one_minus_constant_color = GL_ONE_MINUS_CONSTANT_COLOR,
  /** Constant alpha. */
  constant_alpha = GL_CONSTANT_ALPHA,
  /** One minus constant alpha. */
  one_minus_constant_alpha = GL_ONE_MINUS_CONSTANT_ALPHA,
};

/**
 * Writes a blending_factor enum into a stream.
 *
 * \param os the stream.
 *
 * \param bf the blending_factor enum.
 *
 * \return a reference to the stream.
 */
HOU_GL_API std::ostream& operator<<(std::ostream& os, blending_factor bf);

}

#endif
