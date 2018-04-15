// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Font.hpp"

#include "hou/gfx/GfxError.hpp"
#include "hou/gfx/Glyph.hpp"

#include "hou/cor/Error.hpp"

#include "hou/mth/Rectangle.hpp"
#include "hou/mth/Matrix.hpp"

#include "hou/sys/BinaryFileIn.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <memory>
#include <mutex>



namespace hou
{

namespace
{

class FtLibraryWrapper
  : public NonCopyable
{
public:
  FtLibraryWrapper();
  ~FtLibraryWrapper();
  FT_Library library;
};

// FT_Library is a pointer, can return by value.
FT_Library getFtLibrary();



FtLibraryWrapper::FtLibraryWrapper()
  : NonCopyable()
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



Font::Font(const Span<const uint8_t>& data)
  : mFace()
  , mFaceIndex(0u)
  , mPixelHeight(10u)
  , mData(data.begin(), data.end())
{
  load();
}



Font::Font(NotNull<std::unique_ptr<BinaryStreamIn>> fontStream)
  : mFace()
  , mFaceIndex(0u)
  , mPixelHeight(10u)
  , mData()
{
  fontStream->setBytePos(0u);
  mData.resize(fontStream->getByteCount());
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



Recti Font::getGlyphBoundingBox() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return Recti
    ( FT_MulFix(mFace->bbox.xMin, mFace->size->metrics.x_scale)
    , FT_MulFix(mFace->bbox.yMin, mFace->size->metrics.y_scale)
    , FT_MulFix(mFace->bbox.xMax - mFace->bbox.xMin
      , mFace->size->metrics.x_scale)
    , FT_MulFix(mFace->bbox.yMax - mFace->bbox.yMin
      , mFace->size->metrics.y_scale));
}



int Font::getLineSpacing() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return mFace->size->metrics.height;
}



int Font::getMaxHorizontalAdvance() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return FT_MulFix(mFace->max_advance_width, mFace->size->metrics.x_scale);
}



int Font::getMaxVerticalAdvance() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return FT_MulFix(mFace->max_advance_height, mFace->size->metrics.y_scale);
}



uint Font::getGlyphCount() const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  return mFace->num_glyphs;
}



Glyph Font::getGlyph(Utf32::CodeUnit charCode) const
{
  HOU_EXPECT_DEV(mFace != nullptr);
  HOU_ENSURE(FT_Load_Char(mFace, charCode, FT_LOAD_RENDER) == 0);

  const auto& g = mFace->glyph;

  Vec2u bmpSize(g->bitmap.width, g->bitmap.rows);

  Vec2u size(Vec2<long>(g->metrics.width, g->metrics.height));

  Vec2i horiBearing = hasHorizontal()
    ? Vec2i(g->metrics.horiBearingX, -g->metrics.horiBearingY)
    : Vec2i::zero();
  int horiAdvance = hasHorizontal() ? g->metrics.horiAdvance : 0;

  Vec2i vertBearing = hasVertical()
    ? Vec2i(g->metrics.vertBearingX, -g->metrics.vertBearingY)
    : Vec2i::zero();
  int vertAdvance = hasVertical() ? g->metrics.vertAdvance : 0;

  return Glyph
    ( Image2R
      ( bmpSize
      , Span<const Image2R::Pixel>
        ( reinterpret_cast<Image2R::Pixel*>(g->bitmap.buffer)
        , bmpSize.x() * bmpSize.y()))
    , GlyphMetrics(size, horiBearing, horiAdvance, vertBearing, vertAdvance));
}



Vec2i Font::getKerning(Utf32::CodeUnit first, Utf32::CodeUnit second) const
{
  FT_Vector kerning;
  FT_UInt firstIndex = FT_Get_Char_Index(mFace, first);
  FT_UInt secondIndex = FT_Get_Char_Index(mFace, second);
  HOU_ENSURE(FT_Get_Kerning(mFace, firstIndex, secondIndex
    , FT_KERNING_DEFAULT, &kerning) == 0);
  return Vec2i(kerning.x, kerning.y);
}



void Font::load()
{
  HOU_EXPECT_DEV(mFace == nullptr);
  FT_Library ftLibrary = getFtLibrary();
  {
    std::lock_guard<std::mutex> lock(ftLibraryMutex);
    HOU_RUNTIME_CHECK(FT_New_Memory_Face(ftLibrary, mData.data(), mData.size()
      , mFaceIndex, &mFace) == 0, getText(GfxError::FontLoadFace));
  }
  HOU_EXPECT_DEV(mFace != nullptr);

  // Calling set pixel height here is wrong. The pixel size will not be
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

