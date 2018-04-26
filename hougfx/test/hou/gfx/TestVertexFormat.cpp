// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/VertexFormat.hpp"

using namespace hou;



namespace
{

class TestVertexFormat : public TestGfxBase
{};

class TestVertexFormatDeathTest : public TestVertexFormat
{};

}  // namespace



TEST_F(TestVertexFormat, VafSpanConstructor)
{
  std::vector<VertexAttribFormat> vafs = {
    VertexAttribFormat(GlType::Float, 3u, 12u, false),
    VertexAttribFormat(GlType::Float, 6u, 24u, true),
  };
  VertexFormat vf(2u, 3u, vafs);

  EXPECT_EQ(2, vf.getOffset());
  EXPECT_EQ(3u, vf.getStride());
  EXPECT_EQ(vafs, vf.getVertexAttribFormats());
}



TEST_F(TestVertexFormat, VafSpanConstructorAttribLimit)
{
  VertexAttribFormat vaf(GlType::Float, 3u, 12u, false);
  std::vector<VertexAttribFormat> vafs(
    VertexFormat::getMaxAttribFormatCount(), vaf);
  VertexFormat vf(2u, 3u, vafs);

  EXPECT_EQ(2, vf.getOffset());
  EXPECT_EQ(3u, vf.getStride());
  EXPECT_EQ(vafs, vf.getVertexAttribFormats());
}



TEST_F(TestVertexFormatDeathTest, VafSpanConstructorErrorTooManyAttribFormats)
{
  VertexAttribFormat vaf(GlType::Float, 3u, 12u, false);
  std::vector<VertexAttribFormat> vafs(
    VertexFormat::getMaxAttribFormatCount() + 1u, vaf);
  HOU_EXPECT_PRECONDITION(VertexFormat vf(2u, 3u, vafs));
}



TEST_F(TestVertexFormat, VafMoveConstructor)
{
  std::vector<VertexAttribFormat> vafs = {
    VertexAttribFormat(GlType::Float, 3u, 12u, false),
    VertexAttribFormat(GlType::Float, 6u, 24u, true),
  };
  std::vector<VertexAttribFormat> vafsRef = vafs;
  VertexFormat vf(2u, 3u, std::move(vafs));

  EXPECT_EQ(2, vf.getOffset());
  EXPECT_EQ(3u, vf.getStride());
  EXPECT_EQ(vafsRef, vf.getVertexAttribFormats());
}



TEST_F(TestVertexFormat, VafMoveConstructorAttribLimit)
{
  VertexAttribFormat vaf(GlType::Float, 3u, 12u, false);
  std::vector<VertexAttribFormat> vafs(
    VertexFormat::getMaxAttribFormatCount(), vaf);
  std::vector<VertexAttribFormat> vafsRef = vafs;
  VertexFormat vf(2u, 3u, std::move(vafs));

  EXPECT_EQ(2, vf.getOffset());
  EXPECT_EQ(3u, vf.getStride());
  EXPECT_EQ(vafsRef, vf.getVertexAttribFormats());
}



TEST_F(TestVertexFormatDeathTest, VafMoveConstructorErrorTooManyAttribFormats)
{
  VertexAttribFormat vaf(GlType::Float, 3u, 12u, false);
  std::vector<VertexAttribFormat> vafs(
    VertexFormat::getMaxAttribFormatCount() + 1u, vaf);
  HOU_EXPECT_PRECONDITION(VertexFormat vf(2u, 3u, std::move(vafs)));
}



TEST_F(TestVertexFormat, Comparison)
{
  std::vector<VertexAttribFormat> vafs1 = {
    VertexAttribFormat(GlType::Float, 3u, 12u, false),
    VertexAttribFormat(GlType::Float, 6u, 2u, true),
  };
  std::vector<VertexAttribFormat> vafs2 = {
    VertexAttribFormat(GlType::Float, 3u, 12u, false),
  };

  VertexFormat vf1(2, 3u, vafs1);
  VertexFormat vf2(1, 3u, vafs1);
  VertexFormat vf3(2, 2u, vafs1);
  VertexFormat vf4(2, 3u, vafs2);
  VertexFormat vf5(2, 3u, vafs1);

  EXPECT_TRUE(vf1 != vf2);
  EXPECT_TRUE(vf1 != vf3);
  EXPECT_TRUE(vf1 != vf4);
  EXPECT_TRUE(vf1 == vf5);

  EXPECT_FALSE(vf1 == vf2);
  EXPECT_FALSE(vf1 == vf3);
  EXPECT_FALSE(vf1 == vf4);
  EXPECT_FALSE(vf1 != vf5);
}



TEST_F(TestVertexFormat, OutputStreamOperator)
{
  std::vector<VertexAttribFormat> vafs = {
    VertexAttribFormat(GlType::Float, 3u, 12u, false),
    VertexAttribFormat(GlType::Float, 6u, 24u, true),
  };
  VertexFormat vf(2, 3u, vafs);
  const char* outRef
    = "{Offset = 2, Stride = 3, VertexAttribFormats = {{Type = Float, "
      "ElementCount = 3, ByteOffset = 12, MustBeNormalized = false}, {Type = "
      "Float, ElementCount = 6, ByteOffset = 24, MustBeNormalized = true}}}";
  HOU_EXPECT_OUTPUT(outRef, vf);
}
