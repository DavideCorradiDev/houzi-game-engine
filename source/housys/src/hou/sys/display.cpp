// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "SDL2/SDL_video.h"



namespace hou
{

namespace display
{

uint get_count()
{
  int count = SDL_GetNumVideoDisplays();
  HOU_SDL_CHECK(count >= 1);
  return narrow_cast<uint>(count);
}



std::string get_name(uint display_idx)
{
  const char* name = SDL_GetDisplayName(narrow_cast<int>(display_idx));
  HOU_SDL_CHECK(name != nullptr);
  return name;
}



recti get_bounds(uint display_idx)
{
  SDL_Rect rect;
  HOU_SDL_CHECK(SDL_GetDisplayBounds(display_idx, &rect) == 0);
  return recti(rect.x, rect.y, rect.w, rect.h);
}



recti get_usable_bounds(uint display_idx)
{
  SDL_Rect rect;
  HOU_SDL_CHECK(SDL_GetDisplayUsableBounds(display_idx, &rect) == 0);
  return recti(rect.x, rect.y, rect.w, rect.h);
}



display_mode get_current_mode(uint display_idx)
{
  SDL_DisplayMode dm;
  HOU_SDL_CHECK(SDL_GetCurrentDisplayMode(display_idx, &dm) == 0);
  return prv::convert(dm);
}



std::set<display_mode> get_supported_modes(uint display_idx)
{
  int count = SDL_GetNumDisplayModes(display_idx);
  HOU_SDL_CHECK(count >= 1);

  std::set<display_mode> modes;
  for(int i = 0; i < count; ++i)
  {
    SDL_DisplayMode dm;
    HOU_SDL_CHECK(SDL_GetDisplayMode(display_idx, i, &dm) == 0);
    modes.insert(prv::convert(dm));
  }
  return modes;
}



display_mode get_closest_supported_mode(
  uint display_idx, const display_mode& dm)
{
  SDL_DisplayMode sdl_mode_in = prv::convert(dm);
  SDL_DisplayMode mode_out;
  HOU_SDL_CHECK(
    SDL_GetClosestDisplayMode(display_idx, &sdl_mode_in, &mode_out) != nullptr);
  return prv::convert(mode_out);
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
  HOU_SDL_CHECK(count >= 1);
  for(int i = 0; i < count; ++i)
  {
    const char* driver = SDL_GetVideoDriver(i);
    video_drivers.insert(driver == nullptr ? "" : driver);
  }
  return video_drivers;
}

}  // namespace display

}  // namespace hou
