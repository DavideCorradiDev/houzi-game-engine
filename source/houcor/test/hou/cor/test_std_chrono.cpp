// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/std_chrono.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_std_chrono : public Test
{};

}  // namespace



TEST_F(test_std_chrono, nanoseconds_output_stream_operator)
{
  EXPECT_OUTPUT("42 ns", std::chrono::nanoseconds(42));
}



TEST_F(test_std_chrono, microseconds_output_stream_operator)
{
  EXPECT_OUTPUT("42 us", std::chrono::microseconds(42));
}



TEST_F(test_std_chrono, milliseconds_output_stream_operator)
{
  EXPECT_OUTPUT("42 ms", std::chrono::milliseconds(42));
}



TEST_F(test_std_chrono, seconds_output_stream_operator)
{
  EXPECT_OUTPUT("42 s", std::chrono::seconds(42));
}



TEST_F(test_std_chrono, minutes_output_stream_operator)
{
  EXPECT_OUTPUT("42 m", std::chrono::minutes(42));
}



TEST_F(test_std_chrono, hours_output_stream_operator)
{
  EXPECT_OUTPUT("42 h", std::chrono::hours(42));
}
