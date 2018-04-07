// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/TextureWrapMode.hpp"
#include "hou/cor/Error.hpp"

#define TEXTURE_WRAP_MODE_CASE(twm, os) \
  case TextureWrapMode::twm:            \
    return (os) << #twm



namespace hou
{

std::ostream& operator<<(std::ostream& os, TextureWrapMode twm)
{
  switch(twm)
  {
    TEXTURE_WRAP_MODE_CASE(ClampToEdge, os);
    TEXTURE_WRAP_MODE_CASE(MirrorClampToEdge, os);
    TEXTURE_WRAP_MODE_CASE(ClampToBorder, os);
    TEXTURE_WRAP_MODE_CASE(Repeat, os);
    TEXTURE_WRAP_MODE_CASE(MirroredRepeat, os);
  default:
    HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<GLenum>(twm));
    return os;
  }
}

}  // namespace hou