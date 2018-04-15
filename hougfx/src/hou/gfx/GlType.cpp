// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/GlType.hpp"

#include "hou/cor/BasicTypes.hpp"

#define GFX_GL_TYPE_CASE(type, os) \
  case GlType::type:            \
    return (os) << #type



namespace hou
{

std::ostream& operator<<(std::ostream& os, GlType type)
{
  switch(type)
  {
    GFX_GL_TYPE_CASE(Byte, os);
    GFX_GL_TYPE_CASE(UnsignedByte, os);
    GFX_GL_TYPE_CASE(Short, os);
    GFX_GL_TYPE_CASE(UnsignedShort, os);
    GFX_GL_TYPE_CASE(Int, os);
    GFX_GL_TYPE_CASE(UnsignedInt, os);
    GFX_GL_TYPE_CASE(HalfFloat, os);
    GFX_GL_TYPE_CASE(Float, os);
    GFX_GL_TYPE_CASE(Double, os);
    GFX_GL_TYPE_CASE(Fixed, os);
  default:
    return os;
  }
}



template <>
GlType toGlType<int8_t>()
{
  return GlType::Byte;
}



template <>
GlType toGlType<uint8_t>()
{
  return GlType::UnsignedByte;
}



template <>
GlType toGlType<int16_t>()
{
  return GlType::Short;
}



template <>
GlType toGlType<uint16_t>()
{
  return GlType::UnsignedShort;
}



template <>
GlType toGlType<int32_t>()
{
  return GlType::Int;
}



template <>
GlType toGlType<uint32_t>()
{
  return GlType::UnsignedInt;
}



template <>
GlType toGlType<float>()
{
  return GlType::Float;
}



template <>
GlType toGlType<double>()
{
  return GlType::Double;
}

}  // namespace hou
