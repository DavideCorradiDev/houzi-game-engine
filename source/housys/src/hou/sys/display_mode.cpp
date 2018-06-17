// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_mode.hpp"

#include <algorithm>



namespace hou
{

namespace prv
{

display_mode convert(const SDL_DisplayMode& mode_in)
{
  display_mode mode_out;
  mode_out.set_size(
    vec2u(narrow_cast<uint>(mode_in.w), narrow_cast<uint>(mode_in.h)));
  mode_out.set_format(static_cast<display_format>(mode_in.format));
  mode_out.set_refresh_rate(narrow_cast<uint>(mode_in.refresh_rate));
  return mode_out;
}



SDL_DisplayMode convert(const display_mode& mode_in)
{
  SDL_DisplayMode mode_out;
  mode_out.w = narrow_cast<int>(mode_in.get_size().x());
  mode_out.h = narrow_cast<int>(mode_in.get_size().y());
  mode_out.format = static_cast<std::underlying_type<display_format>::type>(
    mode_in.get_format());
  mode_out.refresh_rate = narrow_cast<int>(mode_in.get_refresh_rate());
  mode_out.driverdata = nullptr;
  return mode_out;
}

} //  namespace prv



display_mode::display_mode()
  : display_mode(vec2u(), display_format::unknown, 0u)
{}



display_mode::display_mode(
  const vec2u& size, display_format f, uint refresh_rate) noexcept
  : m_size(size)
  , m_format(f)
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



display_format display_mode::get_format() const noexcept
{
  return m_format;
}



void display_mode::set_format(display_format f) noexcept
{
  m_format = f;
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
    && lhs.get_format() == rhs.get_format()
    && lhs.get_refresh_rate() == rhs.get_refresh_rate();
}



bool operator!=(const display_mode& lhs, const display_mode& rhs) noexcept
{
  return !(lhs == rhs);
}



bool operator<(const display_mode& lhs, const display_mode& rhs) noexcept
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
            << ", display_format = " << vm.get_format()
            << ", refresh_rate = " << vm.get_refresh_rate() << "}";
}

}  // namespace hou
