// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/TextureChannelMapping.hpp"

using namespace testing;
using namespace hou;

namespace
{

class TestTextureChannelMapping : public Test {};

}




TEST_F(TestTextureChannelMapping, Creation)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::G, TextureChannel::Zero);

  EXPECT_EQ(TextureChannel::B, tcm.getR());
  EXPECT_EQ(TextureChannel::One, tcm.getG());
  EXPECT_EQ(TextureChannel::G, tcm.getB());
  EXPECT_EQ(TextureChannel::Zero, tcm.getA());
}



TEST_F(TestTextureChannelMapping, SetR)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::B, TextureChannel::Zero);

  tcm.setR(TextureChannel::G);
  EXPECT_EQ(TextureChannel::G, tcm.getR());
  EXPECT_EQ(TextureChannel::One, tcm.getG());
  EXPECT_EQ(TextureChannel::B, tcm.getB());
  EXPECT_EQ(TextureChannel::Zero, tcm.getA());
}



TEST_F(TestTextureChannelMapping, SetG)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::B, TextureChannel::Zero);

  tcm.setG(TextureChannel::G);
  EXPECT_EQ(TextureChannel::B, tcm.getR());
  EXPECT_EQ(TextureChannel::G, tcm.getG());
  EXPECT_EQ(TextureChannel::B, tcm.getB());
  EXPECT_EQ(TextureChannel::Zero, tcm.getA());
}



TEST_F(TestTextureChannelMapping, SetB)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::B, TextureChannel::Zero);

  tcm.setB(TextureChannel::G);
  EXPECT_EQ(TextureChannel::B, tcm.getR());
  EXPECT_EQ(TextureChannel::One, tcm.getG());
  EXPECT_EQ(TextureChannel::G, tcm.getB());
  EXPECT_EQ(TextureChannel::Zero, tcm.getA());
}



TEST_F(TestTextureChannelMapping, SetA)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::B, TextureChannel::Zero);

  tcm.setA(TextureChannel::G);
  EXPECT_EQ(TextureChannel::B, tcm.getR());
  EXPECT_EQ(TextureChannel::One, tcm.getG());
  EXPECT_EQ(TextureChannel::B, tcm.getB());
  EXPECT_EQ(TextureChannel::G, tcm.getA());
}



TEST_F(TestTextureChannelMapping, Comparison)
{
  TextureChannelMapping tcm1
    ( TextureChannel::B
    , TextureChannel::A
    , TextureChannel::One
    , TextureChannel::R);
  TextureChannelMapping tcm2
    ( TextureChannel::B
    , TextureChannel::A
    , TextureChannel::One
    , TextureChannel::R);
  TextureChannelMapping tcm3
    ( TextureChannel::R
    , TextureChannel::A
    , TextureChannel::One
    , TextureChannel::R);
  TextureChannelMapping tcm4
    ( TextureChannel::B
    , TextureChannel::R
    , TextureChannel::One
    , TextureChannel::R);
  TextureChannelMapping tcm5
    ( TextureChannel::B
    , TextureChannel::A
    , TextureChannel::R
    , TextureChannel::R);
  TextureChannelMapping tcm6
    ( TextureChannel::B
    , TextureChannel::A
    , TextureChannel::One
    , TextureChannel::Zero);

  EXPECT_TRUE(tcm1 == tcm2);
  EXPECT_FALSE(tcm1 == tcm3);
  EXPECT_FALSE(tcm1 == tcm4);
  EXPECT_FALSE(tcm1 == tcm5);
  EXPECT_FALSE(tcm1 == tcm6);

  EXPECT_FALSE(tcm1 != tcm2);
  EXPECT_TRUE(tcm1 != tcm3);
  EXPECT_TRUE(tcm1 != tcm4);
  EXPECT_TRUE(tcm1 != tcm5);
  EXPECT_TRUE(tcm1 != tcm6);
}



TEST_F(TestTextureChannelMapping, OutputStreamOperator)
{
  TextureChannelMapping tcm
    ( TextureChannel::B
    , TextureChannel::A
    , TextureChannel::One
    , TextureChannel::R);
  const char outRef[] = "{B -> R, A -> G, One -> B, R -> A}";
  HOU_EXPECT_OUTPUT(outRef, tcm);
}

