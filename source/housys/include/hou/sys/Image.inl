// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <size_t dim, pixel_format fmt>
constexpr size_t image<dim, fmt>::get_dimension_count()
{
  return dim;
}



template <size_t dim, pixel_format fmt>
constexpr pixel_format image<dim, fmt>::get_pixel_format()
{
  return fmt;
}



template <size_t dim, pixel_format fmt>
constexpr uint image<dim, fmt>::get_pixel_byte_count()
{
  return pixel::get_byte_count();
}

}  // namespace hou
