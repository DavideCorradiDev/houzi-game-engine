// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FORMATTED_TEXT_HPP
#define HOU_GFX_FORMATTED_TEXT_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/cor/std_string.hpp"
#include "hou/cor/std_vector.hpp"

#include "hou/mth/rectangle.hpp"
#include "hou/mth/transform2.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/TextBoxFormattingParams.hpp"
#include "hou/gfx/TextVertex.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/image_fwd.hpp"

#include <memory>



namespace hou
{

class Font;

/** Formatted, renderable text.
 *
 * The text will be formatted according to the given parameters.
 * The object stores a mesh and a texture atlas for quick rendering.
 */
class HOU_GFX_API FormattedText : public non_copyable
{
public:
  /** Type representing a collection of mesh vertices. */
  using VertexContainer = std::vector<TextVertex>;

public:
  /** Create a FormattedText with the given utf-8 string and formatting parameters.
   *
   * \param text the text.
   * \param font the font.
   * \param tbfp the text box formatting parameters.
   */
  FormattedText(const std::string& text, const Font& font,
    const TextBoxFormattingParams& tbfp = TextBoxFormattingParams::default);

  /** Create a FormattedText with the given utf-32 string and formatting parameters.
   *
   * \param text the text.
   * \param font the font.
   * \param tbfp the text box formatting parameters.
   */
  FormattedText(std::u32string text, const Font& font,
    const TextBoxFormattingParams& tbfp = TextBoxFormattingParams::default);

  /** Move constructor.
   *
   * \param other the other object.
   */
  FormattedText(FormattedText&& other);

  /** Retrieves the texture atlas.
   *
   * \return the texture atlas.
   */
  const Texture2Array& getAtlas() const;

  /** Retrieves the text mesh.
   *
   * \return the text mesh.
   */
  const TextMesh& getMesh() const;

  /** Retrieves the text bounding box.
   *
   * \return the text bounding box.
   */
  const rectf& getBoundingBox() const;

private:
  std::unique_ptr<Texture2Array> mAtlas;
  std::unique_ptr<TextMesh> mMesh;
  rectf mBoundingBox;
};

}  // namespace hou

#endif
