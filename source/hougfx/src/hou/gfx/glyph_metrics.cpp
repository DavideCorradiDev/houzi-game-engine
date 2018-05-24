// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/glyph_metrics.hpp"

#include "hou/cor/narrow_cast.hpp"



namespace hou
{

namespace
{
constexpr float pf266_to_pixel_factor = 1.f / 64.f;
}



glyph_metrics::glyph_metrics() noexcept
  : m_size()
  , m_horizontal_bearing()
  , m_horizontal_advance(0)
  , m_vertical_bearing()
  , m_vertical_advance(0)
{}



glyph_metrics::glyph_metrics(const vec2u& size, const vec2i& horizontal_bearing,
  int horizontal_advance, const vec2i& vertical_bearing,
  int vertical_advance) noexcept
  : m_size(size)
  , m_horizontal_bearing(horizontal_bearing)
  , m_horizontal_advance(horizontal_advance)
  , m_vertical_bearing(vertical_bearing)
  , m_vertical_advance(vertical_advance)
{}



const vec2u& glyph_metrics::get_size() const noexcept
{
  return m_size;
}



vec2f glyph_metrics::get_pixel_size() const noexcept
{
  return narrow_cast<vec2f>(m_size) * pf266_to_pixel_factor;
}



void glyph_metrics::set_size(const vec2u& size) noexcept
{
  m_size = size;
}



const vec2i& glyph_metrics::get_horizontal_bearing() const noexcept
{
  return m_horizontal_bearing;
}



vec2f glyph_metrics::get_pixel_horizontal_bearing() const noexcept
{
  return narrow_cast<vec2f>(m_horizontal_bearing) * pf266_to_pixel_factor;
}



void glyph_metrics::setHorizontalBearing(
  const vec2i& horizontal_bearing) noexcept
{
  m_horizontal_bearing = horizontal_bearing;
}



int glyph_metrics::get_horizontal_advance() const noexcept
{
  return m_horizontal_advance;
}



float glyph_metrics::get_pixel_horizontal_advance() const noexcept
{
  return narrow_cast<float>(m_horizontal_advance) * pf266_to_pixel_factor;
}



void glyph_metrics::set_horizontal_advance(int horizontal_advance) noexcept
{
  m_horizontal_advance = horizontal_advance;
}



const vec2i& glyph_metrics::get_vertical_bearing() const noexcept
{
  return m_vertical_bearing;
}



vec2f glyph_metrics::get_pixel_vertical_bearing() const noexcept
{
  return narrow_cast<vec2f>(m_vertical_bearing) * pf266_to_pixel_factor;
}



void glyph_metrics::set_vertical_bearing(const vec2i& vertical_bearing) noexcept
{
  m_vertical_bearing = vertical_bearing;
}



int glyph_metrics::get_vertical_advance() const noexcept
{
  return m_vertical_advance;
}



float glyph_metrics::get_pixel_vertical_advance() const noexcept
{
  return narrow_cast<float>(m_vertical_advance) * pf266_to_pixel_factor;
}



void glyph_metrics::set_vertical_advance(int vertical_advance) noexcept
{
  m_vertical_advance = vertical_advance;
}



bool operator==(const glyph_metrics& lhs, const glyph_metrics& rhs) noexcept
{
  return lhs.get_size() == rhs.get_size()
    && lhs.get_horizontal_bearing() == rhs.get_horizontal_bearing()
    && lhs.get_horizontal_advance() == rhs.get_horizontal_advance()
    && lhs.get_vertical_bearing() == rhs.get_vertical_bearing()
    && lhs.get_vertical_advance() == rhs.get_vertical_advance();
}



bool operator!=(const glyph_metrics& lhs, const glyph_metrics& rhs) noexcept
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const glyph_metrics& gm)
{
  return os << "{size = " << transpose(gm.get_size())
            << ", horizontal_bearing = "
            << transpose(gm.get_horizontal_bearing())
            << ", horizontal_advance = " << gm.get_horizontal_advance()
            << ", vertical_bearing = " << transpose(gm.get_vertical_bearing())
            << ", vertical_advance = " << gm.get_vertical_advance() << "}";
}

}  // namespace hou
