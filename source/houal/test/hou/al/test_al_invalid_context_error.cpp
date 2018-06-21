// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/test_al_base.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_invalid_context_error.hpp".hpp"
#include "hou/al/al_object_handle.hpp"

using namespace hou;



namespace
{

class test_al_invalid_context_error : public test_al_base
{};

using test_al_invalid_context_error_death_test = test_al_invalid_context_error;



class concrete_device_owned_object_handle
  : public al::device_owned_object_handle
{
public:
  concrete_device_owned_object_handle(ALuint name)
    : al::device_owned_object_handle(name)
  {}
};



class concrete_context_owned_object_handle
  : public al::context_owned_object_handle
{
public:
  concrete_context_owned_object_handle(ALuint name)
    : al::context_owned_object_handle(name)
  {}
};

}  // namespace



TEST_F(test_al_invalid_context_error, invalid_context_error)
{
  al::invalid_context_error ex("foo.cpp", 42u);
  EXPECT_STREQ(
    "foo.cpp:42 - The current OpenAL context does not own the object.",
    ex.what());
}



TEST_F(test_al_invalid_context_error,
  al_check_context_ownership_device_owned_object_function_success)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_device_owned_object_handle o1(1u);
  EXPECT_NO_ERROR(al::check_context_ownership(o1, "", 0));

  al::context::set_current(c2);
  concrete_device_owned_object_handle o2(1u);
  EXPECT_NO_ERROR(al::check_context_ownership(o2, "", 0));
}



TEST_F(test_al_invalid_context_error_death_test,
  al_check_context_ownership_device_owned_object_function_failure)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_device_owned_object_handle o1(1u);

  al::context::set_current(c2);
  EXPECT_ERROR_0(
    al::check_context_ownership(o1, "", 0), al::invalid_context_error);
}



TEST_F(test_al_invalid_context_error,
  al_check_context_ownership_device_owned_object_macro_success)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_device_owned_object_handle o1(1u);
  al::check_context_ownership(o1, "", 0);
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1));

  al::context::set_current(c2);
  concrete_device_owned_object_handle o2(1u);
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o2));
}



TEST_F(test_al_invalid_context_error_death_test,
  al_check_context_ownership_device_owned_object_macro_failure)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_device_owned_object_handle o1(1u);

  al::context::set_current(c2);

#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1), al::invalid_context_error);
#else
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1));
#endif
}



TEST_F(test_al_invalid_context_error,
  al_check_context_ownership_context_owned_object_function_success)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_context_owned_object_handle o1(1u);
  EXPECT_NO_ERROR(al::check_context_ownership(o1, "", 0));

  al::context::set_current(c2);
  concrete_context_owned_object_handle o2(1u);
  EXPECT_NO_ERROR(al::check_context_ownership(o2, "", 0));
}



TEST_F(test_al_invalid_context_error_death_test,
  al_check_context_ownership_context_owned_object_function_failure)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_context_owned_object_handle o1(1u);

  al::context::set_current(c2);
  EXPECT_ERROR_0(
    al::check_context_ownership(o1, "", 0), al::invalid_context_error);
}



TEST_F(test_al_invalid_context_error,
  al_check_context_ownership_context_owned_object_macro_success)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_context_owned_object_handle o1(1u);
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1));

  al::context::set_current(c2);
  concrete_context_owned_object_handle o2(1u);
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o2));
}



TEST_F(test_al_invalid_context_error_death_test,
  al_check_context_ownership_context_owned_object_macro_failure)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_context_owned_object_handle o1(1u);

  al::context::set_current(c2);
#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1), al::invalid_context_error);
#else
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1));
#endif
}
