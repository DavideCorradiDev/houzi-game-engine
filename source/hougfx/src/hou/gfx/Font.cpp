// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Font.hpp"

#include "hou/gfx/GfxError.hpp"
#include "hou/gfx/Glyph.hpp"

#include "hou/cor/error.hpp"

#include "hou/mth/rectangle.hpp"
#include "hou/mth/matrix.hpp"

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

static constexpr float pf266ToPixelFactor = 1.f / 64.f;

class FtLibraryWrapper
  : public non_copyable
{
public:
  FtLibraryWrapper();
  ~FtLibraryWrapper();
  FT_Library library;
};

// FT_Library is a pointer, can return by value.
FT_Library getFtLibrary();



FtLibraryWrapper::FtLibraryWrapper()
  : non_copyable()
  , library(nullptr)
{
  HOU_ENSURE(FT_Init_FreeType(&library) == 0);
  HOU_ENSURE_DEV(library != nullptr);
}



FtLibraryWrapper::~FtLibraryWrapper()
{
  if(library != nullptr)
  {
    HOU_ENSURE_FATAL(FT_Done_FreeType(library) == 0);
  }
}



// Declaring a static thread_local variable inside a function causes a sef fault
// at execution end. This is probably a minGW bug. Usnig a single global with
// locks momentarily...
std::mutex ftLibraryMutex;

FT_Library getFtLibrary()
{
  static FtLibraryWrapper ftLibraryWrapper;
  return ftLibraryWrapper.library;
}

}



Font::Font(const span<const uint8_t>& data)
  : mFace()
  , mFaceIndex(0u)
  , mPixelHeight(10u)
  , mData(data.begin(), data.end())
{
  load();
}



Font::Font(not_null<std::unique_ptr<binary_stream_in>> fontStream)
  : mFace()
  , mFaceIndex(0u)
  , mPixelHeight(10u)
  , mData()
{
  fontStream->set_byte_pos(0u);
  mData.resize(fontStream->get_byte_count());
  fontStream->read(mData);
  load();
}



Font::Font(Font&& other)
  : mFace(std::move(other.mFace))
  , mFaceIndex(std::move(other.mFaceIndex))
  , mPixelHeight(std::move(other.mPixelHeight))
  , mData(std::move(other.mData))
{
  other.mFace = nullptr;
}



Font::~Font()
{
  if(mFace != nullptr)
  {
    destroy();
  }
}



uint Font::getFaceIndexCount() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return mFace->num_faces;
}



uint Font::getFaceIndex() const
{
  return mFaceIndex;
}



void Font::setFaceIndex(uint faceIndex)
{
  if(mFaceIndex != faceIndex)
  {
    HOU_EXPECT_DEV(mFace != nullptr);
    HOU_EXPECT(faceIndex < getFaceIndexCount());
    mFaceIndex = faceIndex;
    destroy();
    load();
  }
}



uint Font::getPixelHeight() const
{
  return mPixelHeight;
}



void Font::setPixelHeight(uint pixelHeight)
{
  if(mPixelHeight != pixelHeight)
  {
    HOU_EXPECT_DEV(mFace != nullptr);
    mPixelHeight = pixelHeight;
    HOU_ENSURE(FT_Set_Pixel_Sizes(mFace, 0, pixelHeight) == 0);
  }
}



bool Font::hasHorizontal() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return FT_HAS_HORIZONTAL(mFace);
}



bool Font::hasVertical() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return FT_HAS_VERTICAL(mFace);
}



bool Font::hasKerning() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return FT_HAS_KERNING(mFace);
}



bool Font::isScalable() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return FT_IS_SCALABLE(mFace);
}



recti Font::getGlyphBoundingBox() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return recti
    ( FT_MulFix(mFace->bbox.xMin, mFace->size->metrics.x_scale)
    , FT_MulFix(mFace->bbox.yMin, mFace->size->metrics.y_scale)
    , FT_MulFix(mFace->bbox.xMax - mFace->bbox.xMin
      , mFace->size->metrics.x_scale)
    , FT_MulFix(mFace->bbox.yMax - mFace->bbox.yMin
      , mFace->size->metrics.y_scale));
}



rectf Font::getPixelGlyphBoundingBox() const
{
  recti pf266Rect = getGlyphBoundingBox();
  return rectf(static_cast<vec2f>(pf266Rect.get_position()) * pf266ToPixelFactor,
    static_cast<vec2f>(pf266Rect.get_size()) * pf266ToPixelFactor);
}



int Font::getLineSpacing() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return mFace->size->metrics.height;
}



float Font::getPixelLineSpacing() const
{
  return static_cast<float>(getLineSpacing()) * pf266ToPixelFactor;
}



int Font::getMaxAdvance() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return mFace->size->metrics.max_advance;
}



float Font::getMaxPixelAdvance() const
{
  return static_cast<float>(getMaxAdvance()) * pf266ToPixelFactor;
}



int Font::getMaxHorizontalAdvance() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return FT_MulFix(mFace->max_advance_width, mFace->size->metrics.x_scale);
}



float Font::getMaxPixelHorizontalAdvance() const
{
  return static_cast<float>(getMaxHorizontalAdvance()) * pf266ToPixelFactor;
}


int Font::getMaxVerticalAdvance() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return FT_MulFix(mFace->max_advance_height, mFace->size->metrics.y_scale);
}



float Font::getMaxPixelVerticalAdvance() const
{
  return static_cast<float>(getMaxVerticalAdvance()) * pf266ToPixelFactor;
}



uint Font::getGlyphCount() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return mFace->num_glyphs;
}



Glyph Font::getGlyph(utf32::code_unit charCode) const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  HOU_ENSURE(FT_Load_Char(mFace, charCode, FT_LOAD_RENDER) == 0);

  const auto& g = mFace->glyph;

  vec2u bmpSize(g->bitmap.width, g->bitmap.rows);

  vec2u size(vec2<long>(g->metrics.width, g->metrics.height));

  vec2i horiBearing = hasHorizontal()
    ? vec2i(g->metrics.horiBearingX, -g->metrics.horiBearingY)
    : vec2i::zero();
  int horiAdvance = hasHorizontal() ? g->metrics.horiAdvance : 0;

  vec2i vertBearing = hasVertical()
    ? vec2i(g->metrics.vertBearingX, -g->metrics.vertBearingY)
    : vec2i::zero();
  int vertAdvance = hasVertical() ? g->metrics.vertAdvance : 0;

  return Glyph
    ( image2R
      ( bmpSize
      , span<const image2R::pixel>
        ( reinterpret_cast<image2R::pixel*>(g->bitmap.buffer)
        , bmpSize.x() * bmpSize.y()))
    , GlyphMetrics(size, horiBearing, horiAdvance, vertBearing, vertAdvance));
}



vec2i Font::getKerning(utf32::code_unit first, utf32::code_unit second) const
{
  FT_Vector kerning;
  FT_UInt firstIndex = FT_Get_Char_Index(mFace, first);
  FT_UInt secondIndex = FT_Get_Char_Index(mFace, second);
  HOU_ENSURE(FT_Get_Kerning(mFace, firstIndex, secondIndex
    , FT_KERNING_DEFAULT, &kerning) == 0);
  return vec2i(kerning.x, kerning.y);
}



vec2f Font::getPixelKerning(utf32::code_unit first, utf32::code_unit second) const
{
  return static_cast<vec2f>(getKerning(first, second)) * pf266ToPixelFactor;
}



void Font::load()
{
  HOU_EXPECT_DEV(mFace == nullptr);
  FT_Library ftLibrary = getFtLibrary();
  {
    std::lock_guard<std::mutex> lock(ftLibraryMutex);
    HOU_RUNTIME_CHECK(FT_New_Memory_Face(ftLibrary, mData.data(), mData.size()
      , mFaceIndex, &mFace) == 0, get_text(GfxError::FontLoadFace));
  }
  HOU_EXPECT_DEV(mFace != nullptr);

  // Calling set ph_pixel height here is wrong. The ph_pixel size will not be
  // adjusted because mPixelHeight is not modified.
  HOU_ENSURE(FT_Set_Pixel_Sizes(mFace, 0, mPixelHeight) == 0);
  HOU_ENSURE(FT_Select_Charmap(mFace, FT_ENCODING_UNICODE) == 0);
}



void Font::destroy()
{
  HOU_EXPECT_DEV(mFace != nullptr);
  {
    std::lock_guard<std::mutex> lock(ftLibraryMutex);
    HOU_ENSURE_FATAL(FT_Done_Face(mFace) == 0);
  }
  mFace = nullptr;
}

}
