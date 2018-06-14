// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/key_code.hpp"
#include "hou/sys/modifier_keys.hpp"
#include "hou/sys/scan_code.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_keys : public Test
  {};

}



TEST_F(test_keys, key_code_to_scan_code)
{
  EXPECT_EQ(scan_code::a, get_scan_code(key_code::a));
  EXPECT_EQ(scan_code::unknown, get_scan_code(key_code::ampersand));
  EXPECT_EQ(scan_code::unknown, get_scan_code(key_code::unknown));
}



TEST_F(test_keys, scan_code_to_key_code)
{
  EXPECT_EQ(key_code::a, get_key_code(scan_code::a));
  EXPECT_EQ(key_code::unknown, get_key_code(scan_code::international1));
  EXPECT_EQ(key_code::unknown, get_key_code(scan_code::unknown));
}



TEST_F(test_keys, output_stream_operator)
{
  EXPECT_OUTPUT("", modifier_keys::none);
  EXPECT_OUTPUT("lalt", modifier_keys::lalt);
  EXPECT_OUTPUT("ralt", modifier_keys::ralt);
  EXPECT_OUTPUT("lctrl", modifier_keys::lctrl);
  EXPECT_OUTPUT("rctrl", modifier_keys::rctrl);
  EXPECT_OUTPUT("lshift", modifier_keys::lshift);
  EXPECT_OUTPUT("rshift", modifier_keys::rshift);
  EXPECT_OUTPUT("lsystem", modifier_keys::lsystem);
  EXPECT_OUTPUT("rsystem", modifier_keys::rsystem);
  EXPECT_OUTPUT("num", modifier_keys::num);
  EXPECT_OUTPUT("caps", modifier_keys::caps);
  EXPECT_OUTPUT("mode", modifier_keys::mode);

  EXPECT_OUTPUT("lalt | ralt", modifier_keys::alt);
  EXPECT_OUTPUT("lctrl | rctrl", modifier_keys::ctrl);
  EXPECT_OUTPUT("lshift | rshift", modifier_keys::shift);
  EXPECT_OUTPUT("lsystem | rsystem", modifier_keys::system);

  EXPECT_OUTPUT("lalt | ralt", modifier_keys::lalt | modifier_keys::ralt);
  EXPECT_OUTPUT("lalt | rctrl", modifier_keys::lalt | modifier_keys::rctrl);
  EXPECT_OUTPUT("lalt | rctrl | lshift",
    modifier_keys::lalt | modifier_keys::rctrl | modifier_keys::lshift);
}
