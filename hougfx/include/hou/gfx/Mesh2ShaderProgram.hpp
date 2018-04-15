// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_MESH_2_SHADER_PROGRAM_HPP
#define HOU_GFX_MESH_2_SHADER_PROGRAM_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/gfx/ShaderProgram.hpp"

#include "hou/mth/Transform2Fwd.hpp"



namespace hou
{

class Color;

/** Shader program used to render Mesh2d objects.
 */
class HOU_GFX_API Mesh2ShaderProgram
  : public ShaderProgram
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

  /** Sets the color used when rendering Mesh2d objects.
   *
   *  The default value is white.
   *
   *  \param color the color.
   */
  void setColor(const Color& color);

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
  void setTransform(const Trans2f& trans);

private:
  int mUniColor;
  int mUniTexture;
  int mUniTransform;
};

}

#endif

