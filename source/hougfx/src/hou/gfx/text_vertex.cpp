// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/text_vertex.hpp"

#include "hou/gfx/vertex_format.hpp"



namespace hou
{

const vertex_format& text_vertex::get_vertex_format()
{
  static constexpr bool must_be_normalized = true;
  static const vertex_format vf(0, sizeof(text_vertex),
    {vertex_attrib_format(gl_type::float_decimal, text_vertex::s_position_size,
       offsetof(text_vertex, m_position), !must_be_normalized),
      vertex_attrib_format(gl_type::float_decimal,
        text_vertex::s_texture_coordinates_size,
        offsetof(text_vertex, m_tex_coords), must_be_normalized)});
  return vf;
}



text_vertex::text_vertex() noexcept
  : text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f))
{}



text_vertex::text_vertex(
  const vec2f& position, const vec3f& tex_coords) noexcept
  : m_position{position.x(), position.y()}
  , m_tex_coords{tex_coords.x(), tex_coords.y(), tex_coords.z()}
{}



vec2f text_vertex::get_position() const noexcept
{
  return vec2f(m_position[0], m_position[1]);
}



void text_vertex::set_position(const vec2f& pos) noexcept
{
  m_position[0] = pos.x();
  m_position[1] = pos.y();
}



vec3f text_vertex::get_texture_coordinates() const noexcept
{
  return vec3f(m_tex_coords[0], m_tex_coords[1], m_tex_coords[2]);
}



void text_vertex::set_texture_coordinates(const vec3f& tex_coords) noexcept
{
  m_tex_coords[0] = tex_coords.x();
  m_tex_coords[1] = tex_coords.y();
  m_tex_coords[2] = tex_coords.z();
}



bool operator==(const text_vertex& lhs, const text_vertex& rhs) noexcept
{
  return lhs.get_position() == rhs.get_position()
    && lhs.get_texture_coordinates() == rhs.get_texture_coordinates();
}



bool operator!=(const text_vertex& lhs, const text_vertex& rhs) noexcept
{
  return !(lhs == rhs);
}



bool close(const text_vertex& lhs, const text_vertex& rhs, float acc) noexcept
{
  return close(lhs.get_position(), rhs.get_position(), acc)
    && close(lhs.get_texture_coordinates(), rhs.get_texture_coordinates(), acc);
}



std::ostream& operator<<(std::ostream& os, const text_vertex& v)
{
  return os << "{position = " << transpose(v.get_position())
            << ", texture_coordinates = "
            << transpose(v.get_texture_coordinates()) << "}";
}

}  // namespace hou
