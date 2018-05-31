// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/video_mode.hpp"

#include <algorithm>



namespace hou
{

video_mode::video_mode(const vec2u& resolution, uint bytes_per_pixel) noexcept
  : m_resolution(resolution)
  , m_bytes_per_pixel(bytes_per_pixel)
{}



const vec2u& video_mode::get_resolution() const noexcept
{
  return m_resolution;
}



uint video_mode::get_bytes_per_pixel() const noexcept
{
  return m_bytes_per_pixel;
}



bool operator==(const video_mode& lhs, const video_mode& rhs) noexcept
{
  return (lhs.get_resolution() == rhs.get_resolution())
    && (lhs.get_bytes_per_pixel() == rhs.get_bytes_per_pixel());
}



bool operator!=(const video_mode& lhs, const video_mode& rhs) noexcept
{
  return !(lhs == rhs);
}



bool operator<(const video_mode& lhs, const video_mode& rhs) noexcept
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



bool operator>(const video_mode& lhs, const video_mode& rhs) noexcept
{
  return rhs < lhs;
}



bool operator<=(const video_mode& lhs, const video_mode& rhs) noexcept
{
  return !(rhs < lhs);
}



bool operator>=(const video_mode& lhs, const video_mode& rhs) noexcept
{
  return !(lhs < rhs);
}



std::ostream& operator<<(std::ostream& os, const video_mode& vm)
{
  return os << "{resolution = " << transpose(vm.get_resolution())
            << ", bytes_per_pixel = " << vm.get_bytes_per_pixel() << "}";
}

}  // namespace hou
