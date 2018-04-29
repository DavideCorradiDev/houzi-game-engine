// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

constexpr size_t get_texture_type_dimension_count(TextureType t)
{
  switch(t)
  {
  case TextureType::texture1:
    return 1u;
  case TextureType::texture1_array:
  case TextureType::texture2:
  case TextureType::multisample_texture2:
    return 2u;
  case TextureType::texture2_array:
  case TextureType::texture3:
  case TextureType::multisample_texture2_array:
    return 3u;
  default:
    return 1u;
  }
}



constexpr bool is_texture_type_mipmapped(TextureType t)
{
  return t == TextureType::texture1 || t == TextureType::texture1_array
    || t == TextureType::texture2 || t == TextureType::texture2_array
    || t == TextureType::texture3;
}



constexpr bool is_texture_type_multisampled(TextureType t)
{
  return t == TextureType::multisample_texture2
    || t == TextureType::multisample_texture2_array;
}

}  // namespace hou
