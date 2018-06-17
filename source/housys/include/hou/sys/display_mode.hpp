// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_MODE_HPP
#define HOU_SYS_DISPLAY_MODE_HPP

#include "hou/sys/display_format.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/mth/matrix.hpp"

#include <ostream>
#include <vector>



namespace hou
{

/** Class representing a display mode.
 */
class HOU_SYS_API display_mode
{
public:
  /** Creates display_mode object with all fields initialized to zero.
   */
  display_mode();

  /** Creates a display_mode object.
   *
   * \param size the size.
   *
   * \param f the pixel format.
   *
   * \param refres_rate the refresh_rate.
   */
  display_mode(const vec2u& size, display_format f, uint refresh_rate) noexcept;

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

  /** Gets the pixel format.
   *
   * \return the pixel format.
   */
  display_format get_format() const noexcept;

  /** Sets the pixel format.
   *
   * \param f the pixel format.
   */
  void set_format(display_format f) noexcept;

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
  display_format m_format;
  uint m_refresh_rate;
};

/** Checks if two display_mode objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator==(
  const display_mode& lhs, const display_mode& rhs) noexcept;

/** Checks if two display_mode objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator!=(
  const display_mode& lhs, const display_mode& rhs) noexcept;

/** Checks if lhs is lower than rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator<(
  const display_mode& lhs, const display_mode& rhs) noexcept;

/** Checks if lhs is greater than rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator>(
  const display_mode& lhs, const display_mode& rhs) noexcept;

/** Checks if lhs is lower or equal to rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator<=(
  const display_mode& lhs, const display_mode& rhs) noexcept;

/** Checks if lhs is greater or equal to rhs.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator>=(
  const display_mode& lhs, const display_mode& rhs) noexcept;

/** Writes a display_mode object into a stream.
 *
 * \param os the stream.
 *
 * \param vm the display_mode object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const display_mode& vm);

}  // namespace hou

#endif
