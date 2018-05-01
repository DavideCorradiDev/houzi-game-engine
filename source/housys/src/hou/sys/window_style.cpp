// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window_style.hpp"

#define WINDOW_STYLE_CASE(ws, os) \
  case window_style::ws: \
    return (os) << #ws



namespace hou
{

std::ostream& operator<<(std::ostream& os, window_style ws)
{
  switch(ws)
  {
    WINDOW_STYLE_CASE(windowed, os);
    WINDOW_STYLE_CASE(windowed_resizable, os);
    WINDOW_STYLE_CASE(fullscreen, os);
    default:
      return os;
  }
}

}  // namespace hou
