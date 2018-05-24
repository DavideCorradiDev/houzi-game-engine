// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_data.hpp"

#include "hou/gfx/font.hpp"
#include "hou/gfx/gfx_exceptions.hpp"
#include "hou/gfx/glyph.hpp"

#include "hou/cor/std_vector.hpp"

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



TEST_F(test_font, data_move_constructor)
{
  std::vector<uint8_t> buffer;
  {
    binary_file_in inf(font_name);
    buffer.resize(inf.get_byte_count());
    inf.read(buffer.data(), buffer.size());
  }
  std::vector<uint8_t> tmp_buffer = buffer;
  font f(std::move(tmp_buffer));

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



TEST_F(test_font, data_constructor)
{
  std::vector<uint8_t> buffer;
  {
    binary_file_in inf(font_name);
    buffer.resize(inf.get_byte_count());
    inf.read(buffer.data(), buffer.size());
  }
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
  EXPECT_ERROR_0(font f(data), font_creation_error);
}



TEST_F(test_font, stream_constructor)
{
  binary_file_in fi(font_name);
  fi.set_byte_pos(4u);
  font f = font(fi);

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

  EXPECT_EQ(fi.get_byte_count(), static_cast<size_t>(fi.get_byte_pos()));
}



TEST_F(test_font, stream_move_constructor)
{
  font f = font(binary_file_in(font_name));

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
  font f_dummy = font(binary_file_in(font_name));
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
    fontPtr.reset(new font(binary_file_in(font_name)));
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
  EXPECT_ERROR_0(
    font f = font(binary_file_in(get_data_dir() + u8"TestImage.png")),
    font_creation_error);
}



TEST_F(test_font, multi_threading_destruction)
{
  auto thread_fun = []() { font f = font(binary_file_in(font_name)); };

  std::thread t1(thread_fun);
  std::thread t2(thread_fun);

  t1.join();
  t2.join();

  SUCCEED();
}



TEST_F(test_font, set_face_index_same_value)
{
  font f = font(binary_file_in(font_name));
  f.set_face_index(0u);
  EXPECT_EQ(0u, f.get_face_index());
}



TEST_F(test_font_death_test, set_face_index_error_out_of_bounds)
{
  font f = font(binary_file_in(font_name));
  EXPECT_PRECOND_ERROR(f.set_face_index(f.get_face_index_count()));
}



TEST_F(test_font, set_pixel_height)
{
  font f = font(binary_file_in(font_name));
  f.set_pixel_height(20u);

  EXPECT_EQ(20u, f.get_pixel_height());
}



TEST_F(test_font, get_glyph)
{
  font f = font(binary_file_in(font_name));

  glyph g1_ref(image2_r(vec2u(5u, 5u),
                 std::vector<image2_r::pixel>{0u, 152u, 180u, 199u, 87u, 0u, 4u,
                   0u, 30u, 195u, 26u, 168u, 160u, 162u, 204u, 125u, 120u, 0u,
                   54u, 204u, 51u, 208u, 177u, 142u, 191u}),
    glyph_metrics(vec2u(320u, 320u), vec2i(0, -320), 384, vec2i(0, 0), 0));

  glyph g2_ref(image2_r(vec2u(6u, 7u),
                 std::vector<image2_r::pixel>{40u, 188u, 0u, 0u, 0u, 0u, 40u,
                   187u, 0u, 0u, 0u, 0u, 40u, 208u, 172u, 190u, 173u, 9u, 40u,
                   230u, 8u, 0u, 137u, 106u, 40u, 194u, 0u, 0u, 87u, 142u, 40u,
                   232u, 9u, 0u, 140u, 104u, 40u, 185u, 175u, 191u, 171u, 8u}),
    glyph_metrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));

  EXPECT_EQ(g1_ref, f.get_glyph('a'));
  EXPECT_EQ(g2_ref, f.get_glyph('b'));
}



TEST_F(test_font, get_glyph_not_existing)
{
  font f = font(binary_file_in(font_name));
  glyph g_ref(
    image2_r(vec2u(6u, 7u),
      std::vector<image2_r::pixel>{16, 188, 132, 132, 188, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0, 116, 12, 16, 116, 0, 0,
        116, 12, 16, 116, 0, 0, 116, 12, 16, 188, 132, 132, 188, 12}),
    glyph_metrics(vec2u(384u, 448u), vec2i(0, -448), 384, vec2i(0, 0), 0));
  EXPECT_EQ(g_ref, f.get_glyph(U'\U00004f68'));
}



TEST_F(test_font, get_kerning)
{
  font f = font(binary_file_in(font_name));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('a', 'b'));
  EXPECT_EQ(vec2i(0, 0), f.get_kerning('j', 'k'));
}



TEST_F(test_font, get_pixel_glyph_bounding_box)
{
  font f = font(binary_file_in(font_name));

  EXPECT_EQ(recti(-356, -175, 1202, 845), f.get_glyph_bounding_box());
  EXPECT_FLOAT_CLOSE(rectf(-5.5625f, -2.734375f, 18.78125f, 13.203125),
    f.get_pixel_glyph_bounding_box());
}



TEST_F(test_font, get_pixel_line_spacing)
{
  font f = font(binary_file_in(font_name));

  EXPECT_EQ(896, f.get_line_spacing());
  EXPECT_FLOAT_CLOSE(14.f, f.get_pixel_line_spacing());
}



TEST_F(test_font, get_pixel_max_advance)
{
  font f = font(binary_file_in(font_name));

  EXPECT_EQ(832, f.get_max_advance());
  EXPECT_FLOAT_CLOSE(13.f, f.get_pixel_max_advance());
}



TEST_F(test_font, get_pixel_max_horizontal_advance)
{
  font f = font(binary_file_in(font_name));

  EXPECT_EQ(857, f.get_max_horizontal_advance());
  EXPECT_FLOAT_CLOSE(13.390625f, f.get_pixel_max_horizontal_advance());
}



TEST_F(test_font, get_pixel_max_vertical_advance)
{
  font f = font(binary_file_in(font_name));

  EXPECT_EQ(872, f.get_max_vertical_advance());
  EXPECT_FLOAT_CLOSE(13.625f, f.get_pixel_max_vertical_advance());
}



TEST_F(test_font, get_pixel_kerning)
{
  font f = font(binary_file_in(font_name));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('a', 'b'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.get_pixel_kerning('a', 'b'));

  EXPECT_EQ(vec2i(0, 0), f.get_kerning('j', 'k'));
  EXPECT_EQ(vec2f(0.f, 0.f), f.get_pixel_kerning('j', 'k'));
}
