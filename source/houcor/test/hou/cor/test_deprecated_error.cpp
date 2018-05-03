// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/deprecated_error.hpp"

#include <string>

using namespace hou;
using namespace testing;

namespace
{

class test_error : public Test
{};

class test_error_death_test : public test_error
{};

}  // namespace



TEST_F(test_error, deprecated_format_error_message)
{
#if defined(HOU_SYSTEM_WINDOWS)
  std::string file_path(u8"\\hello\\bye\\myfile.txt");
#else
  std::string file_path(u8"/hello/bye/myfile.txt");
#endif
  std::string msg = deprecated_format_error_message(
    file_path, 42, u8"This is a \u5436%s error with code %d \u3245",
    u8"BIG\u1234", 33);
  std::string msg_ref
    = u8"myfile.txt:42 - This is a \u5436BIG\u1234 error with code 33 \u3245";
  EXPECT_EQ(msg_ref, msg);
}



TEST_F(test_error_death_test, terminate)
{
  EXPECT_DEATH(
    DEPRECATED_HOU_TERMINATE(u8"This is a fatal error!"), u8"This is a fatal error!");
}



TEST_F(test_error_death_test, throw)
{
  std::error_code ec(1, std::generic_category());
  std::string ecmsg(ec.message());

  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_THROW(
      std::system_error, 1, std::generic_category(),
      DEPRECATED_HOU_ERRMSG(u8"This is a %s error with code %d", "BIG", 42)),
    std::system_error, u8"This is a BIG error with code 42: " + ec.message());
}



TEST_F(test_error_death_test, fatal_error)
{
  EXPECT_DEATH(
    DEPRECATED_HOU_FATAL_ERROR(u8"This is a %s error!%d!", "bad", 1),
    u8"This is a bad error!1!");
}



TEST_F(test_error, fatal_check_passed)
{
  DEPRECATED_HOU_FATAL_CHECK(2 > 1, u8"This is a %s error!", u8"fatal");
  SUCCEED();
}



TEST_F(test_error_death_test, fatal_check_failed)
{
  EXPECT_DEATH(
    DEPRECATED_HOU_FATAL_CHECK(2 < 1, u8"This is a %s error!", u8"fatal"),
    u8"This is a fatal error!");
}



TEST_F(test_error, fatal_check_dev_passed)
{
  HOU_FATAL_CHECK_DEV(2 > 1, u8"This is a %s error!", u8"fatal");
  SUCCEED();
}



TEST_F(test_error_death_test, fatal_check_dev_failed)
{
#if defined(NDEBUG)
  HOU_FATAL_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"fatal");
  SUCCEED();
#else
  EXPECT_DEATH(
    HOU_FATAL_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"fatal"),
    u8"This is a fatal error!");
#endif
}



TEST_F(test_error_death_test, runtime_error)
{
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_RUNTIME_ERROR(u8"This is a %s error!", u8"runtime"), std::runtime_error,
    "This is a runtime error!");
}



TEST_F(test_error, runtime_check_passed)
{
  DEPRECATED_HOU_RUNTIME_CHECK(2 > 1, u8"This is a %s error!", u8"runtime");
  SUCCEED();
}



TEST_F(test_error_death_test, runtime_check_failed)
{
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_RUNTIME_CHECK(2 < 1, u8"This is a %s error!", u8"runtime"),
    std::runtime_error, u8"This is a runtime error!");
}



TEST_F(test_error, runtime_check_dev_passed)
{
  DEPRECATED_HOU_RUNTIME_CHECK_DEV(2 > 1, u8"This is a %s error!", u8"runtime");
  SUCCEED();
}



TEST_F(test_error_death_test, runtime_check_dev_failed)
{
#if defined(NDEBUG)
  DEPRECATED_HOU_RUNTIME_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"runtime");
  SUCCEED();
#else
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_RUNTIME_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"runtime"),
    std::runtime_error, u8"This is a runtime error!");
#endif
}



TEST_F(test_error_death_test, logic_error)
{
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_LOGIC_ERROR(u8"This is a %s error!", u8"logic"), std::logic_error,
    u8"This is a logic error!");
}



TEST_F(test_error, logic_check_passed)
{
  DEPRECATED_HOU_LOGIC_CHECK(2 > 1, u8"This is a %s error!", u8"logic");
  SUCCEED();
}



TEST_F(test_error_death_test, logic_check_failed)
{
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_LOGIC_CHECK(2 < 1, u8"This is a %s error!", u8"logic"),
    std::logic_error, u8"This is a logic error!");
}



TEST_F(test_error, logic_check_dev_passed)
{
  DEPRECATED_HOU_LOGIC_CHECK_DEV(2 > 1, u8"This is a %s error!", u8"logic");
  SUCCEED();
}



TEST_F(test_error_death_test, logic_check_dev_failed)
{
#if defined(NDEBUG)
  DEPRECATED_HOU_LOGIC_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"logic");
  SUCCEED();
#else
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_LOGIC_CHECK_DEV(2 < 1, u8"This is a %s error!", u8"logic"),
    std::logic_error, u8"This is a logic error!");
#endif
}



TEST_F(test_error, expect_passed)
{
  DEPRECATED_HOU_EXPECT(2 > 1);
  SUCCEED();
}



TEST_F(test_error_death_test, expect_failed)
{
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_EXPECT(2 < 1), std::logic_error,
    format_string(get_text(cor_error::pre_condition), "2 < 1"));
}



TEST_F(test_error_death_test, expect_dev_failed)
{
#if defined(NDEBUG)
  DEPRECATED_HOU_EXPECT_DEV(2 < 1);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_EXPECT_DEV(2 < 1), std::logic_error,
    format_string(get_text(cor_error::pre_condition), "2 < 1"));
#endif
}



TEST_F(test_error, expect_dev_passed)
{
  DEPRECATED_HOU_EXPECT_DEV(2 > 1);
  SUCCEED();
}



TEST_F(test_error, ensure_passed)
{
  DEPRECATED_HOU_ENSURE(2 > 1);
  SUCCEED();
}



TEST_F(test_error_death_test, ensure_failed)
{
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_ENSURE(2 < 1), std::logic_error,
    format_string(get_text(cor_error::post_condition), "2 < 1"));
}



TEST_F(test_error, ensure_dev_passed)
{
  DEPRECATED_HOU_ENSURE_DEV(2 > 1);
  SUCCEED();
}



TEST_F(test_error_death_test, ensure_dev_failed)
{
#if defined(NDEBUG)
  DEPRECATED_HOU_ENSURE_DEV(2 < 1);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(
    DEPRECATED_HOU_ENSURE_DEV(2 < 1), std::logic_error,
    format_string(get_text(cor_error::post_condition), "2 < 1"));
#endif
}
