// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/Stopwatch.hpp"

#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class TestStopwatch : public Test {};

}



TEST_F(TestStopwatch, GetResolution)
{
  EXPECT_GE(std::chrono::nanoseconds(100), Stopwatch::get_resolution());
  EXPECT_EQ(clock::get_resolution(), Stopwatch::get_resolution());
}



TEST_F(TestStopwatch, Construction)
{
  Stopwatch t;
  EXPECT_EQ(std::chrono::nanoseconds(0), t.get_elapsed_time());
  EXPECT_FALSE(t.isRunning());
}



TEST_F(TestStopwatch, StartPauseResetStop)
{
  // Sleep calls were inserted because execution was sometimes too fast for the
  // timer resolution.

  Stopwatch t;
  const std::chrono::nanoseconds sleepTime(1000000);

  std::chrono::nanoseconds t0 = t.start();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t1 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t2 = t.pause();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t3 = t.get_elapsed_time();
  std::chrono::nanoseconds t4 = t.start();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t5 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t6 = t.reset();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t7 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t8 = t.pause();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t9 = t.reset();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t10 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t11 = t.start();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t12 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t13 = t.stop();
  std::this_thread::sleep_for(sleepTime);
  std::chrono::nanoseconds t14 = t.get_elapsed_time();


  EXPECT_EQ(std::chrono::nanoseconds(0), t0);
  EXPECT_GT(t1, t0);
  EXPECT_GT(t2, t1);
  EXPECT_EQ(t3, t2);
  EXPECT_EQ(t4, t3);
  EXPECT_GT(t5, t4);
  EXPECT_GT(t6, t5);
  EXPECT_LT(t7, t6);
  EXPECT_GT(t8, t7);
  EXPECT_EQ(t9, t8);
  EXPECT_EQ(std::chrono::nanoseconds(0), t10);
  EXPECT_EQ(std::chrono::nanoseconds(0), t11);
  EXPECT_GT(t12, t11);
  EXPECT_GT(t13, t12);
  EXPECT_EQ(std::chrono::nanoseconds(0), t14);
}



TEST_F(TestStopwatch, IsRunning)
{
  Stopwatch t;
  EXPECT_FALSE(t.isRunning());
  t.pause();
  EXPECT_FALSE(t.isRunning());
  t.stop();
  EXPECT_FALSE(t.isRunning());
  t.reset();
  EXPECT_FALSE(t.isRunning());
  t.start();
  EXPECT_TRUE(t.isRunning());
  t.pause();
  EXPECT_FALSE(t.isRunning());
  t.start();
  EXPECT_TRUE(t.isRunning());
  t.stop();
  EXPECT_FALSE(t.isRunning());
  t.start();
  EXPECT_TRUE(t.isRunning());
  t.reset();
  EXPECT_TRUE(t.isRunning());
}

