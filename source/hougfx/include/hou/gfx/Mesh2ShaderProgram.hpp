// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_2_SHADER_PROGRAM_HPP
#define HOU_GFX_MESH_2_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/ShaderProgram.hpp"
#include "hou/gfx/Texture.hpp"
#include "hou/gfx/Vertex2Fwd.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

class RenderSurface;

/** Shader program used to render Mesh2d objects.
 */
class HOU_GFX_API mesh2_shader_program : public ShaderProgram
{
public:
  /** Creates a mesh2_shader_program.
   */
  mesh2_shader_program();

  /** Move constructor.
   *
   *  \param other the other mesh2_shader_program.
   */
  mesh2_shader_program(mesh2_shader_program&& other);

  /** Sets the ph_color used when rendering Mesh2d objects.
   *
   *  The default value is white.
   *
   *  \param ph_color the ph_color.
   */
  void set_color(const color& ph_color);

  /** Sets the texture unit used when rendering Mesh2d objects.
   *
   *  The default value is 0.
   *
   *  \param unit the texture unit to be used.
   */
  void set_texture_unit(uint unit);

  /** Sets the transform to be used when rendering Mesh2d objects.
   *
   *  The default is the identity transform.
   *
   *  \param trans the transform to be used.
   */
  void set_transform(const trans2f& trans);

  void draw(RenderSurface& target, const Mesh2& ph_mesh, const Texture2& tex,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  void draw(RenderSurface& target, const Mesh2& ph_mesh,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  void draw(RenderSurface& target, const Mesh2& ph_mesh, const Texture2& tex,
    const trans2f& trn);

  void draw(RenderSurface& target, const Mesh2& ph_mesh, const trans2f& trn);

private:
  Texture2 m_blank_texture;
  int m_uni_color;
  int m_uni_texture;
  int m_uni_transform;
};

}  // namespace hou

#endif
