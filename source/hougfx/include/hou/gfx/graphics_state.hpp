// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GRAPHICS_STATE_HPP
#define HOU_GFX_GRAPHICS_STATE_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gfx/blending_factor.hpp"
#include "hou/gfx/blending_equation.hpp"

#include "hou/gl/gl_vsync_mode.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

using vsync_mode = gl::vsync_mode;
using gl::get_vsync_mode;

bool is_multisampling_enabled();

void set_multisampling_enabled(bool value);

bool is_blending_enabled();

void set_blending_enabled(bool value);

blending_factor get_source_blending_factor();

void set_source_blending_factor(blending_factor f);

blending_factor get_destination_blending_factor();

void set_destination_blending_factor(blending_factor f);

blending_equation get_blending_equation();

void set_blending_equation(blending_equation eq);

color get_blending_color();

void set_blending_color(const color& c);

}  // namespace hou

#endif
