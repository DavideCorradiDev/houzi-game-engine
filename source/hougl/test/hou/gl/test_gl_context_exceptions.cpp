// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_context_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_gl_context_exceptions : public test_gl_single_context
{};

class test_gl_context_exceptions_death_test : public test_gl_context_exceptions
{};

}  // namespace



TEST_F(test_gl_context_exceptions, context_creation_error)
{
  gl::context_creation_error ex("foo.cpp", 42u, "Bzzz.");
  EXPECT_STREQ(
    "foo.cpp:42 - Failed to create the OpenGL context.\nBzzz.", ex.what());
}



TEST_F(test_gl_context_exceptions, context_switch_error)
{
  gl::context_switch_error ex("foo.cpp", 42u, "Oh noes!");
  EXPECT_STREQ(
    "foo.cpp:42 - Failed to switch the current OpenGL context.\nOh noes!",
    ex.what());
}
