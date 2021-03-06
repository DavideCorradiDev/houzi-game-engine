// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/vertex_attrib_format.hpp"

using namespace hou;



namespace
{

class test_vertex_attrib_format : public test_gfx_base
{};

}  // namespace



TEST_F(test_vertex_attrib_format, constructor)
{
  vertex_attrib_format vaf(gl_type::float_decimal, 3u, 12u, false);
  EXPECT_EQ(gl_type::float_decimal, vaf.get_type());
  EXPECT_EQ(3u, vaf.get_element_count());
  EXPECT_EQ(12u, vaf.get_byte_offset());
  EXPECT_EQ(false, vaf.must_be_normalized());
}



TEST_F(test_vertex_attrib_format, comparison)
{
  vertex_attrib_format vaf1(gl_type::float_decimal, 3u, 12u, false);
  vertex_attrib_format vaf2(gl_type::byte, 3u, 12u, false);
  vertex_attrib_format vaf3(gl_type::float_decimal, 4u, 12u, false);
  vertex_attrib_format vaf4(gl_type::float_decimal, 3u, 10u, false);
  vertex_attrib_format vaf5(gl_type::float_decimal, 3u, 12u, true);
  vertex_attrib_format vaf6(gl_type::float_decimal, 3u, 12u, false);

  EXPECT_TRUE(vaf1 != vaf2);
  EXPECT_TRUE(vaf1 != vaf3);
  EXPECT_TRUE(vaf1 != vaf4);
  EXPECT_TRUE(vaf1 != vaf5);
  EXPECT_TRUE(vaf1 == vaf6);

  EXPECT_FALSE(vaf1 == vaf2);
  EXPECT_FALSE(vaf1 == vaf3);
  EXPECT_FALSE(vaf1 == vaf4);
  EXPECT_FALSE(vaf1 == vaf5);
  EXPECT_FALSE(vaf1 != vaf6);
}



TEST_F(test_vertex_attrib_format, output_stream_operator)
{
  vertex_attrib_format vaf(gl_type::float_decimal, 3u, 12u, false);
  const char* out_ref
    = "{type = float_decimal, element_count = 3, byte_offset = 12, "
      "must_be_normalized = false}";
  EXPECT_OUTPUT(out_ref, vaf);
}
