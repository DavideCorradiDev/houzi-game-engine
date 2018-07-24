// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_FORMAT_MASK_HPP
#define HOU_SYS_DISPLAY_FORMAT_MASK_HPP

#include "hou/sys/display_format.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/std_iostream.hpp"



namespace hou
{

/**
 * Represents a display format mask.
 *
 * The mask stores the size of a pixel in bits, and masks for the red, blue,
 * green, and alpha channels.
 */
class HOU_SYS_API display_format_mask
{
public:
  /**
   * Creates the mask associated to the given display_format.
   *
   * \param f the display_format.
   */
  explicit display_format_mask(display_format f);

  /**
   * Gets the display_format associated to the mask.
   *
   * \return the display_format associated to the mask.
   */
  display_format get_format() const;

  /**
   * Gets the number of bits per pixel.
   *
   * \return the number of bits per pixel.
   */
  uint get_bpp() const noexcept;

  /**
   * Gets the red bits mask.
   *
   * \return the red bits mask.
   */
  uint32_t get_red_bit_mask() const noexcept;

  /**
   * Gets the green bits mask.
   *
   * \return the green bits mask.
   */
  uint32_t get_green_bit_mask() const noexcept;

  /**
   * Gets the blue bits mask.
   *
   * \return the blue bits mask.
   */
  uint32_t get_blue_bit_mask() const noexcept;

  /**
   * Gets the alpha bits mask.
   *
   * \return the alpha bits mask.
   */
  uint32_t get_alpha_bit_mask() const noexcept;

private:
  uint m_bpp;
  uint32_t m_red_bit_mask;
  uint32_t m_green_bit_mask;
  uint32_t m_blue_bit_mask;
  uint32_t m_alpha_bit_mask;
};

/**
 * Checks if two display_format_mask objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator==(
  const display_format_mask& lhs, const display_format_mask& rhs) noexcept;

/**
 * Checks if two display_format_mask objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator!=(
  const display_format_mask& lhs, const display_format_mask& rhs) noexcept;

/** Writes a display_format_mask object into a stream.
 *
 * \param os the stream.
 *
 * \param fm the display_format_mask object.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, const display_format_mask& fm);

}  // namespace hou

#endif
