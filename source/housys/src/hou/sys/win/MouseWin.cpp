// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/Mouse.hpp"

#include "hou/sys/Window.hpp"
#include "hou/sys/win/Win.hpp"

#include "hou/cor/error.hpp"

#include "hou/mth/Matrix.hpp"



namespace hou
{

namespace
{

UINT mouseButtonToWinKey(MouseButton button);



UINT mouseButtonToWinKey(MouseButton button)
{
  bool lrSwapped = GetSystemMetrics(SM_SWAPBUTTON);
  switch(button)
  {
    case MouseButton::LB:
      return lrSwapped ? VK_RBUTTON : VK_LBUTTON;
    case MouseButton::RB:
      return lrSwapped ? VK_LBUTTON : VK_RBUTTON;
    case MouseButton::MB:
      return VK_MBUTTON;
    case MouseButton::XB1:
      return VK_XBUTTON1;
    case MouseButton::XB2:
      return VK_XBUTTON2;
    default:
      return 0u;
  }
}

}



namespace Mouse
{

bool isButtonPressed(MouseButton button)
{
  // Most significant bit set if the button is pressed.
  return (GetKeyState(mouseButtonToWinKey(button)) & 0x8000) != 0;
}



Vec2i getPosition()
{
  POINT position;
  GetCursorPos(&position);
  return Vec2i(position.x, position.y);
}



Vec2i getPosition(const Window& window)
{
  HOU_EXPECT_DEV(window.getWindowHandle() != nullptr);

  POINT position;
  GetCursorPos(&position);
  ScreenToClient(window.getWindowHandle(), &position);
  return Vec2i(position.x, position.y);
}



void setPosition(const Vec2i& value)
{
  SetCursorPos(value.x(), value.y());
}



void setPosition(const Vec2i& value, const Window& window)
{
  HOU_EXPECT_DEV(window.getWindowHandle() != nullptr);

  POINT position = {value.x(), value.y()};
  ClientToScreen(window.getWindowHandle(), &position);
  SetCursorPos(position.x, position.y);
}

}

}

