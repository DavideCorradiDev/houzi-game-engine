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

using IntBuffer = StaticVertexBuffer<int>;
using FloatBuffer = StaticVertexBuffer<float>;
using DynamicFloatBuffer = DynamicVertexBuffer<float>;

class TestVertexBuffer : public TestGfxBase
{};

class TestVertexBufferDeathTest : public TestVertexBuffer
{};

}  // namespace



TEST_F(TestVertexBuffer, Binding)
{
  IntBuffer vb1(2u);
  IntBuffer vb2(2u);

  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::ElementArray));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::ElementArray));

  IntBuffer::bind(vb1, VertexBufferTarget::Array);
  EXPECT_TRUE(vb1.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::ElementArray));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::ElementArray));

  IntBuffer::bind(vb1, VertexBufferTarget::ElementArray);
  EXPECT_TRUE(vb1.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::Array));
  EXPECT_TRUE(vb1.isBound(VertexBufferTarget::ElementArray));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::ElementArray));

  IntBuffer::bind(vb2, VertexBufferTarget::Array);
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::Array));
  EXPECT_TRUE(vb2.isBound(VertexBufferTarget::Array));
  EXPECT_TRUE(vb1.isBound(VertexBufferTarget::ElementArray));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::ElementArray));

  IntBuffer::bind(vb2, VertexBufferTarget::ElementArray);
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::Array));
  EXPECT_TRUE(vb2.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::ElementArray));
  EXPECT_TRUE(vb2.isBound(VertexBufferTarget::ElementArray));

  IntBuffer::unbind(VertexBufferTarget::Array);
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::ElementArray));
  EXPECT_TRUE(vb2.isBound(VertexBufferTarget::ElementArray));

  IntBuffer::unbind(VertexBufferTarget::ElementArray);
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::Array));
  EXPECT_FALSE(vb1.isBound(VertexBufferTarget::ElementArray));
  EXPECT_FALSE(vb2.isBound(VertexBufferTarget::ElementArray));
}



TEST_F(TestVertexBuffer, SizeConstructor)
{
  uint sizeRef = 7u;
  IntBuffer vb(sizeRef);

  EXPECT_NE(0u, vb.getHandle().getName());
  EXPECT_EQ(sizeRef * sizeof(IntBuffer::ValueType), vb.getByteCount());
  EXPECT_EQ(sizeRef, vb.getSize());
  EXPECT_EQ(std::vector<int>(sizeRef, 0u), vb.getData());
}



TEST_F(TestVertexBuffer, DataConstructor)
{
  DynamicFloatBuffer::DataType dataRef = {1.f, 2.f, 3.f, 4.f, 5.f};
  FloatBuffer vb(dataRef);

  EXPECT_NE(0u, vb.getHandle().getName());
  EXPECT_EQ(dataRef.size() * sizeof(float), vb.getByteCount());
  EXPECT_EQ(dataRef, vb.getData());
}



TEST_F(TestVertexBuffer, MoveConstructor)
{
  DynamicFloatBuffer::DataType dataRef = {1.f, 2.f, 3.f, 4.f, 5.f};
  FloatBuffer vbDummy(dataRef);
  GLuint name = vbDummy.getHandle().getName();
  FloatBuffer vb(std::move(vbDummy));

  EXPECT_EQ(0u, vbDummy.getHandle().getName());
  EXPECT_EQ(name, vb.getHandle().getName());
  EXPECT_EQ(dataRef.size() * sizeof(float), vb.getByteCount());
  EXPECT_EQ(dataRef, vb.getData());
}



TEST_F(TestVertexBuffer, GetSubData)
{
  DynamicFloatBuffer::DataType dataRef = {1.f, 2.f, 3.f, 4.f, 5.f};
  DynamicFloatBuffer::DataType subDataRef = {2.f, 3.f};
  FloatBuffer vb(dataRef);
  EXPECT_EQ(subDataRef, vb.getSubData(1u, 2u));
}



TEST_F(TestVertexBuffer, GetSubDataLimit)
{
  DynamicFloatBuffer::DataType dataRef = {1.f, 2.f, 3.f, 4.f, 5.f};
  DynamicFloatBuffer::DataType subDataRef = {3.f, 4.f, 5.f};
  FloatBuffer vb(dataRef);
  EXPECT_EQ(dataRef, vb.getSubData(0u, vb.getSize()));
  EXPECT_EQ(subDataRef, vb.getSubData(2u, 3u));
}



TEST_F(TestVertexBufferDeathTest, GetSubDataErrorOverflow)
{
  DynamicFloatBuffer::DataType dataRef = {1.f, 2.f, 3.f, 4.f, 5.f};
  FloatBuffer vb(dataRef);
  HOU_EXPECT_PRECONDITION(vb.getSubData(0u, vb.getSize() + 1u));
  HOU_EXPECT_PRECONDITION(vb.getSubData(2u, vb.getSize() - 1u));
}



TEST_F(TestVertexBuffer, SetSubData)
{
  DynamicFloatBuffer vb(6u);
  EXPECT_EQ(DynamicFloatBuffer::DataType(6u, 0.f), vb.getData());

  DynamicFloatBuffer::DataType subDataRef = {1.f, 2.f, 3.f};
  DynamicFloatBuffer::DataType dataRef = {0.0f, 1.f, 2.f, 3.f, 0.f, 0.f};
  vb.setSubData(1u, subDataRef);
  EXPECT_EQ(dataRef, vb.getData());
  EXPECT_EQ(subDataRef, vb.getSubData(1u, 3u));
}



TEST_F(TestVertexBuffer, SetSubDataLimit)
{
  DynamicFloatBuffer vb(6u);
  EXPECT_EQ(DynamicFloatBuffer::DataType(6u, 0.f), vb.getData());

  DynamicFloatBuffer::DataType subDataRef = {1.f, 2.f, 3.f};
  DynamicFloatBuffer::DataType dataRef = {0.f, 0.f, 0.f, 1.f, 2.f, 3.f};
  vb.setSubData(3u, subDataRef);
  EXPECT_EQ(dataRef, vb.getData());
  EXPECT_EQ(subDataRef, vb.getSubData(3u, 3u));

  DynamicFloatBuffer::DataType dataRef2 = {4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
  vb.setSubData(0u, dataRef2);
  EXPECT_EQ(dataRef2, vb.getData());
  EXPECT_EQ(dataRef2, vb.getSubData(0u, 6u));
}



TEST_F(TestVertexBufferDeathTest, SetSubDataErrorOverflow)
{
  DynamicFloatBuffer vb(6u);
  DynamicFloatBuffer::DataType data(3u, 0.f);
  HOU_EXPECT_PRECONDITION(vb.setSubData(vb.getSize() - data.size() + 1u, data));
}



TEST_F(TestVertexBuffer, SetData)
{
  DynamicFloatBuffer vb(3u);
  EXPECT_EQ(DynamicFloatBuffer::DataType(vb.getSize(), 0.f), vb.getData());

  DynamicFloatBuffer::DataType dataRef = {0.1f, 0.2f, 0.3f};
  vb.setData(dataRef);
  EXPECT_EQ(dataRef, vb.getData());
}



TEST_F(TestVertexBufferDeathTest, SetDataErrorTooFewElements)
{
  DynamicFloatBuffer vb(3u);
  DynamicFloatBuffer::DataType data(vb.getSize() - 1u, 0.f);
  HOU_EXPECT_PRECONDITION(vb.setData(data));
}



TEST_F(TestVertexBufferDeathTest, SetDataErrorTooManyElements)
{
  DynamicFloatBuffer vb(3u);
  DynamicFloatBuffer::DataType data(vb.getSize() + 1u, 0.f);
  HOU_EXPECT_PRECONDITION(vb.setData(data));
}
