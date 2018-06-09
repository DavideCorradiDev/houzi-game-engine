// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sdl/sdl_utils.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "hou/sys/display_format.hpp"
#include "hou/sys/display_mode.hpp"
#include "hou/sys/sys_exceptions.hpp"



namespace hou
{

namespace prv
{

display::mode convert(const SDL_DisplayMode& mode_in)
{
  display::mode mode_out;
  mode_out.set_size(
    vec2u(narrow_cast<uint>(mode_in.w), narrow_cast<uint>(mode_in.h)));
  mode_out.set_format(static_cast<display::format>(mode_in.format));
  mode_out.set_refresh_rate(narrow_cast<uint>(mode_in.refresh_rate));
  return mode_out;
}



SDL_DisplayMode convert(const display::mode& mode_in)
{
  SDL_DisplayMode mode_out;
  mode_out.w = narrow_cast<int>(mode_in.get_size().x());
  mode_out.h = narrow_cast<int>(mode_in.get_size().y());
  mode_out.format = static_cast<std::underlying_type<display::format>::type>(
    mode_in.get_format());
  mode_out.refresh_rate = narrow_cast<int>(mode_in.get_refresh_rate());
  mode_out.driverdata = nullptr;
  return mode_out;
}

}  // namespace prv

}  // namespace hou
