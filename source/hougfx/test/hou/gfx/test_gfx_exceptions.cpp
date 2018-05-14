// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gfx/gfx_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_gfx_exceptions : public Test
{};

}  // namespace



TEST_F(test_gfx_exceptions, font_creation_error)
{
  font_creation_error ex("foo.cpp", 88u);
  EXPECT_STREQ(
    "foo.cpp:88 - Failed to create the font object.", ex.what());
}



TEST_F(test_gfx_exceptions, font_destruction_error)
{
  font_destruction_error ex("foo.cpp", 88u);
  EXPECT_STREQ(
    "foo.cpp:88 - Failed to destroy the font object.", ex.what());
}



TEST_F(test_gfx_exceptions, font_operation_error)
{
  font_operation_error ex("foo.cpp", 88u);
  EXPECT_STREQ(
    "foo.cpp:88 - Failed to perform an operation on a font object.", ex.what());
}
