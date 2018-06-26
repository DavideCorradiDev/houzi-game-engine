// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/test_al_base.hpp"

#include "hou/al/al_exceptions.hpp"

using namespace hou;



namespace
{

class test_al_exceptions : public test_al_base
{};

using test_al_exceptions_death_test = test_al_exceptions;

}  // namespace



TEST_F(test_al_exceptions, call_error)
{
  al::call_error ex0("foo.cpp", 42u, AL_INVALID_ENUM);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL error with code 40962: invalid enum.", ex0.what());

  al::call_error ex1("foo.cpp", 42u, AL_INVALID_NAME);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL error with code 40961: invalid name.", ex1.what());

  al::call_error ex2("foo.cpp", 42u, AL_INVALID_OPERATION);
  EXPECT_STREQ("foo.cpp:42 - OpenAL error with code 40964: invalid operation.",
    ex2.what());

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
    "foo.cpp:42 - OpenAL context error with code 40963: invalid enum.",
    ex0.what());

  al::context_call_error ex1("foo.cpp", 42u, ALC_INVALID_VALUE);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40964: invalid value.",
    ex1.what());

  al::context_call_error ex2("foo.cpp", 42u, ALC_OUT_OF_MEMORY);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40965: out of memory.",
    ex2.what());

  al::context_call_error ex3("foo.cpp", 42u, ALC_INVALID_CONTEXT);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40962: invalid context.",
    ex3.what());

  al::context_call_error ex4("foo.cpp", 42u, ALC_INVALID_DEVICE);
  EXPECT_STREQ(
    "foo.cpp:42 - OpenAL context error with code 40961: invalid device.",
    ex4.what());

  al::context_call_error ex5("foo.cpp", 42u, 0);
  EXPECT_STREQ("foo.cpp:42 - OpenAL context error with code 0: unknown error.",
    ex5.what());
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
  alcGetString(m_device.get_impl(), ALC_DEVICE_SPECIFIER);
  EXPECT_NO_ERROR(al::check_context_error(m_device, "", 0));
}



TEST_F(test_al_exceptions_death_test, al_check_context_error_function_failure)
{
  alcGetString(m_device.get_impl(), ALC_MAJOR_VERSION);
  EXPECT_ERROR_N(al::check_context_error(m_device, "", 0),
    al::context_call_error, ALC_INVALID_ENUM);
}



TEST_F(test_al_exceptions, al_check_context_error_macro_success)
{
  alcGetString(m_device.get_impl(), ALC_DEVICE_SPECIFIER);
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_ERROR(m_device));
}



TEST_F(test_al_exceptions_death_test, al_check_context_error_macro_failure)
{
  alcGetString(m_device.get_impl(), ALC_MAJOR_VERSION);
#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  EXPECT_ERROR_N(HOU_AL_CHECK_CONTEXT_ERROR(m_device), al::context_call_error,
    ALC_INVALID_ENUM);
#else
  EXPECT_NO_ERROR(HOU_AL_CHECK_CONTEXT_ERROR(m_device));
#endif
}
