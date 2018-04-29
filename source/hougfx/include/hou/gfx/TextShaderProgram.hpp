// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_SHADER_PROGRAM_HPP
#define HOU_GFX_TEXT_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/ShaderProgram.hpp"
#include "hou/gfx/TextVertex.hpp"
#include "hou/gfx/TextureFwd.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

class color;
class font;
class formatted_text;
class RenderSurface;

class HOU_GFX_API TextShaderProgram : public ShaderProgram
{
public:
  TextShaderProgram();
  TextShaderProgram(TextShaderProgram&& other);

  void set_color(const color& ph_color);
  void set_texture_unit(uint unit);
  void set_transform(const trans2f& trans);

  void draw(RenderSurface& target, const TextMesh& ph_mesh,
    const Texture2Array& tex, const color& col = color::white,
    const trans2f& trn = trans2f::identity());

  void draw(RenderSurface& target, const formatted_text& text,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  void draw(RenderSurface& target, const std::string& text, const font& ph_font,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

private:
  int m_uni_color;
  int m_uni_texture;
  int m_uni_transform;
};

}  // namespace hou

#endif
