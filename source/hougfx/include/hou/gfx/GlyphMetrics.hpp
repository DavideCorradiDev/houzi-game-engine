// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GLYPH_METRICS_HPP
#define HOU_GFX_GLYPH_METRICS_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/mth/matrix.hpp"

#include <iostream>



namespace hou
{

/** Class describing the metrics of a glyph.
 *
 * All metrics are internal expressed in 26.6 ph_pixel format, which means the unit
 * is 1/64th of ph_pixel.
 */
class HOU_GFX_API GlyphMetrics
{
public:
  /** default constructor.
   *
   * All properties are set to 0.
   */
  GlyphMetrics();

  /** Creates a GlyphMetrics object with the given properties.
   *
   * \param size the size of the glyph bounding box.
   *
   * \param horizontalBearing the horizontal bearing of the glyph, that is the
   * position of the baseline of the glyph when rendering text horizontally.
   *
   * \param horizontalAdvance the horizontal advance of the glyph, that is the
   * horizontal offset to the next glyph when rendering text horizontally.
   *
   * \param verticalBearing the vertical bearing of the glyph, that is the
   * position of the baseline of the glyph when rendering text vertically.
   *
   * \param verticalAdvance the vertical advance of the glyph, that is the
   * vertical offset to the next glyph when rendering text vertically.
   */
  GlyphMetrics(const vec2u& size, const vec2i& horizontalBearing,
    int horizontalAdvance, const vec2i& verticalBearing, int verticalAdvance);

  /** Gets the size of the bounding box of the glyph in 26.6 ph_pixel format.
   *
   * \return the size of the bounding box of the glyph.
   */
  const vec2u& get_size() const;

  /** Gets the size of the bounding box of the glyph in pixels.
   *
   * \return the size of the bounding box of the glyph.
   */
  vec2f getPixelSize() const;

  /** Sets the size of the bounding box of the glyph.
   *
   * \param size the size of the bounding box of the glyph.
   */
  void set_size(const vec2u& size);

  /** Gets the horizontal bearing of the glyph in 26.6 ph_pixel format.
   *
   * \return the horizontal bearing of the glyph.
   */
  const vec2i& getHorizontalBearing() const;

  /** Gets the horizontal bearing of the glyph in pixels.
   *
   * \return the horizontal bearing of the glyph.
   */
  vec2f getPixelHorizontalBearing() const;

  /** Sets the horizontal bearing of the glyph.
   *
   * \param horizontalBearing the horizontal bearing.
   */
  void setHorizontalBearing(const vec2i& horizontalBearing);

  /** Gets the horizontal advance of the glyph in 26.6 ph_pixel format.
   *
   * \return the horizontal advance of the glyph.
   */
  int getHorizontalAdvance() const;

  /** Gets the horizontal advance of the glyph in pixels.
   *
   * \return the horizontal advance of the glyph.
   */
  float getPixelHorizontalAdvance() const;

  /** Sets the horizontal advance of the glyph.
   *
   * \param horizontalAdvance the horizontal advance.
   */
  void setHorizontalAdvance(int horizontalAdvance);

  /** Gets the vertical bearing of the glyph in 26.6 ph_pixel format.
   *
   * \return the vertical bearing of the glyph.
   */
  const vec2i& getVerticalBearing() const;

  /** Gets the vertical bearing of the glyph in pixels.
   *
   * \return the vertical bearing of the glyph.
   */
  vec2f getPixelVerticalBearing() const;

  /** Sets the vertical bearing of the glyph.
   *
   * \param verticalBearing the vertical bearing.
   */
  void setVerticalBearing(const vec2i& verticalBearing);

  /** Gets the vertical advance of the glyph in 26.6 ph_pixel format.
   *
   * \return the vertical advance of the glyph.
   */
  int getVerticalAdvance() const;

  /** Gets the vertical advance of the glyph in pixels.
   *
   * \return the vertical advance of the glyph.
   */
  float getPixelVerticalAdvance() const;

  /** Sets the vertical advance of the glyph.
   *
   * \param verticalAdvance the vertical advance.
   */
  void setVerticalAdvance(int verticalAdvance);

private:
  vec2u m_size;
  vec2i mHorizontalBearing;
  int mHorizontalAdvance;
  vec2i mVerticalBearing;
  int mVerticalAdvance;
};

/** Checks if two GlyphMetrics objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are equal,
 */
HOU_GFX_API bool operator==(const GlyphMetrics& lhs, const GlyphMetrics& rhs);

/** Checks if two GlyphMetrics objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are not equal,
 */
HOU_GFX_API bool operator!=(const GlyphMetrics& lhs, const GlyphMetrics& rhs);

/** Writes a GlyphMetrics object into a ph_stream.
 *
 * \param os the output ph_stream.
 *
 * \param gm the object.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const GlyphMetrics& gm);

}  // namespace hou

#endif
