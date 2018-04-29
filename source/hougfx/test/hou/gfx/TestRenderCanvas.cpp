// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/render_canvas.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/gl/gl_error.hpp"

#include "hou/sys/color.hpp"

#include <algorithm>

using namespace hou;



namespace
{

class TestRenderCanvas : public TestGfxBase
{};

class TestRenderCanvasDeathTest : public TestRenderCanvas
{};



image2RGBA generateBlitResultImage(const vec2u& dstSize, const recti& dstRect,
  const color& dstColor, const color& srcColor);



image2RGBA generateBlitResultImage(const vec2u& dstSize, const recti& dstRect,
  const color& dstColor, const color& srcColor)
{
  image2RGBA imRef(dstSize);
  imRef.clear(image2RGBA::pixel(dstColor.get_red(), dstColor.get_green(),
    dstColor.get_blue(), dstColor.get_alpha()));

  uint xMax = std::min(static_cast<uint>(dstRect.r()), dstSize.x());
  uint yMax = std::min(static_cast<uint>(dstRect.b()), dstSize.y());
  for(uint y = dstRect.t(); y < yMax; ++y)
  {
    for(uint x = dstRect.l(); x < xMax; ++x)
    {
      imRef.set_pixel(vec2u(x, y),
        image2RGBA::pixel(srcColor.get_red(), srcColor.get_green(),
          srcColor.get_blue(), srcColor.get_alpha()));
    }
  }
  return imRef;
}

}  // namespace



TEST_F(TestRenderCanvas, Creation)
{
  vec2u size(3u, 4u);
  uint samples = 1u;
  render_canvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.get_sample_count());
  EXPECT_FALSE(rs.is_multisampled());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    rs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, CreationErrorZeroSamples)
{
  vec2u size(3u, 4u);
  HOU_EXPECT_PRECONDITION(render_canvas rs(size, 0u));
}



TEST_F(TestRenderCanvas, CreationWithAreaGreaterThanMaxTextureSize)
{
  vec2u size(texture2::get_max_size().x(), 2u);
  uint samples = 1u;
  render_canvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.get_sample_count());
  EXPECT_FALSE(rs.is_multisampled());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    rs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, CreationMultisampled)
{
  vec2u size(3u, 4u);
  uint samples = 2u;
  render_canvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.get_sample_count());
  EXPECT_TRUE(rs.is_multisampled());

  render_canvas ssrs(size);
  blit(rs, rs.get_default_viewport(), ssrs, rs.get_default_viewport());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    ssrs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvasDeathTest, CreationSamplesTooLarge)
{
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(3u, 4u), 40000u));
}



TEST_F(TestRenderCanvasDeathTest, CreationSizeNull)
{
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(0u, 0u), 1u));
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(1u, 0u), 1u));
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(0u, 1u), 1u));
}



TEST_F(TestRenderCanvasDeathTest, CreationSizeTooLarge)
{
  const uint size = gl::get_max_texture_size() + 1;
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(size, size), 1u));
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(1u, size), 1u));
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(size, 1u), 1u));
}



TEST_F(TestRenderCanvas, MoveConstructor)
{
  vec2u size(3u, 4u);
  uint samples = 2u;
  render_canvas rs1(size, samples);
  render_canvas rs2(std::move(rs1));

  EXPECT_EQ(recti(vec2i(0, 0), size), rs2.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs2.get_viewport());
  EXPECT_EQ(size, rs2.get_size());
  EXPECT_EQ(samples, rs2.get_sample_count());
  EXPECT_TRUE(rs2.is_multisampled());

  render_canvas ssrs(size);
  blit(rs2, rs2.get_default_viewport(), ssrs, rs2.get_default_viewport());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    ssrs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, Viewport)
{
  vec2u size(3u, 4u);
  render_canvas rs(size);
  recti viewport(vec2i(1, 2), vec2i(3, 5));
  rs.set_viewport(viewport);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(viewport, rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
}



TEST_F(TestRenderCanvas, NegativeSizeViewport)
{
  vec2u size(3u, 4u);
  render_canvas rs(size);
  recti viewport(vec2i(1, -2), vec2i(-3, 5));
  rs.set_viewport(viewport);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(viewport, rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
}



TEST_F(TestRenderCanvas, IsMultisampled)
{
  render_canvas rs1(vec2u(3u, 4u), 1u);
  render_canvas rs2(vec2u(3u, 4u), 2u);

  EXPECT_FALSE(rs1.is_multisampled());
  EXPECT_TRUE(rs2.is_multisampled());
}



TEST_F(TestRenderCanvas, Clear)
{
  vec2u size(3u, 4u);
  render_canvas rs(size);
  color col(4, 6, 2, 78);

  rs.clear(col);

  image2RGBA imRef(size);
  imRef.clear(image2RGBA::pixel(
    col.get_red(), col.get_green(), col.get_blue(), col.get_alpha()));
  EXPECT_EQ(imRef, rs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitFullSize)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size);
  render_canvas rsDst(size);

  recti blitRect = rsSrc.get_default_viewport();
  rsSrc.clear(color::red);
  blit(rsSrc, blitRect, rsDst, blitRect);

  EXPECT_EQ(rsSrc.to_texture().get_image<pixel_format::rgba>(),
    rsDst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitSmallRect)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size);
  render_canvas rsDst(size);

  recti blitRect(vec2i(1, 2), vec2i(2, 1));
  color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, blitRect, rsDst, blitRect);

  image2RGBA imRef
    = generateBlitResultImage(size, blitRect, color::transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitDifferentSourceAndDestinationRect)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size);
  render_canvas rsDst(size);

  recti srcRect(vec2i(1, 2), vec2i(2, 1));
  recti dstRect(vec2i(0, 1), vec2i(2, 3));
  color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  image2RGBA imRef
    = generateBlitResultImage(size, dstRect, color::transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitOverFlowingSourceRect)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size);
  render_canvas rsDst(size);

  recti srcRect(vec2i(2, 2), vec2i(2, 3));
  recti dstRect(vec2i(0, 0), vec2i(2, 3));
  color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  image2RGBA imRef = generateBlitResultImage(
    size, recti(0, 0, 1, 2), color::transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitOverFlowingDestinationRect)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size);
  render_canvas rsDst(size);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(2, 2), vec2i(2, 3));
  color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  image2RGBA imRef
    = generateBlitResultImage(size, dstRect, color::transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitInvertedSourceRect)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size);
  render_canvas rsDst(size);

  recti srcRect(vec2i(0, 1), vec2i(2, -3));
  recti dstRect(vec2i(0, 0), vec2i(2, 3));
  color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  image2RGBA imRef = generateBlitResultImage(
    size, recti(0, 0, 2, 1), color::transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitInvertedDestinationRect)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size);
  render_canvas rsDst(size);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(0, 1), vec2i(2, -3));
  color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  image2RGBA imRef = generateBlitResultImage(
    size, recti(0, 0, 2, 1), color::transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitDifferentSampleSizeSameRectSize)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size, 2u);
  render_canvas rsDst(size, 1u);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(0, 0), vec2i(2, 3));
  color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  image2RGBA imRef
    = generateBlitResultImage(size, dstRect, color::transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, BlitDifferentSampleSizeSameRectSizeInverted)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size, 2u);
  render_canvas rsDst(size, 1u);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(0, 4), vec2i(2, -3));
  color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  image2RGBA imRef = generateBlitResultImage(
    size, recti(0, 1, 2, 3), color::transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.to_texture().get_image<pixel_format::rgba>());
}


TEST_F(TestRenderCanvasDeathTest, BlitDifferentSampleSizeDifferentRectSize)
{
  vec2u size(3u, 4u);
  render_canvas rsSrc(size, 2u);
  render_canvas rsDst(size, 1u);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(0, 0), vec2i(1, 2));
  rsSrc.clear(color::red);
  HOU_EXPECT_PRECONDITION(blit(rsSrc, srcRect, rsDst, dstRect));
}



TEST_F(TestRenderCanvas, ToTextureMultisampled)
{
  render_canvas rs(vec2u(3u, 4u), 2u);
  color col(3, 5, 8, 9);
  rs.clear(col);

  texture2 tex = rs.to_texture();
  image2RGBA imRef(tex.get_size(), pixelrgba(col));
  EXPECT_EQ(imRef, tex.get_image<pixel_format::rgba>());
}



TEST_F(TestRenderCanvas, SetCurrentRenderSource)
{
  render_canvas rs1(vec2u(3u, 4u));
  render_canvas rs2(vec2u(3u, 4u));
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
  render_canvas::set_current_render_source(rs1);
  EXPECT_TRUE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
  render_canvas::set_current_render_source(rs2);
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_TRUE(rs2.is_current_render_source());
  render_canvas::set_default_render_source();
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
}



TEST_F(TestRenderCanvas, SetCurrentRenderTarget)
{
  render_canvas rs1(vec2u(3u, 4u));
  render_canvas rs2(vec2u(3u, 4u));
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
  render_canvas::set_current_render_target(rs1);
  EXPECT_TRUE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
  render_canvas::set_current_render_target(rs2);
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_TRUE(rs2.is_current_render_target());
  render_canvas::set_default_render_target();
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
}
