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

/**
 * Enumeration for blending equations.
 */
enum class blending_equation
{
  /* Add equation. */
  add = GL_FUNC_ADD,
  /* Subtract equation. */
  subtract = GL_FUNC_SUBTRACT,
  /* Reverse subtract equation. */
  reverse_subtract = GL_FUNC_REVERSE_SUBTRACT,
  /* Min equation. */
  min = GL_MIN,
  /* Max equation. */
  max = GL_MAX,
};

/**
 * Writes a blending_equation enum into a stream.
 *
 * \param os the stream.
 *
 * \param be the blending_equation enum.
 *
 * \return a reference to the stream.
 */
HOU_GL_API std::ostream& operator<<(std::ostream& os, blending_equation be);

}

#endif
