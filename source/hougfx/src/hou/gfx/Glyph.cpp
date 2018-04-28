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



Glyph::Glyph(const Image2R& image, const GlyphMetrics& metrics)
  : mImage(image)
  , mMetrics(metrics)
{}



const Image2R& Glyph::getImage() const
{
  return mImage;
}



void Glyph::setImage(const Image2R& image)
{
  mImage = image;
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
  return lhs.getImage() == rhs.getImage() && lhs.getMetrics() == rhs.getMetrics();
}



bool operator!=(const Glyph& lhs, const Glyph& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const Glyph& gm)
{
  return os
    << "{Image = " << gm.getImage()
    << ", Metrics = " << gm.getMetrics()
    << "}";
}

}

