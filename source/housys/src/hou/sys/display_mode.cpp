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
  : mode(vec2u(), format(), 0u)
{}



mode::mode(const vec2u& size, const format& f, uint refresh_rate) noexcept
  : m_size(size)
  , m_format(f)
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



const format& mode::get_format() const noexcept
{
  return m_format;
}



void mode::set_format(const format& f) noexcept
{
  m_format = f;
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
    && lhs.get_format() == rhs.get_format()
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
      if(lhs.get_format() == rhs.get_format())
      {
        return lhs.get_refresh_rate() < rhs.get_refresh_rate();
      }
      return lhs.get_format() < rhs.get_format();
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
            << ", format = " << vm.get_format()
            << ", refresh_rate = " << vm.get_refresh_rate() << "}";
}
}  // namespace display

}  // namespace hou
