// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/RenderTexture.hpp"
#include "hou/gfx/Texture.hpp"

using namespace hou;



namespace
{

class TestRenderTexture : public TestGfxBase {};

class TestRenderTextureDeathTest : public TestRenderTexture {};

}




TEST_F(TestRenderTexture, Creation)
{
  Vec2u size(3u, 4u);
  uint samples = 0u;
  RenderTexture rs(size, samples);

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getViewport());
  EXPECT_EQ(size, rs.getSize());
  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_FALSE(rs.isMultisampled());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(), rs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderTexture, CreationMultisampled)
{
  Vec2u size(3u, 4u);
  uint samples = 2u;
  RenderTexture rs(size, samples);

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getViewport());
  EXPECT_EQ(size, rs.getSize());
  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_TRUE(rs.isMultisampled());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(), rs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderTexture, MoveConstructor)
{
  Vec2u size(3u, 4u);
  uint samples = 2u;
  RenderTexture rs1(size, samples);
  RenderTexture rs2(std::move(rs1));

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs2.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs2.getViewport());
  EXPECT_EQ(size, rs2.getSize());
  EXPECT_EQ(samples, rs2.getSampleCount());
  EXPECT_TRUE(rs2.isMultisampled());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(), rs2.toTexture().getImage<PixelFormat::RGBA>());
}

