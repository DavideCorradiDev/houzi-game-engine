// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/clock.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

std::chrono::nanoseconds clock::get_resolution()
{
  return std::chrono::nanoseconds
    (static_cast<int64_t>(1000000000.
    * ( static_cast<double>(std::chrono::high_resolution_clock::period::num)
      / static_cast<double>(std::chrono::high_resolution_clock::period::den))));
}



clock::clock()
  : m_clock()
  , m_start_time(m_clock.now())
{}



std::chrono::nanoseconds clock::get_elapsed_time() const
{
  return m_clock.now() - m_start_time;
}



std::chrono::nanoseconds clock::reset()
{
  std::chrono::high_resolution_clock::time_point currentTime = m_clock.now();
  std::chrono::nanoseconds retval = currentTime - m_start_time;
  m_start_time = currentTime;
  return retval;
}

}

