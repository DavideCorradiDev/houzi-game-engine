// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/TextureType.hpp"

#define TEXTURE_TYPE_CASE(type, os) \
  case TextureType::type:           \
    return (os) << #type



namespace hou
{

std::ostream& operator<<(std::ostream& os, TextureType type)
{
  switch(type)
  {
    TEXTURE_TYPE_CASE(Texture1, os);
    TEXTURE_TYPE_CASE(Texture1Array, os);
    TEXTURE_TYPE_CASE(Texture2, os);
    TEXTURE_TYPE_CASE(Texture2Array, os);
    TEXTURE_TYPE_CASE(Texture3, os);
    TEXTURE_TYPE_CASE(MultisampleTexture2, os);
    TEXTURE_TYPE_CASE(MultisampleTexture2Array, os);
  default:
    return os;
  }
}

}  // namespace hou
