// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/core_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_core_exceptions : public Test
{};

class test_core_exceptions_death_test : public test_core_exceptions
{};

enum class test_enum_1 : int
{
  enum_val_0 = 0,
  enum_val_1 = 1,
  enum_val_2 = 2,
};

enum test_enum_2 : int
{
  enum_val_0 = 0,
  enum_val_1 = 1,
  enum_val_2 = 2,
};

}  // namespace



TEST_F(test_core_exceptions, invalid_enumeration_value_enum_class)
{
  invalid_enum<test_enum_1> ex("foo.cpp", 42u, test_enum_1::enum_val_1);
  EXPECT_STREQ("foo.cpp:42 - Invalid enumeration value '1'.", ex.what());
}



TEST_F(test_core_exceptions, invalid_enumeration_value_enum)
{
  invalid_enum<test_enum_2> ex("foo.cpp", 42u, test_enum_2::enum_val_2);
  EXPECT_STREQ("foo.cpp:42 - Invalid enumeration value '2'.", ex.what());
}



TEST_F(test_core_exceptions, overflow_error)
{
  overflow_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Numeric overflow.", ex.what());
}



TEST_F(test_core_exceptions, underflow_error)
{
  underflow_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Numeric underflow.", ex.what());
}



TEST_F(test_core_exceptions, unreachable_code_error)
{
  unreachable_code_error ex("foo.cpp", 42u);
  EXPECT_STREQ(
    "foo.cpp:42 - An unreachable part of code has been reached.", ex.what());
}
