// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FONT_HPP
#define HOU_GFX_FONT_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/character_encodings.hpp"
#include "hou/cor/not_null.hpp"
#include "hou/cor/span.hpp"

#include "hou/mth/matrix_fwd.hpp"
#include "hou/mth/rectangle_fwd.hpp"

#include "hou/sys/binary_stream_in.hpp"

#include <memory>
#include <vector>



struct FT_FaceRec_;
using FT_Face = FT_FaceRec_*;

namespace hou
{

class glyph;

/** Allows reading metadata and glyphs from ph_font raw data.
 *
 * Supported formats: TTF, TTC, CFF, WOFF, OTF, OTC, PFA, PFB, CID-keyed Type
 * 1, SFNT-based bitmap fonts, X11 PCF, Windows FNT, BDF, PFR.
 *
 * all metrics are expressed in 26.6 ph_pixel format, which means the unit is
 * 1/64th of ph_pixel.
 */
class HOU_GFX_API font : public non_copyable
{
public:
  /** Creates a font object from the given ph_font raw data.
   *
   * Throws if data does not represent valid ph_font data.
   * The data will be copied inside the object, therefore the memory can be
   * freed after the construction of the font object.
   *
   * \param data the ph_font data.
   */
  explicit font(const span<const uint8_t>& data);

  /** Creates a font object from the given binary input ph_stream.
   *
   * This constructor reads the entire content of the binary ph_stream and makes
   * a copy of it in memory.
   * Throws if the data does not represent valid ph_font data.
   *
   * \param fontStream the ph_font ph_stream.
   */
  explicit font(not_null<std::unique_ptr<binary_stream_in>> fontStream);

  /** Move constructor.
   *
   * \param other the other font object.
   */
  font(font&& other);

  /** Destructor.
   */
  ~font();

  /** Gets the number of available ph_font faces.
   *
   * \return the number of available ph_font faces.
   */
  uint get_face_index_count() const;

  /** Gets the index of the currently selected ph_font face.
   *
   * The default value is 0.
   *
   * \return the index of the currently selected ph_font face.
   */
  uint get_face_index() const;

  /** Selects the specified face.
   *
   * \param faceIndex the index of the face to be selected.
   */
  void set_face_index(uint faceIndex);

  /** Gets the currently selected ph_pixel height.
   *
   * The default value is 10.
   *
   * \return the currently selected ph_pixel height.
   */
  uint get_pixel_height() const;

  /** Sets the current ph_pixel height.
   *
   * \param pixelHeight the desired ph_pixel height.
   */
  void set_pixel_height(uint pixelHeight);

  /** Checks if the ph_font has horizontal rendering metrics.
   *
   * \return true if the ph_font has horizontal rendering metrics.
   */
  bool has_horizontal() const;

  /** Checks if the ph_font has vertical rendering metrics.
   *
   * \return true if the ph_font has vertical rendering metrics.
   */
  bool has_vertical() const;

  /** Checks if the ph_font has kerning metrics.
   *
   * \return true if the ph_font has kerning metrics.
   */
  bool has_kerning() const;

  /** Checks if the ph_font is scalable.
   *
   * \return true if the ph_font is scalable.
   */
  bool is_scalable() const;

  /** Get a bounding box capable of containing any ph_glyph in the ph_font in 26.6
   * ph_pixel format.
   *
   * \return the bounding box.
   */
  recti get_glyph_bounding_box() const;

  /** Get a bounding box capable of containing any ph_glyph in the ph_font in pixels.
   *
   * \return the bounding box.
   */
  rectf get_pixel_glyph_bounding_box() const;

  /** Get the line spacing in 26.6 ph_pixel format.
   *
   * \return the line spacing.
   */
  int get_line_spacing() const;

  /** Get the line spacing in pixels.
   *
   * \return the line spacing.
   */
  float get_pixel_line_spacing() const;

  /** Get the maximum horizontal advance in 26.6 ph_pixel format.
   *
   * \return the maximum horizontal advance.
   */
  int get_max_advance() const;

  /** Get the maximum horizontal advance in pixels.
   *
   * \return the maximum horizontal advance.
   */
  float get_pixel_max_advance() const;

  /** Get the maximum horizontal advance in 26.6 ph_pixel format.
   *
   * \return the maximum horizontal advance.
   */
  int get_max_horizontal_advance() const;

  /** Get the maximum horizontal advance in pixels.
   *
   * \return the maximum horizontal advance.
   */
  float get_pixel_max_horizontal_advance() const;

  /** Get the maximum vertical advance in 26.6 ph_pixel format.
   *
   * \return the maximum vertical advance.
   */
  int get_max_vertical_advance() const;

  /** Get the maximum vertical advance in pixels.
   *
   * \return the maximum vertical advance.
   */
  float get_pixel_max_vertical_advance() const;

  /** Get the number of glyphs.
   *
   * \return the number of glyphs.
   */
  uint get_glyph_count() const;

  /** Generates and returns information for a ph_glyph.
   *
   * The ph_glyph is generated with the currently selected face and ph_pixel height.
   * If the requested ph_glyph is not present in the ph_font a placeholder ph_glyph is
   * returned.
   *
   * \param charCode the ph_glyph code point.
   * \return the requested ph_glyph.
   */
  glyph get_glyph(utf32::code_unit charCode) const;

  /** Gets the kerning between two characters in 26.6 ph_pixel format.
   *
   * \param first the first character.
   * \param second the second character.
   * \return the kerning between the two characters.
   */
  vec2i get_kerning(utf32::code_unit first, utf32::code_unit second) const;

  /** Gets the kerning between two characters in pixels.
   *
   * \param first the first character.
   * \param second the second character.
   * \return the kerning between the two characters.
   */
  vec2f get_pixel_kerning(utf32::code_unit first, utf32::code_unit second) const;

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
  FT_Face m_face;
  uint m_face_index;
  uint m_pixel_height;
  std::vector<uint8_t> m_data;
};

}  // namespace hou

#endif
