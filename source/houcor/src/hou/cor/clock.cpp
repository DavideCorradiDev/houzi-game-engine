// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/clock.hpp"



namespace hou
{

std::chrono::nanoseconds clock::get_resolution() noexcept
{
  using rep = std::chrono::nanoseconds::rep;
  return std::chrono::nanoseconds(static_cast<rep>(1000000000.
    * (static_cast<double>(std::chrono::high_resolution_clock::period::num)
        / static_cast<double>(
            std::chrono::high_resolution_clock::period::den))));
}



clock::clock() noexcept
  : m_clock()
  , m_start_time(m_clock.now())
{}



std::chrono::nanoseconds clock::get_elapsed_time() const noexcept
{
  return m_clock.now() - m_start_time;
}



std::chrono::nanoseconds clock::reset() noexcept
{
  std::chrono::high_resolution_clock::time_point current_time = m_clock.now();
  std::chrono::nanoseconds retval = current_time - m_start_time;
  m_start_time = current_time;
  return retval;
}

}  // namespace hou
