// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window_mode.hpp"

#include "hou/cor/exception.hpp"

#define WINDOW_MODE_CASE(ws, os)                                               \
  case window_mode::ws:                                                        \
    return (os) << #ws



namespace hou
{

std::ostream& operator<<(std::ostream& os, window_mode wm)
{
  switch(wm)
  {
    WINDOW_MODE_CASE(windowed, os);
    WINDOW_MODE_CASE(fullscreen, os);
    WINDOW_MODE_CASE(desktop_fullscreen, os);
  }
  HOU_UNREACHABLE();
  return os;
}

}  // namespace hou
