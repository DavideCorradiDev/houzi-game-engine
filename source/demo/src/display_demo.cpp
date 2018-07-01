// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/sys/display.hpp"

#include <iostream>



int main(int, char**)
{
  hou::cor_module::initialize();
  hou::mth_module::initialize();
  hou::sys_module::initialize();

  std::cout << "Available video driver(s):\n";
  for(const auto& driver : hou::display::get_available_video_drivers())
  {
    std::cout << "  " << driver;
    if(driver == hou::display::get_current_video_driver())
    {
      std::cout << " (current)";
    }
    std::cout << "\n";
  }

  std::cout << "\n";

  std::cout << "Available display(s):\n";
  for(hou::uint i = 0; i < hou::display::get_count(); ++i)
  {
    std::cout << "  Name: " << hou::display::get_name(i) << "\n";
    std::cout << "  Bounds: " << hou::display::get_bounds(i) << "\n";
    std::cout << "  Usable Bounds: " << hou::display::get_usable_bounds(i)
              << "\n";
    std::cout << "  Current mode: " << hou::display::get_current_mode(i)
              << "\n";
    std::cout << "  Supported modes: "
              << "\n";
    for(const auto& mode : hou::display::get_supported_modes(i))
    {
      std::cout << "    " << mode << "\n";
    }
    std::cout << "\n";
  }

  std::cout << std::endl;

  return 0;
}
