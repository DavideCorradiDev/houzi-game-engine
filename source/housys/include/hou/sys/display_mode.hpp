// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_MODE_HPP
#define HOU_SYS_DISPLAY_MODE_HPP

#include "hou/sys/display_pixel_format.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/mth/matrix.hpp"

#include <ostream>
#include <vector>



namespace hou
{

namespace display
{

/** Class representing a display mode.
 */
class HOU_SYS_API mode
{
public:
  /** Creates mode object with all fields initialized to zero.
   */
  mode();

  /** Creates a mode object.
   *
   * \param size the size.
   *
   * \param format the pixel format.
   *
   * \param refres_rate the refresh_rate.
   */
  mode(
    const vec2u& size, const pixel_format& format, uint refresh_rate) noexcept;

  /** Retrieves the size.
   *
   * \return the size.
   */
  const vec2u& get_size() const noexcept;

  /** Sets the size.
   *
   * \param size the size.
   */
  void set_size(const vec2u& size) noexcept;
  const pixel_format& get_pixel_format() const noexcept;
  void set_pixel_format(const pixel_format& format) noexcept;

  /** Retrieves the refresh rate in Hz.
   *
   * \return the refresh rate in Hz.
   */
  uint get_refresh_rate() const noexcept;

  /** Sets the refresh rate in Hz.
   *
   * \param refresh_rate the refresh rate in Hz.
   */
  void set_refresh_rate(uint refresh_rate) noexcept;

private:
  vec2u m_size;
  pixel_format m_pixel_format;
  uint m_refresh_rate;
};

/** Checks if two mode objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator==(const mode& lhs, const mode& rhs) noexcept;

/** Checks if two mode objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator!=(const mode& lhs, const mode& rhs) noexcept;

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
HOU_SYS_API bool operator<(const mode& lhs, const mode& rhs) noexcept;

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
HOU_SYS_API bool operator>(const mode& lhs, const mode& rhs) noexcept;

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
HOU_SYS_API bool operator<=(const mode& lhs, const mode& rhs) noexcept;

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
HOU_SYS_API bool operator>=(const mode& lhs, const mode& rhs) noexcept;

/** Writes a mode object into a stream.
 *
 * Comparisons happen in the following order: bits per pixel, x size,
 * y size.
 *
 * \param os the stream.
 *
 * \param vm the mode object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const mode& vm);

}  // namespace display

}  // namespace hou

#endif
