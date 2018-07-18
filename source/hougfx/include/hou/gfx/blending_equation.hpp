// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_BLENDING_EQUATION_HPP
#define HOU_GFX_BLENDING_EQUATION_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

enum class blending_equation
{
  add = GL_FUNC_ADD,
  subtract = GL_FUNC_SUBTRACT,
  reverse_subtract = GL_FUNC_REVERSE_SUBTRACT,
  min = GL_MIN,
  max = GL_MAX,
};

/**
 * Writes a blending_equation enum into a stream.
 *
 * \param os the stream.
 *
 * \param vsm the blending_equation enum.
 *
 * \return a reference to the stream.
 */
HOU_GL_API std::ostream& operator<<(std::ostream& os, blending_equation be);

}

#endif
