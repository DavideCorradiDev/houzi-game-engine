// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/mouse.hpp"

#include "hou/sys/sys_exceptions.hpp"
#include "hou/sys/window.hpp"

#include "hou/mth/matrix.hpp"

#include "SDL_events.h"



namespace hou
{

namespace mouse
{

bool set_capture(bool value)
{
  return SDL_CaptureMouse(value ? SDL_TRUE : SDL_FALSE) == 0;
}



bool is_cursor_visible()
{
  return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}



void set_cursor_visible(bool value)
{
  SDL_ShowCursor(value ? SDL_ENABLE : SDL_DISABLE);
}



bool is_relative_mode()
{
  return SDL_GetRelativeMouseMode() == SDL_TRUE;
}



bool set_relative_mode(bool value)
{
  return SDL_SetRelativeMouseMode(value ? SDL_TRUE : SDL_FALSE) == 0;
}



mouse_buttons_state get_buttons_state()
{
  return mouse_buttons_state(SDL_GetMouseState(nullptr, nullptr));
}



bool is_button_pressed(mouse_button mb)
{
  return get_buttons_state().check(mb);
}



vec2i get_position()
{
  vec2i pos;
  SDL_GetGlobalMouseState(&pos.x(), &pos.y());
  return pos;
}



vec2i get_position(const window& w)
{
  return get_position() - w.get_position();
}



vec2i get_position_delta()
{
  vec2i delta;
  SDL_GetRelativeMouseState(&delta.x(), &delta.y());
  return delta;
}



void set_position(const vec2i& pos)
{
  HOU_SDL_CHECK(SDL_WarpMouseGlobal(pos.x(), pos.y()) == 0);
}



void set_position(const vec2i& pos, const window& w)
{
  SDL_WarpMouseInWindow(
    const_cast<SDL_Window*>(w.get_impl()), pos.x(), pos.y());
}

}  // namespace mouse

}  // namespace hou
