// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/cor/clock.hpp"

#include "hou/sys/event.hpp"
#include "hou/sys/mouse.hpp"
#include "hou/sys/system_window.hpp"

#include <iostream>
#include <thread>



std::ostream& stream_if_pressed(std::ostream& os, hou::mouse_button mb);

std::ostream& stream_if_pressed(std::ostream& os, hou::mouse_button mb)
{
  if(hou::mouse::is_button_pressed(mb))
  {
    os << " " << mb;
  }
  return os;
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
  auto on_quit = [&loop](hou::event::timestamp) { loop = false; };
  hou::event::set_quit_callback(on_quit);

  hou::system_window w("MouseDemo", hou::vec2u(640u, 480u));
  w.set_bordered(true);
  w.show();
  w.raise();
  w.focus();

  std::cout << "The mouse state will be printed every second." << std::endl;

  std::chrono::nanoseconds elapsed_time(0);
  std::chrono::nanoseconds tick_period(std::chrono::seconds(1));
  hou::clock c;
  while(loop)
  {
    hou::event::process_all();
    elapsed_time += c.reset();
    while(elapsed_time > tick_period)
    {
      elapsed_time -= tick_period;

      std::cout << "Window has focus: " << hou::to_string(w.has_mouse_focus())
                << std::endl;
      std::cout << "Global position: " << transpose(hou::mouse::get_position())
                << std::endl;
      std::cout << "Window position: " << transpose(hou::mouse::get_position(w))
                << std::endl;
      std::cout << "Relative position: "
                << transpose(hou::mouse::get_position_delta()) << std::endl;
      std::cout << "Buttons:";
      stream_if_pressed(std::cout, hou::mouse_button::lb);
      stream_if_pressed(std::cout, hou::mouse_button::mb);
      stream_if_pressed(std::cout, hou::mouse_button::rb);
      stream_if_pressed(std::cout, hou::mouse_button::xb1);
      stream_if_pressed(std::cout, hou::mouse_button::xb2);
      std::cout << std::endl;

      std::cout << std::endl;
    }
  }

  return EXIT_SUCCESS;
}


