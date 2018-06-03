// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/mth/mth_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_mth_exceptions : public Test
{};

class test_mth_exceptions_death_test : public test_mth_exceptions
{};

}  // namespace



TEST_F(test_mth_exceptions, inversion_error)
{
  inversion_error ex("goo.hpp", 1u);
  EXPECT_STREQ("goo.hpp:1 - The object is not invertible.", ex.what());
}
