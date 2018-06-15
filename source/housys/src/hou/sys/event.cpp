// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/event.hpp"

#include "hou/sys/sys_exceptions.hpp"
#include "hou/sys/window.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_timer.h"



namespace hou
{

namespace event
{

namespace
{

window& get_window_from_id(Uint32 id);
Uint32 get_id_from_window(const window& w);

void process(const SDL_Event& event);

quit_callback& get_quit_callback();
key_callback& get_key_pressed_callback();
key_callback& get_key_released_callback();



window& get_window_from_id(Uint32 id)
{
  SDL_Window* w = SDL_GetWindowFromID(id);
  HOU_SDL_CHECK(w != nullptr);
  return window::get_impl_window(w);
}



Uint32 get_id_from_window(const window& w)
{
  Uint32 id = SDL_GetWindowID(const_cast<SDL_Window*>(w.get_impl().get()));
  HOU_SDL_CHECK(id != 0);
  return id;
}



void process(const SDL_Event& event)
{
  switch(event.type)
  {
    case SDL_QUIT:
    {
      auto callback = get_quit_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.quit.timestamp));
      }
    } break;
    case SDL_KEYDOWN:
    {
      auto callback = get_key_pressed_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.key.timestamp),
          get_window_from_id(event.key.windowID),
          scan_code(event.key.keysym.scancode), key_code(event.key.keysym.sym),
          modifier_keys(event.key.keysym.mod), event.key.repeat);
      }
    } break;
    case SDL_KEYUP:
    {
      auto callback = get_key_released_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.key.timestamp),
          get_window_from_id(event.key.windowID),
          scan_code(event.key.keysym.scancode), key_code(event.key.keysym.sym),
          modifier_keys(event.key.keysym.mod), event.key.repeat);
      }
    } break;
  }
}



quit_callback& get_quit_callback()
{
  static quit_callback callback = nullptr;
  return callback;
}



key_callback& get_key_pressed_callback()
{
  static key_callback callback = nullptr;
  return callback;
}



key_callback& get_key_released_callback()
{
  static key_callback callback = nullptr;
  return callback;
}

}



bool queue_empty()
{
  return SDL_HasEvents(SDL_FIRSTEVENT, SDL_LASTEVENT) == SDL_FALSE;
}



void wait_next()
{
  SDL_Event event;
  HOU_SDL_CHECK(SDL_WaitEvent(&event) != 0);
  process(event);
}



bool process_next()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    process(event);
    return true;
  }
  return false;
}



void process_all()
{
  while(process_next()) {}
}



void flush_all()
{
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}



void set_quit_callback(quit_callback f)
{
  get_quit_callback() = f;
}



void generate_quit()
{
  SDL_Event event;
  event.type = SDL_QUIT;
  event.quit.timestamp = SDL_GetTicks();
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_key_pressed_callback(key_callback f)
{
  get_key_pressed_callback() = f;
}



void generate_key_pressed(
  window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat)
{
  SDL_Event event;
  event.type = SDL_KEYDOWN;
  event.key.timestamp = SDL_GetTicks();
  event.key.windowID = get_id_from_window(w);
  event.key.state = SDL_PRESSED;
  event.key.repeat = is_repeat ? 1 : 0;
  event.key.keysym.scancode = static_cast<SDL_Scancode>(sc);
  event.key.keysym.sym = static_cast<SDL_Keycode>(kc);
  event.key.keysym.mod = static_cast<Uint16>(mk);
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_key_released_callback(key_callback f)
{
  get_key_released_callback() = f;
}



void generate_key_released(
  window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat)
{
  SDL_Event event;
  event.type = SDL_KEYUP;
  event.key.timestamp = SDL_GetTicks();
  event.key.windowID = get_id_from_window(w);
  event.key.state = SDL_RELEASED;
  event.key.repeat = is_repeat ? 1 : 0;
  event.key.keysym.scancode = static_cast<SDL_Scancode>(sc);
  event.key.keysym.sym = static_cast<SDL_Keycode>(kc);
  event.key.keysym.mod = static_cast<Uint16>(mk);
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}

}  // namespace event

}  // namespace hou
