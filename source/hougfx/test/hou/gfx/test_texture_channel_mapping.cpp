// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gfx/texture_channel_mapping.hpp"

using namespace testing;
using namespace hou;

namespace
{

class test_texture_channel_mapping : public Test
{};

}  // namespace



TEST_F(test_texture_channel_mapping, creation)
{
  texture_channel_mapping tcm(texture_channel::b, texture_channel::one,
    texture_channel::g, texture_channel::zero);

  EXPECT_EQ(texture_channel::b, tcm.get_r());
  EXPECT_EQ(texture_channel::one, tcm.get_g());
  EXPECT_EQ(texture_channel::g, tcm.get_b());
  EXPECT_EQ(texture_channel::zero, tcm.get_a());
}



TEST_F(test_texture_channel_mapping, set_r)
{
  texture_channel_mapping tcm(texture_channel::b, texture_channel::one,
    texture_channel::b, texture_channel::zero);

  tcm.set_r(texture_channel::g);
  EXPECT_EQ(texture_channel::g, tcm.get_r());
  EXPECT_EQ(texture_channel::one, tcm.get_g());
  EXPECT_EQ(texture_channel::b, tcm.get_b());
  EXPECT_EQ(texture_channel::zero, tcm.get_a());
}



TEST_F(test_texture_channel_mapping, set_g)
{
  texture_channel_mapping tcm(texture_channel::b, texture_channel::one,
    texture_channel::b, texture_channel::zero);

  tcm.set_g(texture_channel::g);
  EXPECT_EQ(texture_channel::b, tcm.get_r());
  EXPECT_EQ(texture_channel::g, tcm.get_g());
  EXPECT_EQ(texture_channel::b, tcm.get_b());
  EXPECT_EQ(texture_channel::zero, tcm.get_a());
}



TEST_F(test_texture_channel_mapping, set_b)
{
  texture_channel_mapping tcm(texture_channel::b, texture_channel::one,
    texture_channel::b, texture_channel::zero);

  tcm.set_b(texture_channel::g);
  EXPECT_EQ(texture_channel::b, tcm.get_r());
  EXPECT_EQ(texture_channel::one, tcm.get_g());
  EXPECT_EQ(texture_channel::g, tcm.get_b());
  EXPECT_EQ(texture_channel::zero, tcm.get_a());
}



TEST_F(test_texture_channel_mapping, set_a)
{
  texture_channel_mapping tcm(texture_channel::b, texture_channel::one,
    texture_channel::b, texture_channel::zero);

  tcm.set_a(texture_channel::g);
  EXPECT_EQ(texture_channel::b, tcm.get_r());
  EXPECT_EQ(texture_channel::one, tcm.get_g());
  EXPECT_EQ(texture_channel::b, tcm.get_b());
  EXPECT_EQ(texture_channel::g, tcm.get_a());
}



TEST_F(test_texture_channel_mapping, comparison)
{
  texture_channel_mapping tcm1(texture_channel::b, texture_channel::a,
    texture_channel::one, texture_channel::r);
  texture_channel_mapping tcm2(texture_channel::b, texture_channel::a,
    texture_channel::one, texture_channel::r);
  texture_channel_mapping tcm3(texture_channel::r, texture_channel::a,
    texture_channel::one, texture_channel::r);
  texture_channel_mapping tcm4(texture_channel::b, texture_channel::r,
    texture_channel::one, texture_channel::r);
  texture_channel_mapping tcm5(texture_channel::b, texture_channel::a,
    texture_channel::r, texture_channel::r);
  texture_channel_mapping tcm6(texture_channel::b, texture_channel::a,
    texture_channel::one, texture_channel::zero);

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



TEST_F(test_texture_channel_mapping, output_stream_operator)
{
  texture_channel_mapping tcm(texture_channel::b, texture_channel::a,
    texture_channel::one, texture_channel::r);
  const char out_ref[] = "{b -> r, a -> g, one -> b, r -> a}";
  EXPECT_OUTPUT(out_ref, tcm);
}
