// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Vertex2.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/VertexFormat.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rectangle.hpp"



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
    std::vector<Vertex2>{Vertex2(vec2f(l, t), vec2f(tl, tt), Color::White),
      Vertex2(vec2f(l, b), vec2f(tl, tb), Color::White),
      Vertex2(vec2f(r, b), vec2f(tr, tb), Color::White),
      Vertex2(vec2f(r, t), vec2f(tr, tt), Color::White)});
}

}  // namespace



const VertexFormat& Vertex2::getVertexFormat()
{
  static constexpr bool mustBeNormalized = true;
  static const VertexFormat vf(0, sizeof(Vertex2),
    {VertexAttribFormat(GlType::Float, Vertex2::sPositionSize,
       offsetof(Vertex2, m_position), !mustBeNormalized),
      VertexAttribFormat(GlType::Float, Vertex2::sTextureCoordinatesSize,
        offsetof(Vertex2, mTexCoords), mustBeNormalized),
      VertexAttribFormat(GlType::Float, Vertex2::sColorSize,
        offsetof(Vertex2, mColor), mustBeNormalized)});
  return vf;
}



Vertex2::Vertex2()
  : Vertex2(vec2f(0.f, 0.f), vec2f(0.f, 0.f), Color(0, 0, 0, 0))
{}



Vertex2::Vertex2(
  const vec2f& position, const vec2f& texCoords, const Color& col)
  : m_position{position.x(), position.y()}
  , mTexCoords{texCoords.x(), texCoords.y()}
  , mColor{col.getRedf(), col.getGreenf(), col.getBluef(), col.getAlphaf()}
{}



vec2f Vertex2::get_position() const
{
  return vec2f(m_position[0], m_position[1]);
}



void Vertex2::set_position(const vec2f& pos)
{
  m_position[0] = pos.x();
  m_position[1] = pos.y();
}



vec2f Vertex2::getTextureCoordinates() const
{
  return vec2f(mTexCoords[0], mTexCoords[1]);
}



void Vertex2::setTextureCoordinates(const vec2f& texCoords)
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
  return lhs.get_position() == rhs.get_position()
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
    && close(lhs.get_position(), rhs.get_position(), acc)
    && close(lhs.getTextureCoordinates(), rhs.getTextureCoordinates(), acc);
}



std::ostream& operator<<(std::ostream& os, const Vertex2& v)
{
  return os << "{Position = " << transpose(v.get_position())
            << ", TextureCoordinates = " << transpose(v.getTextureCoordinates())
            << ", Color = " << v.getColor() << "}";
}
Mesh2 createRectangleMesh2(const vec2f& size)
{
  return createGenericRectangleMesh2(
    0.f, 0.f, size.x(), size.y(), 0.f, 0.f, 1.f, 1.f);
}



Mesh2 createRectangleOutlineMesh2(const vec2f& size, float thickness)
{
  rectf er(vec2f::zero(), size);
  vec2f tv(thickness, thickness);
  rectf ir(tv, size - 2 * tv);
  return Mesh2(MeshDrawMode::TriangleStrip, MeshFillMode::Fill,
    std::vector<Vertex2>{
      Vertex2(vec2f(er.l(), er.t()), vec2f::zero(), Color::White),
      Vertex2(vec2f(ir.l(), ir.t()), vec2f::zero(), Color::White),
      Vertex2(vec2f(er.l(), er.b()), vec2f::zero(), Color::White),
      Vertex2(vec2f(ir.l(), ir.b()), vec2f::zero(), Color::White),
      Vertex2(vec2f(er.r(), er.b()), vec2f::zero(), Color::White),
      Vertex2(vec2f(ir.r(), ir.b()), vec2f::zero(), Color::White),
      Vertex2(vec2f(er.r(), er.t()), vec2f::zero(), Color::White),
      Vertex2(vec2f(ir.r(), ir.t()), vec2f::zero(), Color::White),
      Vertex2(vec2f(er.l(), er.t()), vec2f::zero(), Color::White),
      Vertex2(vec2f(ir.l(), ir.t()), vec2f::zero(), Color::White)});
}



Mesh2 createEllipseMesh2(const vec2f& size, uint pointCount)
{
  vec2f radius = size / 2.f;

  std::vector<Vertex2> vertices(pointCount + 2);
  vertices[0].set_position(radius);
  vertices[0].setColor(Color::White);

  float t = 0.f;
  float dt = 2.f * pi_f / pointCount;
  for(size_t i = 1; i < vertices.size(); ++i)
  {
    vec2f dPos(radius.x() * cosf(t), radius.y() * sinf(t));
    vertices[i].set_position(radius + dPos);
    vertices[i].setColor(Color::White);
    t += dt;
  }
  return Mesh2(MeshDrawMode::TriangleFan, MeshFillMode::Fill, vertices);
}



Mesh2 createEllipseOutlineMesh2(
  const vec2f& size, uint pointCount, float thickness)
{
  vec2f eRadius = size / 2.f;
  vec2f iRadius = eRadius - vec2f(thickness, thickness);

  float t = 0.f;
  float dt = 2 * pi_f / pointCount;
  std::vector<Vertex2> vertices(2 * pointCount + 2);
  for(size_t i = 0; i < vertices.size(); ++i)
  {
    float c = cosf(t);
    float s = sinf(t);

    vec2f edPos(eRadius.x() * c, eRadius.y() * s);
    vertices[i].set_position(eRadius + edPos);
    vertices[i].setColor(Color::White);
    ++i;
    HOU_ENSURE_DEV(i < vertices.size());

    vec2f idPos(iRadius.x() * c, iRadius.y() * s);
    vertices[i].set_position(eRadius + idPos);
    vertices[i].setColor(Color::White);

    t += dt;
  }
  return Mesh2(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices);
}



Mesh2 createTextureQuadMesh2(const rectf& rect, const vec2f& textureSize)
{
  return createGenericRectangleMesh2(0.f, 0.f, rect.w(), rect.h(),
    rect.x() / textureSize.x(), rect.y() / textureSize.y(),
    rect.w() / textureSize.x(), rect.h() / textureSize.y());
}

}  // namespace hou
