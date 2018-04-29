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
    TEXTURE_TYPE_CASE(texture1, os);
    TEXTURE_TYPE_CASE(texture1_array, os);
    TEXTURE_TYPE_CASE(texture2, os);
    TEXTURE_TYPE_CASE(texture2_array, os);
    TEXTURE_TYPE_CASE(texture3, os);
    TEXTURE_TYPE_CASE(multisample_texture2, os);
    TEXTURE_TYPE_CASE(multisample_texture2_array, os);
  default:
    return os;
  }
}

}  // namespace hou
