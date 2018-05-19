// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <pixel_format pf>
constexpr pixel_format pixel_t<pf>::get_format() noexcept
{
  return pf;
}



template <pixel_format pf>
constexpr uint pixel_t<pf>::get_byte_count() noexcept
{
  return get_pixel_format_byte_count(pf);
}

}  // namespace hou
