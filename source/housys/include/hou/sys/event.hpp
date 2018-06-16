// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_EVENT_HPP
#define HOU_SYS_EVENT_HPP

#include "hou/sys/keyboard.hpp"
#include "hou/sys/mouse.hpp"
#include "hou/sys/window.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/std_chrono.hpp"

#include <functional>



namespace hou
{

namespace event
{

HOU_SYS_API void wait_next();
HOU_SYS_API bool queue_empty();
HOU_SYS_API bool process_next();
HOU_SYS_API void process_all();
HOU_SYS_API void flush_all();

using timestamp = std::chrono::duration<uint32_t, std::milli>;

using key_callback = std::function<void(
  timestamp, window::uid_type, scan_code, key_code, modifier_keys, bool)>;

using mouse_button_callback = std::function<void(
  timestamp, window::uid_type, mouse_button, uint, const vec2i&)>;

using mouse_wheel_callback
  = std::function<void(timestamp, window::uid_type, const vec2i&, bool)>;

using mouse_motion_callback = std::function<void(timestamp, window::uid_type,
  mouse_buttons_state, const vec2i&, const vec2i&)>;

using quit_callback = std::function<void(timestamp)>;

HOU_SYS_API void set_quit_callback(quit_callback f);
HOU_SYS_API void generate_quit();

HOU_SYS_API void set_key_pressed_callback(key_callback f);
HOU_SYS_API void generate_key_pressed(
  const window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat);

HOU_SYS_API void set_key_released_callback(key_callback f);
HOU_SYS_API void generate_key_released(
  const window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat);

HOU_SYS_API void set_mouse_button_pressed_callback(mouse_button_callback f);
HOU_SYS_API void generate_mouse_button_pressed(
  const window& w, mouse_button button, uint clicks, const vec2i& position);

HOU_SYS_API void set_mouse_button_released_callback(mouse_button_callback f);
HOU_SYS_API void generate_mouse_button_released(
  const window& w, mouse_button button, uint clicks, const vec2i& position);

HOU_SYS_API void set_mouse_wheel_moved_callback(mouse_wheel_callback f);
HOU_SYS_API void generate_mouse_wheel_moved(
  const window& w, const vec2i& delta, bool flipped);

HOU_SYS_API void set_mouse_moved_callback(mouse_motion_callback f);
HOU_SYS_API void generate_mouse_moved(const window& w, mouse_buttons_state mbs,
  const vec2i& position, const vec2i& position_delta);

}  // namespace event

}  // namespace hou

#endif
