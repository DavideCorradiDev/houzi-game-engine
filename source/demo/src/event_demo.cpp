// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/cor/clock.hpp"
#include "hou/cor/std_chrono.hpp"

#include "hou/sys/event.hpp"
#include "hou/sys/system_window.hpp"

#include <iostream>

void prompt(const std::string& message);

void on_window_closed(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_hidden(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_shown(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_exposed(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_minimized(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_maximized(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_restored(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_focus_lost(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_focus_gained(hou::event::timestamp t, hou::window::uid_type wid);

void on_window_focus_offered(
  hou::event::timestamp t, hou::window::uid_type wid);

void on_window_moved(
  hou::event::timestamp t, hou::window::uid_type wid, const hou::vec2i& pos);

void on_window_resized(
  hou::event::timestamp t, hou::window::uid_type wid, const hou::vec2u& size);

void on_window_size_changed(
  hou::event::timestamp t, hou::window::uid_type wid, const hou::vec2u& size);

void on_key_pressed(hou::event::timestamp t, hou::window::uid_type wid,
  hou::scan_code sc, hou::key_code kc, hou::modifier_keys mk, bool is_repeat);

void on_key_released(hou::event::timestamp t, hou::window::uid_type wid,
  hou::scan_code sc, hou::key_code kc, hou::modifier_keys mk, bool is_repeat);

void on_mouse_button_pressed(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_button mb, uint clicks, const hou::vec2i& pos);

void on_mouse_button_released(hou::event::timestamp t,
  hou::window::uid_type wid, hou::mouse_button mb, uint clicks,
  const hou::vec2i& pos);

void on_mouse_wheel_moved(hou::event::timestamp t, hou::window::uid_type wid,
  const hou::vec2i& delta, bool flipped);

void on_mouse_moved(hou::event::timestamp t, hou::window::uid_type wid,
  hou::mouse_buttons_state mbs, const hou::vec2i& pos, const hou::vec2i& delta);

void on_mouse_entered(hou::event::timestamp t, hou::window::uid_type wid);

void on_mouse_left(hou::event::timestamp t, hou::window::uid_type wid);



void prompt(const std::string& message)
{
  std::cout << message;
  std::string throwaway;
  std::getline(std::cin, throwaway);
}



void on_window_closed(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window closed: timestamp = " << t << ", window id = " << wid
            << std::endl;
}



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



void on_window_minimized(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window minimized: timestamp = " << t << ", window id = " << wid
            << std::endl;
}



void on_window_maximized(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window maximized: timestamp = " << t << ", window id = " << wid
            << std::endl;
}



void on_window_restored(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window restored: timestamp = " << t << ", window id = " << wid
            << std::endl;
}



void on_window_focus_lost(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window lost focus: timestamp = " << t << ", window id = " << wid
            << std::endl;
}



void on_window_focus_gained(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window gained focus: timestamp = " << t
            << ", window id = " << wid << std::endl;
}



void on_window_focus_offered(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Window was offered focus: timestamp = " << t
            << ", window id = " << wid << std::endl;
}



void on_window_moved(
  hou::event::timestamp t, hou::window::uid_type wid, const hou::vec2i& pos)
{
  std::cout << "Window moved: timestamp = " << t << ", window id = " << wid
            << ", position = " << hou::transpose(pos) << std::endl;
}



void on_window_resized(
  hou::event::timestamp t, hou::window::uid_type wid, const hou::vec2u& size)
{
  std::cout << "Window resized: timestamp = " << t
            << ", window id = " << wid << ", size = " << hou::transpose(size)
            << std::endl;
}



void on_window_size_changed(
  hou::event::timestamp t, hou::window::uid_type wid, const hou::vec2u& size)
{
  hou::window::get_from_uid(wid).clear(hou::color::black());
  std::cout << "Window changed size: timestamp = " << t
            << ", window id = " << wid << ", size = " << hou::transpose(size)
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
    w.set_visible(false);
    prompt("Press enter to show the window again");
    w.set_visible(true);
    w.focus();
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



void on_mouse_button_released(hou::event::timestamp t,
  hou::window::uid_type wid, hou::mouse_button mb, uint clicks,
  const hou::vec2i& pos)
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
  hou::mouse_buttons_state mbs, const hou::vec2i& pos, const hou::vec2i& delta)
{
  std::cout << "Mouse moved: timestamp = " << t << ", window id = " << wid
            << ", pressed buttons = " << mbs
            << ", position = " << hou::transpose(pos)
            << ", position delta = " << hou::transpose(delta) << std::endl;
}



void on_mouse_entered(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Mouse entered window: " << t << ", window id = " << wid
            << std::endl;
}



void on_mouse_left(hou::event::timestamp t, hou::window::uid_type wid)
{
  std::cout << "Mouse left window: " << t << ", window id = " << wid
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

  hou::event::set_window_closed_callback(on_window_closed);
  hou::event::set_window_hidden_callback(on_window_hidden);
  hou::event::set_window_shown_callback(on_window_shown);
  hou::event::set_window_exposed_callback(on_window_exposed);
  hou::event::set_window_minimized_callback(on_window_minimized);
  hou::event::set_window_maximized_callback(on_window_maximized);
  hou::event::set_window_restored_callback(on_window_restored);
  hou::event::set_window_focus_lost_callback(on_window_focus_lost);
  hou::event::set_window_focus_gained_callback(on_window_focus_gained);
  hou::event::set_window_focus_offered_callback(on_window_focus_offered);
  hou::event::set_window_moved_callback(on_window_moved);
  hou::event::set_window_resized_callback(on_window_resized);
  hou::event::set_window_size_changed_callback(on_window_size_changed);

  hou::event::set_key_pressed_callback(on_key_pressed);
  hou::event::set_key_released_callback(on_key_released);

  hou::event::set_mouse_button_pressed_callback(on_mouse_button_pressed);
  hou::event::set_mouse_button_released_callback(on_mouse_button_released);
  hou::event::set_mouse_wheel_moved_callback(on_mouse_wheel_moved);
  hou::event::set_mouse_moved_callback(on_mouse_moved);
  hou::event::set_mouse_entered_callback(on_mouse_entered);
  hou::event::set_mouse_left_callback(on_mouse_left);

  hou::system_window w("EventDemo", hou::vec2u(640u, 480u));
  w.set_bordered(true);
  w.set_resizable(true);
  w.set_size(hou::vec2u(800u, 600u));
  w.set_visible(true);

  std::cout << "The events in the queue will be printed in the terminal."
            << std::endl;
  std::cout << "Press F1 to hide the window." << std::endl;

  while(loop)
  {
    hou::event::process_all();
  }

  return EXIT_SUCCESS;
}
