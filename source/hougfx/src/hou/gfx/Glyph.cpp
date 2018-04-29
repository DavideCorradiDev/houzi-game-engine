// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/glyph.hpp"



namespace hou
{

glyph::glyph()
  : m_image(vec2u())
  , m_metrics()
{}



glyph::glyph(const image2R& ph_image, const glyph_metrics& metrics)
  : m_image(ph_image)
  , m_metrics(metrics)
{}



const image2R& glyph::get_image() const
{
  return m_image;
}



void glyph::set_image(const image2R& ph_image)
{
  m_image = ph_image;
}



const glyph_metrics& glyph::get_metrics() const
{
  return m_metrics;
}



void glyph::set_metrics(const glyph_metrics& metrics)
{
  m_metrics = metrics;
}



bool operator==(const glyph& lhs, const glyph& rhs)
{
  return lhs.get_image() == rhs.get_image() && lhs.get_metrics() == rhs.get_metrics();
}



bool operator!=(const glyph& lhs, const glyph& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const glyph& gm)
{
  return os
    << "{image = " << gm.get_image()
    << ", Metrics = " << gm.get_metrics()
    << "}";
}

}

