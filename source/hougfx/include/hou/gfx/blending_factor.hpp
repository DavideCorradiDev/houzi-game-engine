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

enum class blending_factor
{
  zero = GL_ZERO,
  one = GL_ONE,
  src_color = GL_SRC_COLOR,
  one_minus_src_color = GL_ONE_MINUS_SRC_COLOR,
  dst_color = GL_DST_COLOR,
  one_minus_dst_color = GL_ONE_MINUS_DST_COLOR,
  src_alpha = GL_SRC_ALPHA,
  one_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA,
  dst_alpha = GL_DST_ALPHA,
  one_minus_dst_alpha = GL_ONE_MINUS_DST_ALPHA,
  constant_color = GL_CONSTANT_COLOR,
  one_minus_constant_color = GL_ONE_MINUS_CONSTANT_COLOR,
  constant_alpha = GL_CONSTANT_ALPHA,
  one_minus_constant_alpha = GL_ONE_MINUS_CONSTANT_ALPHA,
};

/**
 * Writes a blending_factor enum into a stream.
 *
 * \param os the stream.
 *
 * \param vsm the blending_factor enum.
 *
 * \return a reference to the stream.
 */
HOU_GL_API std::ostream& operator<<(std::ostream& os, blending_factor bf);

}

#endif
