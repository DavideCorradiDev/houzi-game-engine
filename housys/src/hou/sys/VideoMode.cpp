// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/VideoMode.hpp"

#include <algorithm>



namespace hou
{

std::vector<VideoMode> VideoMode::getFullscreenModes()
{
  std::vector<VideoMode> modes = createFullscreenModesVector();
  std::sort(modes.begin(), modes.end(), std::greater<VideoMode>());
  return modes;
}



VideoMode::VideoMode(const Vec2u& resolution, uint bytesPerPixel)
  : mResolution(resolution)
  , mBytesPerPixel(bytesPerPixel)
{}



const Vec2u& VideoMode::getResolution() const
{
  return mResolution;
}



uint VideoMode::getBytesPerPixel() const
{
  return mBytesPerPixel;
}



bool VideoMode::isFullscreenMode() const
{
  static const std::vector<VideoMode> modes = getFullscreenModes();
  return std::find(modes.begin(), modes.end(), *this) != modes.end();
}



bool operator==(const VideoMode& lhs, const VideoMode& rhs)
{
  return (lhs.getResolution() == rhs.getResolution())
    && (lhs.getBytesPerPixel() == rhs.getBytesPerPixel());
}



bool operator!=(const VideoMode& lhs, const VideoMode& rhs)
{
  return !(lhs == rhs);
}



bool operator<(const VideoMode& lhs, const VideoMode& rhs)
{
  if(lhs.getBytesPerPixel() == rhs.getBytesPerPixel())
  {
    if(lhs.getResolution().x() == rhs.getResolution().x())
    {
      return lhs.getResolution().y() < rhs.getResolution().y();
    }
    else
    {
      return lhs.getResolution().x() < rhs.getResolution().x();
    }
  }
  else
  {
    return lhs.getBytesPerPixel() < rhs.getBytesPerPixel();
  }
}



bool operator>(const VideoMode& lhs, const VideoMode& rhs)
{
  return rhs < lhs;
}



bool operator<=(const VideoMode& lhs, const VideoMode& rhs)
{
  return !(rhs < lhs);
}



bool operator>=(const VideoMode& lhs, const VideoMode& rhs)
{
  return !(lhs < rhs);
}



std::ostream& operator<<(std::ostream& os, const VideoMode& vm)
{
  return os << "{Resolution = " << transpose(vm.getResolution())
    << ", BytesPerPixel = " << vm.getBytesPerPixel() << "}";
}

}

