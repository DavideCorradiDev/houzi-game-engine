// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/vertex2.hpp"

#include "hou/gfx/vertex_format.hpp"



namespace hou
{

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
{
  HOU_DEV_ASSERT(m_color[0] >= 0.f && m_color[0] <= 1.f);
  HOU_DEV_ASSERT(m_color[1] >= 0.f && m_color[1] <= 1.f);
  HOU_DEV_ASSERT(m_color[2] >= 0.f && m_color[2] <= 1.f);
  HOU_DEV_ASSERT(m_color[3] >= 0.f && m_color[3] <= 1.f);
}



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
    static_cast<uint8_t>(m_color[0] * 255),
    static_cast<uint8_t>(m_color[1] * 255),
    static_cast<uint8_t>(m_color[2] * 255),
    static_cast<uint8_t>(m_color[3] * 255));
}



void vertex2::set_color(const color& color) noexcept
{
  m_color[0] = color.get_red_f();
  m_color[1] = color.get_green_f();
  m_color[2] = color.get_blue_f();
  m_color[3] = color.get_alpha_f();

  HOU_DEV_ASSERT(m_color[0] >= 0.f && m_color[0] <= 1.f);
  HOU_DEV_ASSERT(m_color[1] >= 0.f && m_color[1] <= 1.f);
  HOU_DEV_ASSERT(m_color[2] >= 0.f && m_color[2] <= 1.f);
  HOU_DEV_ASSERT(m_color[3] >= 0.f && m_color[3] <= 1.f);
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



bool close(const vertex2& lhs, const vertex2& rhs, float acc) noexcept
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

}  // namespace hou
