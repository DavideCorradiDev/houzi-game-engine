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

  EXPECT_EQ(TextureChannel::B, tcm.get_r());
  EXPECT_EQ(TextureChannel::One, tcm.get_g());
  EXPECT_EQ(TextureChannel::G, tcm.get_b());
  EXPECT_EQ(TextureChannel::Zero, tcm.get_a());
}



TEST_F(TestTextureChannelMapping, SetR)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::B, TextureChannel::Zero);

  tcm.set_r(TextureChannel::G);
  EXPECT_EQ(TextureChannel::G, tcm.get_r());
  EXPECT_EQ(TextureChannel::One, tcm.get_g());
  EXPECT_EQ(TextureChannel::B, tcm.get_b());
  EXPECT_EQ(TextureChannel::Zero, tcm.get_a());
}



TEST_F(TestTextureChannelMapping, SetG)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::B, TextureChannel::Zero);

  tcm.set_g(TextureChannel::G);
  EXPECT_EQ(TextureChannel::B, tcm.get_r());
  EXPECT_EQ(TextureChannel::G, tcm.get_g());
  EXPECT_EQ(TextureChannel::B, tcm.get_b());
  EXPECT_EQ(TextureChannel::Zero, tcm.get_a());
}



TEST_F(TestTextureChannelMapping, SetB)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::B, TextureChannel::Zero);

  tcm.set_b(TextureChannel::G);
  EXPECT_EQ(TextureChannel::B, tcm.get_r());
  EXPECT_EQ(TextureChannel::One, tcm.get_g());
  EXPECT_EQ(TextureChannel::G, tcm.get_b());
  EXPECT_EQ(TextureChannel::Zero, tcm.get_a());
}



TEST_F(TestTextureChannelMapping, SetA)
{
  TextureChannelMapping tcm(TextureChannel::B, TextureChannel::One
    , TextureChannel::B, TextureChannel::Zero);

  tcm.set_a(TextureChannel::G);
  EXPECT_EQ(TextureChannel::B, tcm.get_r());
  EXPECT_EQ(TextureChannel::One, tcm.get_g());
  EXPECT_EQ(TextureChannel::B, tcm.get_b());
  EXPECT_EQ(TextureChannel::G, tcm.get_a());
}



TEST_F(TestTextureChannelMapping, Comparison)
{
  TextureChannelMapping tcm1
    ( TextureChannel::B
    , TextureChannel::A
    , TextureChannel::One
    , TextureChannel::r);
  TextureChannelMapping tcm2
    ( TextureChannel::B
    , TextureChannel::A
    , TextureChannel::One
    , TextureChannel::r);
  TextureChannelMapping tcm3
    ( TextureChannel::r
    , TextureChannel::A
    , TextureChannel::One
    , TextureChannel::r);
  TextureChannelMapping tcm4
    ( TextureChannel::B
    , TextureChannel::r
    , TextureChannel::One
    , TextureChannel::r);
  TextureChannelMapping tcm5
    ( TextureChannel::B
    , TextureChannel::A
    , TextureChannel::r
    , TextureChannel::r);
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
    , TextureChannel::r);
  const char outRef[] = "{B -> r, A -> G, One -> B, r -> A}";
  HOU_EXPECT_OUTPUT(outRef, tcm);
}

