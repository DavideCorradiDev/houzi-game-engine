// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/BitwiseOperators.hpp"

using namespace hou;
using namespace testing;



namespace 
{

class TestBitwiseOperators : public Test {};

enum class Flags : uint
{
  Null = 0u,
  Flag0 = 1u << 0,
  Flag1 = 1u << 1,
  Flag2 = 1u << 2,
  All = 7u,
};

}



namespace hou
{

template <>
  struct EnableBitwiseOperators<Flags>
{
  static constexpr bool enable = true;
};

}



TEST_F(TestBitwiseOperators, BitwiseAnd)
{
  EXPECT_EQ(0u, static_cast<uint>(Flags::Null & Flags::Flag0));
  EXPECT_EQ(0u, static_cast<uint>(Flags::Null & Flags::Flag1));
  EXPECT_EQ(0u, static_cast<uint>(Flags::Null & Flags::Flag2));
  EXPECT_EQ(1u, static_cast<uint>(Flags::Flag0 & Flags::Flag0));
  EXPECT_EQ(0u, static_cast<uint>(Flags::Flag0 & Flags::Flag1));
  EXPECT_EQ(0u, static_cast<uint>(Flags::Flag0 & Flags::Flag2));
  EXPECT_EQ(1u, static_cast<uint>(Flags::All & Flags::Flag0));
  EXPECT_EQ(2u, static_cast<uint>(Flags::All & Flags::Flag1));
  EXPECT_EQ(4u, static_cast<uint>(Flags::All & Flags::Flag2));
}



TEST_F(TestBitwiseOperators, InPlaceBitwiseAnd)
{
  {
    Flags f = Flags::Null;
    EXPECT_EQ(0u, static_cast<uint>(f &= Flags::Flag0));
  }
  {
    Flags f = Flags::Null;
    EXPECT_EQ(0u, static_cast<uint>(f &= Flags::Flag1));
  }
  {
    Flags f = Flags::Null;
    EXPECT_EQ(0u, static_cast<uint>(f &= Flags::Flag2));
  }
  {
    Flags f = Flags::Flag0;
    EXPECT_EQ(1u, static_cast<uint>(f &= Flags::Flag0));
  }
  {
    Flags f = Flags::Flag0;
    EXPECT_EQ(0u, static_cast<uint>(f &= Flags::Flag1));
  }
  {
    Flags f = Flags::Flag0;
    EXPECT_EQ(0u, static_cast<uint>(f &= Flags::Flag2));
  }
  {
    Flags f = Flags::All;
    EXPECT_EQ(1u, static_cast<uint>(f &= Flags::Flag0));
  }
  {
    Flags f = Flags::All;
    EXPECT_EQ(2u, static_cast<uint>(f &= Flags::Flag1));
  }
  {
    Flags f = Flags::All;
    EXPECT_EQ(4u, static_cast<uint>(f &= Flags::Flag2));
  }
}



TEST_F(TestBitwiseOperators, BitwiseOr)
{
  EXPECT_EQ(1u, static_cast<uint>(Flags::Null | Flags::Flag0));
  EXPECT_EQ(2u, static_cast<uint>(Flags::Null | Flags::Flag1));
  EXPECT_EQ(4u, static_cast<uint>(Flags::Null | Flags::Flag2));
  EXPECT_EQ(1u, static_cast<uint>(Flags::Flag0 | Flags::Flag0));
  EXPECT_EQ(3u, static_cast<uint>(Flags::Flag0 | Flags::Flag1));
  EXPECT_EQ(5u, static_cast<uint>(Flags::Flag0 | Flags::Flag2));
  EXPECT_EQ(7u, static_cast<uint>(Flags::All | Flags::Flag0));
  EXPECT_EQ(7u, static_cast<uint>(Flags::All | Flags::Flag1));
  EXPECT_EQ(7u, static_cast<uint>(Flags::All | Flags::Flag2));
}



TEST_F(TestBitwiseOperators, InPlaceBitwiseOr)
{
  {
    Flags f = Flags::Null;
    EXPECT_EQ(1u, static_cast<uint>(f |= Flags::Flag0));
  }
  {
    Flags f = Flags::Null;
    EXPECT_EQ(2u, static_cast<uint>(f |= Flags::Flag1));
  }
  {
    Flags f = Flags::Null;
    EXPECT_EQ(4u, static_cast<uint>(f |= Flags::Flag2));
  }
  {
    Flags f = Flags::Flag0;
    EXPECT_EQ(1u, static_cast<uint>(f |= Flags::Flag0));
  }
  {
    Flags f = Flags::Flag0;
    EXPECT_EQ(3u, static_cast<uint>(f |= Flags::Flag1));
  }
  {
    Flags f = Flags::Flag0;
    EXPECT_EQ(5u, static_cast<uint>(f |= Flags::Flag2));
  }
  {
    Flags f = Flags::All;
    EXPECT_EQ(7u, static_cast<uint>(f |= Flags::Flag0));
  }
  {
    Flags f = Flags::All;
    EXPECT_EQ(7u, static_cast<uint>(f |= Flags::Flag1));
  }
  {
    Flags f = Flags::All;
    EXPECT_EQ(7u, static_cast<uint>(f |= Flags::Flag2));
  }
}



TEST_F(TestBitwiseOperators, CheckBit)
{
  EXPECT_FALSE(checkBit(Flags::Null, Flags::Flag0));
  EXPECT_FALSE(checkBit(Flags::Null, Flags::Flag1));
  EXPECT_FALSE(checkBit(Flags::Null, Flags::Flag2));
  EXPECT_TRUE(checkBit(Flags::Flag0, Flags::Flag0));
  EXPECT_FALSE(checkBit(Flags::Flag0, Flags::Flag1));
  EXPECT_FALSE(checkBit(Flags::Flag0, Flags::Flag2));
  EXPECT_FALSE(checkBit(Flags::Flag1, Flags::Flag0));
  EXPECT_TRUE(checkBit(Flags::Flag1, Flags::Flag1));
  EXPECT_FALSE(checkBit(Flags::Flag1, Flags::Flag2));
  EXPECT_FALSE(checkBit(Flags::Flag2, Flags::Flag0));
  EXPECT_FALSE(checkBit(Flags::Flag2, Flags::Flag1));
  EXPECT_TRUE(checkBit(Flags::Flag2, Flags::Flag2));
  EXPECT_TRUE(checkBit(Flags::All, Flags::Flag0));
  EXPECT_TRUE(checkBit(Flags::All, Flags::Flag1));
  EXPECT_TRUE(checkBit(Flags::All, Flags::Flag2));
}

