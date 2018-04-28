// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Vertex2.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/VertexFormat.hpp"

#include "hou/mth/MathFunctions.hpp"
#include "hou/mth/Rectangle.hpp"



namespace hou
{

namespace
{

Mesh2 createGenericRectangleMesh2(
  float l, float t, float w, float h, float tl, float tt, float tw, float th);



Mesh2 createGenericRectangleMesh2(
  float l, float t, float w, float h, float tl, float tt, float tw, float th)
{
  float r = l + w;
  float b = t + h;
  float tr = tl + tw;
  float tb = tt + th;
  return Mesh2(MeshDrawMode::TriangleFan, MeshFillMode::Fill,
    std::vector<Vertex2>{Vertex2(Vec2f(l, t), Vec2f(tl, tt), Color::White),
      Vertex2(Vec2f(l, b), Vec2f(tl, tb), Color::White),
      Vertex2(Vec2f(r, b), Vec2f(tr, tb), Color::White),
      Vertex2(Vec2f(r, t), Vec2f(tr, tt), Color::White)});
}

}  // namespace



const VertexFormat& Vertex2::getVertexFormat()
{
  static constexpr bool mustBeNormalized = true;
  static const VertexFormat vf(0, sizeof(Vertex2),
    {VertexAttribFormat(GlType::Float, Vertex2::sPositionSize,
       offsetof(Vertex2, mPosition), !mustBeNormalized),
      VertexAttribFormat(GlType::Float, Vertex2::sTextureCoordinatesSize,
        offsetof(Vertex2, mTexCoords), mustBeNormalized),
      VertexAttribFormat(GlType::Float, Vertex2::sColorSize,
        offsetof(Vertex2, mColor), mustBeNormalized)});
  return vf;
}



Vertex2::Vertex2()
  : Vertex2(Vec2f(0.f, 0.f), Vec2f(0.f, 0.f), Color(0, 0, 0, 0))
{}



Vertex2::Vertex2(
  const Vec2f& position, const Vec2f& texCoords, const Color& col)
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
  return Color(
    mColor[0] * 255, mColor[1] * 255, mColor[2] * 255, mColor[3] * 255);
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



bool close(const Vertex2& lhs, const Vertex2& rhs, Vertex2::ComparisonType acc)
{
  return lhs.getColor() == rhs.getColor()
    && close(lhs.getPosition(), rhs.getPosition(), acc)
    && close(lhs.getTextureCoordinates(), rhs.getTextureCoordinates(), acc);
}



std::ostream& operator<<(std::ostream& os, const Vertex2& v)
{
  return os << "{Position = " << transpose(v.getPosition())
            << ", TextureCoordinates = " << transpose(v.getTextureCoordinates())
            << ", Color = " << v.getColor() << "}";
}
Mesh2 createRectangleMesh2(const Vec2f& size)
{
  return createGenericRectangleMesh2(
    0.f, 0.f, size.x(), size.y(), 0.f, 0.f, 1.f, 1.f);
}



Mesh2 createRectangleOutlineMesh2(const Vec2f& size, float thickness)
{
  Rectf er(Vec2f::zero(), size);
  Vec2f tv(thickness, thickness);
  Rectf ir(tv, size - 2 * tv);
  return Mesh2(MeshDrawMode::TriangleStrip, MeshFillMode::Fill,
    std::vector<Vertex2>{
      Vertex2(Vec2f(er.l(), er.t()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(ir.l(), ir.t()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(er.l(), er.b()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(ir.l(), ir.b()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(er.r(), er.b()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(ir.r(), ir.b()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(er.r(), er.t()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(ir.r(), ir.t()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(er.l(), er.t()), Vec2f::zero(), Color::White),
      Vertex2(Vec2f(ir.l(), ir.t()), Vec2f::zero(), Color::White)});
}



Mesh2 createEllipseMesh2(const Vec2f& size, uint pointCount)
{
  Vec2f radius = size / 2.f;

  std::vector<Vertex2> vertices(pointCount + 2);
  vertices[0].setPosition(radius);
  vertices[0].setColor(Color::White);

  float t = 0.f;
  float dt = 2.f * PI_F / pointCount;
  for(size_t i = 1; i < vertices.size(); ++i)
  {
    Vec2f dPos(radius.x() * cosf(t), radius.y() * sinf(t));
    vertices[i].setPosition(radius + dPos);
    vertices[i].setColor(Color::White);
    t += dt;
  }
  return Mesh2(MeshDrawMode::TriangleFan, MeshFillMode::Fill, vertices);
}



Mesh2 createEllipseOutlineMesh2(
  const Vec2f& size, uint pointCount, float thickness)
{
  Vec2f eRadius = size / 2.f;
  Vec2f iRadius = eRadius - Vec2f(thickness, thickness);

  float t = 0.f;
  float dt = 2 * PI_F / pointCount;
  std::vector<Vertex2> vertices(2 * pointCount + 2);
  for(size_t i = 0; i < vertices.size(); ++i)
  {
    float c = cosf(t);
    float s = sinf(t);

    Vec2f edPos(eRadius.x() * c, eRadius.y() * s);
    vertices[i].setPosition(eRadius + edPos);
    vertices[i].setColor(Color::White);
    ++i;
    HOU_ENSURE_DEV(i < vertices.size());

    Vec2f idPos(iRadius.x() * c, iRadius.y() * s);
    vertices[i].setPosition(eRadius + idPos);
    vertices[i].setColor(Color::White);

    t += dt;
  }
  return Mesh2(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices);
}



Mesh2 createTextureQuadMesh2(const Rectf& rect, const Vec2f& textureSize)
{
  return createGenericRectangleMesh2(0.f, 0.f, rect.w(), rect.h(),
    rect.x() / textureSize.x(), rect.y() / textureSize.y(),
    rect.w() / textureSize.x(), rect.h() / textureSize.y());
}

}  // namespace hou
