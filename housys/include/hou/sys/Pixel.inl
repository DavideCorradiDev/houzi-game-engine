// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <PixelFormat format>
constexpr PixelFormat Pixel<format>::getFormat()
{
  return format;
}



template <PixelFormat format>
constexpr size_t Pixel<format>::getByteCount()
{
  return getPixelFormatByteCount(format);
}

}

