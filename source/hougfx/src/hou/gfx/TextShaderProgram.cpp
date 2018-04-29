#include "hou/gfx/TextShaderProgram.hpp"

#include "hou/gfx/Font.hpp"
#include "hou/gfx/FormattedText.hpp"
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
  return "#ph_version 330 core\n"
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
  return "#ph_version 330 core\n"
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
  , mUniColor(getUniformLocation(UNI_COLOR))
  , mUniTexture(getUniformLocation(UNI_TEXTURE))
  , mUniTransform(getUniformLocation(UNI_TRANSFORM))
{}



TextShaderProgram::TextShaderProgram(TextShaderProgram&& other)
  : ShaderProgram(std::move(other))
  , mUniColor(std::move(other.mUniColor))
  , mUniTexture(std::move(other.mUniTexture))
  , mUniTransform(std::move(other.mUniTransform))
{}



void TextShaderProgram::set_color(const color& ph_color)
{
  gl::set_program_uniform_f(getHandle(), mUniColor, ph_color.get_red_f(),
    ph_color.get_green_f(), ph_color.get_blue_f(), ph_color.get_alpha_f());
}



void TextShaderProgram::setTextureUnit(uint unit)
{
  gl::set_program_uniform_i(getHandle(), mUniTexture, unit);
}



void TextShaderProgram::setTransform(const trans2f& trans)
{
  gl::set_program_uniform_mat4x4f(
    getHandle(), mUniTransform, 1u, GL_TRUE, trans.to_mat4x4().data());
}



void TextShaderProgram::draw(RenderSurface& target, const TextMesh& mesh,
  const Texture2Array& tex, const color& col, const trans2f& trn)
{
  static constexpr uint texUnit = 0u;
  RenderSurface::setCurrentRenderTarget(target);
  set_color(col);
  setTextureUnit(texUnit);
  setTransform(trn);
  bind(*this);
  Texture::bind(tex, texUnit);
  Mesh::draw(mesh);
}



void TextShaderProgram::draw(RenderSurface& target, const FormattedText& text,
  const color& col, const trans2f& trn)
{
  draw(target, text.getMesh(), text.getAtlas(), col, trn);
}



void TextShaderProgram::draw(RenderSurface& target, const std::string& text,
  const Font& font, const color& col, const trans2f& trn)
{
  draw(target, FormattedText(text, font), col, trn);
}

}  // namespace hou
