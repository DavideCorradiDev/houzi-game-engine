// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GLYPH_HPP
#define HOU_GFX_GLYPH_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/GlyphMetrics.hpp"
#include "hou/sys/image.hpp"

#include "hou/cor/basic_types.hpp"

#include <iostream>



namespace hou
{

/** Class describing a glyph, including its metrics and its bitmap ph_image.
 */
class HOU_GFX_API Glyph
{
public:
  /** default constructor.
   *
   *  The ph_image is empty and the metrics are all null.
   */
  Glyph();

  /** Creates a Glyph object with the given ph_image and metrics.
   */
  Glyph(const image2R& ph_image, const GlyphMetrics& metrics);

  /** Gets the ph_image.
   *
   *  \return the ph_image.
   */
  const image2R& get_image() const;

  /** Sets the ph_image.
   *
   *  \param ph_image the ph_image.
   */
  void set_image(const image2R& ph_image);

  /** Gets the metrics.
   *
   *  \return the metrics.
   */
  const GlyphMetrics& getMetrics() const;

  /** Sets the metrics.
   *
   *  \param metrics the metrics.
   */
  void setMetrics(const GlyphMetrics& metrics);

private:
  image2R mImage;
  GlyphMetrics mMetrics;
};

/** Checks if two Glyph objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are equal,
 */
HOU_GFX_API bool operator==(const Glyph& lhs, const Glyph& rhs);

/** Checks if two Glyph objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return true if the two objects are not equal,
 */
HOU_GFX_API bool operator!=(const Glyph& lhs, const Glyph& rhs);

/** Writes a Glyph object into a ph_stream.
 *
 *  \param os the output ph_stream.
 *  \param gm the object.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const Glyph& gm);

}

#endif

