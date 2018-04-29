// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestData.hpp"

#include "hou/gfx/font.hpp"
#include "hou/gfx/gfx_error.hpp"
#include "hou/gfx/glyph.hpp"

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
  // font f(s);
  // font f(span<const uint8_t> s(buffer));
  font f(buffer);

  EXPECT_EQ(1u, f.get_face_index_count());
  EXPECT_EQ(0u, f.get_face_index());
  EXPECT_EQ(10u, f.get_pixel_height());
  EXPECT_TRUE(f.has_horizontal());
  EXPECT_FALSE(f.has_vertical());
  EXPECT_FALSE(f.has_kerning());
  EXPECT_TRUE(f.is_scalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f.get_glyph_bounding_box());
  EXPECT_EQ(896, f.get_line_spacing());
  EXPECT_EQ(832, f.get_max_advance());
  EXPECT_EQ(857, f.get_max_horizontal_advance());
  EXPECT_EQ(872, f.get_max_vertical_advance());
  EXPECT_EQ(2416u, f.get_glyph_count());
}



TEST_F(TestFontDeathTest, DataConstructorErrorInvalidData)
{
  std::vector<uint8_t> data;
  HOU_EXPECT_ERROR(
    font f(data), std::runtime_error, get_text(gfx_error::font_load_face));
}



TEST_F(TestFont, StreamConstructor)
{
  font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(1u, f.get_face_index_count());
  EXPECT_EQ(0u, f.get_face_index());
  EXPECT_EQ(10u, f.get_pixel_height());
  EXPECT_TRUE(f.has_horizontal());
  EXPECT_FALSE(f.has_vertical());
  EXPECT_FALSE(f.has_kerning());
  EXPECT_TRUE(f.is_scalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f.get_glyph_bounding_box());
  EXPECT_EQ(896, f.get_line_spacing());
  EXPECT_EQ(832, f.get_max_advance());
  EXPECT_EQ(857, f.get_max_horizontal_advance());
  EXPECT_EQ(872, f.get_max_vertical_advance());
  EXPECT_EQ(2416u, f.get_glyph_count());
}



TEST_F(TestFont, MoveConstructor)
{
  font fDummy(std::make_unique<binary_file_in>(fontName));
  font f(std::move(fDummy));

  EXPECT_EQ(1u, f.get_face_index_count());
  EXPECT_EQ(0u, f.get_face_index());
  EXPECT_EQ(10u, f.get_pixel_height());
  EXPECT_TRUE(f.has_horizontal());
  EXPECT_FALSE(f.has_vertical());
  EXPECT_FALSE(f.has_kerning());
  EXPECT_TRUE(f.is_scalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f.get_glyph_bounding_box());
  EXPECT_EQ(896, f.get_line_spacing());
  EXPECT_EQ(832, f.get_max_advance());
  EXPECT_EQ(857, f.get_max_horizontal_advance());
  EXPECT_EQ(872, f.get_max_vertical_advance());
  EXPECT_EQ(2416u, f.get_glyph_count());
}



TEST_F(TestFont, MultiThreadingCreation)
{
  std::unique_ptr<font> f1(nullptr);
  std::unique_ptr<font> f2(nullptr);

  auto threadFun = [](std::unique_ptr<font>& fontPtr) {
    fontPtr.reset(new font(std::make_unique<binary_file_in>(fontName)));
  };

  std::thread t1(threadFun, std::ref(f1));
  std::thread t2(threadFun, std::ref(f2));

  t1.join();
  t2.join();

  EXPECT_EQ(1u, f1->get_face_index_count());
  EXPECT_EQ(0u, f1->get_face_index());
  EXPECT_EQ(10u, f1->get_pixel_height());
  EXPECT_TRUE(f1->has_horizontal());
  EXPECT_FALSE(f1->has_vertical());
  EXPECT_TRUE(f1->is_scalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f1->get_glyph_bounding_box());
  EXPECT_EQ(896, f1->get_line_spacing());
  EXPECT_EQ(832, f1->get_max_advance());
  EXPECT_EQ(857, f1->get_max_horizontal_advance());
  EXPECT_EQ(872, f1->get_max_vertical_advance());
  EXPECT_EQ(2416u, f1->get_glyph_count());

  EXPECT_EQ(1u, f2->get_face_index_count());
  EXPECT_EQ(0u, f2->get_face_index());
  EXPECT_EQ(10u, f2->get_pixel_height());
  EXPECT_TRUE(f2->has_horizontal());
  EXPECT_FALSE(f2->has_vertical());
  EXPECT_TRUE(f2->is_scalable());
  EXPECT_EQ(recti(-356, -175, 1202, 845), f2->get_glyph_bounding_box());
  EXPECT_EQ(896, f2->get_line_spacing());
  EXPECT_EQ(832, f2->get_max_advance());
  EXPECT_EQ(857, f2->get_max_horizontal_advance());
  EXPECT_EQ(872, f2->get_max_vertical_advance());
  EXPECT_EQ(2416u, f2->get_glyph_count());
}



TEST_F(TestFontDeathTest, FailedCreation)
{
  // Valid ph_file but not a ph_font ph_file.
  HOU_EXPECT_ERROR(
    font f(std::make_unique<binary_file_in>(getDataDir() + u8"TestImage.png")),
    std::runtime_error, get_text(gfx_error::font_load_face));
}



TEST_F(TestFont, MultiThreadingDestruction)
{
  auto threadFun = []() { font f(std::make_unique<binary_file_in>(fontName)); };

  std::thread t1(threadFun);
  std::thread t2(threadFun);

  t1.join();
  t2.join();

  SUCCEED();
}



TEST_F(TestFont, SetFaceIndexSameValue)
{
  font f(std::make_unique<binary_file_in>(fontName));
  f.set_face_index(0u);
  EXPECT_EQ(0u, f.get_face_index());
}



TEST_F(TestFontDeathTest, SetFaceIndexErrorOutOfBounds)
{
  font f(std::make_unique<binary_file_in>(fontName));
  HOU_EXPECT_PRECONDITION(f.set_face_index(f.get_face_index_count()));
}



TEST_F(TestFont, SetPixelHeight)
{
  font f(std::make_unique<binary_file_in>(fontName));
  f.set_pixel_height(20u);

  EXPECT_EQ(20u, f.get_pixel_height());
}



TEST_F(TestFont, GetGlyph)
{
  font f(std::make_unique<binary_file_in>(fontName));

  glyph g1Ref(
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
    glyph_metrics(vec2u(320u, 320u), vec2i(0, -320), 384, vec2i(0, 0), 0));
  glyph g2Ref(
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
    glyph_metrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));

  EXPECT_EQ(g1Ref, f.get_glyph('a'));
  EXPECT_EQ(g2Ref, f.get_glyph('b'));
}



TEST_F(TestFont, GetGlyphNotExisting)
{
  font f(std::make_unique<binary_file_in>(fontName));
  glyph gRef(
    image2R(vec2u(6u, 7u),
      std::vector<image2R::pixel>{16, 188, 132, 132, 188, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 188, 132, 132, 188, 12}),
    glyph_metrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));
  EXPECT_EQ(gRef, f.get_glyph(U'\U00004f68'));
}



TEST_F(TestFont, GetKerning)
{
  font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('a', 'b'));
  EXPECT_EQ(vec2i(0, 0), f.get_kerning('j', 'k'));
}



TEST_F(TestFont, GetPixelGlyphBoundingBox)
{
  font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(recti(-356, -175, 1202, 845), f.get_glyph_bounding_box());
  HOU_EXPECT_FLOAT_CLOSE(rectf(-5.5625f, -2.734375f, 18.78125f, 13.203125),
    f.get_pixel_glyph_bounding_box());
}



TEST_F(TestFont, GetPixelLineSpacing)
{
  font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(896, f.get_line_spacing());
  HOU_EXPECT_FLOAT_CLOSE(14.f, f.get_pixel_line_spacing());
}



TEST_F(TestFont, GetPixelMaxAdvance)
{
  font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(832, f.get_max_advance());
  HOU_EXPECT_FLOAT_CLOSE(13.f, f.get_pixel_max_advance());
}



TEST_F(TestFont, GetPixelMaxHorizontalAdvance)
{
  font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(857, f.get_max_horizontal_advance());
  HOU_EXPECT_FLOAT_CLOSE(13.390625f, f.get_pixel_max_horizontal_advance());
}



TEST_F(TestFont, GetPixelMaxVerticalAdvance)
{
  font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(872, f.get_max_vertical_advance());
  HOU_EXPECT_FLOAT_CLOSE(13.625f, f.get_pixel_max_vertical_advance());
}



TEST_F(TestFont, GetPixelKerning)
{
  font f(std::make_unique<binary_file_in>(fontName));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('a', 'b'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.get_pixel_kerning('a', 'b'));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('j', 'k'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.get_pixel_kerning('j', 'k'));
}
