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

}  // namespace display

namespace prv
{

display::mode convert(const SDL_DisplayMode& mode_in);

SDL_DisplayMode convert(const display::mode& mode_in);

}  // namespace prv

class platform_error;

}  // namespace hou



#define HOU_SDL_CHECK(condition)                                               \
  HOU_CHECK_N(condition, ::hou::platform_error, SDL_GetError());

#endif
