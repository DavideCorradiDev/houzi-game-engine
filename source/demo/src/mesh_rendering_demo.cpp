// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"
#include "hou/gl/gl_module.hpp"
#include "hou/gfx/gfx_module.hpp"

#include "hou/sys/event.hpp"
#include "hou/sys/window.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/mesh2.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"
#include "hou/gfx/render_surface.hpp"

#include <iostream>




#include "hou/cor/clock.hpp"

int main(int, char**)
{
  // Setup.
  hou::cor_module::initialize();
  hou::mth_module::initialize();
  hou::sys_module::initialize();
  hou::gl_module::initialize();
  hou::gfx_module::initialize();

  // Event callbacks.
  bool loop = true;
  auto on_quit = [&loop](hou::event::timestamp) {
    loop = false;
  };
  hou::event::set_quit_callback(on_quit);
  auto on_window_closed = [&loop](hou::event::timestamp, hou::window::uid_type) {
    loop = false;
  };
  hou::event::set_window_closed_callback(on_window_closed);

  // Context and window.
  hou::graphic_context gctx;
  hou::window wnd("MeshRenderingDemo", hou::vec2u(640u, 480u));
  hou::graphic_context::set_current(gctx, wnd);
  wnd.set_bordered(true);
  wnd.set_visible(true);
  wnd.raise();
  wnd.focus();

  // Rendering objects
  hou::render_surface rs(wnd.get_size(), 4u);
  hou::trans2f projection_transform
    = hou::trans2f::orthographic_projection(rs.get_viewport());

  hou::mesh2_shader_program msp;
  hou::mesh2 rectangle = hou::create_rectangle_mesh2(hou::vec2f(32.f, 64.f));

  // Main loop.
  std::chrono::nanoseconds elapsed_time(0);
  std::chrono::nanoseconds tick_period(std::chrono::seconds(1));
  hou::clock c;
  while(loop)
  {
    hou::event::process_all();
    rs.clear(hou::color::black());
    msp.draw(rs, rectangle, hou::color::red(),
      projection_transform * hou::trans2f::translation(hou::vec2f(16.f, 30.f)));
    hou::render_surface rs2(wnd.get_size(), 4u);
    rs.display();
  }

  return EXIT_SUCCESS;
}
