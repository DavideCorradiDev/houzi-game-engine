// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/StdVector.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestStdVector : public Test {};

}



TEST_F(TestStdVector, VectorFloatClose)
{
  std::vector<float> v1{1.3456f, 2.12f};
  std::vector<float> v2(v1);
  std::vector<float> v3{1.3451f, 2.12f};
  std::vector<float> v4{1.3426f, 2.12f};
  std::vector<float> v5{1.3456f};
  std::vector<float> v6{1.3456f, 2.12f, 4.22f};

  EXPECT_TRUE(close<float>(v1, v2));
  EXPECT_FALSE(close<float>(v1, v3));
  EXPECT_FALSE(close<float>(v1, v4));
  EXPECT_FALSE(close<float>(v1, v5));
  EXPECT_FALSE(close<float>(v1, v6));

  EXPECT_TRUE(close(v1, v2, 1e-4f));
  EXPECT_FALSE(close(v1, v3, 1e-4f));
  EXPECT_FALSE(close(v1, v4, 1e-4f));
  EXPECT_FALSE(close(v1, v5, 1e-4f));
  EXPECT_FALSE(close(v1, v6, 1e-4f));

  EXPECT_TRUE(close(v1, v2, 1e-3f));
  EXPECT_TRUE(close(v1, v3, 1e-3f));
  EXPECT_FALSE(close(v1, v4, 1e-3f));
  EXPECT_FALSE(close(v1, v5, 1e-3f));
  EXPECT_FALSE(close(v1, v6, 1e-3f));

  EXPECT_TRUE(close(v1, v2, 1e-2f));
  EXPECT_TRUE(close(v1, v3, 1e-2f));
  EXPECT_TRUE(close(v1, v4, 1e-2f));
  EXPECT_FALSE(close(v1, v5, 1e-2f));
  EXPECT_FALSE(close(v1, v6, 1e-2f));
}



TEST_F(TestStdVector, VectorDoubleClose)
{
  std::vector<double> v1{1.345612345, 2.12};
  std::vector<double> v2(v1);
  std::vector<double> v3{1.345612349, 2.12};
  std::vector<double> v4{1.345112345, 2.12};
  std::vector<double> v5{1.345612345};
  std::vector<double> v6{1.345612345, 2.12, 4.22};

  EXPECT_TRUE(close<double>(v1, v2));
  EXPECT_FALSE(close<double>(v1, v3));
  EXPECT_FALSE(close<double>(v1, v4));
  EXPECT_FALSE(close<double>(v1, v5));
  EXPECT_FALSE(close<double>(v1, v6));

  EXPECT_TRUE(close(v1, v2, 1e-9));
  EXPECT_FALSE(close(v1, v3, 1e-9));
  EXPECT_FALSE(close(v1, v4, 1e-9));
  EXPECT_FALSE(close(v1, v5, 1e-9));
  EXPECT_FALSE(close(v1, v6, 1e-9));

  EXPECT_TRUE(close(v1, v2, 1e-8));
  EXPECT_TRUE(close(v1, v3, 1e-8));
  EXPECT_FALSE(close(v1, v4, 1e-8));
  EXPECT_FALSE(close(v1, v5, 1e-8));
  EXPECT_FALSE(close(v1, v6, 1e-8));

  EXPECT_TRUE(close(v1, v2, 1e-3));
  EXPECT_TRUE(close(v1, v3, 1e-3));
  EXPECT_TRUE(close(v1, v4, 1e-3));
  EXPECT_FALSE(close(v1, v5, 1e-3));
  EXPECT_FALSE(close(v1, v6, 1e-3));
}



TEST_F(TestStdVector, VectorOutputStreamOperator)
{
  std::vector<float> v{1.f, 2.5};
  HOU_EXPECT_OUTPUT("{1, 2.5}", v);
}

