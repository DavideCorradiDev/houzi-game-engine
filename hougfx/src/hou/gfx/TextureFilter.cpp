// Houzi Game Engine
// Copyright (c) 2016-2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/TextureFilter.hpp"

#include "hou/cor/CorError.hpp"
#include "hou/cor/Error.hpp"

#define TEXTURE_FILTER_CASE(tf, os) \
  case TextureFilter::tf:           \
    return (os) << #tf



namespace hou
{

std::ostream& operator<<(std::ostream& os, TextureFilter tf)
{
  switch(tf)
  {
    TEXTURE_FILTER_CASE(Nearest, os);
    TEXTURE_FILTER_CASE(Linear, os);
    TEXTURE_FILTER_CASE(Bilinear, os);
    TEXTURE_FILTER_CASE(Trilinear, os);
  default:
    return os;
  }
}

}  // namespace hou
