// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestData.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/Font.hpp"
#include "hou/gfx/FormattedText.hpp"

#include "hou/sys/BinaryFileIn.hpp"

using namespace hou;



namespace
{

class TestFormattedText : public TestGfxBase
{
public:
  Font loadFont(const std::string& path);
};

Font TestFormattedText::loadFont(const std::string& path)
{
  return Font(std::make_unique<BinaryFileIn>(path));
}

const std::string fontPath = getDataDir() + u8"NotoSans-Regular.ttf";

}



TEST_F(TestFormattedText, Constructor)
{
  Font f = loadFont(fontPath);
  std::u32string s = U"A";
  FormattedText ft(s, f);
  EXPECT_EQ(Image3R(Vec3u(1u, 1u, 1u)), ft.getAtlas().getImage<PixelFormat::R>());
  EXPECT_EQ(TextMesh::VertexCollectionType(), ft.getMesh().getVertices());
}



TEST_F(TestFormattedText, MoveConstructor)
{
  Font f = loadFont(fontPath);
  std::u32string s = U"A";
  FormattedText ftDummy(s, f);
  FormattedText ft(std::move(ftDummy));
  EXPECT_EQ(Image3R(Vec3u(1u, 1u, 1u)), ft.getAtlas().getImage<PixelFormat::R>());
  EXPECT_EQ(TextMesh::VertexCollectionType(), ft.getMesh().getVertices());
}

