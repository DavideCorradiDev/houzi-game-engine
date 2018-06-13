// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/modifier_keys.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_modifier_keys : public Test
  {};

}



TEST_F(test_modifier_keys, output_stream_operator)
{
  EXPECT_OUTPUT("", modifier_keys::none);
  EXPECT_OUTPUT("lalt", modifier_keys::lalt);
  EXPECT_OUTPUT("lalt | rctrl", modifier_keys::lalt | modifier_keys::rctrl);
  EXPECT_OUTPUT("lalt | rctrl | lshift",
    modifier_keys::lalt | modifier_keys::rctrl | modifier_keys::lshift);
}
