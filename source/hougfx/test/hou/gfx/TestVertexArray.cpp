// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/vertex_buffer.hpp"
#include "hou/gfx/vertex_array.hpp"
#include "hou/gfx/vertex_attrib_format.hpp"
#include "hou/gfx/vertex_format.hpp"

using namespace hou;



namespace
{

using FloatBuffer = static_vertex_buffer<float>;

class TestVertexArray : public TestGfxBase
{};

class TestVertexArrayDeathTest : public TestVertexArray
{};

}  // namespace



TEST_F(TestVertexArray, Binding)
{
  vertex_array va1;
  vertex_array va2;

  EXPECT_FALSE(va1.is_bound());
  EXPECT_FALSE(va2.is_bound());

  vertex_array::bind(va1);
  EXPECT_TRUE(va1.is_bound());
  EXPECT_FALSE(va2.is_bound());

  vertex_array::bind(va2);
  EXPECT_FALSE(va1.is_bound());
  EXPECT_TRUE(va2.is_bound());

  vertex_array::unbind();
  EXPECT_FALSE(va1.is_bound());
  EXPECT_FALSE(va2.is_bound());
}



TEST_F(TestVertexArray, DefaultConstructor)
{
  vertex_array va;
  EXPECT_NE(0u, va.get_handle().get_name());
}



TEST_F(TestVertexArray, MoveConstructor)
{
  vertex_array va1;
  uint va1Id = va1.get_handle().get_name();
  vertex_array va2(std::move(va1));

  EXPECT_EQ(va1Id, va2.get_handle().get_name());
  EXPECT_EQ(0u, va1.get_handle().get_name());
}



TEST_F(TestVertexArray, SetVertexData)
{
  vertex_array va;
  FloatBuffer vb(std::vector<float>{1, 2, 3, 4, 5, 6});
  vertex_format vf(0, 3,
    {vertex_attrib_format(gl_type::float_decimal, 2, 0, false),
      vertex_attrib_format(gl_type::float_decimal, 1, 2, true)});
  va.set_vertex_data(vb, 0u, vf);
  SUCCEED();
}



TEST_F(TestVertexArray, SetVertexDataMaxBindingIndex)
{
  vertex_array va;
  FloatBuffer vb(std::vector<float>{1, 2, 3, 4, 5, 6});
  vertex_format vf(0, 3,
    {vertex_attrib_format(gl_type::float_decimal, 2, 0, false),
      vertex_attrib_format(gl_type::float_decimal, 1, 2, true)});
  va.set_vertex_data(vb, vertex_array::get_max_binding_index(), vf);
  SUCCEED();
}



TEST_F(TestVertexArrayDeathTest, SetVertexDataErrorInvalidBindingIndex)
{
  vertex_array va;
  FloatBuffer vb(std::vector<float>{1, 2, 3, 4, 5, 6});
  vertex_format vf(0, 3,
    {vertex_attrib_format(gl_type::float_decimal, 2, 0, false),
      vertex_attrib_format(gl_type::float_decimal, 1, 2, true)});
  HOU_EXPECT_PRECONDITION(
    va.set_vertex_data(vb, vertex_array::get_max_binding_index() + 1u, vf));
}



TEST_F(TestVertexArray, SetVertexDataMaxAttribFormats)
{
  vertex_array va;
  FloatBuffer vb(std::vector<float>{1, 2, 3, 4, 5, 6});
  vertex_attrib_format vaf(gl_type::float_decimal, 2, 0, false);
  HOU_EXPECT_PRECONDITION(
    va.set_vertex_data(vb, vertex_array::get_max_binding_index(),
      vertex_format(0, 3,
        std::vector<vertex_attrib_format>(
          vertex_format::get_max_attrib_format_count() + 1u, vaf))));
}



TEST_F(TestVertexArray, SetElementData)
{
  vertex_array va;
  FloatBuffer vb(std::vector<float>{0, 1});
  va.set_element_data(vb);
}
