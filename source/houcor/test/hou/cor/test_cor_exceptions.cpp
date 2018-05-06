// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/cor_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_cor_exceptions : public Test
{};

class test_cor_exceptions_death_test : public test_cor_exceptions
{};

}  // namespace



TEST_F(test_cor_exceptions, overflow_error)
{
  overflow_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Numeric overflow.", ex.what());
}



TEST_F(test_cor_exceptions, underflow_error)
{
  underflow_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Numeric underflow.", ex.what());
}
