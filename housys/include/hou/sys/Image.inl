// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

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
constexpr uint Image<dim, fmt>::getPixelByteCount()
{
  return Pixel::getByteCount();
}

}  // namespace hou
