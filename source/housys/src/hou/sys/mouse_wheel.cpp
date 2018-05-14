// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/mouse_wheel.hpp"

#include "hou/cor/exception.hpp"

#define MOUSE_WHEEL_CASE(mw, os) \
  case mouse_wheel::mw: \
    return (os) << #mw



namespace hou
{

std::ostream& operator<<(std::ostream& os, mouse_wheel mw)
{
  switch(mw)
  {
    MOUSE_WHEEL_CASE(horizontal, os);
    MOUSE_WHEEL_CASE(vertical, os);
    default:
      HOU_UNREACHABLE();
      return os;
  }
}

}  // namespace hou
