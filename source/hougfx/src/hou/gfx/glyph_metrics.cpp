// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/glyph_metrics.hpp"



namespace hou
{

namespace
{
static constexpr float pf266ToPixelFactor = 1.f / 64.f;
}



glyph_metrics::glyph_metrics()
  : m_size()
  , m_horizontal_bearing()
  , m_horizontal_advance(0)
  , m_vertical_bearing()
  , m_vertical_advance(0)
{}



glyph_metrics::glyph_metrics(const vec2u& size, const vec2i& horizontalBearing,
  int horizontalAdvance, const vec2i& verticalBearing, int verticalAdvance)
  : m_size(size)
  , m_horizontal_bearing(horizontalBearing)
  , m_horizontal_advance(horizontalAdvance)
  , m_vertical_bearing(verticalBearing)
  , m_vertical_advance(verticalAdvance)
{}



const vec2u& glyph_metrics::get_size() const
{
  return m_size;
}



vec2f glyph_metrics::get_pixel_size() const
{
  return static_cast<vec2f>(m_size) * pf266ToPixelFactor;
}



void glyph_metrics::set_size(const vec2u& size)
{
  m_size = size;
}



const vec2i& glyph_metrics::get_horizontal_bearing() const
{
  return m_horizontal_bearing;
}



vec2f glyph_metrics::get_pixel_horizontal_bearing() const
{
  return static_cast<vec2f>(m_horizontal_bearing) * pf266ToPixelFactor;
}



void glyph_metrics::setHorizontalBearing(const vec2i& horizontalBearing)
{
  m_horizontal_bearing = horizontalBearing;
}



int glyph_metrics::get_horizontal_advance() const
{
  return m_horizontal_advance;
}



float glyph_metrics::get_pixel_horizontal_advance() const
{
  return static_cast<float>(m_horizontal_advance) * pf266ToPixelFactor;
}



void glyph_metrics::set_horizontal_advance(int horizontalAdvance)
{
  m_horizontal_advance = horizontalAdvance;
}



const vec2i& glyph_metrics::get_vertical_bearing() const
{
  return m_vertical_bearing;
}



vec2f glyph_metrics::get_pixel_vertical_bearing() const
{
  return static_cast<vec2f>(m_vertical_bearing) * pf266ToPixelFactor;
}



void glyph_metrics::set_vertical_bearing(const vec2i& verticalBearing)
{
  m_vertical_bearing = verticalBearing;
}



int glyph_metrics::get_vertical_advance() const
{
  return m_vertical_advance;
}



float glyph_metrics::get_pixel_vertical_advance() const
{
  return static_cast<float>(m_vertical_advance) * pf266ToPixelFactor;
}



void glyph_metrics::set_vertical_advance(int verticalAdvance)
{
  m_vertical_advance = verticalAdvance;
}



bool operator==(const glyph_metrics& lhs, const glyph_metrics& rhs)
{
  return lhs.get_size() == rhs.get_size()
    && lhs.get_horizontal_bearing() == rhs.get_horizontal_bearing()
    && lhs.get_horizontal_advance() == rhs.get_horizontal_advance()
    && lhs.get_vertical_bearing() == rhs.get_vertical_bearing()
    && lhs.get_vertical_advance() == rhs.get_vertical_advance();
}



bool operator!=(const glyph_metrics& lhs, const glyph_metrics& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const glyph_metrics& gm)
{
  return os << "{size_type = " << transpose(gm.get_size())
            << ", HorizontalBearing = " << transpose(gm.get_horizontal_bearing())
            << ", HorizontalAdvance = " << gm.get_horizontal_advance()
            << ", VerticalBearing = " << transpose(gm.get_vertical_bearing())
            << ", VerticalAdvance = " << gm.get_vertical_advance() << "}";
}

}  // namespace hou
