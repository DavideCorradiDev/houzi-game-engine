// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Mesh2ShaderProgram.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/RenderSurface.hpp"
#include "hou/gfx/Shader.hpp"

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
  return "#ph_version 330 core\n"
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
  return "#ph_version 330 core\n"
         "in vec2 texVs;\n"
         "in vec4 colorVs;\n"
         "out vec4 ph_color;\n"
         "uniform vec4 " UNI_COLOR ";\n"
         "uniform sampler2D " UNI_TEXTURE ";\n"
         "void main()\n"
         "{\n"
         "ph_color = " UNI_COLOR " * colorVs * texture(" UNI_TEXTURE ", texVs);\n"
         "}\n";
}

}  // namespace



Mesh2ShaderProgram::Mesh2ShaderProgram()
  : ShaderProgram(VertexShader(getGlVertexShaderSource()),
      FragmentShader(getGlFragmentShaderSource()))
  , mBlankTexture(vec2u(1u, 1u), TextureFormat::rgba, 1u)
  , mUniColor(getUniformLocation(UNI_COLOR))
  , mUniTexture(getUniformLocation(UNI_TEXTURE))
  , mUniTransform(getUniformLocation(UNI_TRANSFORM))
{
  mBlankTexture.clear(pixelrgba(color::white));
}



Mesh2ShaderProgram::Mesh2ShaderProgram(Mesh2ShaderProgram&& other)
  : ShaderProgram(std::move(other))
  , mBlankTexture(std::move(other.mBlankTexture))
  , mUniColor(std::move(other.mUniColor))
  , mUniTexture(std::move(other.mUniTexture))
  , mUniTransform(std::move(other.mUniTransform))
{}



void Mesh2ShaderProgram::set_color(const color& ph_color)
{
  gl::set_program_uniform_f(getHandle(), mUniColor, ph_color.get_red_f(),
    ph_color.get_green_f(), ph_color.get_blue_f(), ph_color.get_alpha_f());
}



void Mesh2ShaderProgram::setTextureUnit(uint unit)
{
  gl::set_program_uniform_i(getHandle(), mUniTexture, unit);
}



void Mesh2ShaderProgram::setTransform(const trans2f& trans)
{
  gl::set_program_uniform_mat4x4f(
    getHandle(), mUniTransform, 1u, GL_TRUE, trans.to_mat4x4().data());
}



void Mesh2ShaderProgram::draw(RenderSurface& target, const Mesh2& mesh,
  const Texture2& tex, const color& col, const trans2f& trn)
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

void Mesh2ShaderProgram::draw(RenderSurface& target, const Mesh2& mesh,
  const color& col, const trans2f& trn)
{
  draw(target, mesh, mBlankTexture, col, trn);
}

void Mesh2ShaderProgram::draw(RenderSurface& target, const Mesh2& mesh,
  const Texture2& tex, const trans2f& trn)
{
  draw(target, mesh, tex, color::white, trn);
}

void Mesh2ShaderProgram::draw(
  RenderSurface& target, const Mesh2& mesh, const trans2f& trn)
{
  draw(target, mesh, mBlankTexture, color::white, trn);
}

}  // namespace hou
