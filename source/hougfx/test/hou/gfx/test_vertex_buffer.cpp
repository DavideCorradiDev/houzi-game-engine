// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/vertex_buffer.hpp"

#include "hou/gl/gl_error.hpp"

#include "hou/cor/cor_error.hpp"

using namespace hou;



namespace
{

using IntBuffer = static_vertex_buffer<int>;
using FloatBuffer = static_vertex_buffer<float>;
using DynamicFloatBuffer = dynamic_vertex_buffer<float>;

class TestVertexBuffer : public test_gfx_base
{};

class TestVertexBufferDeathTest : public TestVertexBuffer
{};

}  // namespace



TEST_F(TestVertexBuffer, Binding)
{
  IntBuffer vb1(2u);
  IntBuffer vb2(2u);

  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  IntBuffer::bind(vb1, vertex_buffer_target::array_buffer);
  EXPECT_TRUE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  IntBuffer::bind(vb1, vertex_buffer_target::element_array_buffer);
  EXPECT_TRUE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_TRUE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  IntBuffer::bind(vb2, vertex_buffer_target::array_buffer);
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_TRUE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_TRUE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  IntBuffer::bind(vb2, vertex_buffer_target::element_array_buffer);
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_TRUE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_TRUE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  IntBuffer::unbind(vertex_buffer_target::array_buffer);
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_TRUE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  IntBuffer::unbind(vertex_buffer_target::element_array_buffer);
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));
}



TEST_F(TestVertexBuffer, SizeConstructor)
{
  uint size_ref = 7u;
  IntBuffer vb(size_ref);

  EXPECT_NE(0u, vb.get_handle().get_name());
  EXPECT_EQ(size_ref * sizeof(IntBuffer::value_type), vb.get_byte_count());
  EXPECT_EQ(size_ref, vb.get_size());
  EXPECT_EQ(std::vector<int>(size_ref, 0u), vb.get_data());
}



TEST_F(TestVertexBuffer, DataConstructor)
{
  DynamicFloatBuffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  FloatBuffer vb(data_ref);

  EXPECT_NE(0u, vb.get_handle().get_name());
  EXPECT_EQ(data_ref.size() * sizeof(float), vb.get_byte_count());
  EXPECT_EQ(data_ref, vb.get_data());
}



TEST_F(TestVertexBuffer, MoveConstructor)
{
  DynamicFloatBuffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  FloatBuffer vb_dummy(data_ref);
  GLuint name = vb_dummy.get_handle().get_name();
  FloatBuffer vb(std::move(vb_dummy));

  EXPECT_EQ(0u, vb_dummy.get_handle().get_name());
  EXPECT_EQ(name, vb.get_handle().get_name());
  EXPECT_EQ(data_ref.size() * sizeof(float), vb.get_byte_count());
  EXPECT_EQ(data_ref, vb.get_data());
}



TEST_F(TestVertexBuffer, GetSubData)
{
  DynamicFloatBuffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  DynamicFloatBuffer::data_type subData_ref = {2.f, 3.f};
  FloatBuffer vb(data_ref);
  EXPECT_EQ(subData_ref, vb.get_sub_data(1u, 2u));
}



TEST_F(TestVertexBuffer, GetSubDataLimit)
{
  DynamicFloatBuffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  DynamicFloatBuffer::data_type subData_ref = {3.f, 4.f, 5.f};
  FloatBuffer vb(data_ref);
  EXPECT_EQ(data_ref, vb.get_sub_data(0u, vb.get_size()));
  EXPECT_EQ(subData_ref, vb.get_sub_data(2u, 3u));
}



TEST_F(TestVertexBufferDeathTest, GetSubDataErrorOverflow)
{
  DynamicFloatBuffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  FloatBuffer vb(data_ref);
  HOU_EXPECT_PRECONDITION(vb.get_sub_data(0u, vb.get_size() + 1u));
  HOU_EXPECT_PRECONDITION(vb.get_sub_data(2u, vb.get_size() - 1u));
}



TEST_F(TestVertexBuffer, SetSubData)
{
  DynamicFloatBuffer vb(6u);
  EXPECT_EQ(DynamicFloatBuffer::data_type(6u, 0.f), vb.get_data());

  DynamicFloatBuffer::data_type subData_ref = {1.f, 2.f, 3.f};
  DynamicFloatBuffer::data_type data_ref = {0.0f, 1.f, 2.f, 3.f, 0.f, 0.f};
  vb.set_sub_data(1u, subData_ref);
  EXPECT_EQ(data_ref, vb.get_data());
  EXPECT_EQ(subData_ref, vb.get_sub_data(1u, 3u));
}



TEST_F(TestVertexBuffer, SetSubDataLimit)
{
  DynamicFloatBuffer vb(6u);
  EXPECT_EQ(DynamicFloatBuffer::data_type(6u, 0.f), vb.get_data());

  DynamicFloatBuffer::data_type subData_ref = {1.f, 2.f, 3.f};
  DynamicFloatBuffer::data_type data_ref = {0.f, 0.f, 0.f, 1.f, 2.f, 3.f};
  vb.set_sub_data(3u, subData_ref);
  EXPECT_EQ(data_ref, vb.get_data());
  EXPECT_EQ(subData_ref, vb.get_sub_data(3u, 3u));

  DynamicFloatBuffer::data_type dataRef2 = {4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
  vb.set_sub_data(0u, dataRef2);
  EXPECT_EQ(dataRef2, vb.get_data());
  EXPECT_EQ(dataRef2, vb.get_sub_data(0u, 6u));
}



TEST_F(TestVertexBufferDeathTest, SetSubDataErrorOverflow)
{
  DynamicFloatBuffer vb(6u);
  DynamicFloatBuffer::data_type data(3u, 0.f);
  HOU_EXPECT_PRECONDITION(vb.set_sub_data(vb.get_size() - data.size() + 1u, data));
}



TEST_F(TestVertexBuffer, SetData)
{
  DynamicFloatBuffer vb(3u);
  EXPECT_EQ(DynamicFloatBuffer::data_type(vb.get_size(), 0.f), vb.get_data());

  DynamicFloatBuffer::data_type data_ref = {0.1f, 0.2f, 0.3f};
  vb.set_data(data_ref);
  EXPECT_EQ(data_ref, vb.get_data());
}



TEST_F(TestVertexBufferDeathTest, SetDataErrorTooFewElements)
{
  DynamicFloatBuffer vb(3u);
  DynamicFloatBuffer::data_type data(vb.get_size() - 1u, 0.f);
  HOU_EXPECT_PRECONDITION(vb.set_data(data));
}



TEST_F(TestVertexBufferDeathTest, SetDataErrorTooManyElements)
{
  DynamicFloatBuffer vb(3u);
  DynamicFloatBuffer::data_type data(vb.get_size() + 1u, 0.f);
  HOU_EXPECT_PRECONDITION(vb.set_data(data));
}
