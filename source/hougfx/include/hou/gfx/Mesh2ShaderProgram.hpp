// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_2_SHADER_PROGRAM_HPP
#define HOU_GFX_MESH_2_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/GfxExport.hpp"

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
class HOU_GFX_API Mesh2ShaderProgram : public ShaderProgram
{
public:
  /** Creates a Mesh2ShaderProgram.
   */
  Mesh2ShaderProgram();

  /** Move constructor.
   *
   *  \param other the other Mesh2ShaderProgram.
   */
  Mesh2ShaderProgram(Mesh2ShaderProgram&& other);

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
  void setTextureUnit(uint unit);

  /** Sets the transform to be used when rendering Mesh2d objects.
   *
   *  The default is the identity transform.
   *
   *  \param trans the transform to be used.
   */
  void setTransform(const trans2f& trans);

  void draw(RenderSurface& target, const Mesh2& mesh, const Texture2& tex,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  void draw(RenderSurface& target, const Mesh2& mesh,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  void draw(RenderSurface& target, const Mesh2& mesh, const Texture2& tex,
    const trans2f& trn);

  void draw(RenderSurface& target, const Mesh2& mesh, const trans2f& trn);

private:
  Texture2 mBlankTexture;
  int mUniColor;
  int mUniTexture;
  int mUniTransform;
};

}  // namespace hou

#endif
