// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FORMATTED_TEXT_HPP
#define HOU_GFX_FORMATTED_TEXT_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/cor/std_string.hpp"
#include "hou/cor/std_vector.hpp"

#include "hou/mth/rectangle.hpp"
#include "hou/mth/transform2.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/text_box_formatting_params.hpp"
#include "hou/gfx/text_mesh.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/sys/image_fwd.hpp"

#include <memory>



namespace hou
{

class font;

/** Formatted, renderable text.
 *
 * The text will be formatted according to the given parameters.
 * The object stores a mesh and a texture atlas for quick rendering.
 */
class HOU_GFX_API formatted_text : public non_copyable
{
public:
  /** Type representing a collection of mesh vertices. */
  using VertexContainer = std::vector<text_vertex>;

public:
  /** Create a formatted_text with the given utf-8 string and formatting
   * parameters.
   *
   * \param text the text.
   * \param f the font.
   * \param tbfp the text box formatting parameters.
   */
  formatted_text(const std::string& text, const font& f,
    const text_box_formatting_params& tbfp
    = text_box_formatting_params::standard);

  /** Create a formatted_text with the given utf-32 string and formatting
   * parameters.
   *
   * \param text the text.
   * \param f the font.
   * \param tbfp the text box formatting parameters.
   */
  formatted_text(std::u32string text, const font& f,
    const text_box_formatting_params& tbfp
    = text_box_formatting_params::standard);

  /** Retrieves the texture atlas.
   *
   * \return the texture atlas.
   */
  const texture2_array& get_atlas() const;

  /** Retrieves the text mesh.
   *
   * \return the text mesh.
   */
  const text_mesh& get_mesh() const;

  /** Retrieves the text bounding box.
   *
   * \return the text bounding box.
   */
  const rectf& get_bounding_box() const;

private:
  std::unique_ptr<texture2_array> m_atlas;
  std::unique_ptr<text_mesh> m_mesh;
  rectf m_bounding_box;
};

}  // namespace hou

#endif
