// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_mode.hpp"

#include <algorithm>



namespace hou
{

display_mode::display_mode()
  : display_mode(vec2u(), 0u, 0u)
{}



display_mode::display_mode(
  const vec2u& size, uint depth_bit_count, uint refresh_rate) noexcept
  : m_size(size)
  , m_depth_bit_count(depth_bit_count)
  , m_refresh_rate(refresh_rate)
{}



const vec2u& display_mode::get_size() const noexcept
{
  return m_size;
}



void display_mode::set_size(const vec2u& size) noexcept
{
  m_size = size;
}



uint display_mode::get_depth_bit_count() const noexcept
{
  return m_depth_bit_count;
}



void display_mode::set_depth_bit_count(uint depth_bit_count) noexcept
{
  m_depth_bit_count = depth_bit_count;
}



uint display_mode::get_refresh_rate() const noexcept
{
  return m_refresh_rate;
}



void display_mode::set_refresh_rate(uint refres_rate) noexcept
{
  m_refresh_rate = refres_rate;
}



bool operator==(const display_mode& lhs, const display_mode& rhs) noexcept
{
  return lhs.get_size() == rhs.get_size()
    && lhs.get_depth_bit_count() == rhs.get_depth_bit_count()
    && lhs.get_refresh_rate() == rhs.get_refresh_rate();
}



bool operator!=(const display_mode& lhs, const display_mode& rhs) noexcept
{
  return !(lhs == rhs);
}



bool operator<(const display_mode& lhs, const display_mode& rhs) noexcept
{
  if(lhs.get_refresh_rate() == rhs.get_refresh_rate())
  {
    if(lhs.get_depth_bit_count() == rhs.get_depth_bit_count())
    {
      if(lhs.get_size().x() == rhs.get_size().x())
      {
        return lhs.get_size().y() < rhs.get_size().y();
      }
      else
      {
        return lhs.get_size().x() < rhs.get_size().x();
      }
    }
    else
    {
      return lhs.get_depth_bit_count() < rhs.get_depth_bit_count();
    }
  }
  else
  {
    return lhs.get_refresh_rate() < rhs.get_refresh_rate();
  }
}



bool operator>(const display_mode& lhs, const display_mode& rhs) noexcept
{
  return rhs < lhs;
}



bool operator<=(const display_mode& lhs, const display_mode& rhs) noexcept
{
  return !(rhs < lhs);
}



bool operator>=(const display_mode& lhs, const display_mode& rhs) noexcept
{
  return !(lhs < rhs);
}



std::ostream& operator<<(std::ostream& os, const display_mode& vm)
{
  return os << "{size = " << transpose(vm.get_size())
            << ", depth_bit_count = " << vm.get_depth_bit_count()
            << ", refresh_rate = " << vm.get_refresh_rate() << "}";
}

}  // namespace hou
