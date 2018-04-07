// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/GlyphRenderInfo.hpp"
#include "hou/gfx/Mesh2.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/Image.hpp"

using namespace hou;



namespace
{

class TestGlyphRenderInfo : public TestGfxBase {};

class TestGlyphRenderInfoDeathTest : public TestGlyphRenderInfo {};

}



TEST_F(TestGlyphRenderInfo, Constructor)
{
  GlyphMetrics metricsRef(Vec2u(64u, 128u), Vec2i(3, 4), 5, Vec2i(6, 7), 8);
  Texture2 textureRef(Vec2u(16u, 16u), TextureFormat::RG);
  Vec2f offsetRef(9.f, 10.f);
  Mesh2 meshRef(createTextureQuadMesh2(Rectf(offsetRef
    , static_cast<Vec2f>(metricsRef.getSize()) / 64.f), textureRef.getSize()));

  GlyphRenderInfo gri(metricsRef, textureRef, offsetRef);
  EXPECT_EQ(metricsRef, gri.getMetrics());
  EXPECT_EQ(&textureRef, &gri.getTexture());
  HOU_EXPECT_FLOAT_CLOSE(meshRef, gri.getMesh());
}



TEST_F(TestGlyphRenderInfo, MoveConstructor)
{
  GlyphMetrics metricsRef(Vec2u(64u, 128u), Vec2i(3, 4), 5, Vec2i(6, 7), 8);
  Texture2 textureRef(Vec2u(16u, 16u), TextureFormat::RG);
  Vec2f offsetRef(9.f, 10.f);
  Mesh2 meshRef(createTextureQuadMesh2(Rectf(offsetRef
    , static_cast<Vec2f>(metricsRef.getSize()) / 64.f), textureRef.getSize()));

  GlyphRenderInfo griDummy(metricsRef, textureRef, offsetRef);
  GlyphRenderInfo gri(std::move(griDummy));
  EXPECT_EQ(metricsRef, gri.getMetrics());
  EXPECT_EQ(&textureRef, &gri.getTexture());
  HOU_EXPECT_FLOAT_CLOSE(meshRef, gri.getMesh());
}

