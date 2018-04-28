// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/video_mode.hpp"

#include <algorithm>



namespace hou
{

std::vector<video_mode> video_mode::getFullscreenModes()
{
  std::vector<video_mode> modes = createFullscreenModesVector();
  std::sort(modes.begin(), modes.end(), std::greater<video_mode>());
  return modes;
}



video_mode::video_mode(const vec2u& resolution, uint bytesPerPixel)
  : m_resolution(resolution)
  , m_bytes_per_pixel(bytesPerPixel)
{}



const vec2u& video_mode::get_resolution() const
{
  return m_resolution;
}



uint video_mode::get_bytes_per_pixel() const
{
  return m_bytes_per_pixel;
}



bool video_mode::is_fullscreen_mode() const
{
  static const std::vector<video_mode> modes = getFullscreenModes();
  return std::find(modes.begin(), modes.end(), *this) != modes.end();
}



bool operator==(const video_mode& lhs, const video_mode& rhs)
{
  return (lhs.get_resolution() == rhs.get_resolution())
    && (lhs.get_bytes_per_pixel() == rhs.get_bytes_per_pixel());
}



bool operator!=(const video_mode& lhs, const video_mode& rhs)
{
  return !(lhs == rhs);
}



bool operator<(const video_mode& lhs, const video_mode& rhs)
{
  if(lhs.get_bytes_per_pixel() == rhs.get_bytes_per_pixel())
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
    return lhs.get_bytes_per_pixel() < rhs.get_bytes_per_pixel();
  }
}



bool operator>(const video_mode& lhs, const video_mode& rhs)
{
  return rhs < lhs;
}



bool operator<=(const video_mode& lhs, const video_mode& rhs)
{
  return !(rhs < lhs);
}



bool operator>=(const video_mode& lhs, const video_mode& rhs)
{
  return !(lhs < rhs);
}



std::ostream& operator<<(std::ostream& os, const video_mode& vm)
{
  return os << "{Resolution = " << transpose(vm.get_resolution())
    << ", BytesPerPixel = " << vm.get_bytes_per_pixel() << "}";
}

}

