// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FONT_HPP
#define HOU_GFX_FONT_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/cor/character_encodings.hpp"
#include "hou/cor/span.hpp"

#include "hou/mth/matrix_fwd.hpp"
#include "hou/mth/rectangle_fwd.hpp"

#include "hou/sys/binary_stream_in.hpp"

#include <vector>



struct FT_FaceRec_;
using FT_Face = FT_FaceRec_*;

namespace hou
{

class glyph;

/** Allows reading metadata and glyphs from font raw data.
 *
 * Supported formats: TTF, TTC, CFF, WOFF, OTF, OTC, PFA, PFB, CID-keyed Type
 * 1, SFNT-based bitmap fonts, X11 PCF, Windows FNT, BDF, PFR.
 *
 * all metrics are expressed in 26.6 pixel format, which means the unit is
 * 1/64th of pixel.
 */
class HOU_GFX_API font : public non_copyable
{
public:
  /** Underlying data type. */
  using data_type = std::vector<uint8_t>;

public:
  /** Creates a font object from the given font raw data.
   *
   * Throws if data does not represent valid font data.
   * The data will be copied inside the object, therefore the memory can be
   * freed after the construction of the font object.
   *
   * \param data the font data.
   *
   * \throws hou::font_creation_error if the font data is invalid.
   */
  explicit font(data_type&& data);

  /** Creates a font object from the given font raw data.
   *
   * Throws if data does not represent valid font data.
   * The data will be copied inside the object, therefore the memory can be
   * freed after the construction of the font object.
   *
   * \param data the font data.
   *
   * \throws hou::font_creation_error if the font data is invalid.
   */
  explicit font(const span<const uint8_t>& data);

  /** Creates a font object from the given binary input stream.
   *
   * This constructor reads the entire content of the binary stream and makes
   * a copy of it in memory.
   * Throws if the data does not represent valid font data.
   *
   * \param font_stream the font stream.
   *
   * \throws hou::font_creation_error if the font data is invalid.
   */
  explicit font(binary_stream_in& font_stream);

  /** Creates a font object from the given binary input stream.
   *
   * This constructor reads the entire content of the binary stream and makes
   * a copy of it in memory.
   * Throws if the data does not represent valid font data.
   *
   * \param font_stream the font stream.
   *
   * \throws hou::font_creation_error if the font data is invalid.
   */
  explicit font(binary_stream_in&& font_stream);

  /** Move constructor.
   *
   * \param other the other font object.
   */
  font(font&& other) noexcept;

  /** Destructor.
   */
  ~font();

  /** Gets the number of available font faces.
   *
   * \return the number of available font faces.
   */
  uint get_face_index_count() const noexcept;

  /** Gets the index of the currently selected font face.
   *
   * The default value is 0.
   *
   * \return the index of the currently selected font face.
   */
  uint get_face_index() const noexcept;

  /** Selects the specified face.
   *
   * \param face_index the index of the face to be selected.
   *
   * \throws hou::precondition_violation if face_index is not lower than the
   * number of face indices.
   */
  void set_face_index(uint face_index);

  /** Gets the currently selected pixel height.
   *
   * The default value is 10.
   *
   * \return the currently selected pixel height.
   */
  uint get_pixel_height() const noexcept;

  /** Sets the current pixel height.
   *
   * \param pixel_height the desired pixel height.
   */
  void set_pixel_height(uint pixel_height);

  /** Checks if the font has horizontal rendering metrics.
   *
   * \return true if the font has horizontal rendering metrics.
   */
  bool has_horizontal() const noexcept;

  /** Checks if the font has vertical rendering metrics.
   *
   * \return true if the font has vertical rendering metrics.
   */
  bool has_vertical() const noexcept;

  /** Checks if the font has kerning metrics.
   *
   * \return true if the font has kerning metrics.
   */
  bool has_kerning() const noexcept;

  /** Checks if the font is scalable.
   *
   * \return true if the font is scalable.
   */
  bool is_scalable() const noexcept;

  /** Get a bounding box capable of containing any glyph in the font in 26.6
   * pixel format.
   *
   * \return the bounding box.
   */
  recti get_glyph_bounding_box() const noexcept;

  /** Get a bounding box capable of containing any glyph in the font in pixels.
   *
   * \return the bounding box.
   */
  rectf get_pixel_glyph_bounding_box() const noexcept;

  /** Get the line spacing in 26.6 pixel format.
   *
   * \return the line spacing.
   */
  int get_line_spacing() const noexcept;

  /** Get the line spacing in pixels.
   *
   * \return the line spacing.
   */
  float get_pixel_line_spacing() const noexcept;

  /** Get the maximum horizontal advance in 26.6 pixel format.
   *
   * \return the maximum horizontal advance.
   */
  int get_max_advance() const noexcept;

  /** Get the maximum horizontal advance in pixels.
   *
   * \return the maximum horizontal advance.
   */
  float get_pixel_max_advance() const noexcept;

  /** Get the maximum horizontal advance in 26.6 pixel format.
   *
   * \return the maximum horizontal advance.
   */
  int get_max_horizontal_advance() const noexcept;

  /** Get the maximum horizontal advance in pixels.
   *
   * \return the maximum horizontal advance.
   */
  float get_pixel_max_horizontal_advance() const noexcept;

  /** Get the maximum vertical advance in 26.6 pixel format.
   *
   * \return the maximum vertical advance.
   */
  int get_max_vertical_advance() const noexcept;

  /** Get the maximum vertical advance in pixels.
   *
   * \return the maximum vertical advance.
   */
  float get_pixel_max_vertical_advance() const noexcept;

  /** Get the number of glyphs.
   *
   * \return the number of glyphs.
   */
  uint get_glyph_count() const noexcept;

  /** Generates and returns information for a glyph.
   *
   * The glyph is generated with the currently selected face and pixel
   * height. If the requested glyph is not present in the font a placeholder
   * glyph is returned.
   *
   * \param char_code the glyph code point.
   *
   * \return the requested glyph.
   */
  glyph get_glyph(utf32::code_unit char_code) const;

  /** Gets the kerning between two characters in 26.6 pixel format.
   *
   * \param first the first character.
   *
   * \param second the second character.
   *
   * \return the kerning between the two characters.
   */
  vec2i get_kerning(utf32::code_unit first, utf32::code_unit second) const;

  /** Gets the kerning between two characters in pixels.
   *
   * \param first the first character.
   *
   * \param second the second character.
   *
   * \return the kerning between the two characters.
   */
  vec2f get_pixel_kerning(
    utf32::code_unit first, utf32::code_unit second) const;

  // Values of ascender and descender are not standardized and therefore not
  // reliable.
  // int get_ascender() const;
  // int get_descender() const;
  //
  // Underline not currently supported.
  // int get_underline_position() const;
  // int get_underline_thickness() const;

private:
  void load();
  void destroy();

private:
  FT_Face m_face;
  uint m_face_index;
  uint m_pixel_height;
  data_type m_data;
};

}  // namespace hou

#endif
