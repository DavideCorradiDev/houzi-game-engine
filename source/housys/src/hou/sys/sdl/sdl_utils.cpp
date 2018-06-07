// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sdl/sdl_utils.hpp"

#include "hou/sys/display_mode.hpp"



namespace hou
{

namespace prv
{

display_mode convert(const SDL_DisplayMode& mode_in)
{
  display_mode mode_out;
  mode_out.set_size(
    vec2u(narrow_cast<uint>(mode_in.w), narrow_cast<uint>(mode_in.h)));
  mode_out.set_refresh_rate(narrow_cast<uint>(mode_in.refresh_rate));
  mode_out.set_depth_bit_count(SDL_BITSPERPIXEL(mode_in.format));
  return mode_out;
}



SDL_DisplayMode convert(const display_mode& mode_in)
{
  SDL_DisplayMode mode_out;
  mode_out.w = narrow_cast<int>(mode_in.get_size().x());
  mode_out.h = narrow_cast<int>(mode_in.get_size().y());
  mode_out.refresh_rate = narrow_cast<int>(mode_in.get_refresh_rate());
  mode_out.driverdata = nullptr;
  return mode_out;
}

}  // namespace sdl

}  // namespace hou
