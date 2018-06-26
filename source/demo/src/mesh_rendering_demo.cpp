// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/cor_module.hpp"
#include "hou/gfx/gfx_module.hpp"
#include "hou/gl/gl_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/mesh2.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"
#include "hou/gfx/render_surface.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rotation2.hpp"

#include "hou/sys/event.hpp"
#include "hou/sys/image_file.hpp"
#include "hou/sys/window.hpp"

#include <iostream>



template <typename T>
class bounded
{
public:
  bounded(T value, T min, T max);
  const bounded& operator+=(T delta);
  const bounded& operator-=(T delta);
  operator T() const;

private:
  T m_value;
  T m_min;
  T m_max;
};



template <typename T>
bounded<T>::bounded(T value, T min, T max)
  : m_value(value)
  , m_min(min)
  , m_max(max)
{
  HOU_PRECOND(value >= min && value <= max);
}



enum class shape
{
  rectangle,
  rectangle_outline,
  ellipse,
  ellipse_outline,
};



template <typename T>
const bounded<T>& bounded<T>::operator+=(T delta)
{
  m_value += delta;
  if(m_value > m_max)
  {
    m_value = m_max;
  }
  return *this;
}



template <typename T>
const bounded<T>& bounded<T>::operator-=(T delta)
{
  m_value -= delta;
  if(m_value < m_min)
  {
    m_value = m_min;
  }
  return *this;
}



template <typename T>
bounded<T>::operator T() const
{
  return m_value;
}



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
  auto on_quit = [&loop](hou::event::timestamp) { loop = false; };
  hou::event::set_quit_callback(on_quit);

  // Context and window.
  hou::graphic_context gctx;
  hou::window wnd("MeshRenderingDemo", hou::vec2u(640u, 480u));
  hou::graphic_context::set_current(gctx, wnd);
  wnd.set_bordered(true);
  wnd.set_visible(true);
  wnd.raise();
  wnd.focus();

  // Rendering objects.
  hou::render_surface rs(wnd.get_size(), 4u);
  hou::mesh2_shader_program msp;
  hou::texture2 mesh_tex(hou::png_image_file::read<hou::pixel_format::rgba>(
    u8"./source/demo/data/monalisa.png"));

  // Mesh properties.

  bounded<float> mesh_size_x(50.f, 0.f, 100.f);
  bounded<float> mesh_size_y(50.f, 0.f, 100.f);
  float mesh_size_step = 5.f;

  bounded<float> mesh_thickness(1.f, 0.f, 10.f);
  float mesh_thickness_step = 0.5f;

  bounded<int> mesh_point_count(20u, 0u, 100u);
  int mesh_point_count_step = 5u;

  bounded<float> mesh_pos_x(0.f, 0.f, rs.get_size().x());
  bounded<float> mesh_pos_y(0.f, 0.f, rs.get_size().y());
  float mesh_pos_step = 20.f;

  bounded<float> mesh_rotation(
    0.f, -2.f * hou::pi<float>(), 2.f * hou::pi<float>());
  float mesh_rotation_step = hou::pi<float>() / 10.f;

  bounded<float> mesh_scale_x(1.f, 0.f, 3.f);
  bounded<float> mesh_scale_y(1.f, 0.f, 3.f);
  float mesh_scale_step = 0.25f;

  bounded<float> mesh_shear_x(0.f, -1.f, 1.f);
  bounded<float> mesh_shear_y(0.f, -1.f, 1.f);
  float mesh_shear_step = 0.1f;

  bounded<float> mesh_color_red(1.f, 0.f, 1.f);
  bounded<float> mesh_color_green(1.f, 0.f, 1.f);
  bounded<float> mesh_color_blue(1.f, 0.f, 1.f);
  bounded<float> mesh_color_alpha(1.f, 0.f, 1.f);
  float mesh_color_step = 0.1f;

  shape mesh_shape = shape::rectangle;

  bool mesh_texture_active = false;

  auto on_key_pressed
    = [&](hou::event::timestamp, hou::window::uid_type, hou::scan_code sc,
        hou::key_code, hou::modifier_keys, bool) {
        // position
        if(sc == hou::scan_code::a)
        {
          mesh_pos_x -= mesh_pos_step;
        }
        else if(sc == hou::scan_code::f)
        {
          mesh_pos_x += mesh_pos_step;
        }
        else if(sc == hou::scan_code::s)
        {
          mesh_pos_y -= mesh_pos_step;
        }
        else if(sc == hou::scan_code::d)
        {
          mesh_pos_y += mesh_pos_step;
        }
        // scale
        else if(sc == hou::scan_code::g)
        {
          mesh_scale_x -= mesh_scale_step;
        }
        else if(sc == hou::scan_code::k)
        {
          mesh_scale_x += mesh_scale_step;
        }
        else if(sc == hou::scan_code::h)
        {
          mesh_scale_y -= mesh_scale_step;
        }
        else if(sc == hou::scan_code::j)
        {
          mesh_scale_y += mesh_scale_step;
        }
        // shear
        else if(sc == hou::scan_code::z)
        {
          mesh_shear_x -= mesh_shear_step;
        }
        else if(sc == hou::scan_code::v)
        {
          mesh_shear_x += mesh_shear_step;
        }
        else if(sc == hou::scan_code::x)
        {
          mesh_shear_y -= mesh_shear_step;
        }
        else if(sc == hou::scan_code::c)
        {
          mesh_shear_y += mesh_shear_step;
        }
        // size
        else if(sc == hou::scan_code::q)
        {
          mesh_size_x -= mesh_size_step;
        }
        else if(sc == hou::scan_code::r)
        {
          mesh_size_x += mesh_size_step;
        }
        else if(sc == hou::scan_code::w)
        {
          mesh_size_y -= mesh_size_step;
        }
        else if(sc == hou::scan_code::e)
        {
          mesh_size_y += mesh_size_step;
        }
        // rotation
        else if(sc == hou::scan_code::b)
        {
          mesh_rotation -= mesh_rotation_step;
        }
        else if(sc == hou::scan_code::n)
        {
          mesh_rotation += mesh_rotation_step;
        }
        // thickness
        else if(sc == hou::scan_code::t)
        {
          mesh_thickness -= mesh_thickness_step;
        }
        else if(sc == hou::scan_code::y)
        {
          mesh_thickness += mesh_thickness_step;
        }
        // point count
        else if(sc == hou::scan_code::u)
        {
          mesh_point_count -= mesh_point_count_step;
        }
        else if(sc == hou::scan_code::i)
        {
          mesh_point_count += mesh_point_count_step;
        }
        // color
        else if(sc == hou::scan_code::num1)
        {
          mesh_color_red -= mesh_color_step;
        }
        else if(sc == hou::scan_code::num2)
        {
          mesh_color_red += mesh_color_step;
        }
        else if(sc == hou::scan_code::num3)
        {
          mesh_color_green -= mesh_color_step;
        }
        else if(sc == hou::scan_code::num4)
        {
          mesh_color_green += mesh_color_step;
        }
        else if(sc == hou::scan_code::num5)
        {
          mesh_color_blue -= mesh_color_step;
        }
        else if(sc == hou::scan_code::num6)
        {
          mesh_color_blue += mesh_color_step;
        }
        else if(sc == hou::scan_code::num7)
        {
          mesh_color_alpha -= mesh_color_step;
        }
        else if(sc == hou::scan_code::num8)
        {
          mesh_color_alpha += mesh_color_step;
        }
        // Shape
        else if(sc == hou::scan_code::f1)
        {
          mesh_shape = shape::rectangle;
        }
        else if(sc == hou::scan_code::f2)
        {
          mesh_shape = shape::rectangle_outline;
        }
        else if(sc == hou::scan_code::f3)
        {
          mesh_shape = shape::ellipse;
        }
        else if(sc == hou::scan_code::f4)
        {
          mesh_shape = shape::ellipse_outline;
        }
        // Texture
        else if(sc == hou::scan_code::num0)
        {
          mesh_texture_active = !mesh_texture_active;
        }
      };
  hou::event::set_key_pressed_callback(on_key_pressed);

  std::cout << "Controls:" << std::endl;
  std::cout << "    F1, F2, F3, F4: change shape" << std::endl;
  std::cout << "    0: activate / deactivate texture" << std::endl;
  std::cout << "    1, 2: change red color value" << std::endl;
  std::cout << "    3, 4: change green color value" << std::endl;
  std::cout << "    5, 6: change blue color value" << std::endl;
  std::cout << "    7, 8: change alpha color value" << std::endl;
  std::cout << "    q, r: change x-axis size" << std::endl;
  std::cout << "    w, e: change y-axis size" << std::endl;
  std::cout << "    t, y: change outline thickness, if applicable" << std::endl;
  std::cout << "    u, i: change mesh point count, if applicable" << std::endl;
  std::cout << "    a, f: change x-axis position" << std::endl;
  std::cout << "    s, d: change y-axis position" << std::endl;
  std::cout << "    g, k: change x-axis scale" << std::endl;
  std::cout << "    h, j: change y-axis scale" << std::endl;
  std::cout << "    z, v: change x-axis shear" << std::endl;
  std::cout << "    x, c: change y-axis shear" << std::endl;
  std::cout << "    b, n: change rotation" << std::endl;
  std::cout << std::endl;

  // Main loop.
  while(loop)
  {
    hou::event::process_all();
    rs.clear(hou::color::black());

    hou::vec2f mesh_size(mesh_size_x, mesh_size_y);
    std::unique_ptr<hou::mesh2> m = nullptr;
    switch(mesh_shape)
    {
      case shape::rectangle:
        m = std::make_unique<hou::mesh2>(hou::create_rectangle_mesh2(mesh_size));
        break;
      case shape::rectangle_outline:
        m = std::make_unique<hou::mesh2>(
          hou::create_rectangle_outline_mesh2(mesh_size, mesh_thickness));
        break;
      case shape::ellipse:
        m = std::make_unique<hou::mesh2>(
          hou::create_ellipse_mesh2(mesh_size, mesh_point_count));
        break;
      case shape::ellipse_outline:
        m = std::make_unique<hou::mesh2>(hou::create_ellipse_outline_mesh2(
          mesh_size, mesh_point_count, mesh_thickness));
        break;
    }
    HOU_ASSERT(m != nullptr);

    hou::trans2f projection_transform
      = hou::trans2f::orthographic_projection(rs.get_viewport());

    hou::vec2f mesh_pos(mesh_pos_x, mesh_pos_y);
    hou::vec2f mesh_scale(mesh_scale_x, mesh_scale_y);
    hou::trans2f mesh_transform = hou::trans2f::translation(mesh_pos)
      * hou::trans2f::rotation(hou::rot2f(mesh_rotation))
      * hou::trans2f::scale(mesh_scale)
      * hou::trans2f::shear(mesh_shear_x, mesh_shear_y);

    hou::color mesh_color = hou::color_f(
      mesh_color_red, mesh_color_green, mesh_color_blue, mesh_color_alpha);

    if(mesh_texture_active)
    {
      msp.draw(
        rs, *m, mesh_tex, mesh_color, projection_transform * mesh_transform);
    }
    else
    {
      msp.draw(rs, *m, mesh_color, projection_transform * mesh_transform);
    }

    rs.display();
  }

  return EXIT_SUCCESS;
}
