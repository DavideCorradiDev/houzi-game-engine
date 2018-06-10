// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

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

  hou::system_window w("WindowDemo", hou::vec2u(640u, 480u));
  w.show();

  std::cout << "Press return to resize the window";
  std::cin.get();
  w.set_size(hou::vec2u(800u, 600u));
  std::cout << "Press return to end the program";
  std::cin.get();

  return EXIT_SUCCESS;
}
