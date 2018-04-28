// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/TextureWrapMode.hpp"
#include "hou/cor/error.hpp"

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
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<GLenum>(twm));
    return os;
  }
}

}  // namespace hou
