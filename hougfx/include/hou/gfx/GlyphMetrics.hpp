// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_GLYPH_METRICS_HPP
#define HOU_GFX_GLYPH_METRICS_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/mth/Matrix.hpp"

#include <iostream>



namespace hou
{

/** Class describing the metrics of a glyph.
 *
 *  All metrics are expressed in 26.6 pixel format, which means the unit is
 *  1/64th of pixel.
 */
class HOU_GFX_API GlyphMetrics
{
public:
  /** Default constructor.
   *
   *  All properties are set to 0.
   */
  GlyphMetrics();

  /** Creates a GlyphMetrics object with the given properties.
   *
   *  \param size the size of the glyph bounding box.
   *  \param horizontalBearing the horizontal bearing of the glyph, that is the
   *  position of the baseline of the glyph when rendering text horizontally.
   *  \param horizontalAdvance the horizontal advance of the glyph, that is the
   *  horizontal offset to the next glyph when rendering text horizontally.
   *  \param verticalBearing the vertical bearing of the glyph, that is the
   *  position of the baseline of the glyph when rendering text vertically.
   *  \param verticalAdvance the vertical advance of the glyph, that is the
   *  vertical offset to the next glyph when rendering text vertically.
   */
  GlyphMetrics(const Vec2u& size
    , const Vec2i& horizontalBearing, int horizontalAdvance
    , const Vec2i& verticalBearing, int verticalAdvance);

  /** Gets the size of the bounding box of the glyph.
   *
   *  \return the size of the bounding box of the glyph.
   */
  const Vec2u& getSize() const;

  /** Sets the size of the bounding box of the glyph.
   *
   *  \param size the size of the bounding box of the glyph.
   */
  void setSize(const Vec2u& size);

  /** Gets the horizontal bearing of the glyph.
   *
   *  \return the horizontal bearing of the glyph.
   */
  const Vec2i& getHorizontalBearing() const;

  /** Sets the horizontal bearing of the glyph.
   *
   *  \param horizontalBearing the horizontal bearing.
   */
  void setHorizontalBearing(const Vec2i& horizontalBearing);

  /** Gets the horizontal advance of the glyph.
   *
   *  \return the horizontal advance of the glyph.
   */
  int getHorizontalAdvance() const;

  /** Sets the horizontal advance of the glyph.
   *
   *  \param horizontalAdvance the horizontal advance.
   */
  void setHorizontalAdvance(int horizontalAdvance);

  /** Gets the vertical bearing of the glyph.
   *
   *  \return the vertical bearing of the glyph.
   */
  const Vec2i& getVerticalBearing() const;

  /** Sets the vertical bearing of the glyph.
   *
   *  \param verticalBearing the vertical bearing.
   */
  void setVerticalBearing(const Vec2i& verticalBearing);

  /** Gets the vertical advance of the glyph.
   *
   *  \return the vertical advance of the glyph.
   */
  int getVerticalAdvance() const;

  /** Sets the vertical advance of the glyph.
   *
   *  \param verticalAdvance the vertical advance.
   */
  void setVerticalAdvance(int verticalAdvance);

private:
  Vec2u mSize;
  Vec2i mHorizontalBearing;
  int mHorizontalAdvance;
  Vec2i mVerticalBearing;
  int mVerticalAdvance;
};

/** Checks if two GlyphMetrics objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are equal,
 */
HOU_GFX_API bool operator==(const GlyphMetrics& lhs, const GlyphMetrics& rhs);

/** Checks if two GlyphMetrics objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are not equal,
 */
HOU_GFX_API bool operator!=(const GlyphMetrics& lhs, const GlyphMetrics& rhs);

/** Writes a GlyphMetrics object into a stream.
 *
 *  \param os the output stream.
 *  \param gm the object.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const GlyphMetrics& gm);

}

#endif

