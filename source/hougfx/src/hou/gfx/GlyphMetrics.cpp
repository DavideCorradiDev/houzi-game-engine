// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/GlyphMetrics.hpp"



namespace hou
{

namespace
{
static constexpr float pf266ToPixelFactor = 1.f / 64.f;
}



GlyphMetrics::GlyphMetrics()
  : m_size()
  , mHorizontalBearing()
  , mHorizontalAdvance(0)
  , mVerticalBearing()
  , mVerticalAdvance(0)
{}



GlyphMetrics::GlyphMetrics(const vec2u& size, const vec2i& horizontalBearing,
  int horizontalAdvance, const vec2i& verticalBearing, int verticalAdvance)
  : m_size(size)
  , mHorizontalBearing(horizontalBearing)
  , mHorizontalAdvance(horizontalAdvance)
  , mVerticalBearing(verticalBearing)
  , mVerticalAdvance(verticalAdvance)
{}



const vec2u& GlyphMetrics::get_size() const
{
  return m_size;
}



vec2f GlyphMetrics::getPixelSize() const
{
  return static_cast<vec2f>(m_size) * pf266ToPixelFactor;
}



void GlyphMetrics::set_size(const vec2u& size)
{
  m_size = size;
}



const vec2i& GlyphMetrics::getHorizontalBearing() const
{
  return mHorizontalBearing;
}



vec2f GlyphMetrics::getPixelHorizontalBearing() const
{
  return static_cast<vec2f>(mHorizontalBearing) * pf266ToPixelFactor;
}



void GlyphMetrics::setHorizontalBearing(const vec2i& horizontalBearing)
{
  mHorizontalBearing = horizontalBearing;
}



int GlyphMetrics::getHorizontalAdvance() const
{
  return mHorizontalAdvance;
}



float GlyphMetrics::getPixelHorizontalAdvance() const
{
  return static_cast<float>(mHorizontalAdvance) * pf266ToPixelFactor;
}



void GlyphMetrics::setHorizontalAdvance(int horizontalAdvance)
{
  mHorizontalAdvance = horizontalAdvance;
}



const vec2i& GlyphMetrics::getVerticalBearing() const
{
  return mVerticalBearing;
}



vec2f GlyphMetrics::getPixelVerticalBearing() const
{
  return static_cast<vec2f>(mVerticalBearing) * pf266ToPixelFactor;
}



void GlyphMetrics::setVerticalBearing(const vec2i& verticalBearing)
{
  mVerticalBearing = verticalBearing;
}



int GlyphMetrics::getVerticalAdvance() const
{
  return mVerticalAdvance;
}



float GlyphMetrics::getPixelVerticalAdvance() const
{
  return static_cast<float>(mVerticalAdvance) * pf266ToPixelFactor;
}



void GlyphMetrics::setVerticalAdvance(int verticalAdvance)
{
  mVerticalAdvance = verticalAdvance;
}



bool operator==(const GlyphMetrics& lhs, const GlyphMetrics& rhs)
{
  return lhs.get_size() == rhs.get_size()
    && lhs.getHorizontalBearing() == rhs.getHorizontalBearing()
    && lhs.getHorizontalAdvance() == rhs.getHorizontalAdvance()
    && lhs.getVerticalBearing() == rhs.getVerticalBearing()
    && lhs.getVerticalAdvance() == rhs.getVerticalAdvance();
}



bool operator!=(const GlyphMetrics& lhs, const GlyphMetrics& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const GlyphMetrics& gm)
{
  return os << "{size_type = " << transpose(gm.get_size())
            << ", HorizontalBearing = " << transpose(gm.getHorizontalBearing())
            << ", HorizontalAdvance = " << gm.getHorizontalAdvance()
            << ", VerticalBearing = " << transpose(gm.getVerticalBearing())
            << ", VerticalAdvance = " << gm.getVerticalAdvance() << "}";
}

}  // namespace hou
