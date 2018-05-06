// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/assertions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_assertions : public Test
{};

class test_assertions_death_test : public test_assertions
{};

}  // namespace



TEST_F(test_assertions, precondition_violation)
{
  precondition_violation ex(u8"monkeys.txt", 88u);
  EXPECT_STREQ(
    u8"monkeys.txt:88 - A precondition has been violated.", ex.what());
}



TEST_F(test_assertions, hou_precond_macro_success)
{
  EXPECT_NO_ERROR(HOU_PRECOND(2 == 2));
}



TEST_F(test_assertions_death_test, hou_precond_macro_failure)
{
  EXPECT_ERROR_0(HOU_PRECOND(0 == 2), precondition_violation);
}



TEST_F(test_assertions, hou_dev_precond_macro_success)
{
#ifdef NDEBUG
  EXPECT_NO_ERROR(HOU_DEV_PRECOND(2 == 2));
#else
  EXPECT_NO_ERROR(HOU_DEV_PRECOND(2 == 2));
#endif
}



TEST_F(test_assertions_death_test, hou_dev_precond_macro_failure)
{
#ifdef NDEBUG
  EXPECT_NO_ERROR(HOU_DEV_PRECOND(0 == 2));
#else
  EXPECT_ERROR_0(HOU_DEV_PRECOND(0 == 2), precondition_violation);
#endif
}



TEST_F(test_assertions_death_test, expect_precond_error_macro)
{
  EXPECT_PRECOND_ERROR(HOU_PRECOND(0 == 2));
}



TEST_F(test_assertions, postcondition_violation)
{
  postcondition_violation ex(u8"love.jpg", 888u);
  EXPECT_STREQ(
    u8"love.jpg:888 - A postcondition has been violated.", ex.what());
}



TEST_F(test_assertions, hou_postcond_macro_success)
{
  EXPECT_NO_ERROR(HOU_POSTCOND(2 == 2));
}



TEST_F(test_assertions_death_test, hou_postcond_macro_failure)
{
  EXPECT_ERROR_0(HOU_POSTCOND(0 == 2), postcondition_violation);
}



TEST_F(test_assertions, hou_dev_postcond_macro_success)
{
#ifdef NDEBUG
  EXPECT_NO_ERROR(HOU_DEV_POSTCOND(2 == 2));
#else
  EXPECT_NO_ERROR(HOU_DEV_POSTCOND(2 == 2));
#endif
}



TEST_F(test_assertions_death_test, hou_dev_postcond_macro_failure)
{
#ifdef NDEBUG
  EXPECT_NO_ERROR(HOU_DEV_POSTCOND(0 == 2));
#else
  EXPECT_ERROR_0(HOU_DEV_POSTCOND(0 == 2), postcondition_violation);
#endif
}



TEST_F(test_assertions_death_test, expect_postcond_error_macro)
{
  EXPECT_POSTCOND_ERROR(HOU_POSTCOND(0 == 2));
}



TEST_F(test_assertions, invariant_violation)
{
  invariant_violation ex(u8"bananas.ogg", 8888u);
  EXPECT_STREQ(
    u8"bananas.ogg:8888 - An invariant has been violated.", ex.what());
}



TEST_F(test_assertions, hou_invariant_macro_success)
{
  EXPECT_NO_ERROR(HOU_INVARIANT(2 == 2));
}



TEST_F(test_assertions_death_test, hou_invariant_macro_failure)
{
  EXPECT_ERROR_0(HOU_INVARIANT(0 == 2), invariant_violation);
}



TEST_F(test_assertions, hou_dev_invariant_macro_success)
{
#ifdef NDEBUG
  EXPECT_NO_ERROR(HOU_DEV_INVARIANT(2 == 2));
#else
  EXPECT_NO_ERROR(HOU_DEV_INVARIANT(2 == 2));
#endif
}



TEST_F(test_assertions_death_test, hou_dev_invariant_macro_failure)
{
#ifdef NDEBUG
  EXPECT_NO_ERROR(HOU_DEV_INVARIANT(0 == 2));
#else
  EXPECT_ERROR_0(HOU_DEV_INVARIANT(0 == 2), invariant_violation);
#endif
}



TEST_F(test_assertions_death_test, expect_invariant_error_macro)
{
  EXPECT_INVARIANT_ERROR(HOU_INVARIANT(0 == 2));
}



TEST_F(test_assertions, unreachable_error)
{
  unreachable_error ex("foo.cpp", 42u);
  EXPECT_STREQ(
    "foo.cpp:42 - An unreachable part of code has been reached.", ex.what());
}



TEST_F(test_assertions, hou_unreachable_macro)
{
  EXPECT_ERROR_0(HOU_UNREACHABLE(), unreachable_error);
}
