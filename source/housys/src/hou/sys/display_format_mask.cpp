// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_format_mask.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/narrow_cast.hpp"

#include <iomanip>



namespace hou
{

display_format_mask::display_format_mask(display_format f)
  : m_bpp(0u)
  , m_red_bit_mask(0u)
  , m_green_bit_mask(0u)
  , m_blue_bit_mask(0u)
  , m_alpha_bit_mask(0u)
{
  HOU_CHECK_N(SDL_PixelFormatEnumToMasks(
                static_cast<std::underlying_type<display_format>::type>(f),
                reinterpret_cast<int*>(&m_bpp), &m_red_bit_mask,
                &m_green_bit_mask, &m_blue_bit_mask, &m_alpha_bit_mask)
      == SDL_TRUE,
    platform_error, SDL_GetError());
}



display_format display_format_mask::get_format() const
{
  return display_format(SDL_MasksToPixelFormatEnum(narrow_cast<int>(m_bpp),
    m_red_bit_mask, m_green_bit_mask, m_blue_bit_mask, m_alpha_bit_mask));
}



uint display_format_mask::get_bpp() const noexcept
{
  return m_bpp;
}



uint32_t display_format_mask::get_red_bit_mask() const noexcept
{
  return m_red_bit_mask;
}



uint32_t display_format_mask::get_green_bit_mask() const noexcept
{
  return m_green_bit_mask;
}



uint32_t display_format_mask::get_blue_bit_mask() const noexcept
{
  return m_blue_bit_mask;
}



uint32_t display_format_mask::get_alpha_bit_mask() const noexcept
{
  return m_alpha_bit_mask;
}



bool operator==(
  const display_format_mask& lhs, const display_format_mask& rhs) noexcept
{
  return lhs.get_bpp() == rhs.get_bpp()
    && lhs.get_red_bit_mask() == rhs.get_red_bit_mask()
    && lhs.get_green_bit_mask() == rhs.get_green_bit_mask()
    && lhs.get_blue_bit_mask() == rhs.get_blue_bit_mask()
    && lhs.get_alpha_bit_mask() == rhs.get_alpha_bit_mask();
}



bool operator!=(
  const display_format_mask& lhs, const display_format_mask& rhs) noexcept
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const display_format_mask& pf)
{
  ios_formatting_saver<std::ostream> saver(os);
  os << std::showbase << std::internal << std::setfill('0');
  // clang-format off
  return os << "{bpp = "
            << pf.get_bpp()
            << ", red_bit_mask = "
            << std::hex << std::setw(10) << pf.get_red_bit_mask()
            << ", green_bit_mask = "
            << std::hex << std::setw(10) << pf.get_green_bit_mask()
            << ", blue_bit_mask = "
            << std::hex << std::setw(10) << pf.get_blue_bit_mask()
            << ", alpha_bit_mask = "
            << std::hex << std::setw(10) << pf.get_alpha_bit_mask()
            << "}";
  // clang-format on
}

}  // namespace hou
