// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/sys/display_mode.hpp"
#include "hou/sys/event.hpp"
#include "hou/sys/window.hpp"

#include <iostream>
#include <thread>

void prompt(const std::string& message);



void prompt(const std::string& message)
{
  std::cout << message;
  std::string throwaway;
  std::getline(std::cin, throwaway);
}



int main(int, char**)
{
  hou::cor_module::initialize();
  hou::mth_module::initialize();
  hou::sys_module::initialize();

  hou::window w("WindowDemo", hou::vec2u(640u, 480u));
  w.set_bordered(true);
  w.set_visible(true);
  w.clear(hou::color::black());

  // Note: after set_visible(true) is called, the event queue must be processed to
  // correctly update the window state.
  hou::event::process_all();

  std::cout << "Window display index: " << w.get_display_index() << std::endl;
  std::cout << "Window display mode: " << w.get_display_mode() << std::endl;

  prompt("Press enter to change the window title");
  w.set_title("NewWindowDemo");
  std::cout << "Window title: " << w.get_title() << std::endl;

  prompt("Press enter to change the window icon");
  w.set_icon(hou::image2_rgba(hou::vec2u(16u, 32u), hou::color::red()));

  prompt("Press enter to move the window");
  w.set_position(hou::vec2u(32u, 64u));
  w.clear(hou::color::black());
  std::cout << "Window position: " << transpose(w.get_position()) << std::endl;

  prompt("Press enter to resize the window");
  w.set_size(hou::vec2u(800u, 600u));
  w.clear(hou::color::black());
  std::cout << "Window size: " << transpose(w.get_size()) << std::endl;

  prompt("Press enter to make the window border disappear");
  w.set_bordered(false);
  w.clear(hou::color::black());
  std::cout << "Window bordered: " << hou::to_string(w.is_bordered())
            << std::endl;

  prompt("Press enter to restore the window border");
  w.set_bordered(true);
  w.clear(hou::color::black());
  std::cout << "Window bordered: " << hou::to_string(w.is_bordered())
            << std::endl;

  // Note: the window must be focused for set_grab(true) to work.
  prompt("Press enter to make the window grab the input for some seconds");
  w.raise();
  w.focus();
  w.set_grab(true);
  std::cout << "Window grab: " << hou::to_string(w.get_grab()) << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(4));
  w.set_grab(false);
  std::cout << "Window grab: " << hou::to_string(w.get_grab()) << std::endl;

  prompt("Press enter to hide the window");
  w.set_visible(false);
  std::cout << "Window visible: " << hou::to_string(w.is_visible())
            << std::endl;

  prompt("Press enter to show the window");
  w.set_visible(true);
  w.clear(hou::color::black());
  std::cout << "Window visible: " << hou::to_string(w.is_visible())
            << std::endl;

  prompt("Press enter to make the window resizable");
  w.set_resizable(true);
  std::cout << "Window resizable: " << hou::to_string(w.is_resizable())
            << std::endl;

  prompt("Press enter to maximize the window");
  w.maximize();
  w.clear(hou::color::black());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  hou::event::process_all();
  std::cout << "Window maximized: " << hou::to_string(w.is_maximized())
            << std::endl;

  prompt("Press enter to restore the window");
  w.restore();
  w.clear(hou::color::black());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  hou::event::process_all();
  std::cout << "Window maximized: " << hou::to_string(w.is_maximized())
            << std::endl;

  prompt("Press enter to make the window not resizable");
  w.set_resizable(false);
  std::cout << "Window resizable: " << hou::to_string(w.is_resizable())
            << std::endl;

  prompt("Press enter to change the window background color.");
  w.clear(hou::color::blue());

  prompt(
    "Press enter to change the window mode to desktop fullscreen for some "
    "seconds");
  w.set_mode(hou::window_mode::desktop_fullscreen);
  w.clear(hou::color::blue());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  w.set_mode(hou::window_mode::windowed);
  w.clear(hou::color::blue());

  prompt(
    "Press enter to change the window mode to fullscreen for some seconds");
  w.set_mode(hou::window_mode::fullscreen);
  w.clear(hou::color::blue());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  w.set_mode(hou::window_mode::windowed);
  w.clear(hou::color::blue());

  // Note: a little time must be waited the event queue must be processed
  // to correctly update the window minimization state.
  prompt("Press enter to minimize the window");
  w.minimize();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  hou::event::process_all();
  std::cout << "Window minimized: " << hou::to_string(w.is_minimized())
            << std::endl;

  prompt("Press enter to restore the window");
  w.restore();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  w.clear(hou::color::black());
  std::cout << "Window minimized: " << hou::to_string(w.is_minimized())
            << std::endl;

  prompt("Press enter to end the program");
  return EXIT_SUCCESS;
}
