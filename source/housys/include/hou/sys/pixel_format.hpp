// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_PIXEL_FORMAT_HPP
#define HOU_SYS_PIXEL_FORMAT_HPP

#include "hou/sys/sys_config.hpp"

#include "hou/cor/assertions.hpp"

#include <iostream>



namespace hou
{

/**
 * Enumeration for the format of an image pixel.
 */
enum class pixel_format
{
  /** Single channel (red) format. */
  r,
  /** Double channel (red-green) format. */
  rg,
  /** Triple channel (red-green-blue) format. */
  rgb,
  /** Quadruple channel (red-green-blue-alpha) format. */
  rgba,
};

/**
 * Gets the number of bits of a pixel with the given format.
 *
 * \param format the pixel_format.
 *
 * \return the number of bits.
 */
constexpr uint get_bits_per_pixel(pixel_format format) noexcept;

/**
 * Gets the number of bytes of a pixel with the given format.
 *
 * \param format the pixel_format.
 *
 * \return the number of bytes.
 */
constexpr uint get_bytes_per_pixel(pixel_format format) noexcept;

/**
 * Writes a pixel_format enum into a stream.
 *
 * \param os the stream.
 *
 * \param format the pixel_format enum.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, pixel_format format);

}  // namespace hou

#include "hou/sys/pixel_format.inl"

#endif
