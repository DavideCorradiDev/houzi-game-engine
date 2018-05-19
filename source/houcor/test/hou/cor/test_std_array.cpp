// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/std_array.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_std_array : public Test {};

}



TEST_F(test_std_array, array_float_close)
{
  std::array<float, 2u> a1{1.3456f, 2.12f};
  std::array<float, 2u> a2(a1);
  std::array<float, 2u> a3{1.3451f, 2.12f};
  std::array<float, 2u> a4{1.3426f, 2.12f};

  EXPECT_TRUE(close<float>(a1, a2));
  EXPECT_FALSE(close<float>(a1, a3));
  EXPECT_FALSE(close<float>(a1, a4));

  EXPECT_TRUE(close(a1, a2, 1e-4f));
  EXPECT_FALSE(close(a1, a3, 1e-4f));
  EXPECT_FALSE(close(a1, a4, 1e-4f));

  EXPECT_TRUE(close(a1, a2, 1e-3f));
  EXPECT_TRUE(close(a1, a3, 1e-3f));
  EXPECT_FALSE(close(a1, a4, 1e-3f));

  EXPECT_TRUE(close(a1, a2, 1e-2f));
  EXPECT_TRUE(close(a1, a3, 1e-2f));
  EXPECT_TRUE(close(a1, a4, 1e-2f));
}



TEST_F(test_std_array, array_double_close)
{
  std::array<double, 2u> a1{1.345612345, 2.12};
  std::array<double, 2u> a2(a1);
  std::array<double, 2u> a3{1.345612349, 2.12};
  std::array<double, 2u> a4{1.345112345, 2.12};

  EXPECT_TRUE(close<double>(a1, a2));
  EXPECT_FALSE(close<double>(a1, a3));
  EXPECT_FALSE(close<double>(a1, a4));

  EXPECT_TRUE(close(a1, a2, 1e-9));
  EXPECT_FALSE(close(a1, a3, 1e-9));
  EXPECT_FALSE(close(a1, a4, 1e-9));

  EXPECT_TRUE(close(a1, a2, 1e-8));
  EXPECT_TRUE(close(a1, a3, 1e-8));
  EXPECT_FALSE(close(a1, a4, 1e-8));

  EXPECT_TRUE(close(a1, a2, 1e-3));
  EXPECT_TRUE(close(a1, a3, 1e-3));
  EXPECT_TRUE(close(a1, a4, 1e-3));
}



TEST_F(test_std_array, array_output_stream_operator)
{
  std::array<float, 3u> v{1.f, 2.5, -12.71f};
  EXPECT_OUTPUT("{1, 2.5, -12.71}", v);
}

