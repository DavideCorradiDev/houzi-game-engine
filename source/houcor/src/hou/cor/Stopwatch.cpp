// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/Stopwatch.hpp"



namespace hou
{

std::chrono::nanoseconds Stopwatch::get_resolution()
{
  return clock::get_resolution();
}



Stopwatch::Stopwatch()
  : m_clock()
  , mElapsedTime(0)
  , mRunning(false)
{}



std::chrono::nanoseconds Stopwatch::get_elapsed_time() const
{
  return mElapsedTime
    + (mRunning ? m_clock.get_elapsed_time() : std::chrono::nanoseconds(0));
}



bool Stopwatch::isRunning() const
{
  return mRunning;
}



std::chrono::nanoseconds Stopwatch::start()
{
  if(!mRunning)
  {
    m_clock.reset();
    mRunning = true;
  }
  return mElapsedTime;
}



std::chrono::nanoseconds Stopwatch::pause()
{
  mElapsedTime = get_elapsed_time();
  mRunning = false;
  return mElapsedTime;
}



std::chrono::nanoseconds Stopwatch::reset()
{
  std::chrono::nanoseconds elapsedTime = get_elapsed_time();
  mElapsedTime = std::chrono::nanoseconds(0);
  m_clock.reset();
  return elapsedTime;
}



std::chrono::nanoseconds Stopwatch::stop()
{
  std::chrono::nanoseconds elapsedTime = get_elapsed_time();
  mElapsedTime = std::chrono::nanoseconds(0);
  mRunning = false;
  return elapsedTime;
}

}

