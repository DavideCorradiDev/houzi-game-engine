// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_2_SHADER_PROGRAM_HPP
#define HOU_GFX_MESH_2_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gfx/shader_program.hpp"
#include "hou/gfx/texture.hpp"
#include "hou/gfx/vertex2_fwd.hpp"

#include "hou/gfx/gfx_export.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

class render_surface;

/** shader program used to render Mesh2d objects.
 */
class HOU_GFX_API mesh2_shader_program : public shader_program
{
public:
  /** Constructor.
   */
  mesh2_shader_program();

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
  void draw(render_surface& target, const mesh2& m, const texture2& tex,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  /** Draws a mesh onto a render_surface with the given parameters.
   *
   * \param target the rendering target.
   *
   * \param m the mesh.
   *
   * \param col the color.
   *
   * \param trn the transform.
   */
  void draw(render_surface& target, const mesh2& m,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  /** Draws a mesh onto a render_surface with the given parameters.
   *
   * \param target the rendering target.
   *
   * \param m the mesh.
   *
   * \param tex the texture.
   *
   * \param trn the transform.
   */
  void draw(render_surface& target, const mesh2& m, const texture2& tex,
    const trans2f& trn);

  /** Draws a mesh onto a render_surface with the given parameters.
   *
   * \param target the rendering target.
   *
   * \param m the mesh.
   *
   * \param trn the transform.
   */
  void draw(render_surface& target, const mesh2& m, const trans2f& trn);

private:
  texture2 m_blank_texture;
  int m_uni_color;
  int m_uni_texture;
  int m_uni_transform;
};

}  // namespace hou

#endif
