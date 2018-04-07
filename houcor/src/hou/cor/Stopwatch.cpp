// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/cor/Stopwatch.hpp"



namespace hou
{

std::chrono::nanoseconds Stopwatch::getResolution()
{
  return Clock::getResolution();
}



Stopwatch::Stopwatch()
  : mClock()
  , mElapsedTime(0)
  , mRunning(false)
{}



std::chrono::nanoseconds Stopwatch::getElapsedTime() const
{
  return mElapsedTime
    + (mRunning ? mClock.getElapsedTime() : std::chrono::nanoseconds(0));
}



bool Stopwatch::isRunning() const
{
  return mRunning;
}



std::chrono::nanoseconds Stopwatch::start()
{
  if(!mRunning)
  {
    mClock.reset();
    mRunning = true;
  }
  return mElapsedTime;
}



std::chrono::nanoseconds Stopwatch::pause()
{
  mElapsedTime = getElapsedTime();
  mRunning = false;
  return mElapsedTime;
}



std::chrono::nanoseconds Stopwatch::reset()
{
  std::chrono::nanoseconds elapsedTime = getElapsedTime();
  mElapsedTime = std::chrono::nanoseconds(0);
  mClock.reset();
  return elapsedTime;
}



std::chrono::nanoseconds Stopwatch::stop()
{
  std::chrono::nanoseconds elapsedTime = getElapsedTime();
  mElapsedTime = std::chrono::nanoseconds(0);
  mRunning = false;
  return elapsedTime;
}

}

