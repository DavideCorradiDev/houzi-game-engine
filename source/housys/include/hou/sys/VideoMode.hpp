// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_WND_VIDEO_MODE_HPP
#define HOU_WND_VIDEO_MODE_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/mth/matrix.hpp"

#include <ostream>
#include <vector>



namespace hou
{

/** Class representing a video mode, defined by the resolution and the number
 *  of bits per ph_pixel.
 */
class HOU_SYS_API video_mode
{
public:
  /** Retrieves the current desktop video mode.
   *
   *  \return the desktop video mode.
   */
  static video_mode get_desktop_mode();

  /** Retrieves the available fullscreen modes.
   *
   *  \return a collection of the available fullscreen modes.
   */
  static std::vector<video_mode> getFullscreenModes();

  /** Creates a video_mode object.
   *
   *  \param resolution the screen resolution.
   *  \param bytesPerPixel the number of bits per ph_pixel.
   */
  video_mode(const vec2u& resolution, uint bytesPerPixel);

  /** Retrieves the screen resolution.
   *
   *  \return the screen resolution.
   */
  const vec2u& get_resolution() const;

  /** Retrieves the number of bits per ph_pixel.
   *
   *  \return the number of bits per ph_pixel.
   */
  uint get_bytes_per_pixel() const;

  /** Checks if this is a fullscreen video mode.
   *
   *  \return true if this is a fullscreen video mode.
   */
  bool is_fullscreen_mode() const;

private:
  static std::vector<video_mode> createFullscreenModesVector();

private:
  vec2u m_resolution;
  uint m_bytes_per_pixel;
};

/** Checks if two video_mode objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const video_mode& lhs, const video_mode& rhs);

/** Checks if two video_mode objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const video_mode& lhs, const video_mode& rhs);

/** Checks if lhs is lower than rhs.
 *
 *  Comparisons happen in the following order: bits per ph_pixel, x resolution,
 *  y resolution.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator<(const video_mode& lhs, const video_mode& rhs);

/** Checks if lhs is greater than rhs.
 *
 *  Comparisons happen in the following order: bits per ph_pixel, x resolution,
 *  y resolution.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator>(const video_mode& lhs, const video_mode& rhs);

/** Checks if lhs is lower or equal to rhs.
 *
 *  Comparisons happen in the following order: bits per ph_pixel, x resolution,
 *  y resolution.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator<=(const video_mode& lhs, const video_mode& rhs);

/** Checks if lhs is greater or equal to rhs.
 *
 *  Comparisons happen in the following order: bits per ph_pixel, x resolution,
 *  y resolution.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator>=(const video_mode& lhs, const video_mode& rhs);

/** Writes a video_mode object into a ph_stream.
 *
 *  Comparisons happen in the following order: bits per ph_pixel, x resolution,
 *  y resolution.
 *
 *  \param os the ph_stream.
 *  \param vm the video_mode object.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const video_mode& vm);

}

#endif

