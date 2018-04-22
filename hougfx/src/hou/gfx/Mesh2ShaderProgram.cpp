// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Mesh2ShaderProgram.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/RenderSurface.hpp"
#include "hou/gfx/Shader.hpp"

#include "hou/sys/Color.hpp"

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



Mesh2ShaderProgram::Mesh2ShaderProgram()
  : ShaderProgram(VertexShader(getGlVertexShaderSource()),
      FragmentShader(getGlFragmentShaderSource()))
  , mBlankTexture(Vec2u(1u, 1u), TextureFormat::RGBA, 1u)
  , mUniColor(getUniformLocation(UNI_COLOR))
  , mUniTexture(getUniformLocation(UNI_TEXTURE))
  , mUniTransform(getUniformLocation(UNI_TRANSFORM))
{
  mBlankTexture.clear(PixelRGBA(Color::White));
}



Mesh2ShaderProgram::Mesh2ShaderProgram(Mesh2ShaderProgram&& other)
  : ShaderProgram(std::move(other))
  , mBlankTexture(std::move(other.mBlankTexture))
  , mUniColor(std::move(other.mUniColor))
  , mUniTexture(std::move(other.mUniTexture))
  , mUniTransform(std::move(other.mUniTransform))
{}



void Mesh2ShaderProgram::setColor(const Color& color)
{
  gl::setProgramUniformf(getHandle(), mUniColor, color.getRedf(),
    color.getGreenf(), color.getBluef(), color.getAlphaf());
}



void Mesh2ShaderProgram::setTextureUnit(uint unit)
{
  gl::setProgramUniformi(getHandle(), mUniTexture, unit);
}



void Mesh2ShaderProgram::setTransform(const Trans2f& trans)
{
  gl::setProgramUniformMatrix4f(
    getHandle(), mUniTransform, 1u, GL_TRUE, trans.toMat4x4().data());
}



void Mesh2ShaderProgram::draw(RenderSurface& target, const Mesh2& mesh,
  const Texture2& tex, const Color& col, const Trans2f& trn)
{
  static constexpr uint texUnit = 0u;
  RenderSurface::setCurrentRenderTarget(target);
  setColor(col);
  setTextureUnit(texUnit);
  setTransform(trn);
  bind(*this);
  Texture::bind(tex, texUnit);
  Mesh::draw(mesh);
}

void Mesh2ShaderProgram::draw(RenderSurface& target, const Mesh2& mesh,
  const Color& col, const Trans2f& trn)
{
  draw(target, mesh, mBlankTexture, col, trn);
}

void Mesh2ShaderProgram::draw(RenderSurface& target, const Mesh2& mesh,
  const Texture2& tex, const Trans2f& trn)
{
  draw(target, mesh, tex, Color::White, trn);
}

void Mesh2ShaderProgram::draw(
  RenderSurface& target, const Mesh2& mesh, const Trans2f& trn)
{
  draw(target, mesh, mBlankTexture, Color::White, trn);
}

}  // namespace hou
