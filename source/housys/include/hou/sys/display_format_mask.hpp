// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_FORMAT_MASK_HPP
#define HOU_SYS_DISPLAY_FORMAT_MASK_HPP

#include "hou/sys/display_format.hpp"

#include "hou/sys/sys_config.hpp"

#include <ostream>



namespace hou
{

namespace display
{

class HOU_SYS_API format_mask
{
public:
  format_mask(format f);

  format get_format() const;

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
  const format_mask& lhs, const format_mask& rhs) noexcept;

HOU_SYS_API bool operator!=(
  const format_mask& lhs, const format_mask& rhs) noexcept;

/** Writes a format_mask object into a stream.
 *
 * \param os the stream.
 *
 * \param fm the format_mask object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const format_mask& fm);

}  // namespace display

}  // namespace hou

#endif
