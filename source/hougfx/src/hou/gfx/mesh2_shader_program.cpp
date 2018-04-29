// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/mesh2_shader_program.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/render_surface.hpp"
#include "hou/gfx/shader.hpp"

#include "hou/sys/color.hpp"

#define UNI_COLOR "colorUni"
#define UNI_TEXTURE "textureUni"
#define UNI_TRANSFORM "transformUni"



namespace hou
{

namespace
{

std::string getGlVertexShaderSource();
std::string getGlFragmentShaderSource();



std::string getGlVertexShaderSource()
{
  return "#version 330 core\n"
         "layout (location = 0) in vec2 posIn;\n"
         "layout (location = 1) in vec2 texIn;\n"
         "layout (location = 2) in vec4 colorIn;\n"
         "out vec2 texVs;\n"
         "out vec4 colorVs;\n"
         "uniform mat4 " UNI_TRANSFORM ";\n"
         "void main()\n"
         "{\n"
         "texVs = texIn;\n"
         "colorVs = colorIn;\n"
         "gl_Position = " UNI_TRANSFORM " * vec4(posIn, 0.f, 1.f);\n"
         "}\n";
}



std::string getGlFragmentShaderSource()
{
  return "#version 330 core\n"
         "in vec2 texVs;\n"
         "in vec4 colorVs;\n"
         "out vec4 color;\n"
         "uniform vec4 " UNI_COLOR ";\n"
         "uniform sampler2D " UNI_TEXTURE ";\n"
         "void main()\n"
         "{\n"
         "color = " UNI_COLOR " * colorVs * texture(" UNI_TEXTURE ", texVs);\n"
         "}\n";
}

}  // namespace



mesh2_shader_program::mesh2_shader_program()
  : shader_program(vertex_shader(getGlVertexShaderSource()),
      fragment_shader(getGlFragmentShaderSource()))
  , m_blank_texture(vec2u(1u, 1u), texture_format::rgba, 1u)
  , m_uni_color(get_uniform_location(UNI_COLOR))
  , m_uni_texture(get_uniform_location(UNI_TEXTURE))
  , m_uni_transform(get_uniform_location(UNI_TRANSFORM))
{
  m_blank_texture.clear(pixelrgba(color::white));
}



mesh2_shader_program::mesh2_shader_program(mesh2_shader_program&& other)
  : shader_program(std::move(other))
  , m_blank_texture(std::move(other.m_blank_texture))
  , m_uni_color(std::move(other.m_uni_color))
  , m_uni_texture(std::move(other.m_uni_texture))
  , m_uni_transform(std::move(other.m_uni_transform))
{}



void mesh2_shader_program::set_color(const color& ph_color)
{
  gl::set_program_uniform_f(get_handle(), m_uni_color, ph_color.get_red_f(),
    ph_color.get_green_f(), ph_color.get_blue_f(), ph_color.get_alpha_f());
}



void mesh2_shader_program::set_texture_unit(uint unit)
{
  gl::set_program_uniform_i(get_handle(), m_uni_texture, unit);
}



void mesh2_shader_program::set_transform(const trans2f& trans)
{
  gl::set_program_uniform_mat4x4f(
    get_handle(), m_uni_transform, 1u, GL_TRUE, trans.to_mat4x4().data());
}



void mesh2_shader_program::draw(render_surface& target, const mesh2& ph_mesh,
  const texture2& tex, const color& col, const trans2f& trn)
{
  static constexpr uint texUnit = 0u;
  render_surface::set_current_render_target(target);
  set_color(col);
  set_texture_unit(texUnit);
  set_transform(trn);
  bind(*this);
  texture::bind(tex, texUnit);
  mesh::draw(ph_mesh);
}

void mesh2_shader_program::draw(render_surface& target, const mesh2& ph_mesh,
  const color& col, const trans2f& trn)
{
  draw(target, ph_mesh, m_blank_texture, col, trn);
}

void mesh2_shader_program::draw(render_surface& target, const mesh2& ph_mesh,
  const texture2& tex, const trans2f& trn)
{
  draw(target, ph_mesh, tex, color::white, trn);
}

void mesh2_shader_program::draw(
  render_surface& target, const mesh2& ph_mesh, const trans2f& trn)
{
  draw(target, ph_mesh, m_blank_texture, color::white, trn);
}

}  // namespace hou
