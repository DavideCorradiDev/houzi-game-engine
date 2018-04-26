// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FORMATTED_TEXT_HPP
#define HOU_GFX_FORMATTED_TEXT_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/NonCopyable.hpp"

#include "hou/cor/StdString.hpp"
#include "hou/cor/StdVector.hpp"

#include "hou/mth/Rectangle.hpp"
#include "hou/mth/Transform2.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/TextBoxFormattingParams.hpp"
#include "hou/gfx/TextVertex.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/ImageFwd.hpp"

#include <memory>



namespace hou
{

class Font;

/** Formatted, renderable text.
 *
 * The text will be formatted according to the given parameters.
 * The object stores a mesh and a texture atlas for quick rendering.
 */
class HOU_GFX_API FormattedText : public NonCopyable
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
    const TextBoxFormattingParams& tbfp = TextBoxFormattingParams::Default);

  /** Create a FormattedText with the given utf-32 string and formatting parameters.
   *
   * \param text the text.
   * \param font the font.
   * \param tbfp the text box formatting parameters.
   */
  FormattedText(std::u32string text, const Font& font,
    const TextBoxFormattingParams& tbfp = TextBoxFormattingParams::Default);

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
  const Rectf& getBoundingBox() const;

private:
  std::unique_ptr<Texture2Array> mAtlas;
  std::unique_ptr<TextMesh> mMesh;
  Rectf mBoundingBox;
};

}  // namespace hou

#endif
