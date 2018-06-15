// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_EVENT_HPP
#define HOU_SYS_EVENT_HPP

#include "hou/sys/keyboard.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/std_chrono.hpp"

#include <functional>



namespace hou
{

class window;

namespace event
{

HOU_SYS_API void wait_next();
HOU_SYS_API bool queue_empty();
HOU_SYS_API bool process_next();
HOU_SYS_API void process_all();
HOU_SYS_API void flush_all();

using timestamp = std::chrono::duration<uint32_t, std::milli>;
using key_callback = std::function<void(
  timestamp, window&, scan_code, key_code, modifier_keys, bool)>;
using quit_callback = std::function<void(timestamp)>;

HOU_SYS_API void set_quit_callback(quit_callback f);
HOU_SYS_API void generate_quit();

HOU_SYS_API void set_key_pressed_callback(key_callback f);
HOU_SYS_API void generate_key_pressed(
  window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat);

HOU_SYS_API void set_key_released_callback(key_callback f);
HOU_SYS_API void generate_key_released(
  window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat);

}  // namespace event

}  // namespace hou

#endif
