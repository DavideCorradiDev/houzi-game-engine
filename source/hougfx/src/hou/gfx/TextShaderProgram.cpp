#include "hou/gfx/TextShaderProgram.hpp"

#include "hou/gfx/font.hpp"
#include "hou/gfx/formatted_text.hpp"
#include "hou/gfx/RenderSurface.hpp"
#include "hou/gfx/Shader.hpp"
#include "hou/gfx/Texture.hpp"

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
         "out vec4 ph_color;\n"
         "uniform vec4 " UNI_COLOR
         ";\n"
         "uniform sampler2DArray " UNI_TEXTURE
         ";\n"
         "void main()\n"
         "{\n"
         "ph_color = " UNI_COLOR " * texture(" UNI_TEXTURE
         ", texVs);\n"
         "}\n";
}

}  // namespace



TextShaderProgram::TextShaderProgram()
  : ShaderProgram(VertexShader(getGlVertexShaderSource()),
      FragmentShader(getGlFragmentShaderSource()))
  , m_uni_color(getUniformLocation(UNI_COLOR))
  , m_uni_texture(getUniformLocation(UNI_TEXTURE))
  , m_uni_transform(getUniformLocation(UNI_TRANSFORM))
{}



TextShaderProgram::TextShaderProgram(TextShaderProgram&& other)
  : ShaderProgram(std::move(other))
  , m_uni_color(std::move(other.m_uni_color))
  , m_uni_texture(std::move(other.m_uni_texture))
  , m_uni_transform(std::move(other.m_uni_transform))
{}



void TextShaderProgram::set_color(const color& ph_color)
{
  gl::set_program_uniform_f(get_handle(), m_uni_color, ph_color.get_red_f(),
    ph_color.get_green_f(), ph_color.get_blue_f(), ph_color.get_alpha_f());
}



void TextShaderProgram::set_texture_unit(uint unit)
{
  gl::set_program_uniform_i(get_handle(), m_uni_texture, unit);
}



void TextShaderProgram::set_transform(const trans2f& trans)
{
  gl::set_program_uniform_mat4x4f(
    get_handle(), m_uni_transform, 1u, GL_TRUE, trans.to_mat4x4().data());
}



void TextShaderProgram::draw(RenderSurface& target, const TextMesh& ph_mesh,
  const Texture2Array& tex, const color& col, const trans2f& trn)
{
  static constexpr uint texUnit = 0u;
  RenderSurface::setCurrentRenderTarget(target);
  set_color(col);
  set_texture_unit(texUnit);
  set_transform(trn);
  bind(*this);
  Texture::bind(tex, texUnit);
  mesh::draw(ph_mesh);
}



void TextShaderProgram::draw(RenderSurface& target, const formatted_text& text,
  const color& col, const trans2f& trn)
{
  draw(target, text.get_mesh(), text.get_atlas(), col, trn);
}



void TextShaderProgram::draw(RenderSurface& target, const std::string& text,
  const font& ph_font, const color& col, const trans2f& trn)
{
  draw(target, formatted_text(text, ph_font), col, trn);
}

}  // namespace hou
