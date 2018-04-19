// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/RenderTexture.hpp"

#include "hou/gfx/Texture.hpp"



namespace hou
{

RenderTexture::RenderTexture(const Vec2u& size, uint sampleCount)
  : RenderSurface(size, sampleCount)
{}



RenderTexture::RenderTexture(RenderTexture&& other)
  : RenderSurface(std::move(other))
{}



RenderTexture::~RenderTexture()
{}



Texture2 RenderTexture::toTexture() const
{
  if(isMultisampled())
  {
    RenderTexture ssRenderTexture(getSize(), 0u);
    Recti viewport = getDefaultViewport();
    blit(*this, viewport, ssRenderTexture, viewport);
    return ssRenderTexture.toTexture();
  }
  else
  {
    return RenderSurface::toTexture();
  }
}

}

