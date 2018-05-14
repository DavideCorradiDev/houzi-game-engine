// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GLYPH_HPP
#define HOU_GFX_GLYPH_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/glyph_metrics.hpp"
#include "hou/sys/image.hpp"

#include "hou/cor/basic_types.hpp"

#include <iostream>



namespace hou
{

/** Class describing a glyph, including its metrics and its bitmap image.
 */
class HOU_GFX_API glyph
{
public:
  /** default constructor.
   *
   * The image is empty and the metrics are all null.
   *
   * \throws std::bad_alloc.
   */
  glyph();

  /** Creates a glyph object with the given image and metrics.
   *
   * \param im the image.
   *
   * \param metrics the metrics.
   *
   * \throws std::bad_alloc.
   */
  glyph(const image2_r& im, const glyph_metrics& metrics);

  /** Gets the image.
   *
   * \return the image.
   */
  const image2_r& get_image() const noexcept;

  /** Sets the image.
   *
   * \param im the image.
   */
  void set_image(const image2_r& im);

  /** Gets the metrics.
   *
   * \return the metrics.
   */
  const glyph_metrics& get_metrics() const noexcept;

  /** Sets the metrics.
   *
   * \param metrics the metrics.
   */
  void set_metrics(const glyph_metrics& metrics) noexcept;

private:
  image2_r m_image;
  glyph_metrics m_metrics;
};

/** Checks if two glyph objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are equal,
 */
HOU_GFX_API bool operator==(const glyph& lhs, const glyph& rhs) noexcept;

/** Checks if two glyph objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return true if the two objects are not equal,
 */
HOU_GFX_API bool operator!=(const glyph& lhs, const glyph& rhs) noexcept;

/** Writes a glyph object into a stream.
 *
 * \param os the output stream.
 *
 * \param gm the object.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const glyph& gm);

}  // namespace hou

#endif
