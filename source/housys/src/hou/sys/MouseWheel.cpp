// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/MouseWheel.hpp"

#define MOUSE_WHEEL_CASE(mw, os) \
  case MouseWheel::mw: return (os) << #mw



namespace hou
{

std::ostream& operator<<(std::ostream& os, MouseWheel mw)
{
  switch(mw)
  {
    MOUSE_WHEEL_CASE(Horizontal, os);
    MOUSE_WHEEL_CASE(Vertical, os);
    default: return os;
  }
}

}

