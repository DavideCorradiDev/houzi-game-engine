// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_TEXT_VERTEX_HPP
#define HOU_GFX_TEXT_VERTEX_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/mth/Matrix.hpp"


namespace hou
{

class VertexFormat;

class HOU_GFX_API TextVertex
{
public:
  static const VertexFormat& getVertexFormat();

public:
  TextVertex();
  TextVertex(const Vec2f& position, const Vec3f& textureCoordinates);

  Vec2f getPosition() const;
  void setPosition(const Vec2f& pos);
  Vec3f getTextureCoordinates() const;
  void setTextureCoordinates(const Vec3f& textureCoordinates);

private:
  static constexpr size_t sPositionSize = 2u;
  static constexpr size_t sTextureCoordinatesSize = 3u;

private:
  float mPosition[sPositionSize];
  float mTexCoords[sTextureCoordinatesSize];
};

HOU_GFX_API bool operator==(const TextVertex& lhs, const TextVertex& rhs);
HOU_GFX_API bool operator!=(const TextVertex& lhs, const TextVertex& rhs);
HOU_GFX_API bool close(const TextVertex& lhs, const TextVertex& rhs,
  float acc = std::numeric_limits<float>::epsilon());
HOU_GFX_API std::ostream& operator<<(std::ostream& os, const TextVertex& v);

template <typename VertexType>
class MeshT;
using TextMesh = MeshT<TextVertex>;

}  // namespace hou

#endif
