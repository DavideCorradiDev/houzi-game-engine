// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/cor/StdVector.hpp"

#include "hou/sys/Color.hpp"

#include "hou/gfx/Vertex2.hpp"

using namespace hou;



namespace
{

class TestMesh2 : public TestGfxBase {};

}



TEST_F(TestMesh2, Creation)
{
  MeshDrawMode drawModeRef = MeshDrawMode::Points;
  MeshFillMode polygonModeRef = MeshFillMode::Line;
  std::vector<Vertex2> verticesRef
    { Vertex2(Vec2f(1.f, 2.f), Vec2f(3.f, 4.f), Color::Red)
    , Vertex2(Vec2f(5.f, 6.f), Vec2f(7.f, 8.f), Color::Green)};

  Mesh2 m(drawModeRef, polygonModeRef, verticesRef);

  EXPECT_EQ(MeshDrawMode::Points, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Line, m.getFillMode());
  EXPECT_EQ(verticesRef.size(), m.getVertexCount());
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh2, MoveConstructor)
{
  MeshDrawMode drawModeRef = MeshDrawMode::Points;
  MeshFillMode polygonModeRef = MeshFillMode::Line;
  std::vector<Vertex2> verticesRef
    { Vertex2(Vec2f(1.f, 2.f), Vec2f(3.f, 4.f), Color::Red)
    , Vertex2(Vec2f(5.f, 6.f), Vec2f(7.f, 8.f), Color::Green)};

  Mesh2 mDummy(drawModeRef, polygonModeRef, verticesRef);
  Mesh2 m(std::move(mDummy));

  EXPECT_EQ(MeshDrawMode::Points, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Line, m.getFillMode());
  EXPECT_EQ(verticesRef.size(), m.getVertexCount());
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh2, Rectangle)
{
  Mesh2 m = createRectangleMesh2(Vec2f(1.f, 2.f));

  EXPECT_EQ(MeshDrawMode::TriangleFan, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Fill, m.getFillMode());
  EXPECT_EQ(4u, m.getVertexCount());

  std::vector<Vertex2> verticesRef
    { Vertex2(Vec2f(0.f, 0.f), Vec2f(0.f, 0.f), Color::White)
    , Vertex2(Vec2f(0.f, 2.f), Vec2f(0.f, 1.f), Color::White)
    , Vertex2(Vec2f(1.f, 2.f), Vec2f(1.f, 1.f), Color::White)
    , Vertex2(Vec2f(1.f, 0.f), Vec2f(1.f, 0.f), Color::White)};
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh2, RectangleOutline)
{
  Mesh2 m = createRectangleOutlineMesh2(Vec2f(6.f, 8.f), 2);

  EXPECT_EQ(MeshDrawMode::TriangleStrip, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Fill, m.getFillMode());
  EXPECT_EQ(10u, m.getVertexCount());

  std::vector<Vertex2> verticesRef
    { Vertex2(Vec2f(0.f, 0.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(2.f, 2.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.f, 8.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(2.f, 6.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(6.f, 8.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(4.f, 6.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(6.f, 0.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(4.f, 2.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.f, 0.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(2.f, 2.f), Vec2f::zero(), Color::White)};
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh2, Ellipse)
{
  Mesh2 m = createEllipseMesh2(Vec2f(1.f, 2.f), 8);

  EXPECT_EQ(MeshDrawMode::TriangleFan, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Fill, m.getFillMode());
  EXPECT_EQ(10u, m.getVertexCount());

  std::vector<Vertex2> verticesRef
    { Vertex2(Vec2f(0.5f, 1.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(1.f, 1.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.853553f, 1.70711f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.5f, 2.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.146447f, 1.70711f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.f, 1.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.146447f, 0.292893f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.5f, 0.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.853553f, 0.292893f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(1.f, 1.f), Vec2f::zero(), Color::White)};
  HOU_EXPECT_CLOSE(verticesRef, m.getVertices(), 1e-5f);
}



TEST_F(TestMesh2, EllipseOutline)
{
  Mesh2 m = createEllipseOutlineMesh2(Vec2f(1.f, 2.f), 8, 0.25);

  EXPECT_EQ(MeshDrawMode::TriangleStrip, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Fill, m.getFillMode());
  EXPECT_EQ(18u, m.getVertexCount());

  std::vector<Vertex2> verticesRef
    { Vertex2(Vec2f(1.f, 1.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.75f, 1.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.853553f, 1.70711f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.676777f, 1.53033f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.5f, 2.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.5f, 1.75f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.146447f, 1.70711f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.323223f, 1.53033f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.f, 1.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.25f, 1.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.146447f, 0.292893f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.323223f, 0.46967f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.5f, 0.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.5f, 0.25f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.853553f, 0.292893f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.676777f, 0.46967f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(1.f, 1.f), Vec2f::zero(), Color::White)
    , Vertex2(Vec2f(0.75f, 1.f), Vec2f::zero(), Color::White)};
  HOU_EXPECT_CLOSE(verticesRef, m.getVertices(), 1e-5f);
}



TEST_F(TestMesh2, TextureQuad)
{
  Mesh2 m = createTextureQuadMesh2(Rectf(3.f, 8.f, 6.f, 4.f), Vec2f(12.f, 16.f));

  EXPECT_EQ(MeshDrawMode::TriangleFan, m.getDrawMode());
  EXPECT_EQ(MeshFillMode::Fill, m.getFillMode());
  EXPECT_EQ(4u, m.getVertexCount());

  std::vector<Vertex2> verticesRef
    { Vertex2(Vec2f(0.f, 0.f), Vec2f(0.25f, 0.5f), Color::White)
    , Vertex2(Vec2f(0.f, 4.f), Vec2f(0.25f, 0.75f), Color::White)
    , Vertex2(Vec2f(6.f, 4.f), Vec2f(0.75f, 0.75f), Color::White)
    , Vertex2(Vec2f(6.f, 0.f), Vec2f(0.75f, 0.5f), Color::White)};
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh2, Comparison)
{
  std::vector<Vertex2> vertices1
  {
    Vertex2(Vec2f(2.f, 2.f), Vec2f::zero(), Color::White),
    Vertex2(Vec2f(0.f, 8.f), Vec2f::zero(), Color::White),
  };
  std::vector<Vertex2> vertices2
  {
    Vertex2(Vec2f(2.f, 2.f), Vec2f(5.f, 0.f), Color::White),
    Vertex2(Vec2f(0.f, 8.f), Vec2f(0.f, 0.f), Color::White),
  };

  Mesh2 m1(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices1);
  Mesh2 m2(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices1);
  Mesh2 m3(MeshDrawMode::TriangleFan, MeshFillMode::Fill, vertices1);
  Mesh2 m4(MeshDrawMode::TriangleStrip, MeshFillMode::Line, vertices1);
  Mesh2 m5(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices2);

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
  EXPECT_FALSE(m1 == m4);
  EXPECT_FALSE(m1 == m5);

  EXPECT_FALSE(m1 != m2);
  EXPECT_TRUE(m1 != m3);
  EXPECT_TRUE(m1 != m4);
  EXPECT_TRUE(m1 != m5);
}



TEST_F(TestMesh2, CloseComparison)
{
  std::vector<Vertex2> vertices1
  {
    Vertex2(Vec2f(2.f, 2.f), Vec2f(1.1234f, 3.3456f), Color::White),
    Vertex2(Vec2f(0.f, 8.f), Vec2f(1.1234f, 3.3456f), Color::White),
  };
  std::vector<Vertex2> vertices2
  {
    Vertex2(Vec2f(2.f, 2.f), Vec2f(1.1238f, 3.3456f), Color::White),
    Vertex2(Vec2f(0.f, 8.f), Vec2f(1.1234f, 3.3456f), Color::White),
  };

  Mesh2 m1(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices1);
  Mesh2 m2(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices1);
  Mesh2 m3(MeshDrawMode::TriangleFan, MeshFillMode::Fill, vertices1);
  Mesh2 m4(MeshDrawMode::TriangleStrip, MeshFillMode::Line, vertices1);
  Mesh2 m5(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices2);

  EXPECT_TRUE(close(m1, m2, 1e-3f));
  EXPECT_FALSE(close(m1, m3, 1e-3f));
  EXPECT_FALSE(close(m1, m4, 1e-3f));
  EXPECT_TRUE(close(m1, m5, 1e-3f));

  EXPECT_TRUE(close(m1, m2, 1e-4f));
  EXPECT_FALSE(close(m1, m3, 1e-4f));
  EXPECT_FALSE(close(m1, m4, 1e-4f));
  EXPECT_FALSE(close(m1, m5, 1e-4f));

  EXPECT_TRUE(close(m1, m2));
  EXPECT_FALSE(close(m1, m3));
  EXPECT_FALSE(close(m1, m4));
  EXPECT_FALSE(close(m1, m5));
}



TEST_F(TestMesh2, OutputStreamOperator)
{
  std::vector<Vertex2> vertices
  {
    Vertex2(Vec2f(2.f, 2.f), Vec2f::zero(), Color::White),
    Vertex2(Vec2f(0.f, 8.f), Vec2f(1.f, 2.f), Color::Red),
  };
  Mesh2 m(MeshDrawMode::TriangleStrip, MeshFillMode::Fill, vertices);

  const char outRef[] =
    "{"
      "DrawMode = TriangleStrip, "
      "FillMode = Fill, "
      "Vertices = "
      "{"
        "{"
          "Position = (2, 2), "
          "TextureCoordinates = (0, 0), "
          "Color = {Red = 255, Green = 255, Blue = 255, Alpha = 255}"
        "}, "
        "{"
          "Position = (0, 8), "
          "TextureCoordinates = (1, 2), "
          "Color = {Red = 255, Green = 0, Blue = 0, Alpha = 255}"
        "}"
      "}"
    "}";

  HOU_EXPECT_OUTPUT(outRef, m);
}

