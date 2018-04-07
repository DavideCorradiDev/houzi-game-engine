// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <size_t dim, PixelFormat fmt>
constexpr size_t Image<dim, fmt>::getDimensionCount()
{
  return dim;
}



template <size_t dim, PixelFormat fmt>
constexpr PixelFormat Image<dim, fmt>::getPixelFormat()
{
  return fmt;
}



template <size_t dim, PixelFormat fmt>
constexpr size_t Image<dim, fmt>::getPixelByteCount()
{
  return Pixel::getByteCount();
}



template <size_t dim, PixelFormat fmt>
Span<const uint8_t> byteSpan(const Image<dim, fmt>& im)
{
  return Span<const uint8_t>(
    reinterpret_cast<const uint8_t*>(im.getPixels().data()),
    im.getPixels().size() * im.getPixelByteCount());
}



template <PixelFormat fmt>
Span<const Pixel<fmt>> pixelSpan(const Span<const uint8_t>& bytes)
{
  return Span<const Pixel<fmt>>(
    reinterpret_cast<const Pixel<fmt>*>(bytes.data()),
    bytes.size() / Pixel<fmt>::getByteCount());
}

}

