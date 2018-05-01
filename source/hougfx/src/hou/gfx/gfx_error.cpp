// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/gfx_error.hpp"



namespace hou
{

std::string get_text(gfx_error ec)
{
  switch(ec)
  {
    case gfx_error::font_load_face:
      return u8"Failed to load font face.";
    default:
      return u8"";
  }
}

}

