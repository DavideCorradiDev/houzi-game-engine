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

void on_window_hidden(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_shown(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_exposed(hou::event::timestamp t, hou::window::uid_type wid);

void on_key_pressed(hou::event::timestamp t, hou::window::uid_type wid,
  hou::scan_code sc, hou::key_code kc, hou::modifier_keys mk, bool is_repeat);

void on_key_released(hou::event::timestamp t, hou::window::uid_type wid,
  hou::scan_code sc, hou::key_code kc, hou::modifier_keys mk, bool is_repeat);

void on_mouse_button_pressed(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_button mb, uint clicks, const hou::vec2i& pos);

void on_mouse_button_released(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_button mb, uint clicks, const hou::vec2i& pos);

void on_mouse_wheel_moved(hou::event::timestamp t, hou::window::uid_type wid,
  const hou::vec2i& delta, bool flipped);

void on_mouse_moved(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_buttons_state mbs, const hou::vec2i& pos,
  const hou::vec2i& delta);



void on_window_hidden(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window hidden: timestamp = " << t << ", window id = " << wid
            << std::endl;
}



void on_window_shown(hou::event::timestamp t, hou::window::uid_type wid)
{
  hou::window::get_from_uid(wid).clear(hou::color::black());
  std::cout << "Window shown: timestamp = " << t << ", window id = " << wid
            << std::endl;
}



void on_window_exposed(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window exposed: timestamp = " << t << ", window id = " << wid
            << std::endl;
}



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
  if(kc == hou::key_code::f1)
  {
    hou::window& w = hou::window::get_from_uid(wid);
    w.hide();
  }

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



void on_mouse_wheel_moved(hou::event::timestamp t, hou::window::uid_type wid,
  const hou::vec2i& delta, bool flipped)
{
  std::cout << "Mouse wheel moved: timestamp = " << t << ", window id = " << wid
            << ", delta = " << hou::transpose(delta)
            << ", flipped = " << hou::to_string(flipped) << std::endl;
}



void on_mouse_moved(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_buttons_state mbs, const hou::vec2i& pos,
  const hou::vec2i& delta)
{
  std::cout << "Mouse moved: timestamp = " << t << ", window id = " << wid
            << ", pressed buttons = " << mbs
            << ", position = " << hou::transpose(pos)
            << ", position delta = " << hou::transpose(delta) << std::endl;
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

  hou::event::set_window_hidden_callback(on_window_hidden);
  hou::event::set_window_shown_callback(on_window_shown);
  hou::event::set_window_exposed_callback(on_window_exposed);

  hou::event::set_key_pressed_callback(on_key_pressed);
  hou::event::set_key_released_callback(on_key_released);

  hou::event::set_mouse_button_pressed_callback(on_mouse_button_pressed);
  hou::event::set_mouse_button_released_callback(on_mouse_button_released);
  hou::event::set_mouse_wheel_moved_callback(on_mouse_wheel_moved);
  hou::event::set_mouse_moved_callback(on_mouse_moved);

  hou::system_window w("EventDemo", hou::vec2u(640u, 480u));
  w.set_bordered(true);

  std::cout << "The events in the queue will be printed in the terminal." << std::endl;
  std::cout << "Press F1 to temporarily hide the window." << std::endl;

  while(loop)
  {
    w.show();
    hou::event::process_all();
  }

  return EXIT_SUCCESS;
}
