// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/GlyphMetrics.hpp"



namespace hou
{

GlyphMetrics::GlyphMetrics()
  : mSize()
  , mHorizontalBearing()
  , mHorizontalAdvance(0)
  , mVerticalBearing()
  , mVerticalAdvance(0)
{}



GlyphMetrics::GlyphMetrics(const Vec2u& size
  , const Vec2i& horizontalBearing, int horizontalAdvance
  , const Vec2i& verticalBearing, int verticalAdvance)
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



void GlyphMetrics::setSize(const Vec2u& size)
{
  mSize = size;
}



const Vec2i& GlyphMetrics::getHorizontalBearing() const
{
  return mHorizontalBearing;
}



void GlyphMetrics::setHorizontalBearing(const Vec2i& horizontalBearing)
{
  mHorizontalBearing = horizontalBearing;
}



int GlyphMetrics::getHorizontalAdvance() const
{
  return mHorizontalAdvance;
}



void GlyphMetrics::setHorizontalAdvance(int horizontalAdvance)
{
  mHorizontalAdvance = horizontalAdvance;
}



const Vec2i& GlyphMetrics::getVerticalBearing() const
{
  return mVerticalBearing;
}



void GlyphMetrics::setVerticalBearing(const Vec2i& verticalBearing)
{
  mVerticalBearing = verticalBearing;
}



int GlyphMetrics::getVerticalAdvance() const
{
  return mVerticalAdvance;
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
  return os
    << "{Size = " << transpose(gm.getSize())
    << ", HorizontalBearing = " << transpose(gm.getHorizontalBearing())
    << ", HorizontalAdvance = " << gm.getHorizontalAdvance()
    << ", VerticalBearing = " << transpose(gm.getVerticalBearing())
    << ", VerticalAdvance = " << gm.getVerticalAdvance()
    << "}";
}

}

