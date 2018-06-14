// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/cor/clock.hpp"

#include "hou/sys/event.hpp"
#include "hou/sys/keyboard.hpp"
#include "hou/sys/system_window.hpp"

#include <iostream>
#include <thread>



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

  hou::system_window w("KeyboardDemo", hou::vec2u(640u, 480u));
  w.set_bordered(true);
  w.show();
  w.raise();
  w.focus();

  std::cout << "The keyboard state will be printed every second." << std::endl;

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

      hou::span<const uint8_t> keys_state = hou::keyboard::get_keys_state();
      std::vector<int> pressed_keys;
      pressed_keys.reserve(keys_state.size());
      for(size_t i = 0; i < keys_state.size(); ++i)
      {
        if(keys_state[i])
        {
          pressed_keys.push_back(i);
          HOU_ASSERT(hou::keyboard::is_key_pressed(hou::scan_code(i)));
          HOU_ASSERT(hou::keyboard::is_key_pressed(
            hou::get_key_code(hou::scan_code(i))));
        }
        else
        {
          HOU_ASSERT(!hou::keyboard::is_key_pressed(hou::scan_code(i)));
          HOU_ASSERT(!hou::keyboard::is_key_pressed(
            hou::get_key_code(hou::scan_code(i))));
        }
      }

      std::cout << "Window has focus: "
                << hou::to_string(w.has_keyboard_focus()) << std::endl;

      std::cout << "Pressed scan codes:";
      for(auto i : pressed_keys)
      {
        std::cout << " " << hou::scan_code(i);
      }
      std::cout << std::endl;

      std::cout << "Pressed key codes:";
      for(auto i : pressed_keys)
      {
        std::cout << " " << get_key_code(hou::scan_code(i));
      }
      std::cout << std::endl;

      std::cout << "Modifier keys: " << hou::keyboard::get_modifier_keys()
                << std::endl;

      std::cout << std::endl;
    }
  }

  return EXIT_SUCCESS;
}

