// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_pixel_format.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"



namespace hou
{

namespace display
{

const pixel_format& pixel_format::rgb()
{
  static const pixel_format pf(prv::convert(SDL_PIXELFORMAT_RGB888));
  return pf;
}



const pixel_format& pixel_format::rgba()
{
  static const pixel_format pf(prv::convert(SDL_PIXELFORMAT_RGBA8888));
  return pf;
}



pixel_format::pixel_format()
  : m_bpp(0u)
  , m_red_bit_mask(0x00000000u)
  , m_green_bit_mask(0x00000000u)
  , m_blue_bit_mask(0x00000000u)
  , m_alpha_bit_mask(0x00000000u)
{}



pixel_format::pixel_format(uint bpp, uint32_t red_bit_mask,
  uint32_t green_bit_mask, uint32_t blue_bit_mask, uint32_t alpha_bit_mask)
  : m_bpp(bpp)
  , m_red_bit_mask(red_bit_mask)
  , m_green_bit_mask(green_bit_mask)
  , m_blue_bit_mask(blue_bit_mask)
  , m_alpha_bit_mask(alpha_bit_mask)
{}



uint pixel_format::get_bpp() const noexcept
{
  return m_bpp;
}



void pixel_format::set_bpp(uint bpp) noexcept
{
  m_bpp = bpp;
}



uint32_t pixel_format::get_red_bit_mask() const noexcept
{
  return m_red_bit_mask;
}



void pixel_format::set_red_bit_mask(uint32_t mask) noexcept
{
  m_red_bit_mask = mask;
}



uint32_t pixel_format::get_green_bit_mask() const noexcept
{
  return m_green_bit_mask;
}



void pixel_format::set_green_bit_mask(uint32_t mask) noexcept
{
  m_green_bit_mask = mask;
}



uint32_t pixel_format::get_blue_bit_mask() const noexcept
{
  return m_blue_bit_mask;
}



void pixel_format::set_blue_bit_mask(uint32_t mask) noexcept
{
  m_blue_bit_mask = mask;
}



uint32_t pixel_format::get_alpha_bit_mask() const noexcept
{
  return m_alpha_bit_mask;
}



void pixel_format::set_alpha_bit_mask(uint32_t mask) noexcept
{
  m_alpha_bit_mask = mask;
}



bool operator==(const pixel_format& lhs, const pixel_format& rhs) noexcept
{
  return lhs.get_bpp() == rhs.get_bpp()
    && lhs.get_red_bit_mask() == rhs.get_red_bit_mask()
    && lhs.get_green_bit_mask() == rhs.get_green_bit_mask()
    && lhs.get_blue_bit_mask() == rhs.get_blue_bit_mask()
    && lhs.get_alpha_bit_mask() == rhs.get_alpha_bit_mask();
}



bool operator!=(const pixel_format& lhs, const pixel_format& rhs) noexcept
{
  return !(lhs == rhs);
}



bool operator<(const pixel_format& lhs, const pixel_format& rhs) noexcept
{
  if(lhs.get_bpp() == rhs.get_bpp())
  {
    if(lhs.get_red_bit_mask() == rhs.get_red_bit_mask())
    {
      if(lhs.get_green_bit_mask() == rhs.get_green_bit_mask())
      {
        if(lhs.get_blue_bit_mask() == rhs.get_blue_bit_mask())
        {
          return lhs.get_alpha_bit_mask() < rhs.get_alpha_bit_mask();
        }
        return lhs.get_blue_bit_mask() < rhs.get_blue_bit_mask();
      }
      return lhs.get_green_bit_mask() < rhs.get_green_bit_mask();
    }
    return lhs.get_red_bit_mask() < rhs.get_red_bit_mask();
  }
  return lhs.get_bpp() < rhs.get_bpp();
}



bool operator>(const pixel_format& lhs, const pixel_format& rhs) noexcept
{
  return rhs < lhs;
}



bool operator<=(const pixel_format& lhs, const pixel_format& rhs) noexcept
{
  return !(rhs < lhs);
}



bool operator>=(const pixel_format& lhs, const pixel_format& rhs) noexcept
{
  return !(lhs < rhs);
}



std::ostream& operator<<(std::ostream& os, const pixel_format& pf)
{
  return os << "{bpp = " << pf.get_bpp()
            << ", red_bit_mask = " << pf.get_red_bit_mask()
            << ", green_bit_mask = " << pf.get_green_bit_mask()
            << ", blue_bit_mask = " << pf.get_blue_bit_mask()
            << ", alpha_bit_mask = " << pf.get_alpha_bit_mask() << "}";
}

}  // namespace display

}  // namespace hou
