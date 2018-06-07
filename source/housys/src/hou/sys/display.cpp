// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "SDL2/SDL_video.h"



namespace hou
{

namespace display
{

namespace
{

display_mode convert(const SDL_DisplayMode& mode_in);

display_mode convert(const SDL_DisplayMode& mode_in)
{
  display_mode mode_out;
  mode_out.set_size(
    vec2u(narrow_cast<uint>(mode_in.w), narrow_cast<uint>(mode_in.h)));
  mode_out.set_refresh_rate(narrow_cast<uint>(mode_in.refresh_rate));
  mode_out.set_depth_bit_count(SDL_BITSPERPIXEL(mode_in.format));
  return mode_out;
}

}



uint get_count()
{
  int count = SDL_GetNumVideoDisplays();
  HOU_CHECK_N(count >= 1, platform_error, SDL_GetError());
  return narrow_cast<uint>(count);
}



std::string get_name(uint display_idx)
{
  const char* name = SDL_GetDisplayName(narrow_cast<int>(display_idx));
  HOU_CHECK_N(name != nullptr, platform_error, SDL_GetError());
  return name;
}



recti get_bounds(uint display_idx)
{
  SDL_Rect rect;
  HOU_CHECK_N(SDL_GetDisplayBounds(display_idx, &rect) == 0, platform_error,
    SDL_GetError());
  return recti(rect.x, rect.y, rect.w, rect.h);
}



recti get_usable_bounds(uint display_idx)
{
  SDL_Rect rect;
  HOU_CHECK_N(SDL_GetDisplayUsableBounds(display_idx, &rect) == 0,
    platform_error, SDL_GetError());
  return recti(rect.x, rect.y, rect.w, rect.h);
}



display_mode get_current_mode(uint display_idx)
{
  SDL_DisplayMode mode;
  HOU_CHECK_N(SDL_GetCurrentDisplayMode(display_idx, &mode) == 0,
    platform_error, SDL_GetError());
  return convert(mode);
}



std::set<display_mode> get_supported_modes(uint display_idx)
{
  int count = SDL_GetNumDisplayModes(display_idx);
  HOU_CHECK_N(count >= 1, platform_error, SDL_GetError());

  std::set<display_mode> modes;
  for(int i = 0; i < count; ++i)
  {
    SDL_DisplayMode mode;
    HOU_CHECK_N(SDL_GetDisplayMode(display_idx, i, &mode) == 0, platform_error,
        SDL_GetError());
    modes.insert(convert(mode));
  }
  return modes;
}



std::string get_current_video_driver()
{
  const char* driver = SDL_GetCurrentVideoDriver();
  return driver == nullptr ? "" : driver;
}



std::set<std::string> get_available_video_drivers()
{
  std::set<std::string> video_drivers;
  int count = SDL_GetNumVideoDrivers();
  HOU_CHECK_N(count >= 1, platform_error, SDL_GetError());
  for(int i = 0; i < count; ++i)
  {
    const char* driver = SDL_GetVideoDriver(i);
    video_drivers.insert(driver == nullptr ? "" : driver);
  }
  return video_drivers;
}

}  // namespace display

}  // namespace hou
