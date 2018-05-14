// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/vertex2.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/vertex_format.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rectangle.hpp"



namespace hou
{

namespace
{

mesh2 create_generic_rectangle_mesh2(
  float l, float t, float w, float h, float tl, float tt, float tw, float th);



mesh2 create_generic_rectangle_mesh2(
  float l, float t, float w, float h, float tl, float tt, float tw, float th)
{
  float r = l + w;
  float b = t + h;
  float tr = tl + tw;
  float tb = tt + th;
  return mesh2(mesh_draw_mode::triangle_fan, mesh_fill_mode::fill,
    std::vector<vertex2>{vertex2(vec2f(l, t), vec2f(tl, tt), color::white),
      vertex2(vec2f(l, b), vec2f(tl, tb), color::white),
      vertex2(vec2f(r, b), vec2f(tr, tb), color::white),
      vertex2(vec2f(r, t), vec2f(tr, tt), color::white)});
}

}  // namespace



const vertex_format& vertex2::get_vertex_format()
{
  static constexpr bool must_be_normalized = true;
  static const vertex_format vf(0, sizeof(vertex2),
    {vertex_attrib_format(gl_type::float_decimal, vertex2::s_position_size,
       offsetof(vertex2, m_position), !must_be_normalized),
      vertex_attrib_format(gl_type::float_decimal,
        vertex2::s_texture_coordinates_size, offsetof(vertex2, m_tex_coords),
        must_be_normalized),
      vertex_attrib_format(gl_type::float_decimal, vertex2::s_color_size,
        offsetof(vertex2, m_color), must_be_normalized)});
  return vf;
}



vertex2::vertex2() noexcept
  : vertex2(vec2f(0.f, 0.f), vec2f(0.f, 0.f), color(0, 0, 0, 0))
{}



vertex2::vertex2(
  const vec2f& position, const vec2f& tex_coords, const color& col) noexcept
  : m_position{position.x(), position.y()}
  , m_tex_coords{tex_coords.x(), tex_coords.y()}
  , m_color{
      col.get_red_f(), col.get_green_f(), col.get_blue_f(), col.get_alpha_f()}
{}



vec2f vertex2::get_position() const noexcept
{
  return vec2f(m_position[0], m_position[1]);
}



void vertex2::set_position(const vec2f& pos) noexcept
{
  m_position[0] = pos.x();
  m_position[1] = pos.y();
}



vec2f vertex2::get_texture_coordinates() const noexcept
{
  return vec2f(m_tex_coords[0], m_tex_coords[1]);
}



void vertex2::set_texture_coordinates(const vec2f& tex_coords) noexcept
{
  m_tex_coords[0] = tex_coords.x();
  m_tex_coords[1] = tex_coords.y();
}



color vertex2::get_color() const noexcept
{
  return color(
    m_color[0] * 255, m_color[1] * 255, m_color[2] * 255, m_color[3] * 255);
}



void vertex2::set_color(const color& color) noexcept
{
  m_color[0] = color.get_red_f();
  m_color[1] = color.get_green_f();
  m_color[2] = color.get_blue_f();
  m_color[3] = color.get_alpha_f();
}



bool operator==(const vertex2& lhs, const vertex2& rhs) noexcept
{
  return lhs.get_position() == rhs.get_position()
    && lhs.get_texture_coordinates() == rhs.get_texture_coordinates()
    && lhs.get_color() == rhs.get_color();
}



bool operator!=(const vertex2& lhs, const vertex2& rhs) noexcept
{
  return !(lhs == rhs);
}



bool close(
  const vertex2& lhs, const vertex2& rhs, vertex2::comparison_type acc) noexcept
{
  return lhs.get_color() == rhs.get_color()
    && close(lhs.get_position(), rhs.get_position(), acc)
    && close(lhs.get_texture_coordinates(), rhs.get_texture_coordinates(), acc);
}



std::ostream& operator<<(std::ostream& os, const vertex2& v)
{
  return os << "{position = " << transpose(v.get_position())
            << ", texture_coordinates = "
            << transpose(v.get_texture_coordinates())
            << ", color = " << v.get_color() << "}";
}
mesh2 create_rectangle_mesh2(const vec2f& size)
{
  return create_generic_rectangle_mesh2(
    0.f, 0.f, size.x(), size.y(), 0.f, 0.f, 1.f, 1.f);
}



mesh2 create_rectangle_outline_mesh2(const vec2f& size, float thickness)
{
  rectf er(vec2f::zero(), size);
  vec2f tv(thickness, thickness);
  rectf ir(tv, size - 2 * tv);
  return mesh2(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill,
    std::vector<vertex2>{
      vertex2(vec2f(er.l(), er.t()), vec2f::zero(), color::white),
      vertex2(vec2f(ir.l(), ir.t()), vec2f::zero(), color::white),
      vertex2(vec2f(er.l(), er.b()), vec2f::zero(), color::white),
      vertex2(vec2f(ir.l(), ir.b()), vec2f::zero(), color::white),
      vertex2(vec2f(er.r(), er.b()), vec2f::zero(), color::white),
      vertex2(vec2f(ir.r(), ir.b()), vec2f::zero(), color::white),
      vertex2(vec2f(er.r(), er.t()), vec2f::zero(), color::white),
      vertex2(vec2f(ir.r(), ir.t()), vec2f::zero(), color::white),
      vertex2(vec2f(er.l(), er.t()), vec2f::zero(), color::white),
      vertex2(vec2f(ir.l(), ir.t()), vec2f::zero(), color::white)});
}



mesh2 create_ellipse_mesh2(const vec2f& size, uint point_count)
{
  vec2f radius = size / 2.f;

  std::vector<vertex2> vertices(point_count + 2);
  vertices[0].set_position(radius);
  vertices[0].set_color(color::white);

  float t = 0.f;
  float dt = 2.f * pi_f / point_count;
  for(size_t i = 1; i < vertices.size(); ++i)
  {
    vec2f dPos(radius.x() * cosf(t), radius.y() * sinf(t));
    vertices[i].set_position(radius + dPos);
    vertices[i].set_color(color::white);
    t += dt;
  }
  return mesh2(mesh_draw_mode::triangle_fan, mesh_fill_mode::fill, vertices);
}



mesh2 create_ellipse_outline_mesh2(
  const vec2f& size, uint point_count, float thickness)
{
  vec2f e_radius = size / 2.f;
  vec2f i_radius = e_radius - vec2f(thickness, thickness);

  float t = 0.f;
  float dt = 2 * pi_f / point_count;
  std::vector<vertex2> vertices(2 * point_count + 2);
  for(size_t i = 0; i < vertices.size(); ++i)
  {
    float c = cosf(t);
    float s = sinf(t);

    vec2f ed_pos(e_radius.x() * c, e_radius.y() * s);
    vertices[i].set_position(e_radius + ed_pos);
    vertices[i].set_color(color::white);
    ++i;
    HOU_DEV_ASSERT(i < vertices.size());

    vec2f idPos(i_radius.x() * c, i_radius.y() * s);
    vertices[i].set_position(e_radius + idPos);
    vertices[i].set_color(color::white);

    t += dt;
  }
  return mesh2(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices);
}



mesh2 create_texture_quad_mesh2(const rectf& rect, const vec2f& tex_size)
{
  return create_generic_rectangle_mesh2(0.f, 0.f, rect.w(), rect.h(),
    rect.x() / tex_size.x(), rect.y() / tex_size.y(), rect.w() / tex_size.x(),
    rect.h() / tex_size.y());
}

}  // namespace hou
