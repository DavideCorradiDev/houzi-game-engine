// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/mouse.hpp"

#include "hou/sys/sys_exceptions.hpp"
#include "hou/sys/window.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"

#include "hou/mth/matrix.hpp"

#include "SDL2/SDL_events.h"



namespace hou
{

namespace mouse
{

bool set_capture(bool value)
{
  return SDL_CaptureMouse(value ? SDL_TRUE : SDL_FALSE) == 0;
}



bool is_cursor_hidden()
{
  return SDL_ShowCursor(SDL_QUERY) == SDL_DISABLE;
}



void set_cursor_hidden(bool value)
{
  SDL_ShowCursor(value ? SDL_DISABLE : SDL_ENABLE);
}



bool is_relative_mode()
{
  return SDL_GetRelativeMouseMode() == SDL_TRUE;
}



bool set_relative_mode(bool value)
{
  return SDL_SetRelativeMouseMode(value ? SDL_TRUE : SDL_FALSE) == 0;
}



bool is_button_pressed(mouse_button mb)
{
  return SDL_GetMouseState(nullptr, nullptr)
    & SDL_BUTTON(static_cast<std::underlying_type<mouse_button>::type>(mb));
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
    const_cast<SDL_Window*>(w.get_impl().get()), pos.x(), pos.y());
}

}  // namespace mouse

}  // namespace hou
