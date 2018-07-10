// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GL_TYPE_HPP
#define HOU_GFX_GL_TYPE_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Enum representing an OpenGL type.
 */
enum class gl_type : GLenum
{
  /** byte type. */
  byte = GL_BYTE,
  /** unsigned byte type. */
  unsigned_byte = GL_UNSIGNED_BYTE,
  /** short integer type. */
  short_integer = GL_SHORT,
  /** unsigned short integer type. */
  unsigned_short_integer = GL_UNSIGNED_SHORT,
  /** integer type. */
  integer = GL_INT,
  /** unsigned integer type. */
  unsigned_integer = GL_UNSIGNED_INT,
  /** half float type. */
  half_float_decimal = GL_HALF_FLOAT,
  /** float type. */
  float_decimal = GL_FLOAT,
  /** double type. */
  double_decimal = GL_DOUBLE,
  /** fixed type. */
  fixed_decimal = GL_FIXED,
};

/** Retrieves the gl_type enum value associated to a specific data type.
 *
 * \tparam data_type the actual data type.
 *
 * \return the correspondong gl_enum value.
 */
template <typename data_type>
gl_type to_gl_type();

template<> HOU_GFX_API gl_type to_gl_type<int8_t>();
template<> HOU_GFX_API gl_type to_gl_type<uint8_t>();
template<> HOU_GFX_API gl_type to_gl_type<int16_t>();
template<> HOU_GFX_API gl_type to_gl_type<uint16_t>();
template<> HOU_GFX_API gl_type to_gl_type<int32_t>();
template<> HOU_GFX_API gl_type to_gl_type<uint32_t>();
template<> HOU_GFX_API gl_type to_gl_type<float>();
template<> HOU_GFX_API gl_type to_gl_type<double>();

/**
 * Retrieves the size in bytes for a variable of type gl_type.
 *
 * \param type the type.
 *
 * \return the size in bytes.
 */
uint get_gl_type_byte_size(gl_type type);

/** Writes the object into a stream.
 *
 * \param os the output stream.
 *
 * \param type the gl_type enum.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, gl_type type);

}  // namespace hou

#endif
