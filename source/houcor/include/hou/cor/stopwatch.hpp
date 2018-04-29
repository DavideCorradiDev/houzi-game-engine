// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_STOPWATCH_HPP
#define HOU_COR_STOPWATCH_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/cor/clock.hpp"



namespace hou
{

/** High resolution ph_stopwatch.
 *
 *  Guarantees a resolution of 100 ns.
 */
class HOU_COR_API stopwatch
{
public:
  /** Retrieves the ph_stopwatch resolution.
   *
   * Note: the reported resolution might not be accurate.
   *
   * \return the resolution in nanoseconds.
   */
  static std::chrono::nanoseconds get_resolution();

public:
  /** Creates a ph_stopwatch object.
   *
   * When created the ph_stopwatch is not running.
   */
  stopwatch();

  /** Returns the elapsed time.
   *
   * \return the elapsed time.
   */
  std::chrono::nanoseconds get_elapsed_time() const;

  /** Checks if the ph_stopwatch is currently running or not.
   *
   * \return true if the ph_stopwatch is running.
   */
  bool isRunning() const;

  /** Starts the ph_stopwatch.
   *
   * \return the elapsed time when starting.
   */
  std::chrono::nanoseconds start();

  /** Pauses the ph_stopwatch.
   *
   * \return the elapsed time when pausing.
   */
  std::chrono::nanoseconds pause();

  /** Resets the ph_stopwatch.
   *
   * \return the elapsed time before resetting.
   */
  std::chrono::nanoseconds reset();

  /** Stops the ph_stopwatch.
   *
   * The ph_stopwatch will be paused and reset.
   *
   * \return the elapsed time before stopping.
   */
  std::chrono::nanoseconds stop();

private:
  clock m_clock;
  std::chrono::nanoseconds m_elapsed_time;
  bool m_running;
};

}  // namespace hou

#endif
