// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FONT_HPP
#define HOU_GFX_FONT_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/CharacterEncodings.hpp"
#include "hou/cor/NotNull.hpp"
#include "hou/cor/Span.hpp"

#include "hou/mth/MatrixFwd.hpp"
#include "hou/mth/RectangleFwd.hpp"

#include "hou/sys/BinaryStreamIn.hpp"

#include <memory>
#include <vector>



struct FT_FaceRec_;
using FT_Face = FT_FaceRec_*;

namespace hou
{

class Glyph;

/** Allows reading metadata and glyphs from font raw data.
 *
 * Supported formats: TTF, TTC, CFF, WOFF, OTF, OTC, PFA, PFB, CID-keyed Type
 * 1, SFNT-based bitmap fonts, X11 PCF, Windows FNT, BDF, PFR.
 *
 * All metrics are expressed in 26.6 pixel format, which means the unit is
 * 1/64th of pixel.
 */
class HOU_GFX_API Font : public NonCopyable
{
public:
  /** Creates a Font object from the given font raw data.
   *
   * Throws if data does not represent valid font data.
   * The data will be copied inside the object, therefore the memory can be
   * freed after the construction of the Font object.
   *
   * \param data the font data.
   */
  explicit Font(const Span<const uint8_t>& data);

  /** Creates a Font object from the given binary input stream.
   *
   * This constructor reads the entire content of the binary stream and makes
   * a copy of it in memory.
   * Throws if the data does not represent valid font data.
   *
   * \param fontStream the font stream.
   */
  explicit Font(NotNull<std::unique_ptr<BinaryStreamIn>> fontStream);

  /** Move constructor.
   *
   * \param other the other Font object.
   */
  Font(Font&& other);

  /** Destructor.
   */
  ~Font();

  /** Gets the number of available font faces.
   *
   * \return the number of available font faces.
   */
  uint getFaceIndexCount() const;

  /** Gets the index of the currently selected font face.
   *
   * The default value is 0.
   *
   * \return the index of the currently selected font face.
   */
  uint getFaceIndex() const;

  /** Selects the specified face.
   *
   * \param faceIndex the index of the face to be selected.
   */
  void setFaceIndex(uint faceIndex);

  /** Gets the currently selected pixel height.
   *
   * The default value is 10.
   *
   * \return the currently selected pixel height.
   */
  uint getPixelHeight() const;

  /** Sets the current pixel height.
   *
   * \param pixelHeight the desired pixel height.
   */
  void setPixelHeight(uint pixelHeight);

  /** Checks if the font has horizontal rendering metrics.
   *
   * \return true if the font has horizontal rendering metrics.
   */
  bool hasHorizontal() const;

  /** Checks if the font has vertical rendering metrics.
   *
   * \return true if the font has vertical rendering metrics.
   */
  bool hasVertical() const;

  /** Checks if the font has kerning metrics.
   *
   * \return true if the font has kerning metrics.
   */
  bool hasKerning() const;

  /** Checks if the font is scalable.
   *
   * \return true if the font is scalable.
   */
  bool isScalable() const;

  /** Get a bounding box capable of containing any glyph in the font in 26.6
   * pixel format.
   *
   * \return the bounding box.
   */
  Recti getGlyphBoundingBox() const;

  /** Get a bounding box capable of containing any glyph in the font in pixels.
   *
   * \return the bounding box.
   */
  Rectf getPixelGlyphBoundingBox() const;

  /** Get the line spacing in 26.6 pixel format.
   *
   * \return the line spacing.
   */
  int getLineSpacing() const;

  /** Get the line spacing in pixels.
   *
   * \return the line spacing.
   */
  float getPixelLineSpacing() const;

  /** Get the maximum horizontal advance in 26.6 pixel format.
   *
   * \return the maximum horizontal advance.
   */
  int getMaxAdvance() const;

  /** Get the maximum horizontal advance in pixels.
   *
   * \return the maximum horizontal advance.
   */
  float getMaxPixelAdvance() const;

  /** Get the maximum horizontal advance in 26.6 pixel format.
   *
   * \return the maximum horizontal advance.
   */
  int getMaxHorizontalAdvance() const;

  /** Get the maximum horizontal advance in pixels.
   *
   * \return the maximum horizontal advance.
   */
  float getMaxPixelHorizontalAdvance() const;

  /** Get the maximum vertical advance in 26.6 pixel format.
   *
   * \return the maximum vertical advance.
   */
  int getMaxVerticalAdvance() const;

  /** Get the maximum vertical advance in pixels.
   *
   * \return the maximum vertical advance.
   */
  float getMaxPixelVerticalAdvance() const;

  /** Get the number of glyphs.
   *
   * \return the number of glyphs.
   */
  uint getGlyphCount() const;

  /** Generates and returns information for a glyph.
   *
   * The glyph is generated with the currently selected face and pixel height.
   * If the requested glyph is not present in the font a placeholder glyph is
   * returned.
   *
   * \param the glyph code point.
   * \return the requested glyph.
   */
  Glyph getGlyph(Utf32::CodeUnit charCode) const;

  /** Gets the kerning between two characters in 26.6 pixel format.
   *
   * \param first the first character.
   * \param second the second character.
   * \return the kerning between the two characters.
   */
  Vec2i getKerning(Utf32::CodeUnit first, Utf32::CodeUnit second) const;

  /** Gets the kerning between two characters in pixels.
   *
   * \param first the first character.
   * \param second the second character.
   * \return the kerning between the two characters.
   */
  Vec2f getPixelKerning(Utf32::CodeUnit first, Utf32::CodeUnit second) const;

  // Values of ascender and descender are not standardized and therefore not
  // reliable.
  // int getAscender() const;
  // int getDescender() const;
  //
  // Underline not currently supported.
  // int getUnderlinePosition() const;
  // int getUnderlineThickness() const;

private:
  void load();
  void destroy();

private:
  FT_Face mFace;
  uint mFaceIndex;
  uint mPixelHeight;
  std::vector<uint8_t> mData;
};

}  // namespace hou

#endif
