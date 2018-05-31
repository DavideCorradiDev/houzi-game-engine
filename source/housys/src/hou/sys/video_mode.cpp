// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/video_mode.hpp"

#include <algorithm>



namespace hou
{

video_mode::video_mode(
  const vec2u& resolution, uint depth_byte_count, uint refresh_rate) noexcept
  : m_resolution(resolution)
  , m_depth_byte_count(depth_byte_count)
  , m_refresh_rate(refresh_rate)
{}



const vec2u& video_mode::get_resolution() const noexcept
{
  return m_resolution;
}



void video_mode::set_resolution(const vec2u& resolution) noexcept
{
  m_resolution = resolution;
}



uint video_mode::get_depth_byte_count() const noexcept
{
  return m_depth_byte_count;
}



void video_mode::set_depth_byte_count(uint depth_byte_count) noexcept
{
  m_depth_byte_count = depth_byte_count;
}



uint video_mode::get_refresh_rate() const noexcept
{
  return m_refresh_rate;
}



void video_mode::set_refresh_rate(uint refres_rate) noexcept
{
  m_refresh_rate = refres_rate;
}



bool operator==(const video_mode& lhs, const video_mode& rhs) noexcept
{
  return lhs.get_resolution() == rhs.get_resolution()
    && lhs.get_depth_byte_count() == rhs.get_depth_byte_count()
    && lhs.get_refresh_rate() == rhs.get_refresh_rate();
}



bool operator!=(const video_mode& lhs, const video_mode& rhs) noexcept
{
  return !(lhs == rhs);
}



bool operator<(const video_mode& lhs, const video_mode& rhs) noexcept
{
  if(lhs.get_refresh_rate() == rhs.get_refresh_rate())
  {
    if(lhs.get_depth_byte_count() == rhs.get_depth_byte_count())
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
      return lhs.get_depth_byte_count() < rhs.get_depth_byte_count();
    }
  }
  else
  {
    return lhs.get_refresh_rate() < rhs.get_refresh_rate();
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
            << ", depth_byte_count = " << vm.get_depth_byte_count()
            << ", refresh_rate = " << vm.get_refresh_rate()
            << "}";
}

}  // namespace hou
