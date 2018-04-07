// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/VertexArray.hpp"
#include "hou/gfx/VertexAttribFormat.hpp"
#include "hou/gfx/VertexBuffer.hpp"
#include "hou/gfx/VertexFormat.hpp"



using namespace hou;

namespace
{

class TestVertexArray : public TestGfxBase
{};

class TestVertexArrayDeathTest : public TestVertexArray
{};

}  // namespace



TEST_F(TestVertexArray, Binding)
{
  VertexArray va1;
  VertexArray va2;

  EXPECT_FALSE(va1.isBound());
  EXPECT_FALSE(va2.isBound());

  VertexArray::bind(va1);
  EXPECT_TRUE(va1.isBound());
  EXPECT_FALSE(va2.isBound());

  VertexArray::bind(va2);
  EXPECT_FALSE(va1.isBound());
  EXPECT_TRUE(va2.isBound());

  VertexArray::unbind();
  EXPECT_FALSE(va1.isBound());
  EXPECT_FALSE(va2.isBound());
}



TEST_F(TestVertexArray, DefaultConstructor)
{
  VertexArray va;
  EXPECT_NE(0u, va.getHandle().getName());
}



TEST_F(TestVertexArray, MoveConstructor)
{
  VertexArray va1;
  uint va1Id = va1.getHandle().getName();
  VertexArray va2(std::move(va1));

  EXPECT_EQ(va1Id, va2.getHandle().getName());
  EXPECT_EQ(0u, va1.getHandle().getName());
}



TEST_F(TestVertexArray, SetVertexData)
{
  VertexArray va;
  VertexBuffer vb(
    std::vector<float>{1, 2, 3, 4, 5, 6}, VertexBufferAttributes::None);
  VertexFormat vf(0, 3,
    {VertexAttribFormat(GlType::Float, 2, 0, false),
      VertexAttribFormat(GlType::Float, 1, 2, true)});
  va.setVertexData(vb, 0u, vf);
  SUCCEED();
}



TEST_F(TestVertexArray, SetVertexDataMaxBindingIndex)
{
  VertexArray va;
  VertexBuffer vb(
    std::vector<float>{1, 2, 3, 4, 5, 6}, VertexBufferAttributes::None);
  VertexFormat vf(0, 3,
    {VertexAttribFormat(GlType::Float, 2, 0, false),
      VertexAttribFormat(GlType::Float, 1, 2, true)});
  va.setVertexData(vb, VertexArray::getMaxBindingIndex(), vf);
  SUCCEED();
}



TEST_F(TestVertexArrayDeathTest, SetVertexDataErrorInvalidBindingIndex)
{
  VertexArray va;
  VertexBuffer vb(
    std::vector<float>{1, 2, 3, 4, 5, 6}, VertexBufferAttributes::None);
  VertexFormat vf(0, 3,
    {VertexAttribFormat(GlType::Float, 2, 0, false),
      VertexAttribFormat(GlType::Float, 1, 2, true)});
  HOU_EXPECT_PRECONDITION(
    va.setVertexData(vb, VertexArray::getMaxBindingIndex() + 1u, vf));
}



TEST_F(TestVertexArray, SetVertexDataMaxAttribFormats)
{
  VertexArray va;
  VertexBuffer vb(
    std::vector<float>{1, 2, 3, 4, 5, 6}, VertexBufferAttributes::None);
  VertexAttribFormat vaf(GlType::Float, 2, 0, false);
  HOU_EXPECT_PRECONDITION(
    va.setVertexData(vb, VertexArray::getMaxBindingIndex(),
      VertexFormat(0, 3,
        std::vector<VertexAttribFormat>(
          VertexFormat::getMaxAttribFormatCount() + 1u, vaf))));
}



TEST_F(TestVertexArray, SetElementData)
{
  VertexArray va;
  VertexBuffer vb(std::vector<float>{0, 1}, VertexBufferAttributes::None);
  va.setElementData(vb);
}