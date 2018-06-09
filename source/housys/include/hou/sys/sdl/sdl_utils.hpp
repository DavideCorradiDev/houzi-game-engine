// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SDL_SDL_UTILS_HPP
#define HOU_SYS_SDL_SDL_UTILS_HPP

#include "hou/sys/sys_config.hpp"

#include "SDL2/SDL_video.h"



namespace hou
{

namespace display
{

class mode;
class pixel_format;

}  // namespace display

namespace prv
{

display::pixel_format convert(Uint32 pf_in);

Uint32 convert(const display::pixel_format& pf_in);

display::mode convert(const SDL_DisplayMode& mode_in);

SDL_DisplayMode convert(const display::mode& mode_in);

}  // namespace prv

}  // namespace hou

#endif
