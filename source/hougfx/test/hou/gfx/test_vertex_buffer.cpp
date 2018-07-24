// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/vertex_buffer.hpp"

using namespace hou;



namespace
{

using int_buffer = static_vertex_buffer<int>;
using float_buffer = static_vertex_buffer<float>;
using dynamic_float_buffer = dynamic_vertex_buffer<float>;

class test_vertex_buffer : public test_gfx_base
{};

using test_vertex_buffer_death_test = test_vertex_buffer;

}  // namespace



TEST_F(test_vertex_buffer, binding)
{
#if defined(HOU_EMSCRIPTEN)
  SKIP(
    "Binding a GL buffer to different targets in its lifetime is not supported "
    "on Emscripten.");
#endif

  int_buffer vb1(2u);
  int_buffer vb2(2u);

  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  int_buffer::bind(vb1, vertex_buffer_target::array_buffer);
  EXPECT_TRUE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  int_buffer::bind(vb1, vertex_buffer_target::element_array_buffer);
  EXPECT_TRUE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_TRUE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  int_buffer::bind(vb2, vertex_buffer_target::array_buffer);
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_TRUE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_TRUE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  int_buffer::bind(vb2, vertex_buffer_target::element_array_buffer);
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_TRUE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_TRUE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  int_buffer::unbind(vertex_buffer_target::array_buffer);
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_TRUE(vb2.is_bound(vertex_buffer_target::element_array_buffer));

  int_buffer::unbind(vertex_buffer_target::element_array_buffer);
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::array_buffer));
  EXPECT_FALSE(vb1.is_bound(vertex_buffer_target::element_array_buffer));
  EXPECT_FALSE(vb2.is_bound(vertex_buffer_target::element_array_buffer));
}



TEST_F(test_vertex_buffer, size_constructor)
{
  uint size_ref = 7u;
  int_buffer vb(size_ref);

  EXPECT_NE(0u, vb.get_handle().get_name());
  EXPECT_EQ(size_ref * sizeof(int_buffer::value_type), vb.get_byte_count());
  EXPECT_EQ(size_ref, vb.get_size());
#if !defined(HOU_GL_ES)
  EXPECT_EQ(std::vector<int>(size_ref, 0u), vb.get_data());
#endif
}



TEST_F(test_vertex_buffer, data_constructor)
{
  dynamic_float_buffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  float_buffer vb(data_ref);

  EXPECT_NE(0u, vb.get_handle().get_name());
  EXPECT_EQ(data_ref.size() * sizeof(float), vb.get_byte_count());
#if !defined(HOU_GL_ES)
  EXPECT_EQ(data_ref, vb.get_data());
#endif
}



TEST_F(test_vertex_buffer, move_constructor)
{
  dynamic_float_buffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  float_buffer vb_dummy(data_ref);
  GLuint name = vb_dummy.get_handle().get_name();
  float_buffer vb(std::move(vb_dummy));

  EXPECT_EQ(0u, vb_dummy.get_handle().get_name());
  EXPECT_EQ(name, vb.get_handle().get_name());
  EXPECT_EQ(data_ref.size() * sizeof(float), vb.get_byte_count());
#if !defined(HOU_GL_ES)
  EXPECT_EQ(data_ref, vb.get_data());
#endif
}



TEST_F(test_vertex_buffer, get_sub_data)
{
#if defined(HOU_GL_ES)
  SKIP("Reading data from a GL buffer is not supported on GLES.");
#endif
  dynamic_float_buffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  dynamic_float_buffer::data_type sub_data_ref = {2.f, 3.f};
  float_buffer vb(data_ref);
  EXPECT_EQ(sub_data_ref, vb.get_sub_data(1u, 2u));
}



TEST_F(test_vertex_buffer, get_sub_data_limit)
{
#if defined(HOU_GL_ES)
  SKIP("Reading data from a GL buffer is not supported on GLES.");
#endif
  dynamic_float_buffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  dynamic_float_buffer::data_type sub_data_ref = {3.f, 4.f, 5.f};
  float_buffer vb(data_ref);
  EXPECT_EQ(data_ref, vb.get_sub_data(0u, vb.get_size()));
  EXPECT_EQ(sub_data_ref, vb.get_sub_data(2u, 3u));
}



TEST_F(test_vertex_buffer_death_test, get_sub_data_error_overflow)
{
#if defined(HOU_GL_ES)
  SKIP("Reading data from a GL buffer is not supported on GLES.");
#endif
  dynamic_float_buffer::data_type data_ref = {1.f, 2.f, 3.f, 4.f, 5.f};
  float_buffer vb(data_ref);
  EXPECT_PRECOND_ERROR(vb.get_sub_data(0u, vb.get_size() + 1u));
  EXPECT_PRECOND_ERROR(vb.get_sub_data(2u, vb.get_size() - 1u));
}



TEST_F(test_vertex_buffer, set_sub_data)
{
  dynamic_float_buffer vb(6u);
#if !defined(HOU_GL_ES)
  EXPECT_EQ(dynamic_float_buffer::data_type(6u, 0.f), vb.get_data());
#endif

  dynamic_float_buffer::data_type sub_data_ref = {1.f, 2.f, 3.f};
  dynamic_float_buffer::data_type data_ref = {0.0f, 1.f, 2.f, 3.f, 0.f, 0.f};
  vb.set_sub_data(1u, sub_data_ref);
#if !defined(HOU_GL_ES)
  EXPECT_EQ(data_ref, vb.get_data());
  EXPECT_EQ(sub_data_ref, vb.get_sub_data(1u, 3u));
#endif
}



TEST_F(test_vertex_buffer, set_sub_data_limit)
{
  dynamic_float_buffer vb(6u);
#if !defined(HOU_GL_ES)
  EXPECT_EQ(dynamic_float_buffer::data_type(6u, 0.f), vb.get_data());
#endif

  dynamic_float_buffer::data_type sub_data_ref = {1.f, 2.f, 3.f};
  dynamic_float_buffer::data_type data_ref = {0.f, 0.f, 0.f, 1.f, 2.f, 3.f};
  vb.set_sub_data(3u, sub_data_ref);
#if !defined(HOU_GL_ES)
  EXPECT_EQ(data_ref, vb.get_data());
  EXPECT_EQ(sub_data_ref, vb.get_sub_data(3u, 3u));
#endif

  dynamic_float_buffer::data_type data_ref2 = {4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
  vb.set_sub_data(0u, data_ref2);
#if !defined(HOU_GL_ES)
  EXPECT_EQ(data_ref2, vb.get_data());
  EXPECT_EQ(data_ref2, vb.get_sub_data(0u, 6u));
#endif
}



TEST_F(test_vertex_buffer_death_test, set_sub_data_error_overflow)
{
  dynamic_float_buffer vb(6u);
  dynamic_float_buffer::data_type data(3u, 0.f);
  EXPECT_PRECOND_ERROR(
    vb.set_sub_data(vb.get_size() - data.size() + 1u, data));
}



TEST_F(test_vertex_buffer, set_data)
{
  dynamic_float_buffer vb(3u);
#if !defined(HOU_GL_ES)
  EXPECT_EQ(dynamic_float_buffer::data_type(vb.get_size(), 0.f), vb.get_data());
#endif

  dynamic_float_buffer::data_type data_ref = {0.1f, 0.2f, 0.3f};
  vb.set_data(data_ref);
#if !defined(HOU_GL_ES)
  EXPECT_EQ(data_ref, vb.get_data());
#endif
}



TEST_F(test_vertex_buffer_death_test, set_data_error_too_few_elements)
{
  dynamic_float_buffer vb(3u);
  dynamic_float_buffer::data_type data(vb.get_size() - 1u, 0.f);
  EXPECT_PRECOND_ERROR(vb.set_data(data));
}



TEST_F(test_vertex_buffer_death_test, set_data_error_too_many_elements)
{
  dynamic_float_buffer vb(3u);
  dynamic_float_buffer::data_type data(vb.get_size() + 1u, 0.f);
  EXPECT_PRECOND_ERROR(vb.set_data(data));
}
