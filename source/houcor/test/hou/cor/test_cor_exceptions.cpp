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



TEST_F(test_cor_exceptions, out_of_range)
{
  out_of_range ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Index out of range.", ex.what());
}



TEST_F(test_cor_exceptions, bad_union_access)
{
  bad_union_access ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Bad union access.", ex.what());
}



TEST_F(test_cor_exceptions, narrowing_error)
{
  narrowing_error ex("foo.cpp", 42u);
  EXPECT_STREQ("foo.cpp:42 - Narrowing type cast.", ex.what());
}
