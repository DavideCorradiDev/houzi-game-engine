// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_format_mask.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"

#include "hou/cor/narrow_cast.hpp"



namespace hou
{

namespace display
{

format_mask::format_mask(format f)
  : m_bpp(0u)
  , m_red_bit_mask(0u)
  , m_green_bit_mask(0u)
  , m_blue_bit_mask(0u)
  , m_alpha_bit_mask(0u)
{
  HOU_CHECK_N(SDL_PixelFormatEnumToMasks(
                static_cast<std::underlying_type<format>::type>(f),
                reinterpret_cast<int*>(&m_bpp), &m_red_bit_mask,
                &m_green_bit_mask, &m_blue_bit_mask, &m_alpha_bit_mask)
      == SDL_TRUE,
    platform_error, SDL_GetError());
}



format format_mask::get_format() const
{
  return format(SDL_MasksToPixelFormatEnum(narrow_cast<int>(m_bpp),
    m_red_bit_mask, m_green_bit_mask, m_blue_bit_mask, m_alpha_bit_mask));
}



uint format_mask::get_bpp() const noexcept
{
  return m_bpp;
}



void format_mask::set_bpp(uint bpp) noexcept
{
  m_bpp = bpp;
}



uint32_t format_mask::get_red_bit_mask() const noexcept
{
  return m_red_bit_mask;
}



void format_mask::set_red_bit_mask(uint32_t mask) noexcept
{
  m_red_bit_mask = mask;
}



uint32_t format_mask::get_green_bit_mask() const noexcept
{
  return m_green_bit_mask;
}



void format_mask::set_green_bit_mask(uint32_t mask) noexcept
{
  m_green_bit_mask = mask;
}



uint32_t format_mask::get_blue_bit_mask() const noexcept
{
  return m_blue_bit_mask;
}



void format_mask::set_blue_bit_mask(uint32_t mask) noexcept
{
  m_blue_bit_mask = mask;
}



uint32_t format_mask::get_alpha_bit_mask() const noexcept
{
  return m_alpha_bit_mask;
}



void format_mask::set_alpha_bit_mask(uint32_t mask) noexcept
{
  m_alpha_bit_mask = mask;
}



bool operator==(const format_mask& lhs, const format_mask& rhs) noexcept
{
  return lhs.get_bpp() == rhs.get_bpp()
    && lhs.get_red_bit_mask() == rhs.get_red_bit_mask()
    && lhs.get_green_bit_mask() == rhs.get_green_bit_mask()
    && lhs.get_blue_bit_mask() == rhs.get_blue_bit_mask()
    && lhs.get_alpha_bit_mask() == rhs.get_alpha_bit_mask();
}



std::ostream& operator<<(std::ostream& os, const format_mask& pf)
{
  return os << "{bpp = " << pf.get_bpp()
            << ", red_bit_mask = " << pf.get_red_bit_mask()
            << ", green_bit_mask = " << pf.get_green_bit_mask()
            << ", blue_bit_mask = " << pf.get_blue_bit_mask()
            << ", alpha_bit_mask = " << pf.get_alpha_bit_mask() << "}";
}

}  // namespace display

}  // namespace hou
