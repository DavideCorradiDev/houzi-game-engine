// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/core_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_core_exceptions : public Test
{};

}  // namespace



TEST_F(test_core_exceptions, precondition_violated)
{
  precondition_violated ex(u8"monkeys.txt", 88u);
  EXPECT_STREQ(
    u8"monkeys.txt:88 - A precondition has been violated.", ex.what());
}



TEST_F(test_core_exceptions, postcondition_violated)
{
  postcondition_violated ex(u8"love.jpg", 888u);
  EXPECT_STREQ(
    u8"love.jpg:888 - A postcondition has been violated.", ex.what());
}



TEST_F(test_core_exceptions, invariant_violated)
{
  invariant_violated ex(u8"bananas.ogg", 8888u);
  EXPECT_STREQ(
    u8"bananas.ogg:8888 - An invariant has been violated.", ex.what());
}
