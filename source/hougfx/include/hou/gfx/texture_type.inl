// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

constexpr size_t get_texture_type_dimension_count(texture_type t) noexcept
{
  switch(t)
  {
    case texture_type::texture1:
      return 1u;
    case texture_type::texture1_array:
    case texture_type::texture2:
    case texture_type::multisample_texture2:
      return 2u;
    case texture_type::texture2_array:
    case texture_type::texture3:
    case texture_type::multisample_texture2_array:
      return 3u;
    default:
      HOU_UNREACHABLE();
      return 1u;
  }
}



constexpr bool is_texture_type_mipmapped(texture_type t) noexcept
{
  return t == texture_type::texture1 || t == texture_type::texture1_array
    || t == texture_type::texture2 || t == texture_type::texture2_array
    || t == texture_type::texture3;
}



constexpr bool is_texture_type_multisampled(texture_type t) noexcept
{
  return t == texture_type::multisample_texture2
    || t == texture_type::multisample_texture2_array;
}

}  // namespace hou
