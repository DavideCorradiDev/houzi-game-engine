// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/pixel_format.hpp"

#include "hou/cor/std_vector.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_pixel_format : public Test
{
public:
  static const std::vector<pixel_format>& get_values();
};



const std::vector<pixel_format>& test_pixel_format::get_values()
{
  static const std::vector<pixel_format> v
  {
    pixel_format::r,
    pixel_format::rg,
    pixel_format::rgb,
    pixel_format::rgba,
  };
  return v;
}

}  // namespace



TEST_F(test_pixel_format, get_bits_per_pixel)
{
  EXPECT_EQ(1u, get_bytes_per_pixel(pixel_format::r));
  EXPECT_EQ(2u, get_bytes_per_pixel(pixel_format::rg));
  EXPECT_EQ(3u, get_bytes_per_pixel(pixel_format::rgb));
  EXPECT_EQ(4u, get_bytes_per_pixel(pixel_format::rgba));
}



TEST_F(test_pixel_format, get_bytes_per_pixel)
{
  for(auto pf : get_values())
  {
    EXPECT_EQ(get_bytes_per_pixel(pf) * 8u, get_bits_per_pixel(pf));
  }
}
