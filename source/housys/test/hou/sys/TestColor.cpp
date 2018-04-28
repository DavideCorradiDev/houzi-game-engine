// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/sys/Color.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestColor : public Test {};

}



TEST_F(TestColor, ValueConstructor)
{
  Color c(20u, 30u, 40u, 50u);
  EXPECT_EQ(20u, c.getRed());
  EXPECT_EQ(30u, c.getGreen());
  EXPECT_EQ(40u, c.getBlue());
  EXPECT_EQ(50u, c.getAlpha());
  EXPECT_EQ(20u, static_cast<uint8_t>(255.f * c.getRedf()));
  EXPECT_EQ(30u, static_cast<uint8_t>(255.f * c.getGreenf()));
  EXPECT_EQ(40u, static_cast<uint8_t>(255.f * c.getBluef()));
  EXPECT_EQ(50u, static_cast<uint8_t>(255.f * c.getAlphaf()));
}



TEST_F(TestColor, SetRed)
{
  Color c(20u, 30u, 40u, 50u);
  c.setRed(100u);
  EXPECT_EQ(100u, c.getRed());
  EXPECT_EQ(100u, static_cast<uint8_t>(c.getRedf() * 255.f));
  c.setRedf(0.5f);
  EXPECT_EQ(127, c.getRed());
  EXPECT_EQ(127, static_cast<uint8_t>(c.getRedf() * 255.f));
}



TEST_F(TestColor, SetGreen)
{
  Color c(20u, 30u, 40u, 50u);
  c.setGreen(100u);
  EXPECT_EQ(100u, c.getGreen());
  EXPECT_EQ(100u, static_cast<uint8_t>(c.getGreenf() * 255.f));
  c.setGreenf(0.5f);
  EXPECT_EQ(127, c.getGreen());
  EXPECT_EQ(127, static_cast<uint8_t>(c.getGreenf() * 255.f));
}



TEST_F(TestColor, SetBlue)
{
  Color c(20u, 30u, 40u, 50u);
  c.setBlue(100u);
  EXPECT_EQ(100u, c.getBlue());
  EXPECT_EQ(100u, static_cast<uint8_t>(c.getBluef() * 255.f));
  c.setBluef(0.5f);
  EXPECT_EQ(127, c.getBlue());
  EXPECT_EQ(127, static_cast<uint8_t>(c.getBluef() * 255.f));
}



TEST_F(TestColor, SetAlpha)
{
  Color c(20u, 30u, 40u, 50u);
  c.setAlpha(100u);
  EXPECT_EQ(100u, c.getAlpha());
  EXPECT_EQ(100u, static_cast<uint8_t>(c.getAlphaf() * 255.f));
  c.setAlphaf(0.5f);
  EXPECT_EQ(127, c.getAlpha());
  EXPECT_EQ(127, static_cast<uint8_t>(c.getAlphaf() * 255.f));
}



TEST_F(TestColor, FloatConversion)
{
  Color c(0u, 0u, 0u, 0u);
  for(uint i = 0; i < 256; ++i)
  {
    c.setRed(i);
    EXPECT_EQ(i, static_cast<uint8_t>(255.f * c.getRedf()));
    c.setRedf(c.getRedf());
    EXPECT_EQ(i, c.getRed());
  }
}



TEST_F(TestColor, FloatValueThresholds)
{
  Color c(0u, 0u, 0u, 0u);
  c.setRedf(1.1f);
  EXPECT_FLOAT_EQ(1.f, c.getRedf());
  EXPECT_EQ(255u, c.getRed());
  c.setRedf(-0.1f);
  EXPECT_FLOAT_EQ(0.f, c.getRedf());
  EXPECT_EQ(0u, c.getRed());
}



TEST_F(TestColor, Comparison)
{
  Color c1(100u, 100u, 100u, 100u);
  Color c2(110u, 100u, 100u, 100u);
  Color c3(100u, 110u, 100u, 100u);
  Color c4(100u, 100u, 110u, 100u);
  Color c5(100u, 100u, 100u, 110u);
  Color c6(100u, 100u, 100u, 100u);

  EXPECT_FALSE(c1 == c2);
  EXPECT_FALSE(c1 == c3);
  EXPECT_FALSE(c1 == c4);
  EXPECT_FALSE(c1 == c5);
  EXPECT_TRUE(c1 == c6);

  EXPECT_TRUE(c1 != c2);
  EXPECT_TRUE(c1 != c3);
  EXPECT_TRUE(c1 != c4);
  EXPECT_TRUE(c1 != c5);
  EXPECT_FALSE(c1 != c6);
}



TEST_F(TestColor, OutputStreamOperator)
{
  HOU_EXPECT_OUTPUT("{Red = 1, Green = 2, Blue = 3, Alpha = 4}"
    , Color(1u, 2u, 3u, 4u));
}

