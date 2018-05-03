// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/mouse.hpp"

#include "hou/sys/win/win.hpp"
#include "hou/sys/window.hpp"

#include "hou/cor/deprecated_error.hpp"

#include "hou/mth/matrix.hpp"



namespace hou
{

namespace
{

UINT mouse_button_to_win_key(mouse_button button);



UINT mouse_button_to_win_key(mouse_button button)
{
  bool lr_swapped = GetSystemMetrics(SM_SWAPBUTTON);
  switch(button)
  {
    case mouse_button::lb:
      return lr_swapped ? VK_RBUTTON : VK_LBUTTON;
    case mouse_button::rb:
      return lr_swapped ? VK_LBUTTON : VK_RBUTTON;
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

}  // namespace



namespace mouse
{

bool is_button_pressed(mouse_button button)
{
  // Most significant bit set if the button is pressed.
  return (GetKeyState(mouse_button_to_win_key(button)) & 0x8000) != 0;
}



vec2i get_position()
{
  POINT position;
  GetCursorPos(&position);
  return vec2i(position.x, position.y);
}



vec2i get_position(const window& w)
{
  DEPRECATED_HOU_EXPECT_DEV(w.get_handle() != nullptr);

  POINT position;
  GetCursorPos(&position);
  ScreenToClient(w.get_handle(), &position);
  return vec2i(position.x, position.y);
}



void set_position(const vec2i& value)
{
  SetCursorPos(value.x(), value.y());
}



void set_position(const vec2i& value, const window& w)
{
  DEPRECATED_HOU_EXPECT_DEV(w.get_handle() != nullptr);

  POINT position = {value.x(), value.y()};
  ClientToScreen(w.get_handle(), &position);
  SetCursorPos(position.x, position.y);
}

}  // namespace mouse

}  // namespace hou
