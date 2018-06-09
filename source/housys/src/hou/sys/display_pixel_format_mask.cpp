// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_pixel_format_mask.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"



namespace hou
{

namespace display
{

pixel_format_mask::pixel_format_mask()
  : m_bpp(0u)
  , m_red_bit_mask(0x00000000u)
  , m_green_bit_mask(0x00000000u)
  , m_blue_bit_mask(0x00000000u)
  , m_alpha_bit_mask(0x00000000u)
{}



pixel_format_mask::pixel_format_mask(uint bpp, uint32_t red_bit_mask,
  uint32_t green_bit_mask, uint32_t blue_bit_mask, uint32_t alpha_bit_mask)
  : m_bpp(bpp)
  , m_red_bit_mask(red_bit_mask)
  , m_green_bit_mask(green_bit_mask)
  , m_blue_bit_mask(blue_bit_mask)
  , m_alpha_bit_mask(alpha_bit_mask)
{}



uint pixel_format_mask::get_bpp() const noexcept
{
  return m_bpp;
}



void pixel_format_mask::set_bpp(uint bpp) noexcept
{
  m_bpp = bpp;
}



uint32_t pixel_format_mask::get_red_bit_mask() const noexcept
{
  return m_red_bit_mask;
}



void pixel_format_mask::set_red_bit_mask(uint32_t mask) noexcept
{
  m_red_bit_mask = mask;
}



uint32_t pixel_format_mask::get_green_bit_mask() const noexcept
{
  return m_green_bit_mask;
}



void pixel_format_mask::set_green_bit_mask(uint32_t mask) noexcept
{
  m_green_bit_mask = mask;
}



uint32_t pixel_format_mask::get_blue_bit_mask() const noexcept
{
  return m_blue_bit_mask;
}



void pixel_format_mask::set_blue_bit_mask(uint32_t mask) noexcept
{
  m_blue_bit_mask = mask;
}



uint32_t pixel_format_mask::get_alpha_bit_mask() const noexcept
{
  return m_alpha_bit_mask;
}



void pixel_format_mask::set_alpha_bit_mask(uint32_t mask) noexcept
{
  m_alpha_bit_mask = mask;
}



bool operator==(const pixel_format_mask& lhs, const pixel_format_mask& rhs) noexcept
{
  return lhs.get_bpp() == rhs.get_bpp()
    && lhs.get_red_bit_mask() == rhs.get_red_bit_mask()
    && lhs.get_green_bit_mask() == rhs.get_green_bit_mask()
    && lhs.get_blue_bit_mask() == rhs.get_blue_bit_mask()
    && lhs.get_alpha_bit_mask() == rhs.get_alpha_bit_mask();
}



std::ostream& operator<<(std::ostream& os, const pixel_format_mask& pf)
{
  return os << "{bpp = " << pf.get_bpp()
            << ", red_bit_mask = " << pf.get_red_bit_mask()
            << ", green_bit_mask = " << pf.get_green_bit_mask()
            << ", blue_bit_mask = " << pf.get_blue_bit_mask()
            << ", alpha_bit_mask = " << pf.get_alpha_bit_mask() << "}";
}

}  // namespace display

}  // namespace hou
