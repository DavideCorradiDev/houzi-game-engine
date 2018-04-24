// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_ANCHORING_HPP
#define HOU_GFX_TEXT_ANCHORING_HPP

#include "hou/gfx/GfxExport.hpp"

#include <iostream>



namespace hou
{

enum class TextAnchoring
{
  TopLeft,
  TopCenter,
  TopRight,
  CenterLeft,
  Center,
  CenterRight,
  BottomLeft,
  BottomCenter,
  BottomRight,
  Baseline,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextAnchoring t);

}  // namespace hou

#endif
