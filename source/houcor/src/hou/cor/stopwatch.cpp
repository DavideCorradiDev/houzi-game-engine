// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/stopwatch.hpp"



namespace hou
{

std::chrono::nanoseconds stopwatch::get_resolution() noexcept
{
  return clock::get_resolution();
}



stopwatch::stopwatch() noexcept
  : m_clock()
  , m_elapsed_time(0)
  , m_running(false)
{}



std::chrono::nanoseconds stopwatch::get_elapsed_time() const noexcept
{
  return m_elapsed_time
    + (m_running ? m_clock.get_elapsed_time() : std::chrono::nanoseconds(0));
}



bool stopwatch::is_running() const noexcept
{
  return m_running;
}



std::chrono::nanoseconds stopwatch::start() noexcept
{
  if(!m_running)
  {
    m_clock.reset();
    m_running = true;
  }
  return m_elapsed_time;
}



std::chrono::nanoseconds stopwatch::pause() noexcept
{
  m_elapsed_time = get_elapsed_time();
  m_running = false;
  return m_elapsed_time;
}



std::chrono::nanoseconds stopwatch::reset() noexcept
{
  std::chrono::nanoseconds elapsed_time = get_elapsed_time();
  m_elapsed_time = std::chrono::nanoseconds(0);
  m_clock.reset();
  return elapsed_time;
}



std::chrono::nanoseconds stopwatch::stop() noexcept
{
  std::chrono::nanoseconds elapsed_time = get_elapsed_time();
  m_elapsed_time = std::chrono::nanoseconds(0);
  m_running = false;
  return elapsed_time;
}

}  // namespace hou
