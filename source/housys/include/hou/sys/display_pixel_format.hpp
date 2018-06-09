// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_config.hpp"

#include <ostream>



namespace hou
{

namespace display
{

class HOU_SYS_API pixel_format
{
public:
  static const pixel_format& rgb();
  static const pixel_format& rgba();

public:
  pixel_format();
  pixel_format(uint bpp, uint32_t red_bit_mask, uint32_t green_bit_mask,
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

/** Checks if two pixel_format objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator==(
  const pixel_format& lhs, const pixel_format& rhs) noexcept;

/** Checks if two pixel_format objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator!=(
  const pixel_format& lhs, const pixel_format& rhs) noexcept;

/** Checks if lhs is lower than rhs.
 *
 * Comparisons happen in the following order: bits per pixel, x size,
 * y size.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator<(
  const pixel_format& lhs, const pixel_format& rhs) noexcept;

/** Checks if lhs is greater than rhs.
 *
 * Comparisons happen in the following order: bits per pixel, x size,
 * y size.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator>(
  const pixel_format& lhs, const pixel_format& rhs) noexcept;

/** Checks if lhs is lower or equal to rhs.
 *
 * Comparisons happen in the following order: bits per pixel, x size,
 * y size.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator<=(
  const pixel_format& lhs, const pixel_format& rhs) noexcept;

/** Checks if lhs is greater or equal to rhs.
 *
 * Comparisons happen in the following order: bits per pixel, x size,
 * y size.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator>=(
  const pixel_format& lhs, const pixel_format& rhs) noexcept;

/** Writes a pixel_format object into a stream.
 *
 * Comparisons happen in the following order: bits per pixel, x size,
 * y size.
 *
 * \param os the stream.
 *
 * \param pf the pixel_format object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const pixel_format& pf);

}  // namespace display

}  // namespace hou
