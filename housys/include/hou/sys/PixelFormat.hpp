// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_PIXEL_FORMAT_HPP
#define HOU_SYS_PIXEL_FORMAT_HPP

#include "hou/sys/SysExport.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the format of an image pixel. */
enum class PixelFormat
{
  /** Single channel (red) format. */
  R,
  /** double channel (red-green) format. */
  RG,
  /** Triple channel (red-green-blue) format. */
  RGB,
  /** Quadruple channel (red-green-blue-alpha) format. */
  RGBA,
};

/** Writes a PixelFormat enum into a stream.
 *
 *  \param os the stream.
 *  \param format the PixelFormat enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, PixelFormat format);

constexpr size_t getPixelFormatByteCount(PixelFormat format)
{
  switch(format)
  {
    case PixelFormat::R:
      return 1u;
    case PixelFormat::RG:
      return 2u;
    case PixelFormat::RGB:
      return 3u;
    case PixelFormat::RGBA:
      return 4u;
    default:
      return 1u;
  };
}

}

#endif

