// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "bounded.hpp"

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/display_mode.hpp"
#include "hou/sys/event.hpp"
#include "hou/sys/image_file.hpp"
#include "hou/sys/window.hpp"

#include <iostream>
#include <thread>



int main(int, char**)
{
  // Initialization.
  hou::cor_module::initialize();
  hou::mth_module::initialize();
  hou::sys_module::initialize();

  // Window creation.
  static const std::string title = u8"Window Demo";
  hou::window w(title, hou::vec2u(640u, 480u));
  w.set_bordered(true);
  w.set_visible(true);
  w.raise();
  w.focus();

  // Window properties.
  hou::vec2i dsp_size
    = hou::display::get_bounds(w.get_display_index()).get_size();
  bounded<int> wnd_pos_x(w.get_position().x(), 0, dsp_size.x());
  bounded<int> wnd_pos_y(w.get_position().y(), 0, dsp_size.y());
  int wnd_pos_step = 20;

  bounded<int> wnd_size_x(800, 100, 1400);
  bounded<int> wnd_size_y(600, 100, 1400);
  int wnd_size_step = 100;

  bounded<float> bg_color_red(1.f, 0.f, 1.f);
  bounded<float> bg_color_green(1.f, 0.f, 1.f);
  bounded<float> bg_color_blue(1.f, 0.f, 1.f);
  bounded<float> bg_color_alpha(1.f, 0.f, 1.f);
  float bg_color_step = 0.1f;

  // Event callbacks.
  bool loop = true;
  auto on_quit = [&loop](hou::event::timestamp) { loop = false; };
  hou::event::set_quit_callback(on_quit);

  auto on_window_moved
    = [&](hou::event::timestamp, hou::window::uid_type, const hou::vec2i& pos) {
        wnd_pos_x = pos.x();
        wnd_pos_y = pos.y();
      };
  hou::event::set_window_moved_callback(on_window_moved);

  auto on_window_resized = [&](hou::event::timestamp, hou::window::uid_type,
                             const hou::vec2u& size) {
    wnd_size_x = size.x();
    wnd_size_y = size.y();
  };
  hou::event::set_window_resized_callback(on_window_resized);

  auto on_key_pressed
    = [&](hou::event::timestamp, hou::window::uid_type, hou::scan_code sc,
        hou::key_code, hou::modifier_keys, bool) {
        // position
        if(sc == hou::scan_code::f1)
        {
          w.set_mode(hou::window_mode::windowed);
        }
        else if(sc == hou::scan_code::f2)
        {
          w.set_mode(hou::window_mode::desktop_fullscreen);
        }
        else if(sc == hou::scan_code::f3)
        {
          w.set_mode(hou::window_mode::fullscreen);
        }
        else if(sc == hou::scan_code::num1)
        {
          bg_color_red -= bg_color_step;
        }
        else if(sc == hou::scan_code::num2)
        {
          bg_color_red += bg_color_step;
        }
        else if(sc == hou::scan_code::num3)
        {
          bg_color_green -= bg_color_step;
        }
        else if(sc == hou::scan_code::num4)
        {
          bg_color_green += bg_color_step;
        }
        else if(sc == hou::scan_code::num5)
        {
          bg_color_blue -= bg_color_step;
        }
        else if(sc == hou::scan_code::num6)
        {
          bg_color_blue += bg_color_step;
        }
        else if(sc == hou::scan_code::num7)
        {
          bg_color_alpha -= bg_color_step;
        }
        else if(sc == hou::scan_code::num8)
        {
          bg_color_alpha += bg_color_step;
        }
        else if(sc == hou::scan_code::q)
        {
          static const std::string title2 = u8"The title has changed";
          if(w.get_title() == title)
          {
            w.set_title(title2);
          }
          else
          {
            w.set_title(title);
          }
        }
        else if(sc == hou::scan_code::w)
        {
          static const hou::image2_rgba icon1(
            hou::png_image_file::read<hou::pixel_format::rgba>(
              "./source/demo/data/monalisa.png"));
          static const hou::image2_rgba icon2(
            hou::vec2u(16u, 8u), hou::color::red());

          if(w.get_icon() == icon1)
          {
            w.set_icon(icon2);
          }
          else
          {
            w.set_icon(icon1);
          }
        }
        else if(sc == hou::scan_code::e)
        {
          w.set_bordered(!w.is_bordered());
        }
        else if(sc == hou::scan_code::r)
        {
          w.set_resizable(!w.is_resizable());
        }
        else if(sc == hou::scan_code::t)
        {
          w.set_grab(!w.get_grab());
        }
        else if(sc == hou::scan_code::y)
        {
          w.set_visible(false);
          std::this_thread::sleep_for(std::chrono::seconds(1));
          w.set_visible(true);
        }
        else if(sc == hou::scan_code::u)
        {
          w.minimize();
          std::this_thread::sleep_for(std::chrono::seconds(1));
          w.restore();
        }
        else if(sc == hou::scan_code::i)
        {
          if(w.is_resizable())
          {
            w.maximize();
            w.clear(hou::color_f(
              bg_color_red, bg_color_green, bg_color_blue, bg_color_alpha));
            std::this_thread::sleep_for(std::chrono::seconds(1));
            w.restore();
          }
        }
        if(sc == hou::scan_code::a)
        {
          wnd_pos_x -= wnd_pos_step;
          w.set_position(hou::vec2i(wnd_pos_x, wnd_pos_y));
        }
        else if(sc == hou::scan_code::f)
        {
          wnd_pos_x += wnd_pos_step;
          w.set_position(hou::vec2i(wnd_pos_x, wnd_pos_y));
        }
        else if(sc == hou::scan_code::s)
        {
          wnd_pos_y -= wnd_pos_step;
          w.set_position(hou::vec2i(wnd_pos_x, wnd_pos_y));
        }
        else if(sc == hou::scan_code::d)
        {
          wnd_pos_y += wnd_pos_step;
          w.set_position(hou::vec2i(wnd_pos_x, wnd_pos_y));
        }
        else if(sc == hou::scan_code::g)
        {
          wnd_size_x -= wnd_size_step;
          w.set_size(hou::vec2i(wnd_size_x, wnd_size_y));
        }
        else if(sc == hou::scan_code::k)
        {
          wnd_size_x += wnd_size_step;
          w.set_size(hou::vec2i(wnd_size_x, wnd_size_y));
        }
        else if(sc == hou::scan_code::h)
        {
          wnd_size_y -= wnd_size_step;
          w.set_size(hou::vec2i(wnd_size_x, wnd_size_y));
        }
        else if(sc == hou::scan_code::j)
        {
          wnd_size_y += wnd_size_step;
          w.set_size(hou::vec2i(wnd_size_x, wnd_size_y));
        }
      };
  hou::event::set_key_pressed_callback(on_key_pressed);

  std::cout << "Window display index: " << w.get_display_index() << std::endl;
  std::cout << "Window display mode: " << w.get_display_mode() << std::endl;
  std::cout << std::endl;

  std::cout << "Controls:" << std::endl;
  std::cout << "    f1: switch to windowed mode" << std::endl;
  std::cout << "    f2: switch to desktop fullscreen mode" << std::endl;
  std::cout << "    f3: switch to fullscreen mode" << std::endl;
  std::cout << "    1, 2: change background red color value" << std::endl;
  std::cout << "    3, 4: change background green color value" << std::endl;
  std::cout << "    5, 6: change background blue color value" << std::endl;
  std::cout << "    7, 8: change background alpha color value" << std::endl;
  std::cout << "    q: change window title" << std::endl;
  std::cout << "    w: change window icon" << std::endl;
  std::cout << "    e: toggle window border" << std::endl;
  std::cout << "    r: toggle window resizable" << std::endl;
  std::cout << "    t: toggle window input grab" << std::endl;
  std::cout << "    y: hide window for a short time" << std::endl;
  std::cout << "    u: minimize window for a short time" << std::endl;
  std::cout << "    i: maximize window for a short time (must be resizable)"
            << std::endl;
  std::cout << "    a, f: change window x-axis position" << std::endl;
  std::cout << "    s, d: change window y-axis position" << std::endl;
  std::cout << "    g, k: change window x-axis size" << std::endl;
  std::cout << "    h, j: change window y-axis size" << std::endl;
  std::cout << std::endl;

  while(loop)
  {
    hou::event::process_all();

    w.clear(hou::color_f(
      bg_color_red, bg_color_green, bg_color_blue, bg_color_alpha));
    w.swap_buffers();
  }

  return EXIT_SUCCESS;
}
