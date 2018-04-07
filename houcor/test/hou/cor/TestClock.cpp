// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/cor/Clock.hpp"

#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class TestClock : public Test {};

}



TEST_F(TestClock, GetResolution)
{
  EXPECT_GE(std::chrono::nanoseconds(100), Clock::getResolution());
}



TEST_F(TestClock, DefaultConstructor)
{
  Clock c;
  SUCCEED();
}



TEST_F(TestClock, GetElapsedTime)
{
  // Sleep calls were inserted because execution was sometimes too fast for the
  // timer resolution.

  const std::chrono::nanoseconds sleepTime(1000000);
  Clock c;
  std::chrono::nanoseconds t1 = c.getElapsedTime();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t2 = c.getElapsedTime();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t3 = c.getElapsedTime();

  EXPECT_GT(t2, t1);
  EXPECT_GT(t3, t2);
  EXPECT_GT((t2 - t1), sleepTime);
  EXPECT_GT((t3 - t2), sleepTime);
}



TEST_F(TestClock, Reset)
{
  Clock c;
  std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
  std::chrono::nanoseconds t1 = c.getElapsedTime();
  c.reset();
  std::chrono::nanoseconds t2 = c.getElapsedTime();
  EXPECT_LT(t2, t1);
}

