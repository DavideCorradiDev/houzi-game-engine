// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/stopwatch.hpp"

#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class test_stopwatch : public Test
{};

}  // namespace



TEST_F(test_stopwatch, get_resolution)
{
  EXPECT_GE(std::chrono::nanoseconds(100), stopwatch::get_resolution());
  EXPECT_EQ(clock::get_resolution(), stopwatch::get_resolution());
}



TEST_F(test_stopwatch, construction)
{
  stopwatch t;
  EXPECT_EQ(std::chrono::nanoseconds(0), t.get_elapsed_time());
  EXPECT_FALSE(t.is_running());
}



TEST_F(test_stopwatch, start_pause_reset_stop)
{
  // Sleep calls were inserted because execution was sometimes too fast for the
  // timer resolution.

  stopwatch t;
  const std::chrono::nanoseconds sleep_time(1000000);

  std::chrono::nanoseconds t0 = t.start();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t1 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t2 = t.pause();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t3 = t.get_elapsed_time();
  std::chrono::nanoseconds t4 = t.start();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t5 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t6 = t.reset();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t7 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t8 = t.pause();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t9 = t.reset();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t10 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t11 = t.start();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t12 = t.get_elapsed_time();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t13 = t.stop();
  std::this_thread::sleep_for(sleep_time);
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



TEST_F(test_stopwatch, is_running)
{
  stopwatch t;
  EXPECT_FALSE(t.is_running());
  t.pause();
  EXPECT_FALSE(t.is_running());
  t.stop();
  EXPECT_FALSE(t.is_running());
  t.reset();
  EXPECT_FALSE(t.is_running());
  t.start();
  EXPECT_TRUE(t.is_running());
  t.pause();
  EXPECT_FALSE(t.is_running());
  t.start();
  EXPECT_TRUE(t.is_running());
  t.stop();
  EXPECT_FALSE(t.is_running());
  t.start();
  EXPECT_TRUE(t.is_running());
  t.reset();
  EXPECT_TRUE(t.is_running());
}
