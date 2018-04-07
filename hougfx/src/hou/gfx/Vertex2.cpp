// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/Vertex2.hpp"

#include "hou/gfx/VertexFormat.hpp"



namespace hou
{

const VertexFormat& Vertex2::getVertexFormat()
{
  static constexpr bool mustBeNormalized = true;
  static const VertexFormat vf
    ( 0
    , sizeof(Vertex2)
    , { VertexAttribFormat
        ( GlType::Float
        , Vertex2::sPositionSize
        , offsetof(Vertex2, mPosition)
        , !mustBeNormalized)
      , VertexAttribFormat
        ( GlType::Float
        , Vertex2::sTextureCoordinatesSize
        , offsetof(Vertex2, mTexCoords)
        , mustBeNormalized)
      , VertexAttribFormat
        ( GlType::Float
        , Vertex2::sColorSize
        , offsetof(Vertex2, mColor)
        , mustBeNormalized)});
  return vf;
}



Vertex2::Vertex2()
  : Vertex2(Vec2f(0.f, 0.f), Vec2f(0.f, 0.f), Color(0, 0, 0, 0))
{}



Vertex2::Vertex2(const Vec2f& position, const Vec2f& texCoords
  , const Color& col)
  : mPosition{position.x(), position.y()}
  , mTexCoords{texCoords.x(), texCoords.y()}
  , mColor{col.getRedf(), col.getGreenf(), col.getBluef(), col.getAlphaf()}
{}



Vec2f Vertex2::getPosition() const
{
  return Vec2f(mPosition[0], mPosition[1]);
}



void Vertex2::setPosition(const Vec2f& pos)
{
  mPosition[0] = pos.x();
  mPosition[1] = pos.y();
}



Vec2f Vertex2::getTextureCoordinates() const
{
  return Vec2f(mTexCoords[0], mTexCoords[1]);
}



void Vertex2::setTextureCoordinates(const Vec2f& texCoords)
{
  mTexCoords[0] = texCoords.x();
  mTexCoords[1] = texCoords.y();
}



Color Vertex2::getColor() const
{
  return Color(mColor[0] * 255, mColor[1] * 255, mColor[2] * 255
    , mColor[3] * 255);
}



void Vertex2::setColor(const Color& color)
{
  mColor[0] = color.getRedf();
  mColor[1] = color.getGreenf();
  mColor[2] = color.getBluef();
  mColor[3] = color.getAlphaf();
}



bool operator==(const Vertex2& lhs, const Vertex2& rhs)
{
  return lhs.getPosition() == rhs.getPosition()
    && lhs.getTextureCoordinates() == rhs.getTextureCoordinates()
    && lhs.getColor() == rhs.getColor();
}



bool operator!=(const Vertex2& lhs, const Vertex2& rhs)
{
  return !(lhs == rhs);
}



bool close(const Vertex2& lhs, const Vertex2& rhs, float acc)
{
  return lhs.getColor() == rhs.getColor()
    && close(lhs.getPosition(), rhs.getPosition(), acc)
    && close(lhs.getTextureCoordinates(), rhs.getTextureCoordinates(), acc);
}



std::ostream& operator<<(std::ostream& os, const Vertex2& v)
{
  return os
    << "{Position = " << transpose(v.getPosition())
    << ", TextureCoordinates = " << transpose(v.getTextureCoordinates())
    << ", Color = " << v.getColor()
    << "}";
}

}

