// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

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



VideoMode::VideoMode(const vec2u& resolution, uint bytesPerPixel)
  : mResolution(resolution)
  , mBytesPerPixel(bytesPerPixel)
{}



const vec2u& VideoMode::get_resolution() const
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
  return (lhs.get_resolution() == rhs.get_resolution())
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
    if(lhs.get_resolution().x() == rhs.get_resolution().x())
    {
      return lhs.get_resolution().y() < rhs.get_resolution().y();
    }
    else
    {
      return lhs.get_resolution().x() < rhs.get_resolution().x();
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
  return os << "{Resolution = " << transpose(vm.get_resolution())
    << ", BytesPerPixel = " << vm.getBytesPerPixel() << "}";
}

}

