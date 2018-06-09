// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_mode.hpp"

#include <algorithm>



namespace hou
{

namespace display
{

mode::mode()
  : mode(vec2u(), pixel_format(), 0u)
{}



mode::mode(
  const vec2u& size, const pixel_format& format, uint refresh_rate) noexcept
  : m_size(size)
  , m_pixel_format(format)
  , m_refresh_rate(refresh_rate)
{}



const vec2u& mode::get_size() const noexcept
{
  return m_size;
}



void mode::set_size(const vec2u& size) noexcept
{
  m_size = size;
}



const pixel_format& mode::get_pixel_format() const noexcept
{
  return m_pixel_format;
}



void mode::set_pixel_format(const pixel_format& format) noexcept
{
  m_pixel_format = format;
}



uint mode::get_refresh_rate() const noexcept
{
  return m_refresh_rate;
}



void mode::set_refresh_rate(uint refres_rate) noexcept
{
  m_refresh_rate = refres_rate;
}



bool operator==(const mode& lhs, const mode& rhs) noexcept
{
  return lhs.get_size() == rhs.get_size()
    && lhs.get_pixel_format() == rhs.get_pixel_format()
    && lhs.get_refresh_rate() == rhs.get_refresh_rate();
}



bool operator!=(const mode& lhs, const mode& rhs) noexcept
{
  return !(lhs == rhs);
}



bool operator<(const mode& lhs, const mode& rhs) noexcept
{
  if(lhs.get_size().x() == rhs.get_size().x())
  {
    if(lhs.get_size().y() == rhs.get_size().y())
    {
      if(lhs.get_pixel_format() == rhs.get_pixel_format())
      {
        return lhs.get_refresh_rate() < rhs.get_refresh_rate();
      }
      return lhs.get_pixel_format() < rhs.get_pixel_format();
    }
    return lhs.get_size().y() < rhs.get_size().y();
  }
  return lhs.get_size().x() < rhs.get_size().x();
}



bool operator>(const mode& lhs, const mode& rhs) noexcept
{
  return rhs < lhs;
}



bool operator<=(const mode& lhs, const mode& rhs) noexcept
{
  return !(rhs < lhs);
}



bool operator>=(const mode& lhs, const mode& rhs) noexcept
{
  return !(lhs < rhs);
}



std::ostream& operator<<(std::ostream& os, const mode& vm)
{
  return os << "{size = " << transpose(vm.get_size())
            << ", pixel_format = " << vm.get_pixel_format()
            << ", refresh_rate = " << vm.get_refresh_rate() << "}";
}
}  // namespace display

}  // namespace hou
