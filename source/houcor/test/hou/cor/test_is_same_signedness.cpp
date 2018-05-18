// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/is_same_signedness.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_is_same_signedness : public Test
{};

}  // namespace



TEST_F(test_is_same_signedness, int_int)
{
  using is_same_signedness = is_same_signedness<int, int>;
  EXPECT_TRUE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, int_uint)
{
  using is_same_signedness = is_same_signedness<int, uint>;
  EXPECT_FALSE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, int_float)
{
  using is_same_signedness = is_same_signedness<int, float>;
  EXPECT_TRUE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, int_uchar)
{
  using is_same_signedness = is_same_signedness<int, uchar>;
  EXPECT_FALSE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, uint_int)
{
  using is_same_signedness = is_same_signedness<uint, int>;
  EXPECT_FALSE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, uint_uint)
{
  using is_same_signedness = is_same_signedness<uint, uint>;
  EXPECT_TRUE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, uint_float)
{
  using is_same_signedness = is_same_signedness<uint, float>;
  EXPECT_FALSE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, uint_uchar)
{
  using is_same_signedness = is_same_signedness<uint, uchar>;
  EXPECT_TRUE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, float_int)
{
  using is_same_signedness = is_same_signedness<float, int>;
  EXPECT_TRUE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, float_uint)
{
  using is_same_signedness = is_same_signedness<float, uint>;
  EXPECT_FALSE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, float_float)
{
  using is_same_signedness = is_same_signedness<float, float>;
  EXPECT_TRUE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, float_uchar)
{
  using is_same_signedness = is_same_signedness<float, uchar>;
  EXPECT_FALSE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, uchar_int)
{
  using is_same_signedness = is_same_signedness<uchar, int>;
  EXPECT_FALSE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, uchar_uint)
{
  using is_same_signedness = is_same_signedness<uchar, uint>;
  EXPECT_TRUE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, uchar_float)
{
  using is_same_signedness = is_same_signedness<uchar, float>;
  EXPECT_FALSE(is_same_signedness::value);
}



TEST_F(test_is_same_signedness, uchar_uchar)
{
  using is_same_signedness = is_same_signedness<uchar, uchar>;
  EXPECT_TRUE(is_same_signedness::value);
}
