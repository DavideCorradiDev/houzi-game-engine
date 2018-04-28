// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/GfxError.hpp"



namespace hou
{

std::string getText(GfxError ec)
{
  switch(ec)
  {
    case GfxError::FontLoadFace:
      return u8"Failed to load font face.";
    default:
      return u8"";
  }
}

}

