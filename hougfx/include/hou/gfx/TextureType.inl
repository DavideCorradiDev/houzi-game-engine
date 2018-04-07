// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

constexpr size_t getTextureTypeDimensionCount(TextureType t)
{
  switch(t)
  {
  case TextureType::Texture1:
    return 1u;
  case TextureType::Texture1Array:
  case TextureType::Texture2:
  case TextureType::MultisampleTexture2:
    return 2u;
  case TextureType::Texture2Array:
  case TextureType::Texture3:
  case TextureType::MultisampleTexture2Array:
    return 3u;
  default:
    return 1u;
  }
}



constexpr bool isTextureTypeMipMapped(TextureType t)
{
  return t == TextureType::Texture1 || t == TextureType::Texture1Array
    || t == TextureType::Texture2 || t == TextureType::Texture2Array
    || t == TextureType::Texture3;
}



constexpr bool isTextureTypeMultisampled(TextureType t)
{
  return t == TextureType::MultisampleTexture2
    || t == TextureType::MultisampleTexture2Array;
}

}  // namespace hou
