#include "hou/gfx/TextShaderProgram.hpp"

#include "hou/gfx/Font.hpp"
#include "hou/gfx/RenderFont.hpp"
#include "hou/gfx/RenderSurface.hpp"
#include "hou/gfx/Shader.hpp"

#include "hou/mth/Transform2.hpp"

#include "hou/sys/Color.hpp"

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
         "uniform mat4 " UNI_TRANSFORM ";\n"
         "void main()\n"
         "{\n"
         "texVs = texIn;\n"
         "gl_Position = " UNI_TRANSFORM " * vec4(posIn, 0.f, 1.f);\n"
         "}\n";
}



std::string getGlFragmentShaderSource()
{
  return "#version 330 core\n"
         "in vec3 texVs;\n"
         "out vec4 color;\n"
         "uniform vec4 " UNI_COLOR ";\n"
         "uniform sampler2DArray " UNI_TEXTURE ";\n"
         "void main()\n"
         "{\n"
         "color = " UNI_COLOR " * texture(" UNI_TEXTURE ", texVs);\n"
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



void TextShaderProgram::setColor(const Color& color)
{
  gl::setProgramUniformf(getHandle(), mUniColor, color.getRedf(),
    color.getGreenf(), color.getBluef(), color.getAlphaf());
}



void TextShaderProgram::setTextureUnit(uint unit)
{
  gl::setProgramUniformi(getHandle(), mUniTexture, unit);
}



void TextShaderProgram::setTransform(const Trans2f& trans)
{
  gl::setProgramUniformMatrix4f(
    getHandle(), mUniTransform, 1u, GL_TRUE, trans.toMat4x4().data());
}

void TextShaderProgram::draw(RenderSurface& target, const std::string& text,
  const Font& font, const Color& col, const Trans2f& trn)
{
  std::u32string textUtf32 = convertEncoding<Utf8, Utf32>(text);
  std::set<Utf32::CodeUnit> charSet(textUtf32.begin(), textUtf32.end());
  std::vector<Utf32::CodeUnit> charVec(charSet.begin(), charSet.end());
  RenderFont renderFont(charVec, font);
  RenderSurface::setCurrentRenderTarget(target);
  setColor(col);
  setTransform(trn);
  bind(*this);
  renderFont.draw(textUtf32);
}

}  // namespace hou
