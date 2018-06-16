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

void process(const SDL_Event& event);

quit_callback& get_quit_callback();
key_callback& get_key_pressed_callback();
key_callback& get_key_released_callback();
mouse_button_callback& get_mouse_button_pressed_callback();
mouse_button_callback& get_mouse_button_released_callback();
mouse_wheel_callback& get_mouse_wheel_moved_callback();



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
        callback(timestamp(event.key.timestamp), event.key.windowID,
          scan_code(event.key.keysym.scancode), key_code(event.key.keysym.sym),
          modifier_keys(event.key.keysym.mod), event.key.repeat);
      }
    } break;
    case SDL_KEYUP:
    {
      auto callback = get_key_released_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.key.timestamp), event.key.windowID,
          scan_code(event.key.keysym.scancode), key_code(event.key.keysym.sym),
          modifier_keys(event.key.keysym.mod), event.key.repeat);
      }
    } break;
    case SDL_MOUSEBUTTONDOWN:
    {
      if(event.button.which != SDL_TOUCH_MOUSEID)
      {
        auto callback = get_mouse_button_pressed_callback();
        if(callback != nullptr)
        {
          callback(timestamp(event.button.timestamp), event.button.windowID,
            mouse_button(event.button.button),
            static_cast<uint>(event.button.clicks),
            vec2i(event.button.x, event.button.y));
        }
      }
    } break;
    case SDL_MOUSEBUTTONUP:
    {
      if(event.button.which != SDL_TOUCH_MOUSEID)
      {
        auto callback = get_mouse_button_released_callback();
        if(callback != nullptr)
        {
            callback(timestamp(event.button.timestamp), event.button.windowID,
              mouse_button(event.button.button),
              static_cast<uint>(event.button.clicks),
              vec2i(event.button.x, event.button.y));
        }
      }
    } break;
    case SDL_MOUSEWHEEL:
    {
      if(event.wheel.which != SDL_TOUCH_MOUSEID)
      {
        auto callback = get_mouse_wheel_moved_callback();
        if(callback != nullptr)
        {
          callback(timestamp(event.wheel.timestamp), event.wheel.windowID,
            vec2i(event.wheel.x, event.wheel.y),
            event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED);
        }
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



mouse_button_callback& get_mouse_button_pressed_callback()
{
  static mouse_button_callback callback = nullptr;
  return callback;
}



mouse_button_callback& get_mouse_button_released_callback()
{
  static mouse_button_callback callback = nullptr;
  return callback;
}



mouse_wheel_callback& get_mouse_wheel_moved_callback()
{
  static mouse_wheel_callback callback = nullptr;
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
  const window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat)
{
  SDL_Event event;
  event.type = SDL_KEYDOWN;
  event.key.timestamp = SDL_GetTicks();
  event.key.windowID = w.get_uid();
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
  const window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat)
{
  SDL_Event event;
  event.type = SDL_KEYUP;
  event.key.timestamp = SDL_GetTicks();
  event.key.windowID = w.get_uid();
  event.key.state = SDL_RELEASED;
  event.key.repeat = is_repeat ? 1 : 0;
  event.key.keysym.scancode = static_cast<SDL_Scancode>(sc);
  event.key.keysym.sym = static_cast<SDL_Keycode>(kc);
  event.key.keysym.mod = static_cast<Uint16>(mk);
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_mouse_button_pressed_callback(mouse_button_callback f)
{
  get_mouse_button_pressed_callback() = f;
}



void generate_mouse_button_pressed(
  const window& w, mouse_button button, uint clicks, const vec2i& position)
{
  SDL_Event event;
  event.type = SDL_MOUSEBUTTONDOWN;
  event.button.timestamp = SDL_GetTicks();
  event.button.windowID = w.get_uid();
  event.button.which = 0;
  event.button.button = narrow_cast<uint8_t>(button);
  event.button.state = SDL_PRESSED;
  event.button.clicks = narrow_cast<uint8_t>(clicks);
  event.button.x = position.x();
  event.button.y = position.y();
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_mouse_button_released_callback(mouse_button_callback f)
{
  get_mouse_button_released_callback() = f;
}



void generate_mouse_button_released(
  const window& w, mouse_button button, uint clicks, const vec2i& position)
{
  SDL_Event event;
  event.type = SDL_MOUSEBUTTONUP;
  event.button.timestamp = SDL_GetTicks();
  event.button.windowID = w.get_uid();
  event.button.which = 0u;
  event.button.button = narrow_cast<uint8_t>(button);
  event.button.state = SDL_RELEASED;
  event.button.clicks = narrow_cast<uint8_t>(clicks);
  event.button.x = position.x();
  event.button.y = position.y();
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_mouse_wheel_moved_callback(mouse_wheel_callback f)
{
  get_mouse_wheel_moved_callback() = f;
}



void generate_mouse_wheel_moved(
  const window& w, const vec2i& delta, bool flipped)
{
  SDL_Event event;
  event.type = SDL_MOUSEWHEEL;
  event.wheel.timestamp = SDL_GetTicks();
  event.wheel.windowID = w.get_uid();
  event.wheel.which = 0u;
  event.wheel.x = delta.x();
  event.wheel.y = delta.y();
  event.wheel.direction
    = flipped ? SDL_MOUSEWHEEL_FLIPPED : SDL_MOUSEWHEEL_NORMAL;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}

}  // namespace event

}  // namespace hou
