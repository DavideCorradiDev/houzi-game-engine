// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/cor/StdChrono.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestStdChrono : public Test {};

}



TEST_F(TestStdChrono, NanosecondsOutputStreamOperator)
{
  HOU_EXPECT_OUTPUT("42 ns", std::chrono::nanoseconds(42));
}



TEST_F(TestStdChrono, MicrosecondsOutputStreamOperator)
{
  HOU_EXPECT_OUTPUT("42 us", std::chrono::microseconds(42));
}



TEST_F(TestStdChrono, MillisecondsOutputStreamOperator)
{
  HOU_EXPECT_OUTPUT("42 ms", std::chrono::milliseconds(42));
}



TEST_F(TestStdChrono, SecondsOutputStreamOperator)
{
  HOU_EXPECT_OUTPUT("42 s", std::chrono::seconds(42));
}



TEST_F(TestStdChrono, MinutesOutputStreamOperator)
{
  HOU_EXPECT_OUTPUT("42 m", std::chrono::minutes(42));
}



TEST_F(TestStdChrono, HoursOutputStreamOperator)
{
  HOU_EXPECT_OUTPUT("42 h", std::chrono::hours(42));
}

