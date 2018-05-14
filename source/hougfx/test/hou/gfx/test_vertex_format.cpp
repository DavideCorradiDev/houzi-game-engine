// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/vertex_format.hpp"

using namespace hou;



namespace
{

class test_vertex_format : public test_gfx_base
{};

class test_vertex_format_death_test : public test_vertex_format
{};

}  // namespace



TEST_F(test_vertex_format, vaf_span_constructor)
{
  std::vector<vertex_attrib_format> vafs = {
    vertex_attrib_format(gl_type::float_decimal, 3u, 12u, false),
    vertex_attrib_format(gl_type::float_decimal, 6u, 24u, true),
  };
  vertex_format vf(2u, 3u, vafs);

  EXPECT_EQ(2, vf.get_offset());
  EXPECT_EQ(3u, vf.get_stride());
  EXPECT_EQ(vafs, vf.get_vertex_attrib_formats());
}



TEST_F(test_vertex_format, vaf_span_constructor_attrib_limit)
{
  vertex_attrib_format vaf(gl_type::float_decimal, 3u, 12u, false);
  std::vector<vertex_attrib_format> vafs(
    vertex_format::get_max_attrib_format_count(), vaf);
  vertex_format vf(2u, 3u, vafs);

  EXPECT_EQ(2, vf.get_offset());
  EXPECT_EQ(3u, vf.get_stride());
  EXPECT_EQ(vafs, vf.get_vertex_attrib_formats());
}



TEST_F(test_vertex_format_death_test,
  vaf_span_constructor_error_too_many_attrib_formats)
{
  vertex_attrib_format vaf(gl_type::float_decimal, 3u, 12u, false);
  std::vector<vertex_attrib_format> vafs(
    vertex_format::get_max_attrib_format_count() + 1u, vaf);
  EXPECT_PRECOND_ERROR(vertex_format vf(2u, 3u, vafs));
}



TEST_F(test_vertex_format, vaf_move_constructor)
{
  std::vector<vertex_attrib_format> vafs = {
    vertex_attrib_format(gl_type::float_decimal, 3u, 12u, false),
    vertex_attrib_format(gl_type::float_decimal, 6u, 24u, true),
  };
  std::vector<vertex_attrib_format> vafs_ref = vafs;
  vertex_format vf(2u, 3u, std::move(vafs));

  EXPECT_EQ(2, vf.get_offset());
  EXPECT_EQ(3u, vf.get_stride());
  EXPECT_EQ(vafs_ref, vf.get_vertex_attrib_formats());
}



TEST_F(test_vertex_format, vaf_move_constructor_attrib_limit)
{
  vertex_attrib_format vaf(gl_type::float_decimal, 3u, 12u, false);
  std::vector<vertex_attrib_format> vafs(
    vertex_format::get_max_attrib_format_count(), vaf);
  std::vector<vertex_attrib_format> vafs_ref = vafs;
  vertex_format vf(2u, 3u, std::move(vafs));

  EXPECT_EQ(2, vf.get_offset());
  EXPECT_EQ(3u, vf.get_stride());
  EXPECT_EQ(vafs_ref, vf.get_vertex_attrib_formats());
}



TEST_F(test_vertex_format_death_test,
  vaf_move_constructor_error_too_many_attrib_formats)
{
  vertex_attrib_format vaf(gl_type::float_decimal, 3u, 12u, false);
  std::vector<vertex_attrib_format> vafs(
    vertex_format::get_max_attrib_format_count() + 1u, vaf);
  EXPECT_PRECOND_ERROR(vertex_format vf(2u, 3u, std::move(vafs)));
}



TEST_F(test_vertex_format, comparison)
{
  std::vector<vertex_attrib_format> vafs1 = {
    vertex_attrib_format(gl_type::float_decimal, 3u, 12u, false),
    vertex_attrib_format(gl_type::float_decimal, 6u, 2u, true),
  };
  std::vector<vertex_attrib_format> vafs2 = {
    vertex_attrib_format(gl_type::float_decimal, 3u, 12u, false),
  };

  vertex_format vf1(2, 3u, vafs1);
  vertex_format vf2(1, 3u, vafs1);
  vertex_format vf3(2, 2u, vafs1);
  vertex_format vf4(2, 3u, vafs2);
  vertex_format vf5(2, 3u, vafs1);

  EXPECT_TRUE(vf1 != vf2);
  EXPECT_TRUE(vf1 != vf3);
  EXPECT_TRUE(vf1 != vf4);
  EXPECT_TRUE(vf1 == vf5);

  EXPECT_FALSE(vf1 == vf2);
  EXPECT_FALSE(vf1 == vf3);
  EXPECT_FALSE(vf1 == vf4);
  EXPECT_FALSE(vf1 != vf5);
}



TEST_F(test_vertex_format, output_stream_operator)
{
  std::vector<vertex_attrib_format> vafs = {
    vertex_attrib_format(gl_type::float_decimal, 3u, 12u, false),
    vertex_attrib_format(gl_type::float_decimal, 6u, 24u, true),
  };
  vertex_format vf(2, 3u, vafs);
  const char* out_ref
    = "{offset = 2, stride = 3, vertex_attrib_formats = {{type = "
      "float_decimal, element_count = 3, byte_offset = 12, must_be_normalized "
      "= false}, {type = float_decimal, element_count = 6, byte_offset = 24, "
      "must_be_normalized = true}}}";
  EXPECT_OUTPUT(out_ref, vf);
}
