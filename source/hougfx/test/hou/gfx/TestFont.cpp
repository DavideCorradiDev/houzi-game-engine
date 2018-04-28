// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestData.hpp"

#include "hou/gfx/Font.hpp"
#include "hou/gfx/GfxError.hpp"
#include "hou/gfx/Glyph.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle.hpp"

#include "hou/sys/BinaryFileIn.hpp"

#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class TestFont : public Test
{};
class TestFontDeathTest : public TestFont
{};

const std::string fontName = getDataDir() + u8"NotoSans-Regular.ttf";

}  // namespace



TEST_F(TestFont, DataConstructor)
{
  std::vector<uint8_t> buffer;
  {
    BinaryFileIn inf(fontName);
    buffer.resize(inf.getByteCount());
    inf.read(buffer.data(), buffer.size());
  }
  // span<const uint8_t> s(buffer);
  // Font f(s);
  // Font f(span<const uint8_t> s(buffer));
  Font f(buffer);

  EXPECT_EQ(1u, f.getFaceIndexCount());
  EXPECT_EQ(0u, f.getFaceIndex());
  EXPECT_EQ(10u, f.getPixelHeight());
  EXPECT_TRUE(f.hasHorizontal());
  EXPECT_FALSE(f.hasVertical());
  EXPECT_FALSE(f.hasKerning());
  EXPECT_TRUE(f.isScalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f.getGlyphBoundingBox());
  EXPECT_EQ(896, f.getLineSpacing());
  EXPECT_EQ(832, f.getMaxAdvance());
  EXPECT_EQ(857, f.getMaxHorizontalAdvance());
  EXPECT_EQ(872, f.getMaxVerticalAdvance());
  EXPECT_EQ(2416u, f.getGlyphCount());
}



TEST_F(TestFontDeathTest, DataConstructorErrorInvalidData)
{
  std::vector<uint8_t> data;
  HOU_EXPECT_ERROR(
    Font f(data), std::runtime_error, get_text(GfxError::FontLoadFace));
}



TEST_F(TestFont, StreamConstructor)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  EXPECT_EQ(1u, f.getFaceIndexCount());
  EXPECT_EQ(0u, f.getFaceIndex());
  EXPECT_EQ(10u, f.getPixelHeight());
  EXPECT_TRUE(f.hasHorizontal());
  EXPECT_FALSE(f.hasVertical());
  EXPECT_FALSE(f.hasKerning());
  EXPECT_TRUE(f.isScalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f.getGlyphBoundingBox());
  EXPECT_EQ(896, f.getLineSpacing());
  EXPECT_EQ(832, f.getMaxAdvance());
  EXPECT_EQ(857, f.getMaxHorizontalAdvance());
  EXPECT_EQ(872, f.getMaxVerticalAdvance());
  EXPECT_EQ(2416u, f.getGlyphCount());
}



TEST_F(TestFont, MoveConstructor)
{
  Font fDummy(std::make_unique<BinaryFileIn>(fontName));
  Font f(std::move(fDummy));

  EXPECT_EQ(1u, f.getFaceIndexCount());
  EXPECT_EQ(0u, f.getFaceIndex());
  EXPECT_EQ(10u, f.getPixelHeight());
  EXPECT_TRUE(f.hasHorizontal());
  EXPECT_FALSE(f.hasVertical());
  EXPECT_FALSE(f.hasKerning());
  EXPECT_TRUE(f.isScalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f.getGlyphBoundingBox());
  EXPECT_EQ(896, f.getLineSpacing());
  EXPECT_EQ(832, f.getMaxAdvance());
  EXPECT_EQ(857, f.getMaxHorizontalAdvance());
  EXPECT_EQ(872, f.getMaxVerticalAdvance());
  EXPECT_EQ(2416u, f.getGlyphCount());
}



TEST_F(TestFont, MultiThreadingCreation)
{
  std::unique_ptr<Font> f1(nullptr);
  std::unique_ptr<Font> f2(nullptr);

  auto threadFun = [](std::unique_ptr<Font>& fontPtr) {
    fontPtr.reset(new Font(std::make_unique<BinaryFileIn>(fontName)));
  };

  std::thread t1(threadFun, std::ref(f1));
  std::thread t2(threadFun, std::ref(f2));

  t1.join();
  t2.join();

  EXPECT_EQ(1u, f1->getFaceIndexCount());
  EXPECT_EQ(0u, f1->getFaceIndex());
  EXPECT_EQ(10u, f1->getPixelHeight());
  EXPECT_TRUE(f1->hasHorizontal());
  EXPECT_FALSE(f1->hasVertical());
  EXPECT_TRUE(f1->isScalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f1->getGlyphBoundingBox());
  EXPECT_EQ(896, f1->getLineSpacing());
  EXPECT_EQ(832, f1->getMaxAdvance());
  EXPECT_EQ(857, f1->getMaxHorizontalAdvance());
  EXPECT_EQ(872, f1->getMaxVerticalAdvance());
  EXPECT_EQ(2416u, f1->getGlyphCount());

  EXPECT_EQ(1u, f2->getFaceIndexCount());
  EXPECT_EQ(0u, f2->getFaceIndex());
  EXPECT_EQ(10u, f2->getPixelHeight());
  EXPECT_TRUE(f2->hasHorizontal());
  EXPECT_FALSE(f2->hasVertical());
  EXPECT_TRUE(f2->isScalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f2->getGlyphBoundingBox());
  EXPECT_EQ(896, f2->getLineSpacing());
  EXPECT_EQ(832, f2->getMaxAdvance());
  EXPECT_EQ(857, f2->getMaxHorizontalAdvance());
  EXPECT_EQ(872, f2->getMaxVerticalAdvance());
  EXPECT_EQ(2416u, f2->getGlyphCount());
}



TEST_F(TestFontDeathTest, FailedCreation)
{
  // Valid file but not a font file.
  HOU_EXPECT_ERROR(
    Font f(std::make_unique<BinaryFileIn>(getDataDir() + u8"TestImage.png")),
    std::runtime_error, get_text(GfxError::FontLoadFace));
}



TEST_F(TestFont, MultiThreadingDestruction)
{
  auto threadFun = []() { Font f(std::make_unique<BinaryFileIn>(fontName)); };

  std::thread t1(threadFun);
  std::thread t2(threadFun);

  t1.join();
  t2.join();

  SUCCEED();
}



TEST_F(TestFont, SetFaceIndexSameValue)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));
  f.setFaceIndex(0u);
  EXPECT_EQ(0u, f.getFaceIndex());
}



TEST_F(TestFontDeathTest, SetFaceIndexErrorOutOfBounds)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));
  HOU_EXPECT_PRECONDITION(f.setFaceIndex(f.getFaceIndexCount()));
}



TEST_F(TestFont, SetPixelHeight)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));
  f.setPixelHeight(20u);

  EXPECT_EQ(20u, f.getPixelHeight());
}



TEST_F(TestFont, GetGlyph)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  Glyph g1Ref(
    Image2R(vec2u(5u, 5u),
      std::vector<Image2R::Pixel>{Image2R::Pixel(0u), Image2R::Pixel(152u),
        Image2R::Pixel(180u), Image2R::Pixel(199u), Image2R::Pixel(87u),
        Image2R::Pixel(0u), Image2R::Pixel(4u), Image2R::Pixel(0u),
        Image2R::Pixel(30u), Image2R::Pixel(195u), Image2R::Pixel(26u),
        Image2R::Pixel(168u), Image2R::Pixel(160u), Image2R::Pixel(162u),
        Image2R::Pixel(204u), Image2R::Pixel(125u), Image2R::Pixel(120u),
        Image2R::Pixel(0u), Image2R::Pixel(54u), Image2R::Pixel(204u),
        Image2R::Pixel(51u), Image2R::Pixel(208u), Image2R::Pixel(177u),
        Image2R::Pixel(142u), Image2R::Pixel(191u)}),
    GlyphMetrics(vec2u(320u, 320u), vec2i(0, -320), 384, vec2i(0, 0), 0));
  Glyph g2Ref(
    Image2R(vec2u(6u, 7u),
      std::vector<Image2R::Pixel>{Image2R::Pixel(40u), Image2R::Pixel(188u),
        Image2R::Pixel(0u), Image2R::Pixel(0u), Image2R::Pixel(0u),
        Image2R::Pixel(0u), Image2R::Pixel(40u), Image2R::Pixel(187u),
        Image2R::Pixel(0u), Image2R::Pixel(0u), Image2R::Pixel(0u),
        Image2R::Pixel(0u), Image2R::Pixel(40u), Image2R::Pixel(208u),
        Image2R::Pixel(172u), Image2R::Pixel(190u), Image2R::Pixel(173u),
        Image2R::Pixel(9u), Image2R::Pixel(40u), Image2R::Pixel(230u),
        Image2R::Pixel(8u), Image2R::Pixel(0u), Image2R::Pixel(137u),
        Image2R::Pixel(106u), Image2R::Pixel(40u), Image2R::Pixel(194u),
        Image2R::Pixel(0u), Image2R::Pixel(0u), Image2R::Pixel(87u),
        Image2R::Pixel(142u), Image2R::Pixel(40u), Image2R::Pixel(232u),
        Image2R::Pixel(9u), Image2R::Pixel(0u), Image2R::Pixel(140u),
        Image2R::Pixel(104u), Image2R::Pixel(40u), Image2R::Pixel(185u),
        Image2R::Pixel(175u), Image2R::Pixel(191u), Image2R::Pixel(171u),
        Image2R::Pixel(8u)}),
    GlyphMetrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));

  EXPECT_EQ(g1Ref, f.getGlyph('a'));
  EXPECT_EQ(g2Ref, f.getGlyph('b'));
}



TEST_F(TestFont, GetGlyphNotExisting)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));
  Glyph gRef(
    Image2R(vec2u(6u, 7u),
      std::vector<Image2R::Pixel>{16, 188, 132, 132, 188, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 188, 132, 132, 188, 12}),
    GlyphMetrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));
  EXPECT_EQ(gRef, f.getGlyph(U'\U00004f68'));
}



TEST_F(TestFont, GetKerning)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  EXPECT_EQ(vec2i(0, 0), f.getKerning('a', 'b'));
  EXPECT_EQ(vec2i(0, 0), f.getKerning('j', 'k'));
}



TEST_F(TestFont, GetPixelGlyphBoundingBox)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  EXPECT_EQ(recti(-356, -175, 1202, 845), f.getGlyphBoundingBox());
  HOU_EXPECT_FLOAT_CLOSE(rectf(-5.5625f, -2.734375f, 18.78125f, 13.203125),
    f.getPixelGlyphBoundingBox());
}



TEST_F(TestFont, GetPixelLineSpacing)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  EXPECT_EQ(896, f.getLineSpacing());
  HOU_EXPECT_FLOAT_CLOSE(14.f, f.getPixelLineSpacing());
}



TEST_F(TestFont, GetPixelMaxAdvance)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  EXPECT_EQ(832, f.getMaxAdvance());
  HOU_EXPECT_FLOAT_CLOSE(13.f, f.getMaxPixelAdvance());
}



TEST_F(TestFont, GetPixelMaxHorizontalAdvance)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  EXPECT_EQ(857, f.getMaxHorizontalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(13.390625f, f.getMaxPixelHorizontalAdvance());
}



TEST_F(TestFont, GetPixelMaxVerticalAdvance)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  EXPECT_EQ(872, f.getMaxVerticalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(13.625f, f.getMaxPixelVerticalAdvance());
}



TEST_F(TestFont, GetPixelKerning)
{
  Font f(std::make_unique<BinaryFileIn>(fontName));

  EXPECT_EQ(vec2i(0, 0), f.getKerning('a', 'b'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.getPixelKerning('a', 'b'));

  EXPECT_EQ(vec2i(0, 0), f.getKerning('j', 'k'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.getPixelKerning('j', 'k'));
}
