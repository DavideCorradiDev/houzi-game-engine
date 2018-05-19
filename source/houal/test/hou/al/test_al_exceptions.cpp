// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/test_al_base.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_exceptions.hpp"
#include "hou/al/al_object_handle.hpp"

using namespace hou;



namespace
{

class test_al_exceptions : public test_al_base
{};

class test_al_exceptions_death_test : public test_al_exceptions
{};



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



TEST_F(test_al_exceptions, context_creation_error)
{
  al::context_creation_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Failed to create the OpenAL context.", ex.what());
}



TEST_F(test_al_exceptions, context_destruction_error)
{
  al::context_destruction_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Failed to destroy the OpenAL context.", ex.what());
}



TEST_F(test_al_exceptions, context_switch_error)
{
  al::context_switch_error ex("foo.cpp", 42u);
  EXPECT_STREQ(
    "foo.cpp:42 - Failed to switch the current OpenAL context.", ex.what());
}



TEST_F(test_al_exceptions, missing_context_error)
{
  al::missing_context_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - No current OpenAL context.", ex.what());
}



TEST_F(test_al_exceptions, invalid_context_error)
{
  al::invalid_context_error ex("foo.cpp", 42u);
  EXPECT_STREQ(
    "foo.cpp:42 - The current OpenAL context does not own the object.",
    ex.what());
}



TEST_F(test_al_exceptions, call_error)
{
  al::call_error ex0("foo.cpp", 42u, AL_INVALID_ENUM);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL error with code 40962: invalid enum.", ex0.what());

  al::call_error ex1("foo.cpp", 42u, AL_INVALID_NAME);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL error with code 40961: invalid name.", ex1.what());

  al::call_error ex2("foo.cpp", 42u, AL_INVALID_OPERATION);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL error with code 40964: invalid operation.", ex2.what());

  al::call_error ex3("foo.cpp", 42u, AL_INVALID_VALUE);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL error with code 40963: invalid value.", ex3.what());

  al::call_error ex4("foo.cpp", 42u, AL_OUT_OF_MEMORY);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL error with code 40965: out of memory.", ex4.what());

  al::call_error ex5("foo.cpp", 42u, 0);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL error with code 0: unknown error.", ex5.what());
}



TEST_F(test_al_exceptions, context_call_error)
{
  al::context_call_error ex0("foo.cpp", 42u, ALC_INVALID_ENUM);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40963: invalid enum.", ex0.what());

  al::context_call_error ex1("foo.cpp", 42u, ALC_INVALID_VALUE);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40964: invalid value.", ex1.what());

  al::context_call_error ex2("foo.cpp", 42u, ALC_OUT_OF_MEMORY);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40965: out of memory.", ex2.what());

  al::context_call_error ex3("foo.cpp", 42u, ALC_INVALID_CONTEXT);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40962: invalid context.", ex3.what());

  al::context_call_error ex4("foo.cpp", 42u, ALC_INVALID_DEVICE);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40961: invalid device.", ex4.what());

  al::context_call_error ex5("foo.cpp", 42u, 0);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 0: unknown error.", ex5.what());
}



TEST_F(test_al_exceptions, al_check_error_function_success)
{
  alGetString(AL_VERSION);
  EXPECT_NO_ERROR(al::check_error("", 0));
}



TEST_F(test_al_exceptions_death_test, al_check_error_function_failure)
{
  alGetString(AL_INVERSE_DISTANCE);
  EXPECT_ERROR_N(al::check_error("", 0), al::call_error, AL_INVALID_ENUM);
}



TEST_F(test_al_exceptions, al_check_error_macro_success)
{
  alGetString(AL_VERSION);
  EXPECT_NO_ERROR(HOU_AL_CHECK_ERROR());
}



TEST_F(test_al_exceptions_death_test, al_check_error_macro_failure)
{
  alGetString(AL_INVERSE_DISTANCE);
#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  EXPECT_ERROR_N(HOU_AL_CHECK_ERROR(), al::call_error, AL_INVALID_ENUM);
#else
  EXPECT_NO_ERROR(HOU_AL_CHECK_ERROR());
#endif
}



TEST_F(test_al_exceptions, al_check_context_error_function_success)
{
  alcGetString(m_device.get_handle(), ALC_DEVICE_SPECIFIER);
  EXPECT_NO_ERROR(al::check_context_error(m_device, "", 0));
}



TEST_F(test_al_exceptions_death_test, al_check_context_error_function_failure)
{
  alcGetString(m_device.get_handle(), ALC_MAJOR_VERSION);
  EXPECT_ERROR_N(al::check_context_error(m_device, "", 0),
    al::context_call_error, ALC_INVALID_ENUM);
}



TEST_F(test_al_exceptions, al_check_context_error_macro_success)
{
  alcGetString(m_device.get_handle(), ALC_DEVICE_SPECIFIER);
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_ERROR(m_device));
}



TEST_F(test_al_exceptions_death_test, al_check_context_error_macro_failure)
{
  alcGetString(m_device.get_handle(), ALC_MAJOR_VERSION);
#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  EXPECT_ERROR_N(HOU_AL_CHECK_CONTEXT_ERROR(m_device), al::context_call_error,
    ALC_INVALID_ENUM);
#else
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_ERROR(m_device));
#endif
}



TEST_F(test_al_exceptions, al_check_context_existence_function_success)
{
  EXPECT_NO_ERROR(al::check_context_existence("", 0));
}



TEST_F(
  test_al_exceptions_death_test, al_check_context_existence_function_failure)
{
  al::context::unset_current();
  EXPECT_ERROR_0(al::check_context_existence("", 0), al::missing_context_error);
}



TEST_F(test_al_exceptions, al_check_context_existence_macro_success)
{
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_EXISTENCE());
}



TEST_F(test_al_exceptions_death_test, al_check_context_existence_macro_failure)
{
  al::context::unset_current();
#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  EXPECT_ERROR_0(HOU_AL_CHECK_CONTEXT_EXISTENCE(), al::missing_context_error);
#else
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_EXISTENCE());
#endif
}



TEST_F(test_al_exceptions,
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



TEST_F(test_al_exceptions_death_test,
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



TEST_F(test_al_exceptions,
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



TEST_F(test_al_exceptions_death_test,
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



TEST_F(test_al_exceptions,
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



TEST_F(test_al_exceptions_death_test,
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



TEST_F(test_al_exceptions,
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



TEST_F(test_al_exceptions_death_test,
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
