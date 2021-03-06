// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/event.hpp"

#include "hou/sys/sys_exceptions.hpp"
#include "hou/sys/window.hpp"

#include "hou/cor/basic_static_string.hpp"

#include "SDL_events.h"
#include "SDL_timer.h"



namespace hou
{

namespace event
{

namespace
{

quit_callback& get_quit_callback();

window_callback& get_window_closed_callback();
window_callback& get_window_hidden_callback();
window_callback& get_window_shown_callback();
window_callback& get_window_exposed_callback();
window_callback& get_window_minimized_callback();
window_callback& get_window_maximized_callback();
window_callback& get_window_restored_callback();
window_callback& get_window_focus_lost_callback();
window_callback& get_window_focus_gained_callback();
window_callback& get_window_focus_offered_callback();
window_motion_callback& get_window_moved_callback();
window_resize_callback& get_window_resized_callback();
window_resize_callback& get_window_size_changed_callback();

key_callback& get_key_pressed_callback();
key_callback& get_key_released_callback();

mouse_button_callback& get_mouse_button_pressed_callback();
mouse_button_callback& get_mouse_button_released_callback();
mouse_wheel_callback& get_mouse_wheel_moved_callback();
mouse_motion_callback& get_mouse_moved_callback();
window_callback& get_mouse_entered_callback();
window_callback& get_mouse_left_callback();

text_editing_callback& get_text_editing_callback();
text_input_callback& get_text_input_callback();

void process(const SDL_Event& event);



quit_callback& get_quit_callback()
{
  static quit_callback callback = nullptr;
  return callback;
}



window_callback& get_window_closed_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_hidden_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_shown_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_exposed_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_minimized_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_maximized_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_restored_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_focus_lost_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_focus_gained_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_window_focus_offered_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_motion_callback& get_window_moved_callback()
{
  static window_motion_callback callback = nullptr;
  return callback;
}



window_resize_callback& get_window_resized_callback()
{
  static window_resize_callback callback = nullptr;
  return callback;
}



window_resize_callback& get_window_size_changed_callback()
{
  static window_resize_callback callback = nullptr;
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



mouse_motion_callback& get_mouse_moved_callback()
{
  static mouse_motion_callback callback = nullptr;
  return callback;
}



window_callback& get_mouse_entered_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



window_callback& get_mouse_left_callback()
{
  static window_callback callback = nullptr;
  return callback;
}



text_editing_callback& get_text_editing_callback()
{
  static text_editing_callback callback = nullptr;
  return callback;
}



text_input_callback& get_text_input_callback()
{
  static text_input_callback callback = nullptr;
  return callback;
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
    }
    break;
    case SDL_WINDOWEVENT:
    {
      switch(event.window.event)
      {
        case SDL_WINDOWEVENT_CLOSE:
        {
          auto callback = get_window_closed_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_HIDDEN:
        {
          auto callback = get_window_hidden_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_SHOWN:
        {
          auto callback = get_window_shown_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_EXPOSED:
        {
          auto callback = get_window_exposed_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_MINIMIZED:
        {
          auto callback = get_window_minimized_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_MAXIMIZED:
        {
          auto callback = get_window_maximized_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_RESTORED:
        {
          auto callback = get_window_restored_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
        {
          auto callback = get_window_focus_lost_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
        {
          auto callback = get_window_focus_gained_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_TAKE_FOCUS:
        {
          auto callback = get_window_focus_offered_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_ENTER:
        {
          auto callback = get_mouse_entered_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_LEAVE:
        {
          auto callback = get_mouse_left_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID);
          }
        }
        break;
        case SDL_WINDOWEVENT_MOVED:
        {
          auto callback = get_window_moved_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID,
              vec2i(event.window.data1, event.window.data2));
          }
        }
        break;
        case SDL_WINDOWEVENT_RESIZED:
        {
          auto callback = get_window_resized_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID,
              vec2u(narrow_cast<uint>(event.window.data1),
                narrow_cast<uint>(event.window.data2)));
          }
        }
        break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        {
          auto callback = get_window_size_changed_callback();
          if(callback != nullptr)
          {
            callback(timestamp(event.window.timestamp), event.window.windowID,
              vec2u(narrow_cast<uint>(event.window.data1),
                narrow_cast<uint>(event.window.data2)));
          }
        }
        break;
      }
    }
    break;
    case SDL_KEYDOWN:
    {
      auto callback = get_key_pressed_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.key.timestamp), event.key.windowID,
          scan_code(event.key.keysym.scancode), key_code(event.key.keysym.sym),
          modifier_keys(event.key.keysym.mod), event.key.repeat);
      }
    }
    break;
    case SDL_KEYUP:
    {
      auto callback = get_key_released_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.key.timestamp), event.key.windowID,
          scan_code(event.key.keysym.scancode), key_code(event.key.keysym.sym),
          modifier_keys(event.key.keysym.mod), event.key.repeat);
      }
    }
    break;
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
    }
    break;
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
    }
    break;
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
    }
    break;
    case SDL_MOUSEMOTION:
    {
      if(event.motion.which != SDL_TOUCH_MOUSEID)
      {
        auto callback = get_mouse_moved_callback();
        if(callback != nullptr)
        {
          callback(timestamp(event.motion.timestamp), event.motion.windowID,
            mouse_buttons_state(event.motion.state),
            vec2i(event.motion.x, event.motion.y),
            vec2i(event.motion.xrel, event.motion.yrel));
        }
      }
    }
    break;
    case SDL_TEXTEDITING:
    {
      auto callback = get_text_editing_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.edit.timestamp), event.edit.windowID,
          event.edit.text, event.edit.start, event.edit.length);
      }
    }
    break;
    case SDL_TEXTINPUT:
    {
      auto callback = get_text_input_callback();
      if(callback != nullptr)
      {
        callback(timestamp(event.text.timestamp), event.text.windowID,
          event.text.text);
      }
    }
    break;
  }
}

}  // namespace



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
  while(process_next())
  {
  }
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



void set_window_closed_callback(window_callback f)
{
  get_window_closed_callback() = f;
}



void generate_window_closed(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_CLOSE;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_hidden_callback(window_callback f)
{
  get_window_hidden_callback() = f;
}



void generate_window_hidden(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_HIDDEN;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_shown_callback(window_callback f)
{
  get_window_shown_callback() = f;
}



void generate_window_shown(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_SHOWN;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_exposed_callback(window_callback f)
{
  get_window_exposed_callback() = f;
}



void generate_window_exposed(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_EXPOSED;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_minimized_callback(window_callback f)
{
  get_window_minimized_callback() = f;
}



void generate_window_minimized(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_MINIMIZED;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_maximized_callback(window_callback f)
{
  get_window_maximized_callback() = f;
}



void generate_window_maximized(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_MAXIMIZED;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_restored_callback(window_callback f)
{
  get_window_restored_callback() = f;
}



void generate_window_restored(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_RESTORED;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_focus_lost_callback(window_callback f)
{
  get_window_focus_lost_callback() = f;
}



void generate_window_focus_lost(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_FOCUS_LOST;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_focus_gained_callback(window_callback f)
{
  get_window_focus_gained_callback() = f;
}



void generate_window_focus_gained(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_focus_offered_callback(window_callback f)
{
  get_window_focus_offered_callback() = f;
}



void generate_window_focus_offered(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_TAKE_FOCUS;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_moved_callback(window_motion_callback f)
{
  get_window_moved_callback() = f;
}



void generate_window_moved(const window& w, const vec2i& position)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_MOVED;
  event.window.data1 = narrow_cast<Sint32>(position.x());
  event.window.data2 = narrow_cast<Sint32>(position.y());
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_resized_callback(window_resize_callback f)
{
  get_window_resized_callback() = f;
}



void generate_window_resized(const window& w, const vec2u& size)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_RESIZED;
  event.window.data1 = narrow_cast<Sint32>(size.x());
  event.window.data2 = narrow_cast<Sint32>(size.y());
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_window_size_changed_callback(window_resize_callback f)
{
  get_window_size_changed_callback() = f;
}



void generate_window_size_changed(const window& w, const vec2u& size)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_SIZE_CHANGED;
  event.window.data1 = narrow_cast<Sint32>(size.x());
  event.window.data2 = narrow_cast<Sint32>(size.y());
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



void set_mouse_moved_callback(mouse_motion_callback f)
{
  get_mouse_moved_callback() = f;
}



void generate_mouse_moved(const window& w, mouse_buttons_state mbs,
  const vec2i& position, const vec2i& position_delta)
{
  SDL_Event event;
  event.type = SDL_MOUSEMOTION;
  event.motion.timestamp = SDL_GetTicks();
  event.motion.windowID = w.get_uid();
  event.motion.which = 0u;
  event.motion.state = mbs.get();
  event.motion.x = position.x();
  event.motion.y = position.y();
  event.motion.xrel = position_delta.x();
  event.motion.yrel = position_delta.y();
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_mouse_entered_callback(window_callback f)
{
  get_mouse_entered_callback() = f;
}



void generate_mouse_entered(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_ENTER;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_mouse_left_callback(window_callback f)
{
  get_mouse_left_callback() = f;
}



void generate_mouse_left(const window& w)
{
  SDL_Event event;
  event.type = SDL_WINDOWEVENT;
  event.window.timestamp = SDL_GetTicks();
  event.window.windowID = w.get_uid();
  event.window.event = SDL_WINDOWEVENT_LEAVE;
  event.window.data1 = 0;
  event.window.data2 = 0;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_text_editing_callback(text_editing_callback f)
{
  get_text_editing_callback() = f;
}



void generate_text_editing(const window& w, const static_string<32u>& text,
  int32_t start, int32_t length)
{
  SDL_Event event;
  event.type = SDL_TEXTEDITING;
  event.edit.timestamp = SDL_GetTicks();
  event.edit.windowID = w.get_uid();
  std::copy(text.begin(), text.end(), event.edit.text);
  event.edit.start = start;
  event.edit.length = length;
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}



void set_text_input_callback(text_input_callback f)
{
  get_text_input_callback() = f;
}



void generate_text_input(const window& w, const static_string<32u>& text)
{
  SDL_Event event;
  event.type = SDL_TEXTINPUT;
  event.text.timestamp = SDL_GetTicks();
  event.text.windowID = w.get_uid();
  std::copy(text.begin(), text.end(), event.text.text);
  HOU_SDL_CHECK(SDL_PushEvent(&event) >= 0);
}

}  // namespace event

}  // namespace hou
