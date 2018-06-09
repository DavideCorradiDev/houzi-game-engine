// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SDL_SDL_UTILS_HPP
#define HOU_SYS_SDL_SDL_UTILS_HPP

#include "hou/sys/display_pixel_format.hpp"

#include "hou/sys/sys_config.hpp"

#include "SDL2/SDL_video.h"



namespace hou
{

namespace display
{

class mode;
class pixel_format_mask;

}  // namespace display

namespace prv
{

display::pixel_format_mask get_mask(Uint32 pf_in);

Uint32 get_format(const display::pixel_format_mask& pf_in);

display::mode convert(const SDL_DisplayMode& mode_in);

SDL_DisplayMode convert(const display::mode& mode_in);

}  // namespace prv

}  // namespace hou

#endif
