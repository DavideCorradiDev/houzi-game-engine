// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/MouseButton.hpp"

#define MOUSE_BUTTON_CASE(mb, os) \
  case MouseButton::mb: return (os) << #mb



namespace hou
{

std::ostream& operator<<(std::ostream& os, MouseButton mb)
{
  switch(mb)
  {
    MOUSE_BUTTON_CASE(LB, os);
    MOUSE_BUTTON_CASE(MB, os);
    MOUSE_BUTTON_CASE(RB, os);
    MOUSE_BUTTON_CASE(XB1, os);
    MOUSE_BUTTON_CASE(XB2, os);
    default: return os;
  }
}

}

