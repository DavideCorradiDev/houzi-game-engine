// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/gl_type.hpp"

#include "hou/cor/cor_exceptions.hpp"
#include "hou/cor/core_functions.hpp"
#include "hou/cor/narrow_cast.hpp"

#define GFX_GL_TYPE_CASE(type, os) \
  case gl_type::type: \
    return (os) << #type



namespace hou
{

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



uint get_gl_type_byte_size(gl_type type)
{
  switch(type)
  {
    case gl_type::byte:
      return sizeof(GLbyte);
    case gl_type::unsigned_byte:
      return sizeof(GLubyte);
    case gl_type::short_integer:
      return sizeof(GLshort);
    case gl_type::unsigned_short_integer:
      return sizeof(GLushort);
    case gl_type::integer:
      return sizeof(GLint);
    case gl_type::unsigned_integer:
      return sizeof(GLuint);
    case gl_type::half_float_decimal:
      return sizeof(GLhalf);
    case gl_type::float_decimal:
      return sizeof(GLfloat);
    case gl_type::double_decimal:
      return sizeof(GLdouble);
    case gl_type::fixed_decimal:
      return sizeof(GLfixed);
  }
  HOU_ERROR_N(invalid_enum, narrow_cast<int>(type));
  return 1u;
}



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
  }
  return STREAM_VALUE(os, gl_type, type);
}

}  // namespace hou
