// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/core_functions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_core_functions : public Test
{};

}  // namespace



TEST_F(test_core_functions, float_close)
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



TEST_F(test_core_functions, double_close)
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



TEST_F(test_core_functions, stream_enum_class_value)
{
  enum class my_enum_class
  {
    val1 = 12,
    val2 = 14,
  };

  {
    std::stringstream ss;
    stream_enum_class_value(ss, "my_enum_class", my_enum_class::val1);
    EXPECT_EQ("my_enum_class(12)", ss.str());
  }

  {
    std::stringstream ss;
    stream_enum_class_value(ss, "my_enum_class", my_enum_class::val2);
    EXPECT_EQ("my_enum_class(14)", ss.str());
  }

  {
    std::stringstream ss;
    STREAM_ENUM_CLASS_VALUE(ss, my_enum_class, my_enum_class::val1);
    EXPECT_EQ("my_enum_class(12)", ss.str());
  }

  {
    std::stringstream ss;
    STREAM_ENUM_CLASS_VALUE(ss, my_enum_class, my_enum_class::val2);
    EXPECT_EQ("my_enum_class(14)", ss.str());
  }
}
