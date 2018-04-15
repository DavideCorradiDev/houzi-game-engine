// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/GlyphRenderInfo.hpp"

#include "hou/gfx/Texture.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/Rectangle.hpp"



namespace hou
{

GlyphRenderInfo::GlyphRenderInfo(const GlyphMetrics& metrics
  , const Texture2& texture, const Vec2f& textureOffset)
  : mMetrics(metrics)
  , mMesh(createTextureQuadMesh2
    ( Rectf(textureOffset, static_cast<Vec2f>(metrics.getSize()) / 64.f)
    , texture.getSize()))
  , mTexture(&texture)
{}



GlyphRenderInfo::GlyphRenderInfo(GlyphRenderInfo&& other)
  : mMetrics(std::move(other.mMetrics))
  , mMesh(std::move(other.mMesh))
  , mTexture(std::move(other.mTexture))
{}



const GlyphMetrics& GlyphRenderInfo::getMetrics() const
{
  return mMetrics;
}



const Mesh2& GlyphRenderInfo::getMesh() const
{
  return mMesh;
}



const Texture2& GlyphRenderInfo::getTexture() const
{
  return *mTexture;
}

}

