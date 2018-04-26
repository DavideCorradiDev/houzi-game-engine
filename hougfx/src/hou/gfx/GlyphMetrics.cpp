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
  : mSize()
  , mHorizontalBearing()
  , mHorizontalAdvance(0)
  , mVerticalBearing()
  , mVerticalAdvance(0)
{}



GlyphMetrics::GlyphMetrics(const Vec2u& size, const Vec2i& horizontalBearing,
  int horizontalAdvance, const Vec2i& verticalBearing, int verticalAdvance)
  : mSize(size)
  , mHorizontalBearing(horizontalBearing)
  , mHorizontalAdvance(horizontalAdvance)
  , mVerticalBearing(verticalBearing)
  , mVerticalAdvance(verticalAdvance)
{}



const Vec2u& GlyphMetrics::getSize() const
{
  return mSize;
}



Vec2f GlyphMetrics::getPixelSize() const
{
  return static_cast<Vec2f>(mSize) * pf266ToPixelFactor;
}



void GlyphMetrics::setSize(const Vec2u& size)
{
  mSize = size;
}



const Vec2i& GlyphMetrics::getHorizontalBearing() const
{
  return mHorizontalBearing;
}



Vec2f GlyphMetrics::getPixelHorizontalBearing() const
{
  return static_cast<Vec2f>(mHorizontalBearing) * pf266ToPixelFactor;
}



void GlyphMetrics::setHorizontalBearing(const Vec2i& horizontalBearing)
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



const Vec2i& GlyphMetrics::getVerticalBearing() const
{
  return mVerticalBearing;
}



Vec2f GlyphMetrics::getPixelVerticalBearing() const
{
  return static_cast<Vec2f>(mVerticalBearing) * pf266ToPixelFactor;
}



void GlyphMetrics::setVerticalBearing(const Vec2i& verticalBearing)
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
  return lhs.getSize() == rhs.getSize()
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
  return os << "{Size = " << transpose(gm.getSize())
            << ", HorizontalBearing = " << transpose(gm.getHorizontalBearing())
            << ", HorizontalAdvance = " << gm.getHorizontalAdvance()
            << ", VerticalBearing = " << transpose(gm.getVerticalBearing())
            << ", VerticalAdvance = " << gm.getVerticalAdvance() << "}";
}

}  // namespace hou
