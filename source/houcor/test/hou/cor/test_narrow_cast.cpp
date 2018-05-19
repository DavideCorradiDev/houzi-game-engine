// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/narrow_cast.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_narrow_cast : public Test
{};

class test_narrow_cast_death_test : public Test
{};

}  // namespace



TEST_F(test_narrow_cast, int_to_uint_success)
{
  EXPECT_EQ(0u, narrow_cast<uint>(int(0)));
  EXPECT_EQ(42u, narrow_cast<uint>(int(42)));
  EXPECT_EQ(static_cast<uint>(std::numeric_limits<int>::max()),
    narrow_cast<uint>(std::numeric_limits<int>::max()));
}



TEST_F(test_narrow_cast_death_test, int_to_uint_failure)
{
  EXPECT_ERROR_0(narrow_cast<uint>(int(-1)), narrowing_error);
}



TEST_F(test_narrow_cast, uint_to_int_success)
{
  EXPECT_EQ(0, narrow_cast<int>(uint(0)));
  EXPECT_EQ(42, narrow_cast<int>(uint(42)));
  EXPECT_EQ(std::numeric_limits<int>::max(),
    static_cast<int>(narrow_cast<uint>(std::numeric_limits<int>::max())));
}



TEST_F(test_narrow_cast_death_test, uint_to_int_failure)
{
  EXPECT_ERROR_0(
    narrow_cast<int>(static_cast<uint>(std::numeric_limits<int>::max()) + 1u),
    narrowing_error);
}



TEST_F(test_narrow_cast, int_to_float_success)
{
  EXPECT_FLOAT_EQ(0.f, narrow_cast<float>(int(0)));
  EXPECT_FLOAT_EQ(42.f, narrow_cast<float>(int(42)));
}



TEST_F(test_narrow_cast, float_to_int_success)
{
  EXPECT_EQ(0, narrow_cast<int>(float(0.f)));
  EXPECT_EQ(-88, narrow_cast<int>(float(-88.f)));
  EXPECT_EQ(42, narrow_cast<int>(float(42.f)));
}



TEST_F(test_narrow_cast_death_test, float_to_int_failure)
{
  EXPECT_ERROR_0(narrow_cast<int>(float(2.5f)), narrowing_error);
  EXPECT_ERROR_0(
    narrow_cast<int>(std::numeric_limits<float>::max()), narrowing_error);
}



TEST_F(test_narrow_cast, float_to_uint_success)
{
  EXPECT_EQ(0u, narrow_cast<uint>(float(0.f)));
  EXPECT_EQ(42u, narrow_cast<uint>(float(42.f)));
}



TEST_F(test_narrow_cast_death_test, float_to_uint_failure)
{
  EXPECT_ERROR_0(narrow_cast<uint>(float(2.5f)), narrowing_error);
  EXPECT_ERROR_0(narrow_cast<uint>(float(-88.f)), narrowing_error);
  EXPECT_ERROR_0(
    narrow_cast<uint>(std::numeric_limits<float>::max()), narrowing_error);
}
