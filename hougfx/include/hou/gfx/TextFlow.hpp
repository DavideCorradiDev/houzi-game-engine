// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_FLOW_HPP
#define HOU_GFX_TEXT_FLOW_HPP

#include "hou/gfx/GfxExport.hpp"

#include <iostream>



namespace hou
{

enum class TextFlow
{
  LeftRight,
  RightLeft,
  TopBottom,
  BottomTop,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextFlow tf);

}

#endif
