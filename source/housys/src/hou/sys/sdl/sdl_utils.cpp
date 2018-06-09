// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sdl/sdl_utils.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "hou/sys/display_mode.hpp"
#include "hou/sys/sys_exceptions.hpp"



namespace hou
{

namespace prv
{

display::pixel_format convert(Uint32 pf_in)
{
  int bpp = 0;
  Uint32 rmask = 0;
  Uint32 gmask = 0;
  Uint32 bmask = 0;
  Uint32 amask = 0;
  HOU_CHECK_N(
    SDL_PixelFormatEnumToMasks(pf_in, &bpp, &rmask, &gmask, &bmask, &amask)
      == SDL_TRUE,
    platform_error, SDL_GetError());
  return display::pixel_format(
    narrow_cast<uint>(bpp), rmask, gmask, bmask, amask);
}



Uint32 convert(const display::pixel_format& pf_in)
{
  return SDL_MasksToPixelFormatEnum(narrow_cast<int>(pf_in.get_bpp()),
    pf_in.get_red_bit_mask(), pf_in.get_green_bit_mask(),
    pf_in.get_blue_bit_mask(), pf_in.get_alpha_bit_mask());
}



display::mode convert(const SDL_DisplayMode& mode_in)
{
  display::mode mode_out;
  mode_out.set_size(
    vec2u(narrow_cast<uint>(mode_in.w), narrow_cast<uint>(mode_in.h)));
  mode_out.set_pixel_format(convert(mode_in.format));
  mode_out.set_refresh_rate(narrow_cast<uint>(mode_in.refresh_rate));
  return mode_out;
}



SDL_DisplayMode convert(const display::mode& mode_in)
{
  SDL_DisplayMode mode_out;
  mode_out.w = narrow_cast<int>(mode_in.get_size().x());
  mode_out.h = narrow_cast<int>(mode_in.get_size().y());
  mode_out.format = convert(mode_in.get_pixel_format());
  mode_out.refresh_rate = narrow_cast<int>(mode_in.get_refresh_rate());
  mode_out.driverdata = nullptr;
  return mode_out;
}

}  // namespace prv

}  // namespace hou
