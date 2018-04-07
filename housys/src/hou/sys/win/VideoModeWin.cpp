// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/VideoMode.hpp"

#include "hou/sys/win/Win.hpp"

#include <algorithm>



namespace hou
{

// Note:
// EnumDisplaySettings fails (returns 0) if the second argument is greater than
// the index of the display's device graphics mode.
//
//

VideoMode VideoMode::getDesktopMode()
{
  DEVMODE winMode;
  winMode.dmSize = sizeof(winMode);
  // No need to check for error here.
  EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &winMode);
  return VideoMode(Vec2u(winMode.dmPelsWidth, winMode.dmPelsHeight)
    , winMode.dmBitsPerPel);
}



std::vector<VideoMode> VideoMode::createFullscreenModesVector()
{
  std::vector<VideoMode> modes;

  DEVMODE winMode;
  winMode.dmSize = sizeof(winMode);
  // End loop when all display settings have been read (EnumDisplaySettings
  // returns zero when the second argument is too high).
  for(int i = 0; EnumDisplaySettings(nullptr, i, &winMode) != 0; ++i)
  {
    VideoMode mode(Vec2u(winMode.dmPelsWidth, winMode.dmPelsHeight)
      , winMode.dmBitsPerPel);
    if(std::find(modes.begin(), modes.end(), mode) == modes.end())
    {
      modes.push_back(mode);
    }
  }

  return modes;
}

}

