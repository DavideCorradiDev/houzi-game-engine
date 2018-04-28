// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/cor/CoreFunctions.hpp"
#include "hou/cor/StdVector.hpp"

#include "hou/gfx/GlType.hpp"
#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/VertexFormat.hpp"

#include "hou/sys/Color.hpp"

using namespace hou;



namespace
{

class TestMesh : public TestGfxBase
{};

class VertexType
{
public:
  using ComparisonType = float;

public:
  static const VertexFormat& getVertexFormat();

public:
  VertexType();
  explicit VertexType(float value);

  float getValue() const;

private:
  GLfloat mValue;
};

bool operator==(const VertexType& lhs, const VertexType& rhs);
bool close(const VertexType& lhs, const VertexType& rhs,
  float acc = std::numeric_limits<GLfloat>::epsilon());
std::ostream& operator<<(std::ostream& os, const VertexType& v);

using MeshType = MeshT<VertexType>;



const VertexFormat& VertexType::getVertexFormat()
{
  static constexpr bool mustBeNormalized = true;
  static const VertexFormat vf(0, sizeof(VertexType),
    {VertexAttribFormat(
      GlType::Float, 1, offsetof(VertexType, mValue), !mustBeNormalized)});
  return vf;
}



VertexType::VertexType()
  : mValue(0.f)
{}



VertexType::VertexType(float value)
  : mValue(value)
{}



float VertexType::getValue() const
{
  return mValue;
}



bool operator==(const VertexType& lhs, const VertexType& rhs)
{
  return lhs.getValue() == rhs.getValue();
}



bool close(const VertexType& lhs, const VertexType& rhs, float acc)
{
  return hou::close(lhs.getValue(), rhs.getValue(), acc);
}



std::ostream& operator<<(std::ostream& os, const VertexType& v)
{
  return os << "{" << v.getValue() << "}";
}

}  // namespace



TEST_F(TestMesh, Constructor)
{
  MeshDrawMode drawModeRef = MeshDrawMode::Points;
  MeshFillMode polygonModeRef = MeshFillMode::Line;
  MeshType::VertexCollectionType verticesRef{
    VertexType(1.f), VertexType(1.3f), VertexType(3.5f)};

  MeshType m(drawModeRef, polygonModeRef, verticesRef);

  EXPECT_EQ(MeshDrawMode::Points, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Line, m.getFillMode());
  EXPECT_EQ(verticesRef.size(), m.getVertexCount());
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh, MoveConstructor)
{
  MeshDrawMode drawModeRef = MeshDrawMode::Points;
  MeshFillMode polygonModeRef = MeshFillMode::Line;
  MeshType::VertexCollectionType verticesRef{
    VertexType(1.f), VertexType(1.3f), VertexType(3.5f)};

  MeshType mDummy(drawModeRef, polygonModeRef, verticesRef);
  MeshType m(std::move(mDummy));

  EXPECT_EQ(MeshDrawMode::Points, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Line, m.getFillMode());
  EXPECT_EQ(verticesRef.size(), m.getVertexCount());
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh, Comparison)
{
  MeshType::VertexCollectionType vertices1{VertexType(1.f), VertexType(2.f)};
  MeshType::VertexCollectionType vertices2{VertexType(3.f), VertexType(2.f)};

  MeshType m1(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices1);
  MeshType m2(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices1);
  MeshType m3(MeshDrawMode::TriangleFan, MeshFillMode::Fill, vertices1);
  MeshType m4(MeshDrawMode::TriangleStrip, MeshFillMode::Line, vertices1);
  MeshType m5(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices2);

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
  EXPECT_FALSE(m1 == m4);
  EXPECT_FALSE(m1 == m5);

  EXPECT_FALSE(m1 != m2);
  EXPECT_TRUE(m1 != m3);
  EXPECT_TRUE(m1 != m4);
  EXPECT_TRUE(m1 != m5);
}



TEST_F(TestMesh, CloseComparison)
{
  MeshType::VertexCollectionType vertices1{
    VertexType(1.1234f), VertexType(2.f)};
  MeshType::VertexCollectionType vertices2{
    VertexType(1.1238f), VertexType(2.f)};

  MeshType m1(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices1);
  MeshType m2(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices1);
  MeshType m3(MeshDrawMode::TriangleFan, MeshFillMode::Fill, vertices1);
  MeshType m4(MeshDrawMode::TriangleStrip, MeshFillMode::Line, vertices1);
  MeshType m5(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices2);

  EXPECT_TRUE(close(m1, m2, static_cast<GLfloat>(1e-3f)));
  EXPECT_FALSE(close(m1, m3, static_cast<GLfloat>(1e-3f)));
  EXPECT_FALSE(close(m1, m4, static_cast<GLfloat>(1e-3f)));
  EXPECT_TRUE(close(m1, m5, static_cast<GLfloat>(1e-3f)));

  EXPECT_TRUE(close(m1, m2, static_cast<GLfloat>(1e-4f)));
  EXPECT_FALSE(close(m1, m3, static_cast<GLfloat>(1e-4f)));
  EXPECT_FALSE(close(m1, m4, static_cast<GLfloat>(1e-4f)));
  EXPECT_FALSE(close(m1, m5, static_cast<GLfloat>(1e-4f)));

  EXPECT_TRUE(close(m1, m2));
  EXPECT_FALSE(close(m1, m3));
  EXPECT_FALSE(close(m1, m4));
  EXPECT_FALSE(close(m1, m5));
}



TEST_F(TestMesh, OutputStreamOperator)
{
  MeshType::VertexCollectionType vertices{VertexType(1.f), VertexType(2.f)};
  MeshType m(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices);

  const char outRef[]
    = "{DrawMode = TriangleStrip, FillMode = Fill, Vertices = {{1}, {2}}}";
  HOU_EXPECT_OUTPUT(outRef, m);
}
