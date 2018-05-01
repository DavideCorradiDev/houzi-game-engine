// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_data.hpp"

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

class test_font : public Test
{};

class test_font_death_test : public test_font
{};

const std::string font_name = get_data_dir() + u8"NotoSans-Regular.ttf";

}  // namespace



TEST_F(test_font, data_constructor)
{
  std::vector<uint8_t> buffer;
  {
    binary_file_in inf(font_name);
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



TEST_F(test_font_death_test, data_constructor_error_invalid_data)
{
  std::vector<uint8_t> data;
  HOU_EXPECT_ERROR(
    font f(data), std::runtime_error, get_text(gfx_error::font_load_face));
}



TEST_F(test_font, stream_constructor)
{
  font f(std::make_unique<binary_file_in>(font_name));

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



TEST_F(test_font, move_constructor)
{
  font f_dummy(std::make_unique<binary_file_in>(font_name));
  font f(std::move(f_dummy));

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



TEST_F(test_font, multi_threading_creation)
{
  std::unique_ptr<font> f1(nullptr);
  std::unique_ptr<font> f2(nullptr);

  auto thread_fun = [](std::unique_ptr<font>& fontPtr) {
    fontPtr.reset(new font(std::make_unique<binary_file_in>(font_name)));
  };

  std::thread t1(thread_fun, std::ref(f1));
  std::thread t2(thread_fun, std::ref(f2));

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



TEST_F(test_font_death_test, failed_creation)
{
  // Valid file but not a font file.
  HOU_EXPECT_ERROR(font f(std::make_unique<binary_file_in>(
                     get_data_dir() + u8"TestImage.png")),
    std::runtime_error, get_text(gfx_error::font_load_face));
}



TEST_F(test_font, multi_threading_destruction)
{
  auto thread_fun
    = []() { font f(std::make_unique<binary_file_in>(font_name)); };

  std::thread t1(thread_fun);
  std::thread t2(thread_fun);

  t1.join();
  t2.join();

  SUCCEED();
}



TEST_F(test_font, set_face_index_same_value)
{
  font f(std::make_unique<binary_file_in>(font_name));
  f.set_face_index(0u);
  EXPECT_EQ(0u, f.get_face_index());
}



TEST_F(test_font_death_test, set_face_index_error_out_of_bounds)
{
  font f(std::make_unique<binary_file_in>(font_name));
  HOU_EXPECT_PRECONDITION(f.set_face_index(f.get_face_index_count()));
}



TEST_F(test_font, set_pixel_height)
{
  font f(std::make_unique<binary_file_in>(font_name));
  f.set_pixel_height(20u);

  EXPECT_EQ(20u, f.get_pixel_height());
}



TEST_F(test_font, get_glyph)
{
  font f(std::make_unique<binary_file_in>(font_name));

  glyph g1_ref(
    image2r(vec2u(5u, 5u),
      std::vector<image2r::pixel>{image2r::pixel(0u), image2r::pixel(152u),
        image2r::pixel(180u), image2r::pixel(199u), image2r::pixel(87u),
        image2r::pixel(0u), image2r::pixel(4u), image2r::pixel(0u),
        image2r::pixel(30u), image2r::pixel(195u), image2r::pixel(26u),
        image2r::pixel(168u), image2r::pixel(160u), image2r::pixel(162u),
        image2r::pixel(204u), image2r::pixel(125u), image2r::pixel(120u),
        image2r::pixel(0u), image2r::pixel(54u), image2r::pixel(204u),
        image2r::pixel(51u), image2r::pixel(208u), image2r::pixel(177u),
        image2r::pixel(142u), image2r::pixel(191u)}),
    glyph_metrics(vec2u(320u, 320u), vec2i(0, -320), 384, vec2i(0, 0), 0));
  glyph g2_ref(
    image2r(vec2u(6u, 7u),
      std::vector<image2r::pixel>{image2r::pixel(40u), image2r::pixel(188u),
        image2r::pixel(0u), image2r::pixel(0u), image2r::pixel(0u),
        image2r::pixel(0u), image2r::pixel(40u), image2r::pixel(187u),
        image2r::pixel(0u), image2r::pixel(0u), image2r::pixel(0u),
        image2r::pixel(0u), image2r::pixel(40u), image2r::pixel(208u),
        image2r::pixel(172u), image2r::pixel(190u), image2r::pixel(173u),
        image2r::pixel(9u), image2r::pixel(40u), image2r::pixel(230u),
        image2r::pixel(8u), image2r::pixel(0u), image2r::pixel(137u),
        image2r::pixel(106u), image2r::pixel(40u), image2r::pixel(194u),
        image2r::pixel(0u), image2r::pixel(0u), image2r::pixel(87u),
        image2r::pixel(142u), image2r::pixel(40u), image2r::pixel(232u),
        image2r::pixel(9u), image2r::pixel(0u), image2r::pixel(140u),
        image2r::pixel(104u), image2r::pixel(40u), image2r::pixel(185u),
        image2r::pixel(175u), image2r::pixel(191u), image2r::pixel(171u),
        image2r::pixel(8u)}),
    glyph_metrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));

  EXPECT_EQ(g1_ref, f.get_glyph('a'));
  EXPECT_EQ(g2_ref, f.get_glyph('b'));
}



TEST_F(test_font, get_glyph_not_existing)
{
  font f(std::make_unique<binary_file_in>(font_name));
  glyph g_ref(
    image2r(vec2u(6u, 7u),
      std::vector<image2r::pixel>{16, 188, 132, 132, 188, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 188, 132, 132, 188, 12}),
    glyph_metrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));
  EXPECT_EQ(g_ref, f.get_glyph(U'\U00004f68'));
}



TEST_F(test_font, get_kerning)
{
  font f(std::make_unique<binary_file_in>(font_name));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('a', 'b'));
  EXPECT_EQ(vec2i(0, 0), f.get_kerning('j', 'k'));
}



TEST_F(test_font, get_pixel_glyph_bounding_box)
{
  font f(std::make_unique<binary_file_in>(font_name));

  EXPECT_EQ(recti(-356, -175, 1202, 845), f.get_glyph_bounding_box());
  HOU_EXPECT_FLOAT_CLOSE(rectf(-5.5625f, -2.734375f, 18.78125f, 13.203125),
    f.get_pixel_glyph_bounding_box());
}



TEST_F(test_font, get_pixel_line_spacing)
{
  font f(std::make_unique<binary_file_in>(font_name));

  EXPECT_EQ(896, f.get_line_spacing());
  HOU_EXPECT_FLOAT_CLOSE(14.f, f.get_pixel_line_spacing());
}



TEST_F(test_font, get_pixel_max_advance)
{
  font f(std::make_unique<binary_file_in>(font_name));

  EXPECT_EQ(832, f.get_max_advance());
  HOU_EXPECT_FLOAT_CLOSE(13.f, f.get_pixel_max_advance());
}



TEST_F(test_font, get_pixel_max_horizontal_advance)
{
  font f(std::make_unique<binary_file_in>(font_name));

  EXPECT_EQ(857, f.get_max_horizontal_advance());
  HOU_EXPECT_FLOAT_CLOSE(13.390625f, f.get_pixel_max_horizontal_advance());
}



TEST_F(test_font, get_pixel_max_vertical_advance)
{
  font f(std::make_unique<binary_file_in>(font_name));

  EXPECT_EQ(872, f.get_max_vertical_advance());
  HOU_EXPECT_FLOAT_CLOSE(13.625f, f.get_pixel_max_vertical_advance());
}



TEST_F(test_font, get_pixel_kerning)
{
  font f(std::make_unique<binary_file_in>(font_name));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('a', 'b'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.get_pixel_kerning('a', 'b'));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('j', 'k'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.get_pixel_kerning('j', 'k'));
}
