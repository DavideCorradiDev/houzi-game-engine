// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/Clock.hpp"

#include "hou/cor/BasicTypes.hpp"



namespace hou
{

std::chrono::nanoseconds Clock::getResolution()
{
  return std::chrono::nanoseconds
    (static_cast<int64_t>(1000000000.
    * ( static_cast<double>(std::chrono::high_resolution_clock::period::num)
      / static_cast<double>(std::chrono::high_resolution_clock::period::den))));
}



Clock::Clock()
  : mClock()
  , mStartTime(mClock.now())
{}



std::chrono::nanoseconds Clock::getElapsedTime() const
{
  return mClock.now() - mStartTime;
}



std::chrono::nanoseconds Clock::reset()
{
  std::chrono::high_resolution_clock::time_point currentTime = mClock.now();
  std::chrono::nanoseconds retval = currentTime - mStartTime;
  mStartTime = currentTime;
  return retval;
}

}

