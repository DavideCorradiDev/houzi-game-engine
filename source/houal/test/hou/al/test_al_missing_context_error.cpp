// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/al_missing_context_error.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_al_missing_context_error : public Test
{};

using test_al_missing_context_error_death_test = test_al_missing_context_error;

}  // namespace



TEST_F(test_al_missing_context_error, missing_context_error)
{
  al::missing_context_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - No current OpenAL context.", ex.what());
}



TEST_F(
  test_al_missing_context_error, al_check_context_existence_function_success)
{
  al::device dev;
  al::context ctx(dev);
  al::context::set_current(ctx);
  EXPECT_NO_ERROR(al::check_context_existence("", 0));
}



TEST_F(test_al_missing_context_error_death_test,
  al_check_context_existence_function_failure)
{
  EXPECT_ERROR_0(al::check_context_existence("", 0), al::missing_context_error);
}



TEST_F(test_al_missing_context_error, al_check_context_existence_macro_success)
{
  al::device dev;
  al::context ctx(dev);
  al::context::set_current(ctx);
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_EXISTENCE());
}



TEST_F(test_al_missing_context_error_death_test,
  al_check_context_existence_macro_failure)
{
#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_AL_CHECK_CONTEXT_EXISTENCE(), al::missing_context_error);
#else
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_EXISTENCE());
#endif
}
