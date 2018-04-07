// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/WindowStyle.hpp"

#define WINDOW_STYLE_CASE(ws, os) \
  case WindowStyle::ws: return (os) << #ws



namespace hou
{

std::ostream& operator<<(std::ostream& os, WindowStyle ws)
{
  switch(ws)
  {
    WINDOW_STYLE_CASE(Windowed, os);
    WINDOW_STYLE_CASE(WindowedResizable, os);
    WINDOW_STYLE_CASE(Fullscreen, os);
    default: return os;
  }
}

}


