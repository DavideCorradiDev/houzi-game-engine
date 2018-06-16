// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/cor/std_chrono.hpp"

#include "hou/sys/event.hpp"
#include "hou/sys/system_window.hpp"

#include <iostream>

void on_key_pressed(hou::event::timestamp t, hou::window::uid_type wid,
  hou::scan_code sc, hou::key_code kc, hou::modifier_keys mk, bool is_repeat);

void on_key_released(hou::event::timestamp t, hou::window::uid_type wid,
  hou::scan_code sc, hou::key_code kc, hou::modifier_keys mk, bool is_repeat);

void on_mouse_button_pressed(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_button mb, uint clicks, const hou::vec2i& pos);

void on_mouse_button_released(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_button mb, uint clicks, const hou::vec2i& pos);



void on_key_pressed(hou::event::timestamp t, hou::window::uid_type wid,
  hou::scan_code sc, hou::key_code kc, hou::modifier_keys mk, bool is_repeat)
{
  std::cout << "Key pressed: timestamp = " << t << ", window id = " << wid
            << ", scan code = " << sc << ", key code = " << kc
            << ", modifier keys = " << mk
            << ", is repeat = " << hou::to_string(is_repeat) << std::endl;
}



void on_key_released(hou::event::timestamp t, hou::window::uid_type wid,
  hou::scan_code sc, hou::key_code kc, hou::modifier_keys mk, bool is_repeat)
{
  std::cout << "Key released: timestamp = " << t << ", window id = " << wid
            << ", scan code = " << sc << ", key code = " << kc
            << ", modifier keys = " << mk
            << ", is repeat = " << hou::to_string(is_repeat) << std::endl;
}



void on_mouse_button_pressed(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_button mb, uint clicks, const hou::vec2i& pos)
{
  std::cout << "Mouse button pressed: timestamp = " << t
            << ", window id = " << wid << ", mouse button = " << mb
            << ", clicks = " << clicks << ", position = " << hou::transpose(pos)
            << std::endl;
}



void on_mouse_button_released(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_button mb, uint clicks, const hou::vec2i& pos)
{
  std::cout << "Mouse button released: timestamp = " << t
            << ", window id = " << wid << ", mouse button = " << mb
            << ", clicks = " << clicks << ", position = " << hou::transpose(pos)
            << std::endl;
}



int main(int, char**)
{
  hou::cor_module::initialize();
  hou::cor_module::register_terminate_callbacks();
  hou::mth_module::initialize();
  hou::mth_module::register_terminate_callbacks();
  hou::sys_module::initialize();
  hou::sys_module::register_terminate_callbacks();

  bool loop = true;
  auto on_quit = [&loop](hou::event::timestamp t) {
    std::cout << "Quit: timestamp = " << t << std::endl;
    loop = false;
  };

  hou::event::set_quit_callback(on_quit);
  hou::event::set_key_pressed_callback(on_key_pressed);
  hou::event::set_key_released_callback(on_key_released);
  hou::event::set_mouse_button_pressed_callback(on_mouse_button_pressed);
  hou::event::set_mouse_button_released_callback(on_mouse_button_released);

  hou::system_window w("EventDemo", hou::vec2u(640u, 480u));
  w.set_bordered(true);
  w.show();

  while(loop)
  {
    hou::event::process_all();
  }

  return EXIT_SUCCESS;
}
