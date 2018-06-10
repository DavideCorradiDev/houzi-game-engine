#include "hou/sys/sys_module.hpp"

#include "hou/mth/rectangle.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/render_window.hpp"
#include "hou/gfx/mesh2.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"

#include <iostream>

using namespace hou;



int main()
{
  sys_module::initialize();
  call_terminate_on_exit<sys_module>();

  graphic_context gctx;
  graphic_context::set_current(gctx);

  mesh2_shader_program m2r;
  mesh2 rect = create_rectangle_mesh2(vec2f(32.f, 16.f));

  render_window rw("WindowDemo", vec2u(640u, 480u));
  trans2f proj_t = trans2f::orthographic_projection(rectf(0, 0, 640, 480));

  m2r.draw(rw, rect, color::red(), proj_t * trans2f::translation(vec2f(40.f, 88.f)));

  rw.show();
  rw.display();


  std::cout << "Press any key";
  std::cin.get();

  return 0;
}

