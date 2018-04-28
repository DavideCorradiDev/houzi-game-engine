// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/TextVertex.hpp"

#include "hou/gfx/VertexFormat.hpp"



namespace hou
{

const VertexFormat& TextVertex::getVertexFormat()
{
  static constexpr bool mustBeNormalized = true;
  static const VertexFormat vf(0, sizeof(TextVertex),
    {VertexAttribFormat(GlType::Float, TextVertex::sPositionSize,
       offsetof(TextVertex, m_position), !mustBeNormalized),
      VertexAttribFormat(GlType::Float, TextVertex::sTextureCoordinatesSize,
        offsetof(TextVertex, mTexCoords), mustBeNormalized)});
  return vf;
}



TextVertex::TextVertex()
  : TextVertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f))
{}



TextVertex::TextVertex(const vec2f& position, const vec3f& texCoords)
  : m_position{position.x(), position.y()}
  , mTexCoords{texCoords.x(), texCoords.y(), texCoords.z()}
{}



vec2f TextVertex::get_position() const
{
  return vec2f(m_position[0], m_position[1]);
}



void TextVertex::set_position(const vec2f& pos)
{
  m_position[0] = pos.x();
  m_position[1] = pos.y();
}



vec3f TextVertex::getTextureCoordinates() const
{
  return vec3f(mTexCoords[0], mTexCoords[1], mTexCoords[2]);
}



void TextVertex::setTextureCoordinates(const vec3f& texCoords)
{
  mTexCoords[0] = texCoords.x();
  mTexCoords[1] = texCoords.y();
  mTexCoords[2] = texCoords.z();
}



bool operator==(const TextVertex& lhs, const TextVertex& rhs)
{
  return lhs.get_position() == rhs.get_position()
    && lhs.getTextureCoordinates() == rhs.getTextureCoordinates();
}



bool operator!=(const TextVertex& lhs, const TextVertex& rhs)
{
  return !(lhs == rhs);
}



bool close(
  const TextVertex& lhs, const TextVertex& rhs, TextVertex::ComparisonType acc)
{
  return close(lhs.get_position(), rhs.get_position(), acc)
    && close(lhs.getTextureCoordinates(), rhs.getTextureCoordinates(), acc);
}



std::ostream& operator<<(std::ostream& os, const TextVertex& v)
{
  return os << "{Position = " << transpose(v.get_position())
            << ", TextureCoordinates = " << transpose(v.getTextureCoordinates())
            << "}";
}

}  // namespace hou
