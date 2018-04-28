// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/RenderCanvas.hpp"



namespace hou
{

RenderCanvas::RenderCanvas(const Vec2u& size, uint sampleCount)
  : RenderSurface(size, sampleCount)
{}



RenderCanvas::RenderCanvas(RenderCanvas&& other)
  : RenderSurface(std::move(other))
{}



RenderCanvas::~RenderCanvas()
{}

}

