// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/mth/MthUtils.hpp"

using namespace hou;
using namespace testing;

namespace
{

class TestMathUtils : public Test {};

}



TEST_F(TestMathUtils, PiFloatValue)
{
  EXPECT_FLOAT_EQ(3.14159265358979f, PI_F);
}



TEST_F(TestMathUtils, PiDoubleValue)
{
  EXPECT_FLOAT_EQ(3.14159265358979, PI_D);
}



TEST_F(TestMathUtils, DegRadFloatConversion)
{
  EXPECT_FLOAT_EQ(-PI_F * 2.f, degToRad(-360.f));
  EXPECT_FLOAT_EQ(-PI_F, degToRad(-180.f));
  EXPECT_FLOAT_EQ(-PI_F / 2.f, degToRad(-90.f));
  EXPECT_FLOAT_EQ(-PI_F / 4.f, degToRad(-45.f));
  EXPECT_FLOAT_EQ(0.f, degToRad(0.f));
  EXPECT_FLOAT_EQ(PI_F / 4.f, degToRad(45.f));
  EXPECT_FLOAT_EQ(PI_F / 2.f, degToRad(90.f));
  EXPECT_FLOAT_EQ(PI_F, degToRad(180.f));
  EXPECT_FLOAT_EQ(PI_F * 2.f, degToRad(360.f));

  EXPECT_FLOAT_EQ(-360.f, radToDeg(-PI_F * 2.f));
  EXPECT_FLOAT_EQ(-180.f, radToDeg(-PI_F));
  EXPECT_FLOAT_EQ(-90.f, radToDeg(-PI_F / 2.f));
  EXPECT_FLOAT_EQ(-45.f, radToDeg(-PI_F / 4.f));
  EXPECT_FLOAT_EQ(0.f, radToDeg(0.f));
  EXPECT_FLOAT_EQ(45.f, radToDeg(PI_F / 4.f));
  EXPECT_FLOAT_EQ(90.f, radToDeg(PI_F / 2.f));
  EXPECT_FLOAT_EQ(180.f, radToDeg(PI_F));
  EXPECT_FLOAT_EQ(360.f, radToDeg(PI_F * 2.f));

  EXPECT_FLOAT_EQ(1.356f, degToRad(radToDeg(1.356f)));
  EXPECT_FLOAT_EQ(-23.74f, radToDeg(degToRad(-23.74f)));
}



TEST_F(TestMathUtils, DegRadDoubleConversion)
{
  EXPECT_DOUBLE_EQ(-PI_D * 2., degToRad(-360.));
  EXPECT_DOUBLE_EQ(-PI_D, degToRad(-180.));
  EXPECT_DOUBLE_EQ(-PI_D / 2., degToRad(-90.));
  EXPECT_DOUBLE_EQ(-PI_D / 4., degToRad(-45.));
  EXPECT_DOUBLE_EQ(0., degToRad(0.));
  EXPECT_DOUBLE_EQ(PI_D / 4., degToRad(45.));
  EXPECT_DOUBLE_EQ(PI_D / 2., degToRad(90.));
  EXPECT_DOUBLE_EQ(PI_D, degToRad(180.));
  EXPECT_DOUBLE_EQ(PI_D * 2., degToRad(360.));

  EXPECT_DOUBLE_EQ(-360., radToDeg(-PI_D * 2.));
  EXPECT_DOUBLE_EQ(-180., radToDeg(-PI_D));
  EXPECT_DOUBLE_EQ(-90., radToDeg(-PI_D / 2.));
  EXPECT_DOUBLE_EQ(-45., radToDeg(-PI_D / 4.));
  EXPECT_DOUBLE_EQ(0., radToDeg(0.));
  EXPECT_DOUBLE_EQ(45., radToDeg(PI_D / 4.));
  EXPECT_DOUBLE_EQ(90., radToDeg(PI_D / 2.));
  EXPECT_DOUBLE_EQ(180., radToDeg(PI_D));
  EXPECT_DOUBLE_EQ(360., radToDeg(PI_D * 2.));

  EXPECT_DOUBLE_EQ(1.35, degToRad(radToDeg(1.35)));
  EXPECT_DOUBLE_EQ(-23.7, radToDeg(degToRad(-23.7)));
}



TEST_F(TestMathUtils, LogFloat)
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



TEST_F(TestMathUtils, LogDouble)
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

