// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GLYPH_HPP
#define HOU_GFX_GLYPH_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/GlyphMetrics.hpp"
#include "hou/sys/Image.hpp"

#include "hou/cor/basic_types.hpp"

#include <iostream>



namespace hou
{

/** Class describing a glyph, including its metrics and its bitmap image.
 */
class HOU_GFX_API Glyph
{
public:
  /** Default constructor.
   *
   *  The image is empty and the metrics are all null.
   */
  Glyph();

  /** Creates a Glyph object with the given image and metrics.
   */
  Glyph(const Image2R& image, const GlyphMetrics& metrics);

  /** Gets the image.
   *
   *  \return the image.
   */
  const Image2R& getImage() const;

  /** Sets the image.
   *
   *  \param image the image.
   */
  void setImage(const Image2R& image);

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
  Image2R mImage;
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

/** Writes a Glyph object into a stream.
 *
 *  \param os the output stream.
 *  \param gm the object.
 *  \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const Glyph& gm);

}

#endif

