// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gfx/TextVertex.hpp"

#include "hou/gfx/VertexFormat.hpp"



namespace hou
{

const VertexFormat& TextVertex::getVertexFormat()
{
  static constexpr bool mustBeNormalized = true;
  static const VertexFormat vf(0, sizeof(TextVertex),
    {VertexAttribFormat(GlType::Float, TextVertex::sPositionSize,
       offsetof(TextVertex, mPosition), !mustBeNormalized),
      VertexAttribFormat(GlType::Float, TextVertex::sTextureCoordinatesSize,
        offsetof(TextVertex, mTexCoords), mustBeNormalized)});
  return vf;
}



TextVertex::TextVertex()
  : TextVertex(Vec2f(0.f, 0.f), Vec3f(0.f, 0.f, 0.f))
{}



TextVertex::TextVertex(const Vec2f& position, const Vec3f& texCoords)
  : mPosition{position.x(), position.y()}
  , mTexCoords{texCoords.x(), texCoords.y(), texCoords.z()}
{}



Vec2f TextVertex::getPosition() const
{
  return Vec2f(mPosition[0], mPosition[1]);
}



void TextVertex::setPosition(const Vec2f& pos)
{
  mPosition[0] = pos.x();
  mPosition[1] = pos.y();
}



Vec3f TextVertex::getTextureCoordinates() const
{
  return Vec3f(mTexCoords[0], mTexCoords[1], mTexCoords[2]);
}



void TextVertex::setTextureCoordinates(const Vec3f& texCoords)
{
  mTexCoords[0] = texCoords.x();
  mTexCoords[1] = texCoords.y();
  mTexCoords[2] = texCoords.z();
}



bool operator==(const TextVertex& lhs, const TextVertex& rhs)
{
  return lhs.getPosition() == rhs.getPosition()
    && lhs.getTextureCoordinates() == rhs.getTextureCoordinates();
}



bool operator!=(const TextVertex& lhs, const TextVertex& rhs)
{
  return !(lhs == rhs);
}



bool close(const TextVertex& lhs, const TextVertex& rhs, float acc)
{
  return close(lhs.getPosition(), rhs.getPosition(), acc)
    && close(lhs.getTextureCoordinates(), rhs.getTextureCoordinates(), acc);
}



std::ostream& operator<<(std::ostream& os, const TextVertex& v)
{
  return os << "{Position = " << transpose(v.getPosition())
            << ", TextureCoordinates = " << transpose(v.getTextureCoordinates())
            << "}";
}

}  // namespace hou
