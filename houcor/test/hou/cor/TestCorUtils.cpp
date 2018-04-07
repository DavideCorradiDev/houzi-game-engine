// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/cor/CorUtils.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestCorUtils : public Test {};

}



TEST_F(TestCorUtils, FloatClose)
{
  float f1 = 1.2345f;
  float f2 = 1.2345f;
  float f3 = 1.2347f;
  float f4 = 1.2365f;

  EXPECT_TRUE(close(f1, f2));
  EXPECT_FALSE(close(f1, f3));
  EXPECT_FALSE(close(f1, f4));

  EXPECT_TRUE(close(f1, f2, 1e-4f));
  EXPECT_FALSE(close(f1, f3, 1e-4f));
  EXPECT_FALSE(close(f1, f4, 1e-4f));

  EXPECT_TRUE(close(f1, f2, 1e-3f));
  EXPECT_TRUE(close(f1, f3, 1e-3f));
  EXPECT_FALSE(close(f1, f4, 1e-3f));

  EXPECT_TRUE(close(f1, f2, 1e-2f));
  EXPECT_TRUE(close(f1, f3, 1e-2f));
  EXPECT_TRUE(close(f1, f4, 1e-2f));
}



TEST_F(TestCorUtils, DoubleClose)
{
  double f1 = 1.234567891;
  double f2 = 1.234567891;
  double f3 = 1.234567893;
  double f4 = 1.236567891;

  EXPECT_TRUE(close(f1, f2));
  EXPECT_FALSE(close(f1, f3));
  EXPECT_FALSE(close(f1, f4));

  EXPECT_TRUE(close(f1, f2, 1e-9));
  EXPECT_FALSE(close(f1, f3, 1e-9));
  EXPECT_FALSE(close(f1, f4, 1e-9));

  EXPECT_TRUE(close(f1, f2, 1e-8));
  EXPECT_TRUE(close(f1, f3, 1e-8));
  EXPECT_FALSE(close(f1, f4, 1e-8));

  EXPECT_TRUE(close(f1, f2, 1e-2));
  EXPECT_TRUE(close(f1, f3, 1e-2));
  EXPECT_TRUE(close(f1, f4, 1e-2));
}

