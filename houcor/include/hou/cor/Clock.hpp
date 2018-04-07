// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_COR_CLOCK_HPP
#define HOU_COR_CLOCK_HPP

#include "hou/cor/CorExport.hpp"

#include "hou/cor/StdChrono.hpp"



namespace hou
{

/** High resolution clock.
 *
 *  Guarantees a resolution of 100 ns.
 */
class HOU_COR_API Clock
{
public:
  /** Retrieves the clock resolution.
   *
   *  Note: the reported resolution might not be accurate.
   *
   *  \return the resolution in nanoseconds.
   */
  static std::chrono::nanoseconds getResolution();

public:
  /** Creates a clock object.
   */
  Clock();

  /** Returns the time elapsed since the clock creation.
   *
   *  \return the elapsed time in nanoseconds.
   */
  std::chrono::nanoseconds getElapsedTime() const;

  /** Resets the clock elapsed time.
   *
   *  \return the elapsed time before resetting it in nanoseconds.
   */
  std::chrono::nanoseconds reset();

private:
  std::chrono::high_resolution_clock mClock;
  std::chrono::high_resolution_clock::time_point mStartTime;
};

}

#endif

