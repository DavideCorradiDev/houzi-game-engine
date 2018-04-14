// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_SHADER_PROGRAM_HPP
#define HOU_GFX_TEXT_SHADER_PROGRAM_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/ShaderProgram.hpp"

#include "hou/mth/Transform2Fwd.hpp"



namespace hou
{

class Color;

class HOU_GFX_API TextShaderProgram : public ShaderProgram
{
public:
  TextShaderProgram();
  TextShaderProgram(TextShaderProgram&& other);

  void setColor(const Color& color);
  void setTextureUnit(uint unit);
  void setTransform(const Trans2f& trans);

private:
  int mUniColor;
  int mUniTexture;
  int mUniTransform;
};

}  // namespace hou

#endif
