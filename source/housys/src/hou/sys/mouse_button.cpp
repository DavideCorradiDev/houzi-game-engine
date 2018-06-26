// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/mouse_button.hpp"

#include "hou/cor/exception.hpp"

#define MOUSE_BUTTON_CASE(mb, os)                                              \
  case mouse_button::mb:                                                       \
    return (os) << #mb



namespace hou
{

std::ostream& operator<<(std::ostream& os, mouse_button mb)
{
  switch(mb)
  {
    MOUSE_BUTTON_CASE(lb, os);
    MOUSE_BUTTON_CASE(mb, os);
    MOUSE_BUTTON_CASE(rb, os);
    MOUSE_BUTTON_CASE(xb1, os);
    MOUSE_BUTTON_CASE(xb2, os);
  }
  HOU_UNREACHABLE();
  return os;
}

}  // namespace hou
