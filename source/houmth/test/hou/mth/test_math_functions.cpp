// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/mth/math_functions.hpp"

using namespace hou;
using namespace testing;

namespace
{

class test_math_functions : public Test
{};

}  // namespace



TEST_F(test_math_functions, pi_float_value)
{
  EXPECT_FLOAT_EQ(3.14159265358979f, pi_f);
}



TEST_F(test_math_functions, pi_double_value)
{
  EXPECT_FLOAT_EQ(3.14159265358979, pi_d);
}



TEST_F(test_math_functions, deg_rad_float_conversion)
{
  EXPECT_FLOAT_EQ(-pi_f * 2.f, deg_to_rad(-360.f));
  EXPECT_FLOAT_EQ(-pi_f, deg_to_rad(-180.f));
  EXPECT_FLOAT_EQ(-pi_f / 2.f, deg_to_rad(-90.f));
  EXPECT_FLOAT_EQ(-pi_f / 4.f, deg_to_rad(-45.f));
  EXPECT_FLOAT_EQ(0.f, deg_to_rad(0.f));
  EXPECT_FLOAT_EQ(pi_f / 4.f, deg_to_rad(45.f));
  EXPECT_FLOAT_EQ(pi_f / 2.f, deg_to_rad(90.f));
  EXPECT_FLOAT_EQ(pi_f, deg_to_rad(180.f));
  EXPECT_FLOAT_EQ(pi_f * 2.f, deg_to_rad(360.f));

  EXPECT_FLOAT_EQ(-360.f, rad_to_deg(-pi_f * 2.f));
  EXPECT_FLOAT_EQ(-180.f, rad_to_deg(-pi_f));
  EXPECT_FLOAT_EQ(-90.f, rad_to_deg(-pi_f / 2.f));
  EXPECT_FLOAT_EQ(-45.f, rad_to_deg(-pi_f / 4.f));
  EXPECT_FLOAT_EQ(0.f, rad_to_deg(0.f));
  EXPECT_FLOAT_EQ(45.f, rad_to_deg(pi_f / 4.f));
  EXPECT_FLOAT_EQ(90.f, rad_to_deg(pi_f / 2.f));
  EXPECT_FLOAT_EQ(180.f, rad_to_deg(pi_f));
  EXPECT_FLOAT_EQ(360.f, rad_to_deg(pi_f * 2.f));

  EXPECT_FLOAT_EQ(1.356f, deg_to_rad(rad_to_deg(1.356f)));
  EXPECT_FLOAT_EQ(-23.74f, rad_to_deg(deg_to_rad(-23.74f)));
}



TEST_F(test_math_functions, deg_rad_double_conversion)
{
  EXPECT_DOUBLE_EQ(-pi_d * 2., deg_to_rad(-360.));
  EXPECT_DOUBLE_EQ(-pi_d, deg_to_rad(-180.));
  EXPECT_DOUBLE_EQ(-pi_d / 2., deg_to_rad(-90.));
  EXPECT_DOUBLE_EQ(-pi_d / 4., deg_to_rad(-45.));
  EXPECT_DOUBLE_EQ(0., deg_to_rad(0.));
  EXPECT_DOUBLE_EQ(pi_d / 4., deg_to_rad(45.));
  EXPECT_DOUBLE_EQ(pi_d / 2., deg_to_rad(90.));
  EXPECT_DOUBLE_EQ(pi_d, deg_to_rad(180.));
  EXPECT_DOUBLE_EQ(pi_d * 2., deg_to_rad(360.));

  EXPECT_DOUBLE_EQ(-360., rad_to_deg(-pi_d * 2.));
  EXPECT_DOUBLE_EQ(-180., rad_to_deg(-pi_d));
  EXPECT_DOUBLE_EQ(-90., rad_to_deg(-pi_d / 2.));
  EXPECT_DOUBLE_EQ(-45., rad_to_deg(-pi_d / 4.));
  EXPECT_DOUBLE_EQ(0., rad_to_deg(0.));
  EXPECT_DOUBLE_EQ(45., rad_to_deg(pi_d / 4.));
  EXPECT_DOUBLE_EQ(90., rad_to_deg(pi_d / 2.));
  EXPECT_DOUBLE_EQ(180., rad_to_deg(pi_d));
  EXPECT_DOUBLE_EQ(360., rad_to_deg(pi_d * 2.));

  EXPECT_DOUBLE_EQ(1.35, deg_to_rad(rad_to_deg(1.35)));
  EXPECT_DOUBLE_EQ(-23.7, rad_to_deg(deg_to_rad(-23.7)));
}



TEST_F(test_math_functions, log_float)
{
  EXPECT_FLOAT_EQ(-3.f, log(0.125f, 2));
  EXPECT_FLOAT_EQ(-2.f, log(0.25f, 2));
  EXPECT_FLOAT_EQ(-1.f, log(0.5f, 2));
  EXPECT_FLOAT_EQ(0.f, log(1.f, 2));
  EXPECT_FLOAT_EQ(1.f, log(2.f, 2));
  EXPECT_FLOAT_EQ(2.f, log(4.f, 2));
  EXPECT_FLOAT_EQ(3.f, log(8.f, 2));
  EXPECT_FLOAT_EQ(4.f, log(16.f, 2));

  EXPECT_FLOAT_EQ(-3.f, log(0.008f, 5));
  EXPECT_FLOAT_EQ(-2.f, log(0.04f, 5));
  EXPECT_FLOAT_EQ(-1.f, log(0.2f, 5));
  EXPECT_FLOAT_EQ(0.f, log(1.f, 5));
  EXPECT_FLOAT_EQ(1.f, log(5.f, 5));
  EXPECT_FLOAT_EQ(2.f, log(25.f, 5));
  EXPECT_FLOAT_EQ(3.f, log(125.f, 5));
  EXPECT_FLOAT_EQ(4.f, log(625.f, 5));

  EXPECT_TRUE(std::isnan(log(2.f, -2)));
  EXPECT_TRUE(std::isnan(log(-2.f, 2)));
  EXPECT_TRUE(std::isnan(log(-2.f, -2)));
}



TEST_F(test_math_functions, log_double)
{
  EXPECT_DOUBLE_EQ(-3., log(0.125, 2));
  EXPECT_DOUBLE_EQ(-2., log(0.25, 2));
  EXPECT_DOUBLE_EQ(-1., log(0.5, 2));
  EXPECT_DOUBLE_EQ(0., log(1., 2));
  EXPECT_DOUBLE_EQ(1., log(2., 2));
  EXPECT_DOUBLE_EQ(2., log(4., 2));
  EXPECT_DOUBLE_EQ(3., log(8., 2));
  EXPECT_DOUBLE_EQ(4., log(16., 2));

  EXPECT_DOUBLE_EQ(-3., log(0.008, 5));
  EXPECT_DOUBLE_EQ(-2., log(0.04, 5));
  EXPECT_DOUBLE_EQ(-1., log(0.2, 5));
  EXPECT_DOUBLE_EQ(0., log(1., 5));
  EXPECT_DOUBLE_EQ(1., log(5., 5));
  EXPECT_DOUBLE_EQ(2., log(25., 5));
  EXPECT_DOUBLE_EQ(3., log(125., 5));
  EXPECT_DOUBLE_EQ(4., log(625., 5));

  EXPECT_TRUE(std::isnan(log(2., -2)));
  EXPECT_TRUE(std::isnan(log(-2., 2)));
  EXPECT_TRUE(std::isnan(log(-2., -2)));
}
