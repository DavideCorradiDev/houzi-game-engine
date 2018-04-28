// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_SHADER_PROGRAM_HPP
#define HOU_GFX_TEXT_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/ShaderProgram.hpp"
#include "hou/gfx/TextVertex.hpp"
#include "hou/gfx/TextureFwd.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

class color;
class Font;
class FormattedText;
class RenderSurface;

class HOU_GFX_API TextShaderProgram : public ShaderProgram
{
public:
  TextShaderProgram();
  TextShaderProgram(TextShaderProgram&& other);

  void set_color(const color& ph_color);
  void setTextureUnit(uint unit);
  void setTransform(const trans2f& trans);

  void draw(RenderSurface& target, const TextMesh& mesh,
    const Texture2Array& tex, const color& col = color::white,
    const trans2f& trn = trans2f::identity());

  void draw(RenderSurface& target, const FormattedText& text,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  void draw(RenderSurface& target, const std::string& text, const Font& font,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

private:
  int mUniColor;
  int mUniTexture;
  int mUniTransform;
};

}  // namespace hou

#endif
