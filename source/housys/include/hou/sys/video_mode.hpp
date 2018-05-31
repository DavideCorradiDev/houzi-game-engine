// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_WND_VIDEO_MODE_HPP
#define HOU_WND_VIDEO_MODE_HPP

#include "hou/sys/sys_config.hpp"

#include "hou/mth/matrix.hpp"

#include <ostream>
#include <vector>



namespace hou
{

/** Class representing a video mode.
 */
class HOU_SYS_API video_mode
{
public:
  /** Creates a video_mode object.
   *
   * \param resolution the resolution.
   *
   * \param depth_byte_count the number of bytes per pixel.
   *
   * \param refres_rate the refresh_rate.
   */
  video_mode(
    const vec2u& resolution, uint depth_byte_count, uint refresh_rate) noexcept;

  /** Retrieves the resolution.
   *
   * \return the resolution.
   */
  const vec2u& get_resolution() const noexcept;

  /** Sets the resolution.
   *
   * \param resolution the resolution.
   */
  void set_resolution(const vec2u& resolution) noexcept;

  /** Retrieves the number of bytes per pixel.
   *
   * \return the number of bytes per pixel.
   */
  uint get_depth_byte_count() const noexcept;

  /** Sets the number of bytes per pixel.
   *
   * \param depth_byte_count the number of bytes per pixel.
   */
  void set_depth_byte_count(uint depth_byte_count) noexcept;

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
  vec2u m_resolution;
  uint m_depth_byte_count;
  uint m_refresh_rate;
};

/** Checks if two video_mode objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator==(
  const video_mode& lhs, const video_mode& rhs) noexcept;

/** Checks if two video_mode objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator!=(
  const video_mode& lhs, const video_mode& rhs) noexcept;

/** Checks if lhs is lower than rhs.
 *
 * Comparisons happen in the following order: bits per pixel, x resolution,
 * y resolution.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator<(
  const video_mode& lhs, const video_mode& rhs) noexcept;

/** Checks if lhs is greater than rhs.
 *
 * Comparisons happen in the following order: bits per pixel, x resolution,
 * y resolution.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator>(
  const video_mode& lhs, const video_mode& rhs) noexcept;

/** Checks if lhs is lower or equal to rhs.
 *
 * Comparisons happen in the following order: bits per pixel, x resolution,
 * y resolution.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator<=(
  const video_mode& lhs, const video_mode& rhs) noexcept;

/** Checks if lhs is greater or equal to rhs.
 *
 * Comparisons happen in the following order: bits per pixel, x resolution,
 * y resolution.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator>=(
  const video_mode& lhs, const video_mode& rhs) noexcept;

/** Writes a video_mode object into a stream.
 *
 * Comparisons happen in the following order: bits per pixel, x resolution,
 * y resolution.
 *
 * \param os the stream.
 *
 * \param vm the video_mode object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const video_mode& vm);

}  // namespace hou

#endif
