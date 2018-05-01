// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/font.hpp"

#include "hou/gfx/gfx_error.hpp"
#include "hou/gfx/glyph.hpp"

#include "hou/cor/error.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle.hpp"

#include "hou/sys/binary_file_in.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <memory>
#include <mutex>



namespace hou
{

namespace
{

static constexpr float pf266_to_pixel_factor = 1.f / 64.f;

class ft_library_wrapper : public non_copyable
{
public:
  ft_library_wrapper();
  ~ft_library_wrapper();
  FT_Library library;
};

// FT_Library is a pointer, can return by value.
FT_Library get_ft_library();



ft_library_wrapper::ft_library_wrapper()
  : non_copyable()
  , library(nullptr)
{
  HOU_ENSURE(FT_Init_FreeType(&library) == 0);
  HOU_ENSURE_DEV(library != nullptr);
}



ft_library_wrapper::~ft_library_wrapper()
{
  if(library != nullptr)
  {
    HOU_ENSURE_FATAL(FT_Done_FreeType(library) == 0);
  }
}



// Declaring a static thread_local variable inside a function causes a sef fault
// at execution end. This is probably a minGW bug. Usnig a single global with
// locks momentarily...
std::mutex ft_library_mutex;

FT_Library get_ft_library()
{
  static ft_library_wrapper wrapper;
  return wrapper.library;
}

}  // namespace



font::font(const span<const uint8_t>& data)
  : m_face()
  , m_face_index(0u)
  , m_pixel_height(10u)
  , m_data(data.begin(), data.end())
{
  load();
}



font::font(not_null<std::unique_ptr<binary_stream_in>> font_stream)
  : m_face()
  , m_face_index(0u)
  , m_pixel_height(10u)
  , m_data()
{
  font_stream->set_byte_pos(0u);
  m_data.resize(font_stream->get_byte_count());
  font_stream->read(m_data);
  load();
}



font::font(font&& other)
  : m_face(std::move(other.m_face))
  , m_face_index(std::move(other.m_face_index))
  , m_pixel_height(std::move(other.m_pixel_height))
  , m_data(std::move(other.m_data))
{
  other.m_face = nullptr;
}



font::~font()
{
  if(m_face != nullptr)
  {
    destroy();
  }
}



uint font::get_face_index_count() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return m_face->num_faces;
}



uint font::get_face_index() const
{
  return m_face_index;
}



void font::set_face_index(uint face_index)
{
  if(m_face_index != face_index)
  {
    HOU_EXPECT_DEV(m_face != nullptr);
    HOU_EXPECT(face_index < get_face_index_count());
    m_face_index = face_index;
    destroy();
    load();
  }
}



uint font::get_pixel_height() const
{
  return m_pixel_height;
}



void font::set_pixel_height(uint pixel_height)
{
  if(m_pixel_height != pixel_height)
  {
    HOU_EXPECT_DEV(m_face != nullptr);
    m_pixel_height = pixel_height;
    HOU_ENSURE(FT_Set_Pixel_Sizes(m_face, 0, pixel_height) == 0);
  }
}



bool font::has_horizontal() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return FT_HAS_HORIZONTAL(m_face);
}



bool font::has_vertical() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return FT_HAS_VERTICAL(m_face);
}



bool font::has_kerning() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return FT_HAS_KERNING(m_face);
}



bool font::is_scalable() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return FT_IS_SCALABLE(m_face);
}



recti font::get_glyph_bounding_box() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return recti(FT_MulFix(m_face->bbox.xMin, m_face->size->metrics.x_scale),
    FT_MulFix(m_face->bbox.yMin, m_face->size->metrics.y_scale),
    FT_MulFix(
      m_face->bbox.xMax - m_face->bbox.xMin, m_face->size->metrics.x_scale),
    FT_MulFix(
      m_face->bbox.yMax - m_face->bbox.yMin, m_face->size->metrics.y_scale));
}



rectf font::get_pixel_glyph_bounding_box() const
{
  recti pf266Rect = get_glyph_bounding_box();
  return rectf(
    static_cast<vec2f>(pf266Rect.get_position()) * pf266_to_pixel_factor,
    static_cast<vec2f>(pf266Rect.get_size()) * pf266_to_pixel_factor);
}



int font::get_line_spacing() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return m_face->size->metrics.height;
}



float font::get_pixel_line_spacing() const
{
  return static_cast<float>(get_line_spacing()) * pf266_to_pixel_factor;
}



int font::get_max_advance() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return m_face->size->metrics.max_advance;
}



float font::get_pixel_max_advance() const
{
  return static_cast<float>(get_max_advance()) * pf266_to_pixel_factor;
}



int font::get_max_horizontal_advance() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return FT_MulFix(m_face->max_advance_width, m_face->size->metrics.x_scale);
}



float font::get_pixel_max_horizontal_advance() const
{
  return static_cast<float>(get_max_horizontal_advance())
    * pf266_to_pixel_factor;
}


int font::get_max_vertical_advance() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return FT_MulFix(m_face->max_advance_height, m_face->size->metrics.y_scale);
}



float font::get_pixel_max_vertical_advance() const
{
  return static_cast<float>(get_max_vertical_advance()) * pf266_to_pixel_factor;
}



uint font::get_glyph_count() const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  return m_face->num_glyphs;
}



glyph font::get_glyph(utf32::code_unit char_code) const
{
  HOU_EXPECT_DEV(m_face != nullptr);
  HOU_ENSURE(FT_Load_Char(m_face, char_code, FT_LOAD_RENDER) == 0);

  const auto& g = m_face->glyph;

  vec2u bmp_size(g->bitmap.width, g->bitmap.rows);

  vec2u size(vec2<long>(g->metrics.width, g->metrics.height));

  vec2i hori_bearing = has_horizontal()
    ? vec2i(g->metrics.horiBearingX, -g->metrics.horiBearingY)
    : vec2i::zero();
  int hori_advance = has_horizontal() ? g->metrics.horiAdvance : 0;

  vec2i vert_bearing = has_vertical()
    ? vec2i(g->metrics.vertBearingX, -g->metrics.vertBearingY)
    : vec2i::zero();
  int vert_advance = has_vertical() ? g->metrics.vertAdvance : 0;

  // clang-format off
  return glyph(
    image2r(
      bmp_size,
      span<const image2r::pixel>(
        reinterpret_cast<image2r::pixel*>(g->bitmap.buffer),
        bmp_size.x() * bmp_size.y())),
    glyph_metrics(
      size,
      hori_bearing,
      hori_advance,
      vert_bearing,
      vert_advance));
  // clang-format on
}



vec2i font::get_kerning(utf32::code_unit first, utf32::code_unit second) const
{
  FT_Vector kerning;
  FT_UInt first_index = FT_Get_Char_Index(m_face, first);
  FT_UInt second_index = FT_Get_Char_Index(m_face, second);
  HOU_ENSURE(FT_Get_Kerning(
               m_face, first_index, second_index, FT_KERNING_DEFAULT, &kerning)
    == 0);
  return vec2i(kerning.x, kerning.y);
}



vec2f font::get_pixel_kerning(
  utf32::code_unit first, utf32::code_unit second) const
{
  return static_cast<vec2f>(get_kerning(first, second)) * pf266_to_pixel_factor;
}



void font::load()
{
  HOU_EXPECT_DEV(m_face == nullptr);
  FT_Library ftLibrary = get_ft_library();
  {
    std::lock_guard<std::mutex> lock(ft_library_mutex);
    HOU_RUNTIME_CHECK(FT_New_Memory_Face(ftLibrary, m_data.data(),
                        m_data.size(), m_face_index, &m_face)
        == 0,
      get_text(gfx_error::font_load_face));
  }
  HOU_EXPECT_DEV(m_face != nullptr);

  // Calling set pixel height here is wrong. The pixel size will not be
  // adjusted because m_pixel_height is not modified.
  HOU_ENSURE(FT_Set_Pixel_Sizes(m_face, 0, m_pixel_height) == 0);
  HOU_ENSURE(FT_Select_Charmap(m_face, FT_ENCODING_UNICODE) == 0);
}



void font::destroy()
{
  HOU_EXPECT_DEV(m_face != nullptr);
  {
    std::lock_guard<std::mutex> lock(ft_library_mutex);
    HOU_ENSURE_FATAL(FT_Done_Face(m_face) == 0);
  }
  m_face = nullptr;
}

}  // namespace hou
