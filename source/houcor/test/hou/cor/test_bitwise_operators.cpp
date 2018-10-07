// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/bitwise_operators.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_bitwise_operators : public Test
{};

enum class flags : uint
{
  null = 0u,
  flag0 = 1u << 0,
  flag1 = 1u << 1,
  flag2 = 1u << 2,
  all = 7u,
};

}  // namespace



namespace hou
{

template <>
struct enable_bitwise_operators<flags>
{
  static constexpr bool enable = true;
};

}  // namespace hou



TEST_F(test_bitwise_operators, bitwise_and)
{
  EXPECT_EQ(0u, static_cast<uint>(flags::null & flags::flag0));
  EXPECT_EQ(0u, static_cast<uint>(flags::null & flags::flag1));
  EXPECT_EQ(0u, static_cast<uint>(flags::null & flags::flag2));
  EXPECT_EQ(1u, static_cast<uint>(flags::flag0 & flags::flag0));
  EXPECT_EQ(0u, static_cast<uint>(flags::flag0 & flags::flag1));
  EXPECT_EQ(0u, static_cast<uint>(flags::flag0 & flags::flag2));
  EXPECT_EQ(1u, static_cast<uint>(flags::all & flags::flag0));
  EXPECT_EQ(2u, static_cast<uint>(flags::all & flags::flag1));
  EXPECT_EQ(4u, static_cast<uint>(flags::all & flags::flag2));
}



TEST_F(test_bitwise_operators, in_place_bitwise_and)
{
  {
    flags f = flags::null;
    EXPECT_EQ(0u, static_cast<uint>(f &= flags::flag0));
  }
  {
    flags f = flags::null;
    EXPECT_EQ(0u, static_cast<uint>(f &= flags::flag1));
  }
  {
    flags f = flags::null;
    EXPECT_EQ(0u, static_cast<uint>(f &= flags::flag2));
  }
  {
    flags f = flags::flag0;
    EXPECT_EQ(1u, static_cast<uint>(f &= flags::flag0));
  }
  {
    flags f = flags::flag0;
    EXPECT_EQ(0u, static_cast<uint>(f &= flags::flag1));
  }
  {
    flags f = flags::flag0;
    EXPECT_EQ(0u, static_cast<uint>(f &= flags::flag2));
  }
  {
    flags f = flags::all;
    EXPECT_EQ(1u, static_cast<uint>(f &= flags::flag0));
  }
  {
    flags f = flags::all;
    EXPECT_EQ(2u, static_cast<uint>(f &= flags::flag1));
  }
  {
    flags f = flags::all;
    EXPECT_EQ(4u, static_cast<uint>(f &= flags::flag2));
  }
}



TEST_F(test_bitwise_operators, bitwise_or)
{
  EXPECT_EQ(1u, static_cast<uint>(flags::null | flags::flag0));
  EXPECT_EQ(2u, static_cast<uint>(flags::null | flags::flag1));
  EXPECT_EQ(4u, static_cast<uint>(flags::null | flags::flag2));
  EXPECT_EQ(1u, static_cast<uint>(flags::flag0 | flags::flag0));
  EXPECT_EQ(3u, static_cast<uint>(flags::flag0 | flags::flag1));
  EXPECT_EQ(5u, static_cast<uint>(flags::flag0 | flags::flag2));
  EXPECT_EQ(7u, static_cast<uint>(flags::all | flags::flag0));
  EXPECT_EQ(7u, static_cast<uint>(flags::all | flags::flag1));
  EXPECT_EQ(7u, static_cast<uint>(flags::all | flags::flag2));
}



TEST_F(test_bitwise_operators, in_place_bitwise_or)
{
  {
    flags f = flags::null;
    EXPECT_EQ(1u, static_cast<uint>(f |= flags::flag0));
  }
  {
    flags f = flags::null;
    EXPECT_EQ(2u, static_cast<uint>(f |= flags::flag1));
  }
  {
    flags f = flags::null;
    EXPECT_EQ(4u, static_cast<uint>(f |= flags::flag2));
  }
  {
    flags f = flags::flag0;
    EXPECT_EQ(1u, static_cast<uint>(f |= flags::flag0));
  }
  {
    flags f = flags::flag0;
    EXPECT_EQ(3u, static_cast<uint>(f |= flags::flag1));
  }
  {
    flags f = flags::flag0;
    EXPECT_EQ(5u, static_cast<uint>(f |= flags::flag2));
  }
  {
    flags f = flags::all;
    EXPECT_EQ(7u, static_cast<uint>(f |= flags::flag0));
  }
  {
    flags f = flags::all;
    EXPECT_EQ(7u, static_cast<uint>(f |= flags::flag1));
  }
  {
    flags f = flags::all;
    EXPECT_EQ(7u, static_cast<uint>(f |= flags::flag2));
  }
}



TEST_F(test_bitwise_operators, check_all)
{
  EXPECT_FALSE(check_all(flags::null, flags::flag0));
  EXPECT_FALSE(check_all(flags::null, flags::flag1));
  EXPECT_FALSE(check_all(flags::null, flags::flag2));
  EXPECT_FALSE(check_all(flags::null, flags::all));
  EXPECT_TRUE(check_all(flags::flag0, flags::flag0));
  EXPECT_FALSE(check_all(flags::flag0, flags::flag1));
  EXPECT_FALSE(check_all(flags::flag0, flags::flag2));
  EXPECT_FALSE(check_all(flags::flag0, flags::all));
  EXPECT_FALSE(check_all(flags::flag1, flags::flag0));
  EXPECT_TRUE(check_all(flags::flag1, flags::flag1));
  EXPECT_FALSE(check_all(flags::flag1, flags::flag2));
  EXPECT_FALSE(check_all(flags::flag1, flags::all));
  EXPECT_FALSE(check_all(flags::flag2, flags::flag0));
  EXPECT_FALSE(check_all(flags::flag2, flags::flag1));
  EXPECT_TRUE(check_all(flags::flag2, flags::flag2));
  EXPECT_FALSE(check_all(flags::flag2, flags::all));
  EXPECT_TRUE(check_all(flags::all, flags::flag0));
  EXPECT_TRUE(check_all(flags::all, flags::flag1));
  EXPECT_TRUE(check_all(flags::all, flags::flag2));
  EXPECT_TRUE(check_all(flags::all, flags::all));
}



TEST_F(test_bitwise_operators, check_any)
{
  EXPECT_FALSE(check_any(flags::null, flags::flag0));
  EXPECT_FALSE(check_any(flags::null, flags::flag1));
  EXPECT_FALSE(check_any(flags::null, flags::flag2));
  EXPECT_FALSE(check_any(flags::null, flags::all));
  EXPECT_TRUE(check_any(flags::flag0, flags::flag0));
  EXPECT_FALSE(check_any(flags::flag0, flags::flag1));
  EXPECT_FALSE(check_any(flags::flag0, flags::flag2));
  EXPECT_TRUE(check_any(flags::flag0, flags::all));
  EXPECT_FALSE(check_any(flags::flag1, flags::flag0));
  EXPECT_TRUE(check_any(flags::flag1, flags::flag1));
  EXPECT_FALSE(check_any(flags::flag1, flags::flag2));
  EXPECT_TRUE(check_any(flags::flag1, flags::all));
  EXPECT_FALSE(check_any(flags::flag2, flags::flag0));
  EXPECT_FALSE(check_any(flags::flag2, flags::flag1));
  EXPECT_TRUE(check_any(flags::flag2, flags::flag2));
  EXPECT_TRUE(check_any(flags::flag2, flags::all));
  EXPECT_TRUE(check_any(flags::all, flags::flag0));
  EXPECT_TRUE(check_any(flags::all, flags::flag1));
  EXPECT_TRUE(check_any(flags::all, flags::flag2));
  EXPECT_TRUE(check_any(flags::all, flags::all));
}



TEST_F(test_bitwise_operators, stream_bitfield)
{
  std::vector<std::pair<flags, std::string>> values{
    {flags::null, "none"},
    {flags::flag0, "flag0"},
    {flags::flag1, "flag1"},
    {flags::flag2, "flag2"},
    {flags::flag0 | flags::flag1, "flag1 | flag0"},
    {flags::flag0 | flags::flag2, "flag2 | flag0"},
    {flags::flag1 | flags::flag2, "flag2 | flag1"},
    {flags::flag0 | flags::flag1 | flags::flag2, "flag2 | flag1 | flag0"},
  };

  for(const auto& kv : values)
  {
    std::stringstream ss;
    stream_bitfield<flags>(ss, kv.first, [](std::ostream& os, flags bm) {
      switch(bm)
      {
        case flags::null:
          os << "none";
          break;
        case flags::flag0:
          os << "flag0";
          break;
        case flags::flag1:
          os << "flag1";
          break;
        case flags::flag2:
          os << "flag2";
          break;
        case flags::all:
          break;
      }
    });
    EXPECT_EQ(kv.second, ss.str());
  }
}
