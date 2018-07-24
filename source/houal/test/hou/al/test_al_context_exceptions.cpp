// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/al/al_context_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_al_context_exceptions : public Test
{};

class test_al_context_exceptions_death_test : public test_al_context_exceptions
{};

}  // namespace



TEST_F(test_al_context_exceptions, context_creation_error)
{
  al::context_creation_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Failed to create the OpenAL context.", ex.what());
}



TEST_F(test_al_context_exceptions, context_destruction_error)
{
  al::context_destruction_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Failed to destroy the OpenAL context.", ex.what());
}



TEST_F(test_al_context_exceptions, context_switch_error)
{
  al::context_switch_error ex("foo.cpp", 42u);
  EXPECT_STREQ(
    "foo.cpp:42 - Failed to switch the current OpenAL context.", ex.what());
}



TEST_F(test_al_context_exceptions, device_open_error)
{
  al::device_open_error ex("foo.cpp", 42u, "awesome_device");
  EXPECT_STREQ(
    "foo.cpp:42 - Failed to open the OpenAL device 'awesome_device'.",
    ex.what());
}



TEST_F(test_al_context_exceptions, device_close_error)
{
  al::device_close_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Failed to close the OpenAL device.", ex.what());
}
