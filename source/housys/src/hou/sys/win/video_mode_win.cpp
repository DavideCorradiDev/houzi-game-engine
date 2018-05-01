// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/video_mode.hpp"

#include "hou/sys/win/win.hpp"

#include <algorithm>



namespace hou
{

namespace
{
  constexpr uint bitsPerByte = 8u;
}

// Note:
// EnumDisplaySettings fails (returns 0) if the second argument is greater than
// the index of the display's device graphics mode.

video_mode video_mode::get_desktop_mode()
{
  DEVMODE winMode;
  winMode.dmSize = sizeof(winMode);
  // No need to check for error here.
  EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &winMode);
  return video_mode(vec2u(winMode.dmPelsWidth, winMode.dmPelsHeight)
    , winMode.dmBitsPerPel / bitsPerByte);
}



std::vector<video_mode> video_mode::create_fullscreen_modes_vector()
{
  std::vector<video_mode> modes;

  DEVMODE winMode;
  winMode.dmSize = sizeof(winMode);
  // End loop when all display settings have been read (EnumDisplaySettings
  // returns zero when the second argument is too high).
  for(int i = 0; EnumDisplaySettings(nullptr, i, &winMode) != 0; ++i)
  {
    video_mode mode(vec2u(winMode.dmPelsWidth, winMode.dmPelsHeight)
      , winMode.dmBitsPerPel / bitsPerByte);
    if(std::find(modes.begin(), modes.end(), mode) == modes.end())
    {
      modes.push_back(mode);
    }
  }

  return modes;
}

}

