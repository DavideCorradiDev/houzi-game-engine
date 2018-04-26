// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_WND_VIDEO_MODE_HPP
#define HOU_WND_VIDEO_MODE_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/mth/Matrix.hpp"

#include <ostream>
#include <vector>



namespace hou
{

/** Class representing a video mode, defined by the resolution and the number
 *  of bits per pixel.
 */
class HOU_SYS_API VideoMode
{
public:
  /** Retrieves the current desktop video mode.
   *
   *  \return the desktop video mode.
   */
  static VideoMode getDesktopMode();

  /** Retrieves the available fullscreen modes.
   *
   *  \return a collection of the available fullscreen modes.
   */
  static std::vector<VideoMode> getFullscreenModes();

  /** Creates a VideoMode object.
   *
   *  \param resolution the screen resolution.
   *  \param bytesPerPixel the number of bits per pixel.
   */
  VideoMode(const Vec2u& resolution, uint bytesPerPixel);

  /** Retrieves the screen resolution.
   *
   *  \return the screen resolution.
   */
  const Vec2u& getResolution() const;

  /** Retrieves the number of bits per pixel.
   *
   *  \return the number of bits per pixel.
   */
  uint getBytesPerPixel() const;

  /** Checks if this is a fullscreen video mode.
   *
   *  \return true if this is a fullscreen video mode.
   */
  bool isFullscreenMode() const;

private:
  static std::vector<VideoMode> createFullscreenModesVector();

private:
  Vec2u mResolution;
  uint mBytesPerPixel;
};

/** Checks if two VideoMode objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const VideoMode& lhs, const VideoMode& rhs);

/** Checks if two VideoMode objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const VideoMode& lhs, const VideoMode& rhs);

/** Checks if lhs is lower than rhs.
 *
 *  Comparisons happen in the following order: bits per pixel, x resolution,
 *  y resolution.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator<(const VideoMode& lhs, const VideoMode& rhs);

/** Checks if lhs is greater than rhs.
 *
 *  Comparisons happen in the following order: bits per pixel, x resolution,
 *  y resolution.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator>(const VideoMode& lhs, const VideoMode& rhs);

/** Checks if lhs is lower or equal to rhs.
 *
 *  Comparisons happen in the following order: bits per pixel, x resolution,
 *  y resolution.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator<=(const VideoMode& lhs, const VideoMode& rhs);

/** Checks if lhs is greater or equal to rhs.
 *
 *  Comparisons happen in the following order: bits per pixel, x resolution,
 *  y resolution.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator>=(const VideoMode& lhs, const VideoMode& rhs);

/** Writes a VideoMode object into a stream.
 *
 *  Comparisons happen in the following order: bits per pixel, x resolution,
 *  y resolution.
 *
 *  \param os the stream.
 *  \param vm the VideoMode object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const VideoMode& vm);

}

#endif

