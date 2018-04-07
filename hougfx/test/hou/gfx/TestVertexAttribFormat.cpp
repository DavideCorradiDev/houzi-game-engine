// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/VertexAttribFormat.hpp"

using namespace hou;



namespace
{

class TestVertexAttribFormat : public TestGfxBase
{};

}  // namespace



TEST_F(TestVertexAttribFormat, Constructor)
{
  VertexAttribFormat vaf(GlType::Float, 3u, 12u, false);
  EXPECT_EQ(GlType::Float, vaf.getType());
  EXPECT_EQ(3u, vaf.getElementCount());
  EXPECT_EQ(12u, vaf.getByteOffset());
  EXPECT_EQ(false, vaf.mustBeNormalized());
}



TEST_F(TestVertexAttribFormat, Comparison)
{
  VertexAttribFormat vaf1(GlType::Float, 3u, 12u, false);
  VertexAttribFormat vaf2(GlType::Byte, 3u, 12u, false);
  VertexAttribFormat vaf3(GlType::Float, 4u, 12u, false);
  VertexAttribFormat vaf4(GlType::Float, 3u, 10u, false);
  VertexAttribFormat vaf5(GlType::Float, 3u, 12u, true);
  VertexAttribFormat vaf6(GlType::Float, 3u, 12u, false);

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



TEST_F(TestVertexAttribFormat, OutputStreamOperator)
{
  VertexAttribFormat vaf(GlType::Float, 3u, 12u, false);
  const char* outRef = "{Type = Float, ElementCount = 3, ByteOffset = 12, "
                       "MustBeNormalized = false}";
  HOU_EXPECT_OUTPUT(outRef, vaf);
}
