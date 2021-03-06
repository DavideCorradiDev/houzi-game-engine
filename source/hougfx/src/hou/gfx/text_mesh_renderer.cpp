#include "hou/gfx/text_mesh_renderer.hpp"

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

std::string get_gl_vertex_shader_source();
std::string get_gl_fragment_shader_source();



// clang-format off
std::string get_gl_vertex_shader_source()
{
  return
    "#version 330 core\n"
    "layout (location = 0) in vec2 posIn;\n"
    "layout (location = 1) in vec3 texIn;\n"
    "out vec3 texVs;\n"
    "uniform mat4 " UNI_TRANSFORM
    ";\n"
    "void main()\n"
    "{\n"
      "texVs = texIn;\n"
      "gl_Position = " UNI_TRANSFORM " * vec4(posIn, 0.f, 1.f);\n"
    "}\n";
}
// clang-format on



// clang-format off
std::string get_gl_fragment_shader_source()
{
  return
    "#version 330 core\n"
    "in vec3 texVs;\n"
    "out vec4 color;\n"
    "uniform vec4 " UNI_COLOR
    ";\n"
    "uniform sampler2DArray " UNI_TEXTURE
    ";\n"
    "void main()\n"
    "{\n"
      "color = " UNI_COLOR " * texture(" UNI_TEXTURE ", texVs);\n"
    "}\n";
}
// clang-format on

}  // namespace



text_mesh_renderer::text_mesh_renderer()
  : shader_program(vertex_shader(get_gl_vertex_shader_source()),
      fragment_shader(get_gl_fragment_shader_source()))
  , m_uni_color(get_uniform_location(UNI_COLOR))
  , m_uni_texture(get_uniform_location(UNI_TEXTURE))
  , m_uni_transform(get_uniform_location(UNI_TRANSFORM))
{}



void text_mesh_renderer::set_color(const color& color)
{
  gl::set_program_uniform_f(get_handle(), m_uni_color, color.get_red_f(),
    color.get_green_f(), color.get_blue_f(), color.get_alpha_f());
}



void text_mesh_renderer::set_texture_unit(uint unit)
{
  gl::set_program_uniform_i(get_handle(), m_uni_texture, unit);
}



void text_mesh_renderer::set_transform(const trans2f& trans)
{
  gl::set_program_uniform_mat4x4f(
    get_handle(), m_uni_transform, 1u, GL_TRUE, trans.to_mat4x4().data());
}



void text_mesh_renderer::draw(render_surface& target, const text_mesh& m,
  const texture2_array& tex, const color& col, const trans2f& trn)
{
  static constexpr uint texUnit = 0u;
  render_surface::set_current_render_target(target);
  set_color(col);
  set_texture_unit(texUnit);
  set_transform(trn);
  bind(*this);
  texture::bind(tex, texUnit);
  mesh::draw(m);
}



void text_mesh_renderer::draw(render_surface& target,
  const formatted_text& text, const color& col, const trans2f& trn)
{
  draw(target, text.get_mesh(), text.get_atlas(), col, trn);
}



void text_mesh_renderer::draw(render_surface& target, const std::string& text,
  const font& f, const color& col, const trans2f& trn)
{
  draw(target, formatted_text(text, f), col, trn);
}

}  // namespace hou
