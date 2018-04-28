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

#include "hou/sys/binary_file_in.hpp"

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
    binary_file_in inf(fontName);
    buffer.resize(inf.get_byte_count());
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
  Font f(std::make_unique<binary_file_in>(fontName));

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
  Font fDummy(std::make_unique<binary_file_in>(fontName));
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
    fontPtr.reset(new Font(std::make_unique<binary_file_in>(fontName)));
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
  // Valid ph_file but not a font ph_file.
  HOU_EXPECT_ERROR(
    Font f(std::make_unique<binary_file_in>(getDataDir() + u8"TestImage.png")),
    std::runtime_error, get_text(GfxError::FontLoadFace));
}



TEST_F(TestFont, MultiThreadingDestruction)
{
  auto threadFun = []() { Font f(std::make_unique<binary_file_in>(fontName)); };

  std::thread t1(threadFun);
  std::thread t2(threadFun);

  t1.join();
  t2.join();

  SUCCEED();
}



TEST_F(TestFont, SetFaceIndexSameValue)
{
  Font f(std::make_unique<binary_file_in>(fontName));
  f.setFaceIndex(0u);
  EXPECT_EQ(0u, f.getFaceIndex());
}



TEST_F(TestFontDeathTest, SetFaceIndexErrorOutOfBounds)
{
  Font f(std::make_unique<binary_file_in>(fontName));
  HOU_EXPECT_PRECONDITION(f.setFaceIndex(f.getFaceIndexCount()));
}



TEST_F(TestFont, SetPixelHeight)
{
  Font f(std::make_unique<binary_file_in>(fontName));
  f.setPixelHeight(20u);

  EXPECT_EQ(20u, f.getPixelHeight());
}



TEST_F(TestFont, GetGlyph)
{
  Font f(std::make_unique<binary_file_in>(fontName));

  Glyph g1Ref(
    image2R(vec2u(5u, 5u),
      std::vector<image2R::pixel>{image2R::pixel(0u), image2R::pixel(152u),
        image2R::pixel(180u), image2R::pixel(199u), image2R::pixel(87u),
        image2R::pixel(0u), image2R::pixel(4u), image2R::pixel(0u),
        image2R::pixel(30u), image2R::pixel(195u), image2R::pixel(26u),
        image2R::pixel(168u), image2R::pixel(160u), image2R::pixel(162u),
        image2R::pixel(204u), image2R::pixel(125u), image2R::pixel(120u),
        image2R::pixel(0u), image2R::pixel(54u), image2R::pixel(204u),
        image2R::pixel(51u), image2R::pixel(208u), image2R::pixel(177u),
        image2R::pixel(142u), image2R::pixel(191u)}),
    GlyphMetrics(vec2u(320u, 320u), vec2i(0, -320), 384, vec2i(0, 0), 0));
  Glyph g2Ref(
    image2R(vec2u(6u, 7u),
      std::vector<image2R::pixel>{image2R::pixel(40u), image2R::pixel(188u),
        image2R::pixel(0u), image2R::pixel(0u), image2R::pixel(0u),
        image2R::pixel(0u), image2R::pixel(40u), image2R::pixel(187u),
        image2R::pixel(0u), image2R::pixel(0u), image2R::pixel(0u),
        image2R::pixel(0u), image2R::pixel(40u), image2R::pixel(208u),
        image2R::pixel(172u), image2R::pixel(190u), image2R::pixel(173u),
        image2R::pixel(9u), image2R::pixel(40u), image2R::pixel(230u),
        image2R::pixel(8u), image2R::pixel(0u), image2R::pixel(137u),
        image2R::pixel(106u), image2R::pixel(40u), image2R::pixel(194u),
        image2R::pixel(0u), image2R::pixel(0u), image2R::pixel(87u),
        image2R::pixel(142u), image2R::pixel(40u), image2R::pixel(232u),
        image2R::pixel(9u), image2R::pixel(0u), image2R::pixel(140u),
        image2R::pixel(104u), image2R::pixel(40u), image2R::pixel(185u),
        image2R::pixel(175u), image2R::pixel(191u), image2R::pixel(171u),
        image2R::pixel(8u)}),
    GlyphMetrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));

  EXPECT_EQ(g1Ref, f.getGlyph('a'));
  EXPECT_EQ(g2Ref, f.getGlyph('b'));
}



TEST_F(TestFont, GetGlyphNotExisting)
{
  Font f(std::make_unique<binary_file_in>(fontName));
  Glyph gRef(
    image2R(vec2u(6u, 7u),
      std::vector<image2R::pixel>{16, 188, 132, 132, 188, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 188, 132, 132, 188, 12}),
    GlyphMetrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));
  EXPECT_EQ(gRef, f.getGlyph(U'\U00004f68'));
}



TEST_F(TestFont, GetKerning)
{
  Font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(vec2i(0, 0), f.getKerning('a', 'b'));
  EXPECT_EQ(vec2i(0, 0), f.getKerning('j', 'k'));
}



TEST_F(TestFont, GetPixelGlyphBoundingBox)
{
  Font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(recti(-356, -175, 1202, 845), f.getGlyphBoundingBox());
  HOU_EXPECT_FLOAT_CLOSE(rectf(-5.5625f, -2.734375f, 18.78125f, 13.203125),
    f.getPixelGlyphBoundingBox());
}



TEST_F(TestFont, GetPixelLineSpacing)
{
  Font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(896, f.getLineSpacing());
  HOU_EXPECT_FLOAT_CLOSE(14.f, f.getPixelLineSpacing());
}



TEST_F(TestFont, GetPixelMaxAdvance)
{
  Font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(832, f.getMaxAdvance());
  HOU_EXPECT_FLOAT_CLOSE(13.f, f.getMaxPixelAdvance());
}



TEST_F(TestFont, GetPixelMaxHorizontalAdvance)
{
  Font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(857, f.getMaxHorizontalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(13.390625f, f.getMaxPixelHorizontalAdvance());
}



TEST_F(TestFont, GetPixelMaxVerticalAdvance)
{
  Font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(872, f.getMaxVerticalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(13.625f, f.getMaxPixelVerticalAdvance());
}



TEST_F(TestFont, GetPixelKerning)
{
  Font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(vec2i(0, 0), f.getKerning('a', 'b'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.getPixelKerning('a', 'b'));

  EXPECT_EQ(vec2i(0, 0), f.getKerning('j', 'k'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.getPixelKerning('j', 'k'));
}
