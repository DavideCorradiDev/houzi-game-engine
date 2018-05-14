// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/gl_type.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/exception.hpp"

#define GFX_GL_TYPE_CASE(type, os) \
  case gl_type::type: \
    return (os) << #type



namespace hou
{

std::ostream& operator<<(std::ostream& os, gl_type type)
{
  switch(type)
  {
    GFX_GL_TYPE_CASE(byte, os);
    GFX_GL_TYPE_CASE(unsigned_byte, os);
    GFX_GL_TYPE_CASE(short_integer, os);
    GFX_GL_TYPE_CASE(unsigned_short_integer, os);
    GFX_GL_TYPE_CASE(integer, os);
    GFX_GL_TYPE_CASE(unsigned_integer, os);
    GFX_GL_TYPE_CASE(half_float_decimal, os);
    GFX_GL_TYPE_CASE(float_decimal, os);
    GFX_GL_TYPE_CASE(double_decimal, os);
    GFX_GL_TYPE_CASE(fixed_decimal, os);
    default:
      HOU_UNREACHABLE();
      return os;
  }
}



template <>
gl_type to_gl_type<int8_t>()
{
  return gl_type::byte;
}



template <>
gl_type to_gl_type<uint8_t>()
{
  return gl_type::unsigned_byte;
}



template <>
gl_type to_gl_type<int16_t>()
{
  return gl_type::short_integer;
}



template <>
gl_type to_gl_type<uint16_t>()
{
  return gl_type::unsigned_short_integer;
}



template <>
gl_type to_gl_type<int32_t>()
{
  return gl_type::integer;
}



template <>
gl_type to_gl_type<uint32_t>()
{
  return gl_type::unsigned_integer;
}



template <>
gl_type to_gl_type<float>()
{
  return gl_type::float_decimal;
}



template <>
gl_type to_gl_type<double>()
{
  return gl_type::double_decimal;
}

}  // namespace hou
