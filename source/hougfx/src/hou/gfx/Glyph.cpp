// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Glyph.hpp"



namespace hou
{

Glyph::Glyph()
  : mImage(vec2u())
  , mMetrics()
{}



Glyph::Glyph(const image2R& ph_image, const GlyphMetrics& metrics)
  : mImage(ph_image)
  , mMetrics(metrics)
{}



const image2R& Glyph::get_image() const
{
  return mImage;
}



void Glyph::set_image(const image2R& ph_image)
{
  mImage = ph_image;
}



const GlyphMetrics& Glyph::getMetrics() const
{
  return mMetrics;
}



void Glyph::setMetrics(const GlyphMetrics& metrics)
{
  mMetrics = metrics;
}



bool operator==(const Glyph& lhs, const Glyph& rhs)
{
  return lhs.get_image() == rhs.get_image() && lhs.getMetrics() == rhs.getMetrics();
}



bool operator!=(const Glyph& lhs, const Glyph& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const Glyph& gm)
{
  return os
    << "{image = " << gm.get_image()
    << ", Metrics = " << gm.getMetrics()
    << "}";
}

}

