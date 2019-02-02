// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture_type.hpp"

#include "hou/cor/core_functions.hpp"

#define TEXTURE_TYPE_CASE(type, os) \
  case texture_type::type: \
    return (os) << #type



namespace hou
{

std::ostream& operator<<(std::ostream& os, texture_type type)
{
  switch(type)
  {
    TEXTURE_TYPE_CASE(texture2, os);
    TEXTURE_TYPE_CASE(texture2_array, os);
    TEXTURE_TYPE_CASE(texture3, os);
    TEXTURE_TYPE_CASE(multisampled_texture2, os);
    TEXTURE_TYPE_CASE(multisampled_texture2_array, os);
  }
  return STREAM_VALUE(os, texture_type, type);
}

}  // namespace hou
