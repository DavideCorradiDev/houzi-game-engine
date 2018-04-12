// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/Renderer2.hpp"

#include "hou/gfx/Glyph.hpp"
#include "hou/gfx/Font.hpp"
#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/RenderFont.hpp"
#include "hou/gfx/RenderSurface.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"

#include "hou/mth/Transform2.hpp"

#include "hou/sys/Image.hpp"

#define UNI_COLOR "colorUni"
#define UNI_TEXTURE "textureUni"
#define UNI_TRANSFORM "transformUni"



namespace hou
{

Renderer2::Renderer2()
  : NonCopyable()
  , mDefaultTexture(Image2RGBA
    ( Vec2u(1u, 1u), Image2RGBA::Pixel(255u, 255u, 255u, 255u)))
  , mShaderProgram()
  , mTextShaderProgram()
{
  mShaderProgram.setTextureUnit(0u);
}



Renderer2::Renderer2(Renderer2&& other)
  : mDefaultTexture(std::move(other.mDefaultTexture))
  , mShaderProgram(std::move(other.mShaderProgram))
  , mTextShaderProgram(std::move(other.mTextShaderProgram))
{}



void Renderer2::draw
  ( RenderSurface& target
  , const Mesh2& mesh
  , const Color& color
  , const Trans2f& trans)
{
  draw(target, mesh, mDefaultTexture, color, trans);
}



void Renderer2::draw
  ( RenderSurface& target
  , const Mesh2& mesh
  , const Texture2& texture
  , const Color& color
  , const Trans2f& trans)
{
  mShaderProgram.setColor(color);
  mShaderProgram.setTransform(trans);
  RenderSurface::setCurrentRenderTarget(target);
  Mesh2ShaderProgram::bind(mShaderProgram);
  Texture2::bind(texture, 0u);
  Mesh2::draw(mesh);
}



void Renderer2::draw
  ( RenderSurface& target
  , const std::string& text
  , Font& font
  , const Color& color
  , const Trans2f& trans)
{
  std::u32string textUtf32 = convertEncoding<Utf8, Utf32>(text);
  Vec2f penPos(0.f, 0.f);
  for(auto c : textUtf32)
  {
    static constexpr Utf32::CodeUnit sLineFeed = 0x0000000A;

    Glyph g = font.getGlyph(c);
    if(c == sLineFeed)
    {
      penPos.x() = 0.f;
      penPos.y() += font.getLineSpacing() / 64.f;
    }
    else if(g.getImage().getSize() == Vec2u::zero())
    {
      penPos.x() += g.getMetrics().getHorizontalAdvance() / 64.f;
    }
    else
    {
      Texture2 texture(g.getImage(), TextureFormat::R);
      texture.setChannelMapping(TextureChannelMapping::Alpha);
      Mesh2 quad = createTextureQuadMesh2(Rectf(Vec2f::zero(), texture.getSize())
        , texture.getSize());
      Trans2f charTrans = trans * Trans2f::translation(penPos
        + static_cast<Vec2f>(g.getMetrics().getHorizontalBearing() / 64.f));
      draw(target, quad, texture, color, charTrans);
      penPos.x() += g.getMetrics().getHorizontalAdvance() / 64.f;
    }
  }
}



void Renderer2::draw
  ( RenderSurface& target
  , const std::string& text
  , const RenderFont& font
  , const Color& color
  , const Trans2f& trans)
{
  mTextShaderProgram.setColor(color);
  mTextShaderProgram.setTransform(trans);
  RenderSurface::setCurrentRenderTarget(target);
  TextShaderProgram::bind(mTextShaderProgram);
  font.draw(text);
}

}

