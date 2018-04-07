// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/VertexBuffer.hpp"

#include "hou/gl/GlError.hpp"

#include "hou/cor/CorError.hpp"

using namespace hou;



namespace
{

class TestVertexBuffer : public TestGfxBase
{};
class TestVertexBufferDeathTest : public TestVertexBuffer
{};

}  // namespace



TEST_F(TestVertexBuffer, Binding)
{
  VertexBuffer vb1(2u, VertexBufferAttributes::None);
  VertexBuffer vb2(2u, VertexBufferAttributes::None);
  VertexBufferTarget target = VertexBufferTarget::Array;

  EXPECT_FALSE(vb1.isBound(target));
  EXPECT_FALSE(vb2.isBound(target));

  VertexBuffer::bind(vb1, target);
  EXPECT_TRUE(vb1.isBound(target));
  EXPECT_FALSE(vb2.isBound(target));

  VertexBuffer::bind(vb2, target);
  EXPECT_FALSE(vb1.isBound(target));
  EXPECT_TRUE(vb2.isBound(target));

  VertexBuffer::unbind(target);
  EXPECT_FALSE(vb1.isBound(target));
  EXPECT_FALSE(vb2.isBound(target));
}



TEST_F(TestVertexBuffer, SizeConstructor)
{
  uint byteCountRef = 7u;
  VertexBuffer vb(byteCountRef, VertexBufferAttributes::None);

  EXPECT_NE(0u, vb.getHandle().getName());
  EXPECT_EQ(byteCountRef, vb.getByteCount());
  EXPECT_EQ(std::vector<uint8_t>(byteCountRef, 0u), vb.getData<uint8_t>());
}



TEST_F(TestVertexBuffer, DataConstructor)
{
  std::vector<float> dataRef = {1.f, 2.f, 3.f, 4.f, 5.f};
  VertexBuffer vb(dataRef, VertexBufferAttributes::None);

  EXPECT_NE(0u, vb.getHandle().getName());
  EXPECT_EQ(dataRef.size() * sizeof(float), vb.getByteCount());
  EXPECT_EQ(dataRef, vb.getData<float>());
}



TEST_F(TestVertexBuffer, MoveConstructor)
{
  std::vector<float> dataRef = {1.f, 2.f, 3.f, 4.f, 5.f};
  VertexBuffer vbDummy(dataRef, VertexBufferAttributes::None);
  GLuint name = vbDummy.getHandle().getName();
  VertexBuffer vb(std::move(vbDummy));

  EXPECT_EQ(0u, vbDummy.getHandle().getName());
  EXPECT_EQ(name, vb.getHandle().getName());
  EXPECT_EQ(dataRef.size() * sizeof(float), vb.getByteCount());
  EXPECT_EQ(dataRef, vb.getData<float>());
}



TEST_F(TestVertexBuffer, SetData)
{
  std::vector<float> zero(3u, 0.f);
  VertexBuffer vb(zero, VertexBufferAttributes::DynamicStorage);
  EXPECT_EQ(zero, vb.getData<float>());

  std::vector<float> dataRef = {0.1f, 0.2f, 0.3f};
  vb.setData(dataRef);
  EXPECT_EQ(dataRef, vb.getData<float>());
}



TEST_F(TestVertexBufferDeathTest, SetDataErrorInvalidSize)
{
  std::vector<float> data(5u, 0.f);
  VertexBuffer vb(data, VertexBufferAttributes::DynamicStorage);
  HOU_EXPECT_PRECONDITION(vb.setData(std::vector<float>(data.size() - 1, 1.f)));
  HOU_EXPECT_PRECONDITION(vb.setData(std::vector<float>(data.size() + 1, 1.f)));
}



TEST_F(TestVertexBuffer, SetSubData)
{
  std::vector<float> zero(6u, 0.f);
  VertexBuffer vb(zero, VertexBufferAttributes::DynamicStorage);
  EXPECT_EQ(zero, vb.getData<float>());

  std::vector<float> subData = {1.f, 2.f, 3.f};
  std::vector<float> dataRef = {0.0f, 1.f, 2.f, 3.f, 0.f, 0.f};
  vb.setSubData(1u, subData);
  EXPECT_EQ(dataRef, vb.getData<float>());
}



TEST_F(TestVertexBufferDeathTest, SetSubDataErrorInvalidSize)
{
  std::vector<float> data(6u, 0.f);
  VertexBuffer vb(data, VertexBufferAttributes::DynamicStorage);
  HOU_EXPECT_PRECONDITION(
    vb.setSubData(4u, std::vector<float>({0.1f, 0.2f, 0.3f})));
}



TEST_F(TestVertexBuffer, GetSubData)
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7};
  VertexBuffer vb(data, VertexBufferAttributes::DynamicStorage);
  std::vector<int> dataRef1{2, 3, 4};
  EXPECT_EQ(dataRef1, vb.getSubData<int>(1u, 3u));
  std::vector<int> dataRef2{6, 7};
  EXPECT_EQ(dataRef2, vb.getSubData<int>(5u, 2u));
}



TEST_F(TestVertexBufferDeathTest, GetSubDataErrorInvalidSize)
{
  std::vector<int> data{1, 2, 3, 4, 5, 6, 7};
  VertexBuffer vb(data, VertexBufferAttributes::DynamicStorage);
  HOU_EXPECT_PRECONDITION(vb.getSubData<int>(3u, 5u));
}
