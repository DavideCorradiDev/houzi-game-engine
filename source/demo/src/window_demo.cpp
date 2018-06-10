// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/sys/display_mode.hpp"
#include "hou/sys/system_window.hpp"

#include <iostream>
#include <thread>

void prompt_key(const std::string& message);



void prompt_key(const std::string& message)
{
  std::cout << message;
  std::string throwaway;
  std::getline(std::cin, throwaway);
}



int main(int, char**)
{
  hou::cor_module::initialize();
  hou::cor_module::register_terminate_callbacks();
  hou::mth_module::initialize();
  hou::mth_module::register_terminate_callbacks();
  hou::sys_module::initialize();
  hou::sys_module::register_terminate_callbacks();

  hou::system_window w("WindowDemo", hou::vec2u(640u, 480u));
  w.set_bordered(true);
  w.show();

  std::cout << "Window display index: " << w.get_display_index() << std::endl;
  std::cout << "Window display mode: " << w.get_display_mode() << std::endl;

  prompt_key("Press return to change the window title");
  w.set_title("NewWindowDemo");

  prompt_key("Press return to change the window icon");
  w.set_icon(hou::image2_rgba(hou::vec2u(16u, 8u), hou::color::red()));

  prompt_key("Press return to move the window");
  w.set_position(hou::vec2u(32u, 64u));

  prompt_key("Press return to resize the window");
  w.set_size(hou::vec2u(800u, 600u));

  prompt_key("Press return to hide the window");
  w.hide();

  prompt_key("Press return to show the window");
  w.show();

  prompt_key("Press return to minimize the window");
  w.minimize();

  prompt_key("Press return to restore the window");
  w.restore();

  prompt_key("Press return to maximize the window");
  w.maximize();

  prompt_key("Press return to restore the window");
  w.restore();

  prompt_key("Press return to make the window border disappear");
  w.set_bordered(false);

  prompt_key("Press return to restore the window border");
  w.set_bordered(true);

  prompt_key("Press return to make the window resizable");
  w.set_resizable(true);

  prompt_key("Press return to make the window not resizable");
  w.set_resizable(false);

  prompt_key("Press return to make the window grab the input for some seconds");
  w.set_grab(true);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  w.set_grab(false);

  // prompt_key("Press return to change the window mode to desktop fullscreen for some seconds");
  // w.set_mode(hou::window_mode::desktop_fullscreen);
  // std::this_thread::sleep_for(std::chrono::seconds(5));
  // w.set_mode(hou::window_mode::windowed);

  // prompt_key("Press return to change the window mode to fullscreen for some seconds");
  // w.set_mode(hou::window_mode::fullscreen);
  // std::this_thread::sleep_for(std::chrono::seconds(5));
  // w.set_mode(hou::window_mode::windowed);

  std::cout << "Press return to end the program";
  std::cin.get();
  return EXIT_SUCCESS;
}
