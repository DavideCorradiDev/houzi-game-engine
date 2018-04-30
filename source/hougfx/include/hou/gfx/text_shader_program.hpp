// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_SHADER_PROGRAM_HPP
#define HOU_GFX_TEXT_SHADER_PROGRAM_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/shader_program.hpp"
#include "hou/gfx/text_vertex.hpp"
#include "hou/gfx/texture_fwd.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

class color;
class font;
class formatted_text;
class render_surface;

class HOU_GFX_API text_shader_program : public shader_program
{
public:
  text_shader_program();
  text_shader_program(text_shader_program&& other);

  void set_color(const color& color);
  void set_texture_unit(uint unit);
  void set_transform(const trans2f& trans);

  void draw(render_surface& target, const text_mesh& ph_mesh,
    const texture2_array& tex, const color& col = color::white,
    const trans2f& trn = trans2f::identity());

  void draw(render_surface& target, const formatted_text& text,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

  void draw(render_surface& target, const std::string& text, const font& ph_font,
    const color& col = color::white, const trans2f& trn = trans2f::identity());

private:
  int m_uni_color;
  int m_uni_texture;
  int m_uni_transform;
};

}  // namespace hou

#endif
