// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/video_mode.hpp"


#include "hou/cor/exception.hpp"
namespace hou
{

video_mode video_mode::get_desktop_mode() noexcept
{
  HOU_UNREACHABLE();
  return video_mode(vec2u(), 0u);
}



std::vector<video_mode> video_mode::create_fullscreen_modes_vector()
{
  HOU_UNREACHABLE();
  return std::vector<video_mode>();
}

}  // namespace hou
