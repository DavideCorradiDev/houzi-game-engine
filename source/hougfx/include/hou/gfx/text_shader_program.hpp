// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_SHADER_PROGRAM_HPP
#define HOU_GFX_TEXT_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/shader_program.hpp"
#include "hou/gfx/text_mesh.hpp"
#include "hou/gfx/texture_fwd.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

class color;
class font;
class formatted_text;
class render_surface;

/** shader program used to render text.
 */
class HOU_GFX_API text_shader_program : public shader_program
{
public:
  /** Constructor.
   */
  text_shader_program();

  /** Sets the color used when rendering.
   *
   * The default value is white.
   *
   * \param color the color.
   */
  void set_color(const color& color);

  /** Sets the texture unit used when rendering.
   *
   * The default value is 0.
   *
   * \param unit the texture unit to be used.
   */
  void set_texture_unit(uint unit);

  /** Sets the transform used when rendering.
   *
   * The default is the identity transform.
   *
   * \param trans the transform to be used.
   */
  void set_transform(const trans2f& trans);

  /** Draws a mesh onto a render_surface with the given parameters.
   *
   * \param target the rendering target.
   *
   * \param m the mesh.
   *
   * \param tex the texture.
   *
   * \param col the color.
   *
   * \param trn the transform.
   */
  void draw(render_surface& target, const text_mesh& m,
    const texture2_array& tex, const color& col = color::white,
    const trans2f& trn = trans2f::identity());

  /** Draws a formatted_text onto a render_surface with the given parameters.
   *
   * \param target the rendering target.
   *
   * \param text the formatted_text.
   *
   * \param col the color.
   *
   * \param trn the transform.
   */
  void draw(render_surface& target, const formatted_text& text,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  /** Draws a text string onto a render_surface with the given font and
   * parameters.
   *
   * \param target the rendering target.
   *
   * \param text the text.
   *
   * \param f the font.
   *
   * \param col the color.
   *
   * \param trn the transform.
   */
  void draw(render_surface& target, const std::string& text, const font& f,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

private:
  int m_uni_color;
  int m_uni_texture;
  int m_uni_transform;
};

}  // namespace hou

#endif
