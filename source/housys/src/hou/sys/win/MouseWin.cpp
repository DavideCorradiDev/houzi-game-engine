// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/mouse.hpp"

#include "hou/sys/window.hpp"
#include "hou/sys/win/Win.hpp"

#include "hou/cor/error.hpp"

#include "hou/mth/matrix.hpp"



namespace hou
{

namespace
{

UINT mouseButtonToWinKey(mouse_button button);



UINT mouseButtonToWinKey(mouse_button button)
{
  bool lrSwapped = GetSystemMetrics(SM_SWAPBUTTON);
  switch(button)
  {
    case mouse_button::lb:
      return lrSwapped ? VK_RBUTTON : VK_LBUTTON;
    case mouse_button::rb:
      return lrSwapped ? VK_LBUTTON : VK_RBUTTON;
    case mouse_button::mb:
      return VK_MBUTTON;
    case mouse_button::xb1:
      return VK_XBUTTON1;
    case mouse_button::xb2:
      return VK_XBUTTON2;
    default:
      return 0u;
  }
}

}



namespace mouse
{

bool is_button_pressed(mouse_button button)
{
  // Most significant bit set if the button is pressed.
  return (GetKeyState(mouseButtonToWinKey(button)) & 0x8000) != 0;
}



vec2i get_position()
{
  POINT position;
  GetCursorPos(&position);
  return vec2i(position.x, position.y);
}



vec2i get_position(const window& ph_window)
{
  HOU_EXPECT_DEV(ph_window.get_handle() != nullptr);

  POINT position;
  GetCursorPos(&position);
  ScreenToClient(ph_window.get_handle(), &position);
  return vec2i(position.x, position.y);
}



void set_position(const vec2i& value)
{
  SetCursorPos(value.x(), value.y());
}



void set_position(const vec2i& value, const window& ph_window)
{
  HOU_EXPECT_DEV(ph_window.get_handle() != nullptr);

  POINT position = {value.x(), value.y()};
  ClientToScreen(ph_window.get_handle(), &position);
  SetCursorPos(position.x, position.y);
}

}

}

