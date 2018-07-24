// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/clock.hpp"

#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class test_clock : public Test
{};

}  // namespace



TEST_F(test_clock, get_resolution)
{
  EXPECT_GE(std::chrono::nanoseconds(100), hou::clock::get_resolution());
}



TEST_F(test_clock, default_constructor)
{
  hou::clock c;
  SUCCEED();
}



TEST_F(test_clock, get_elapsed_time)
{
  // Sleep calls were inserted because execution was sometimes too fast for the
  // timer resolution.

  const std::chrono::nanoseconds sleep_time(1000000);
  hou::clock c;
  std::chrono::nanoseconds t1 = c.get_elapsed_time();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t2 = c.get_elapsed_time();
  std::this_thread::sleep_for(sleep_time);
  std::chrono::nanoseconds t3 = c.get_elapsed_time();

  EXPECT_GT(t2, t1);
  EXPECT_GT(t3, t2);
  EXPECT_GE((t2 - t1), sleep_time);
  EXPECT_GE((t3 - t2), sleep_time);
}



TEST_F(test_clock, reset)
{
  hou::clock c;
  std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
  std::chrono::nanoseconds t1 = c.get_elapsed_time();
  c.reset();
  std::chrono::nanoseconds t2 = c.get_elapsed_time();
  EXPECT_LT(t2, t1);
}
