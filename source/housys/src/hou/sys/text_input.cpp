// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/text_input.hpp"

#include "hou/mth/rectangle.hpp"

#include "SDL_events.h"



namespace hou
{

namespace text_input
{

void start()
{
  SDL_StartTextInput();
}



void stop()
{
  SDL_StopTextInput();
}



bool is_active()
{
  return SDL_IsTextInputActive() == SDL_TRUE;
}



void set_rect(const recti& rect)
{
  SDL_Rect sdl_rect;
  sdl_rect.x = rect.x();
  sdl_rect.y = rect.y();
  sdl_rect.w = rect.w();
  sdl_rect.h = rect.h();
  SDL_SetTextInputRect(&sdl_rect);
}

}  // namespace text_input

}  // namespace hou
