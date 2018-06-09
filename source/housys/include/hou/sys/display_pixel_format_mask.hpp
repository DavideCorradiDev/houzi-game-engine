// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_PIXEL_FORMAT_MASK_HPP
#define HOU_SYS_DISPLAY_PIXEL_FORMAT_MASK_HPP

#include "hou/sys/display_pixel_format.hpp"

#include "hou/sys/sys_config.hpp"

#include <ostream>



namespace hou
{

namespace display
{

class HOU_SYS_API pixel_format_mask
{
public:
  pixel_format_mask();
  pixel_format_mask(uint bpp, uint32_t red_bit_mask, uint32_t green_bit_mask,
    uint32_t blue_bit_mask, uint32_t alpha_bit_mask);

  uint get_bpp() const noexcept;
  void set_bpp(uint bpp) noexcept;

  uint32_t get_red_bit_mask() const noexcept;
  void set_red_bit_mask(uint32_t mask) noexcept;

  uint32_t get_green_bit_mask() const noexcept;
  void set_green_bit_mask(uint32_t mask) noexcept;

  uint32_t get_blue_bit_mask() const noexcept;
  void set_blue_bit_mask(uint32_t mask) noexcept;

  uint32_t get_alpha_bit_mask() const noexcept;
  void set_alpha_bit_mask(uint32_t mask) noexcept;

private:
  uint m_bpp;
  uint32_t m_red_bit_mask;
  uint32_t m_green_bit_mask;
  uint32_t m_blue_bit_mask;
  uint32_t m_alpha_bit_mask;
};

HOU_SYS_API bool operator==(
  const pixel_format_mask& lhs, const pixel_format_mask& rhs) noexcept;

HOU_SYS_API bool operator!=(
  const pixel_format_mask& lhs, const pixel_format_mask& rhs) noexcept;

/** Writes a pixel_format_mask object into a stream.
 *
 * \param os the stream.
 *
 * \param pf the pixel_format_mask object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const pixel_format_mask& pf);

}  // namespace display

}  // namespace hou

#endif
