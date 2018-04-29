// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GL_TYPE_HPP
#define HOU_GFX_GL_TYPE_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

enum class GlType : GLenum
{
  Byte = GL_BYTE,
  UnsignedByte = GL_UNSIGNED_BYTE,
  Short = GL_SHORT,
  UnsignedShort = GL_UNSIGNED_SHORT,
  Int = GL_INT,
  UnsignedInt = GL_UNSIGNED_INT,
  HalfFloat = GL_HALF_FLOAT,
  Float = GL_FLOAT,
  Double = GL_DOUBLE,
  Fixed = GL_FIXED,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, GlType type);
template <typename DataType>
HOU_GFX_API GlType toGlType();

}  // namespace hou

#endif
