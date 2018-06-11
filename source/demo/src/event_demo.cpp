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

  hou::system_window w("EventDemo", hou::vec2u(640u, 480u));
  w.set_bordered(true);
  w.show();

  while(loop)
  {
    hou::event::process_all();
  }

  return EXIT_SUCCESS;
}
