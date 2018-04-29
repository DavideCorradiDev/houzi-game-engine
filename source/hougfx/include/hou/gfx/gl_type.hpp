// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GL_TYPE_HPP
#define HOU_GFX_GL_TYPE_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

enum class gl_type : GLenum
{
  byte = GL_BYTE,
  unsigned_byte = GL_UNSIGNED_BYTE,
  short_integer = GL_SHORT,
  unsigned_short_integer = GL_UNSIGNED_SHORT,
  integer = GL_INT,
  unsigned_integer = GL_UNSIGNED_INT,
  half_float_decimal = GL_HALF_FLOAT,
  float_decimal = GL_FLOAT,
  double_decimal = GL_DOUBLE,
  fixed_decimal = GL_FIXED,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, gl_type type);
template <typename DataType>
HOU_GFX_API gl_type to_gl_type();

}  // namespace hou

#endif
