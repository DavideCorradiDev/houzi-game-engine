// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GLYPH_METRICS_HPP
#define HOU_GFX_GLYPH_METRICS_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/mth/matrix.hpp"

#include <iostream>



namespace hou
{

/** Class describing the metrics of a glyph.
 *
 * all metrics are internal expressed in 26.6 pixel format, which means the
 * unit is 1/64th of pixel.
 */
class HOU_GFX_API glyph_metrics
{
public:
  /** default constructor.
   *
   * all properties are set to 0.
   */
  glyph_metrics() noexcept;

  /** Creates a glyph_metrics object with the given properties.
   *
   * \param size the size of the glyph bounding box.
   *
   * \param horizontal_bearing the horizontal bearing of the glyph, that is
   * the position of the baseline of the glyph when rendering text
   * horizontally.
   *
   * \param horizontal_advance the horizontal advance of the glyph, that is
   * the horizontal offset to the next glyph when rendering text
   * horizontally.
   *
   * \param vertical_bearing the vertical bearing of the glyph, that is the
   * position of the baseline of the glyph when rendering text vertically.
   *
   * \param vertical_advance the vertical advance of the glyph, that is the
   * vertical offset to the next glyph when rendering text vertically.
   */
  glyph_metrics(const vec2u& size, const vec2i& horizontal_bearing,
    int horizontal_advance, const vec2i& vertical_bearing,
    int vertical_advance) noexcept;

  /** Gets the size of the bounding box of the glyph in 26.6 pixel format.
   *
   * \return the size of the bounding box of the glyph.
   */
  const vec2u& get_size() const noexcept;

  /** Gets the size of the bounding box of the glyph in pixels.
   *
   * \return the size of the bounding box of the glyph.
   */
  vec2f get_pixel_size() const noexcept;

  /** Sets the size of the bounding box of the glyph.
   *
   * \param size the size of the bounding box of the glyph.
   */
  void set_size(const vec2u& size) noexcept;

  /** Gets the horizontal bearing of the glyph in 26.6 pixel format.
   *
   * \return the horizontal bearing of the glyph.
   */
  const vec2i& get_horizontal_bearing() const noexcept;

  /** Gets the horizontal bearing of the glyph in pixels.
   *
   * \return the horizontal bearing of the glyph.
   */
  vec2f get_pixel_horizontal_bearing() const noexcept;

  /** Sets the horizontal bearing of the glyph.
   *
   * \param horizontal_bearing the horizontal bearing.
   */
  void setHorizontalBearing(const vec2i& horizontal_bearing) noexcept;

  /** Gets the horizontal advance of the glyph in 26.6 pixel format.
   *
   * \return the horizontal advance of the glyph.
   */
  int get_horizontal_advance() const noexcept;

  /** Gets the horizontal advance of the glyph in pixels.
   *
   * \return the horizontal advance of the glyph.
   */
  float get_pixel_horizontal_advance() const noexcept;

  /** Sets the horizontal advance of the glyph.
   *
   * \param horizontal_advance the horizontal advance.
   */
  void set_horizontal_advance(int horizontal_advance) noexcept;

  /** Gets the vertical bearing of the glyph in 26.6 pixel format.
   *
   * \return the vertical bearing of the glyph.
   */
  const vec2i& get_vertical_bearing() const noexcept;

  /** Gets the vertical bearing of the glyph in pixels.
   *
   * \return the vertical bearing of the glyph.
   */
  vec2f get_pixel_vertical_bearing() const noexcept;

  /** Sets the vertical bearing of the glyph.
   *
   * \param vertical_bearing the vertical bearing.
   */
  void set_vertical_bearing(const vec2i& vertical_bearing) noexcept;

  /** Gets the vertical advance of the glyph in 26.6 pixel format.
   *
   * \return the vertical advance of the glyph.
   */
  int get_vertical_advance() const noexcept;

  /** Gets the vertical advance of the glyph in pixels.
   *
   * \return the vertical advance of the glyph.
   */
  float get_pixel_vertical_advance() const noexcept;

  /** Sets the vertical advance of the glyph.
   *
   * \param vertical_advance the vertical advance.
   */
  void set_vertical_advance(int vertical_advance) noexcept;

private:
  vec2u m_size;
  vec2i m_horizontal_bearing;
  int m_horizontal_advance;
  vec2i m_vertical_bearing;
  int m_vertical_advance;
};

/** Checks if two glyph_metrics objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are equal,
 */
HOU_GFX_API bool operator==(
  const glyph_metrics& lhs, const glyph_metrics& rhs) noexcept;

/** Checks if two glyph_metrics objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are not equal,
 */
HOU_GFX_API bool operator!=(
  const glyph_metrics& lhs, const glyph_metrics& rhs) noexcept;

/** Writes a glyph_metrics object into a stream.
 *
 * \param os the output stream.
 *
 * \param gm the object.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const glyph_metrics& gm);

}  // namespace hou

#endif
