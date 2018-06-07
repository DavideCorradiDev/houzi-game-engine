// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SDL_SDL_UTILS_HPP
#define HOU_SYS_SDL_SDL_UTILS_HPP

#include "hou/sys/sys_config.hpp"

#include "SDL2/SDL_video.h"



namespace hou
{

class display_mode;

namespace prv
{

display_mode convert(const SDL_DisplayMode& mode_in);

SDL_DisplayMode convert(const display_mode& mode_in);

}  // namespace prv

}  // namespace hou

#endif
