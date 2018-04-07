// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/cor/Error.hpp"

#include <string>

using namespace hou;
using namespace testing;

namespace
{

class TestError : public Test {};
class TestErrorDeathTest : public TestError {};

}



TEST_F(TestError, FormatErrorMessage)
{
#if defined(HOU_SYSTEM_WINDOWS)
  std::string filePath(u8"\\hello\\bye\\myfile.txt");
#else
  std::string filePath(u8"/hello/bye/myfile.txt");
#endif
  std::string msg = formatErrorMessage(filePath, 42
    , u8"This is a \u5436%s error with code %d \u3245", u8"BIG\u1234", 33);
  std::string msgRef
    = u8"myfile.txt:42 - This is a \u5436BIG\u1234 error with code 33 \u3245";
  EXPECT_EQ(msgRef, msg);
}



TEST_F(TestErrorDeathTest, Terminate)
{
  EXPECT_DEATH(HOU_TERMINATE(u8"This is a fatal error!")
    , u8"This is a fatal error!");
}



TEST_F(TestErrorDeathTest, Throw)
{
  std::error_code ec(1, std::generic_category());
  std::string ecmsg(ec.message());

  HOU_EXPECT_ERROR
    ( HOU_THROW(std::system_error, 1, std::generic_category()
    , HOU_ERRMSG(u8"This is a %s error with code %d", "BIG", 42))
    , std::system_error, u8"This is a BIG error with code 42: " + ec.message());
}



TEST_F(TestErrorDeathTest, FatalError)
{
  EXPECT_DEATH(HOU_FATAL_ERROR(u8"This is a %s error!%d!", "bad", 1)
    , u8"This is a bad error!1!");
}



TEST_F(TestError, FatalCheckPassed)
{
  HOU_FATAL_CHECK(2 > 1, u8"This is a %s error!", u8"fatal");
  SUCCEED();
}



TEST_F(TestErrorDeathTest, FatalCheckFailed)
{
  EXPECT_DEATH(HOU_FATAL_CHECK(2 < 1, u8"This is a %s error!", u8"fatal")
    , u8"This is a fatal error!");
}




TEST_F(TestError, FatalCheckDevPassed)
{
  HOU_FATAL_CHECK_DEV(2 > 1, u8"This is a %s error!", u8"fatal");
  SUCCEED();
}



TEST_F(TestErrorDeathTest, FatalCheckDevFailed)
{
#if defined(NDEBUG)
  HOU_FATAL_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"fatal");
  SUCCEED();
#else
  EXPECT_DEATH(HOU_FATAL_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"fatal")
    , u8"This is a fatal error!");
#endif
}



TEST_F(TestErrorDeathTest, RuntimeError)
{
  HOU_EXPECT_ERROR(HOU_RUNTIME_ERROR(u8"This is a %s error!", u8"runtime")
    , std::runtime_error, "This is a runtime error!");
}



TEST_F(TestError, RuntimeCheckPassed)
{
  HOU_RUNTIME_CHECK(2 > 1, u8"This is a %s error!", u8"runtime");
  SUCCEED();
}



TEST_F(TestErrorDeathTest, RuntimeCheckFailed)
{
  HOU_EXPECT_ERROR
    ( HOU_RUNTIME_CHECK(2 < 1, u8"This is a %s error!", u8"runtime")
    , std::runtime_error, u8"This is a runtime error!");
}



TEST_F(TestError, RuntimeCheckDevPassed)
{
  HOU_RUNTIME_CHECK_DEV(2 > 1, u8"This is a %s error!", u8"runtime");
  SUCCEED();
}



TEST_F(TestErrorDeathTest, RuntimeCheckDevFailed)
{
#if defined(NDEBUG)
  HOU_RUNTIME_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"runtime");
  SUCCEED();
#else
  HOU_EXPECT_ERROR
    ( HOU_RUNTIME_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"runtime")
    , std::runtime_error, u8"This is a runtime error!");
#endif
}



TEST_F(TestErrorDeathTest, LogicError)
{
  HOU_EXPECT_ERROR(HOU_LOGIC_ERROR(u8"This is a %s error!", u8"logic")
    , std::logic_error, u8"This is a logic error!");
}



TEST_F(TestError, LogicCheckPassed)
{
  HOU_LOGIC_CHECK(2 > 1, u8"This is a %s error!", u8"logic");
  SUCCEED();
}



TEST_F(TestErrorDeathTest, LogicCheckFailed)
{
  HOU_EXPECT_ERROR
    ( HOU_LOGIC_CHECK(2 < 1, u8"This is a %s error!", u8"logic")
    , std::logic_error, u8"This is a logic error!");
}



TEST_F(TestError, LogicCheckDevPassed)
{
  HOU_LOGIC_CHECK_DEV(2 > 1, u8"This is a %s error!", u8"logic");
  SUCCEED();
}



TEST_F(TestErrorDeathTest, LogicCheckDevFailed)
{
#if defined(NDEBUG)
  HOU_LOGIC_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"logic");
  SUCCEED();
#else
  HOU_EXPECT_ERROR
    ( HOU_LOGIC_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"logic")
    , std::logic_error, u8"This is a logic error!");
#endif
}



TEST_F(TestError, ExpectPassed)
{
  HOU_EXPECT(2 > 1);
  SUCCEED();
}



TEST_F(TestErrorDeathTest, ExpectFailed)
{
  HOU_EXPECT_ERROR(HOU_EXPECT(2 < 1), std::logic_error
    , formatString(getText(CorError::Precondition), "2 < 1"));
}



TEST_F(TestErrorDeathTest, ExpectDevFailed)
{
#if defined(NDEBUG)
  HOU_EXPECT_DEV(2 < 1);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_EXPECT_DEV(2 < 1), std::logic_error
    , formatString(getText(CorError::Precondition), "2 < 1"));
#endif
}



TEST_F(TestError, ExpectDevPassed)
{
  HOU_EXPECT_DEV(2 > 1);
  SUCCEED();
}



TEST_F(TestError, EnsurePassed)
{
  HOU_ENSURE(2 > 1);
  SUCCEED();
}



TEST_F(TestErrorDeathTest, EnsureFailed)
{
  HOU_EXPECT_ERROR(HOU_ENSURE(2 < 1), std::logic_error
    , formatString(getText(CorError::Postcondition), "2 < 1"));
}



TEST_F(TestError, EnsureDevPassed)
{
  HOU_ENSURE_DEV(2 > 1);
  SUCCEED();
}



TEST_F(TestErrorDeathTest, EnsureDevFailed)
{
#if defined(NDEBUG)
  HOU_ENSURE_DEV(2 < 1);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_ENSURE_DEV(2 < 1), std::logic_error
    , formatString(getText(CorError::Postcondition), "2 < 1"));
#endif
}

