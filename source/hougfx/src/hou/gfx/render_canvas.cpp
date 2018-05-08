// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/render_canvas.hpp"



namespace hou
{

render_canvas::render_canvas(const vec2u& size, uint sample_count)
  : render_surface(size, sample_count)
{}

}  // namespace hou
