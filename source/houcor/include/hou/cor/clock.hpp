// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_CLOCK_HPP
#define HOU_COR_CLOCK_HPP

#include "hou/cor/std_chrono.hpp"

#include "hou/cor/cor_config.hpp"



namespace hou
{

/**
 * High resolution p_clock.
 *
 * Guarantees a resolution of 100 ns.
 */
class HOU_COR_API clock
{
public:
  /**
   * Retrieves the p_clock resolution.
   *
   * Note: the reported resolution might not be accurate.
   *
   * \return the resolution in nanoseconds.
   */
  static std::chrono::nanoseconds get_resolution() noexcept;

public:
  /**
   * Creates a p_clock object.
   */
  clock() noexcept;

  /**
   * Returns the time elapsed since the p_clock creation.
   *
   * \return the elapsed time in nanoseconds.
   */
  std::chrono::nanoseconds get_elapsed_time() const noexcept;

  /**
   * Resets the p_clock elapsed time.
   *
   * \return the elapsed time before resetting it in nanoseconds.
   */
  std::chrono::nanoseconds reset() noexcept;

private:
  std::chrono::high_resolution_clock m_clock;
  std::chrono::high_resolution_clock::time_point m_start_time;
};

}  // namespace hou

#endif
