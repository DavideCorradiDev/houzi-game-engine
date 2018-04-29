#include "hou/gfx/text_shader_program.hpp"

#include "hou/gfx/font.hpp"
#include "hou/gfx/formatted_text.hpp"
#include "hou/gfx/render_surface.hpp"
#include "hou/gfx/shader.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"

#include <set>

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
         "layout (location = 1) in vec3 texIn;\n"
         "out vec3 texVs;\n"
         "uniform mat4 " UNI_TRANSFORM
         ";\n"
         "void main()\n"
         "{\n"
         "texVs = texIn;\n"
         "gl_Position = " UNI_TRANSFORM
         " * vec4(posIn, 0.f, 1.f);\n"
         "}\n";
}



std::string getGlFragmentShaderSource()
{
  return "#version 330 core\n"
         "in vec3 texVs;\n"
         "out vec4 color;\n"
         "uniform vec4 " UNI_COLOR
         ";\n"
         "uniform sampler2DArray " UNI_TEXTURE
         ";\n"
         "void main()\n"
         "{\n"
         "color = " UNI_COLOR " * texture(" UNI_TEXTURE
         ", texVs);\n"
         "}\n";
}

}  // namespace



text_shader_program::text_shader_program()
  : shader_program(vertex_shader(getGlVertexShaderSource()),
      fragment_shader(getGlFragmentShaderSource()))
  , m_uni_color(get_uniform_location(UNI_COLOR))
  , m_uni_texture(get_uniform_location(UNI_TEXTURE))
  , m_uni_transform(get_uniform_location(UNI_TRANSFORM))
{}



text_shader_program::text_shader_program(text_shader_program&& other)
  : shader_program(std::move(other))
  , m_uni_color(std::move(other.m_uni_color))
  , m_uni_texture(std::move(other.m_uni_texture))
  , m_uni_transform(std::move(other.m_uni_transform))
{}



void text_shader_program::set_color(const color& ph_color)
{
  gl::set_program_uniform_f(get_handle(), m_uni_color, ph_color.get_red_f(),
    ph_color.get_green_f(), ph_color.get_blue_f(), ph_color.get_alpha_f());
}



void text_shader_program::set_texture_unit(uint unit)
{
  gl::set_program_uniform_i(get_handle(), m_uni_texture, unit);
}



void text_shader_program::set_transform(const trans2f& trans)
{
  gl::set_program_uniform_mat4x4f(
    get_handle(), m_uni_transform, 1u, GL_TRUE, trans.to_mat4x4().data());
}



void text_shader_program::draw(render_surface& target, const text_mesh& ph_mesh,
  const texture2_array& tex, const color& col, const trans2f& trn)
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



void text_shader_program::draw(render_surface& target, const formatted_text& text,
  const color& col, const trans2f& trn)
{
  draw(target, text.get_mesh(), text.get_atlas(), col, trn);
}



void text_shader_program::draw(render_surface& target, const std::string& text,
  const font& ph_font, const color& col, const trans2f& trn)
{
  draw(target, formatted_text(text, ph_font), col, trn);
}

}  // namespace hou
