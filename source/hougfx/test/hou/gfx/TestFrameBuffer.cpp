// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/framebuffer.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/image.hpp"

using namespace hou;



namespace
{

class TestFrameBuffer : public TestGfxBase
{};

class TestFrameBufferDeathTest : public TestFrameBuffer
{};

template <typename SrcTexType, typename DstTexType>
void testColorBlit(TextureFormat srcFormat,
  const typename SrcTexType::size_type& srcSize, const recti& srcRect,
  TextureFormat dstFormat, const typename DstTexType::size_type& dstSize,
  const recti& dstRect, framebuffer_blit_filter filter, bool testError = false);

template <typename SrcTexType, typename DstTexType>
void testColorBlit(TextureFormat srcFormat,
  const typename SrcTexType::size_type& srcSize, const recti& srcRect,
  TextureFormat dstFormat, const typename DstTexType::size_type& dstSize,
  const recti& dstRect, framebuffer_blit_filter filter, bool testError)
{
  using image = image2RGBA;
  using pixel = pixelrgba;

  // Build the framebuffers.
  color colorRef(2u, 3u, 5u, 7u);
  pixel pixelRef(colorRef);

  framebuffer srcFb;
  SrcTexType srcTex(srcSize, srcFormat);
  srcFb.set_color_attachment(0u, srcTex);

  framebuffer::bind(srcFb);
  gl::set_clear_color(colorRef.get_red_f(), colorRef.get_green_f(),
    colorRef.get_blue_f(), colorRef.get_alpha_f());
  gl::clear(GL_COLOR_BUFFER_BIT);
  framebuffer::unbind();

  framebuffer dstFb;
  DstTexType dstTex(dstSize, dstFormat);
  dstFb.set_color_attachment(0u, dstTex);

  if(testError)
  {
    HOU_EXPECT_PRECONDITION(
      blit(srcFb, srcRect, dstFb, dstRect, framebuffer_blit_mask::color, filter));
  }
  else
  {
    // Blit.
    blit(srcFb, srcRect, dstFb, dstRect, framebuffer_blit_mask::color, filter);

    // Create the reference ph_image (the rectangles can assume negative values, so
    // pay attention to that).
    image imageRef(dstSize);
    image::size_type subImageSize;

    int left = std::min(dstRect.l(), dstRect.r());
    int right = std::max(dstRect.l(), dstRect.r());
    int top = std::min(dstRect.t(), dstRect.b());
    int bottom = std::max(dstRect.t(), dstRect.b());
    subImageSize.x() = static_cast<int>(dstSize.x()) >= right
      ? std::abs(dstRect.w())
      : static_cast<int>(dstSize.x()) - left;
    subImageSize.y() = static_cast<int>(dstSize.y()) >= bottom
      ? std::abs(dstRect.h())
      : static_cast<int>(dstSize.y()) - top;
    imageRef.set_sub_image(vec2i(left, top), image(subImageSize, pixelRef));

    // Adjust channels in case the destination format is not rgba.
    DstTexType textureRef(imageRef, dstFormat);
    imageRef = textureRef.template get_image<pixel_format::rgba>();

    // Check if the blit was executed as expected
    EXPECT_EQ(imageRef, dstTex.template get_image<pixel_format::rgba>());
  }
}

}  // namespace



TEST_F(TestFrameBuffer, Binding)
{
  framebuffer fb1;
  Texture2 tex1(vec2u(4u, 8u), TextureFormat::rgba);
  fb1.set_color_attachment(0u, tex1);
  EXPECT_TRUE(fb1.is_complete());

  framebuffer fb2;
  Texture2 tex2(vec2u(4u, 8u), TextureFormat::rgba);
  fb2.set_color_attachment(0u, tex2);
  EXPECT_TRUE(fb2.is_complete());

  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());

  framebuffer::bind(fb1);
  EXPECT_TRUE(fb1.is_bound_to_draw_target());
  EXPECT_TRUE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());

  framebuffer::bind(fb2);
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_TRUE(fb2.is_bound_to_draw_target());
  EXPECT_TRUE(fb2.is_bound_to_read_target());

  framebuffer::unbind();
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());
}



TEST_F(TestFrameBuffer, SpecificBinding)
{
  framebuffer fb1;
  Texture2 tex1(vec2u(4u, 8u), TextureFormat::rgba);
  fb1.set_color_attachment(0u, tex1);
  EXPECT_TRUE(fb1.is_complete());

  framebuffer fb2;
  Texture2 tex2(vec2u(4u, 8u), TextureFormat::rgba);
  fb2.set_color_attachment(0u, tex2);
  EXPECT_TRUE(fb2.is_complete());

  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());

  framebuffer::bind_draw_target(fb1);
  EXPECT_TRUE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());

  framebuffer::bind_read_target(fb2);
  EXPECT_TRUE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_TRUE(fb2.is_bound_to_read_target());

  framebuffer::bind_draw_target(fb2);
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_TRUE(fb2.is_bound_to_draw_target());
  EXPECT_TRUE(fb2.is_bound_to_read_target());

  framebuffer::unbind_draw_target();
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_TRUE(fb2.is_bound_to_read_target());

  framebuffer::unbind_read_target();
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());
}



TEST_F(TestFrameBufferDeathTest, BindingErrorIncompleteFrameBuffer)
{
  framebuffer fb;
  HOU_EXPECT_PRECONDITION(framebuffer::bind(fb));
  HOU_EXPECT_PRECONDITION(framebuffer::bind_draw_target(fb));
  HOU_EXPECT_PRECONDITION(framebuffer::bind_read_target(fb));
}



TEST_F(TestFrameBuffer, DefaultConstructor)
{
  framebuffer fb;

  EXPECT_NE(0u, fb.get_handle().get_name());
  EXPECT_FALSE(fb.is_bound_to_draw_target());
  EXPECT_FALSE(fb.is_bound_to_read_target());
  EXPECT_FALSE(fb.is_complete());
}



TEST_F(TestFrameBuffer, MoveConstructor)
{
  framebuffer fbDummy;
  GLuint fbName = fbDummy.get_handle().get_name();
  framebuffer fb(std::move(fbDummy));

  EXPECT_EQ(0u, fbDummy.get_handle().get_name());
  EXPECT_EQ(fbName, fb.get_handle().get_name());
  EXPECT_FALSE(fb.is_bound_to_draw_target());
  EXPECT_FALSE(fb.is_bound_to_read_target());
  EXPECT_FALSE(fb.is_complete());
}



TEST_F(TestFrameBuffer, SetColorAttachment)
{
  framebuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, 2u);

  fb.set_color_attachment(0u, tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetColorAttachmentAttachmentPointLimit)
{
  framebuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, 2u);

  fb.set_color_attachment(framebuffer::get_color_attachment_point_count() - 1u, tex);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetColorAttachmentErrorInvalidAttachmentPoint)
{
  framebuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, 2u);
  HOU_EXPECT_PRECONDITION(
    fb.set_color_attachment(framebuffer::get_color_attachment_point_count(), tex));
}



TEST_F(TestFrameBuffer, SetColorAttachmentMipMapLevelLimit)
{
  framebuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, mipMapLevelCount);

  for(uint i = 0; i < mipMapLevelCount; ++i)
  {
    fb.set_color_attachment(0u, tex, i);
  }

  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetColorAttachmentErrorInvalidMipMapLevel)
{
  framebuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.set_color_attachment(0u, tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetColorAttachmentValidFormats)
{
  framebuffer fb;
  Texture2 texR(vec2u(4u, 8u), TextureFormat::r);
  Texture2 texRG(vec2u(4u, 8u), TextureFormat::rg);
  Texture2 texRGB(vec2u(4u, 8u), TextureFormat::rgb);
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  fb.set_color_attachment(0u, texR);
  fb.set_color_attachment(0u, texRG);
  fb.set_color_attachment(0u, texRGB);
  fb.set_color_attachment(0u, texRGBA);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetColorAttachmentInvalidFormats)
{
  framebuffer fb;
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::depth);
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::stencil);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);
  HOU_EXPECT_PRECONDITION(fb.set_color_attachment(0u, texDepth));
  HOU_EXPECT_PRECONDITION(fb.set_color_attachment(0u, texStencil));
  HOU_EXPECT_PRECONDITION(fb.set_color_attachment(0u, texDepthStencil));
}



TEST_F(TestFrameBuffer, SetDepthAttachment)
{
  framebuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::depth, 2u);

  fb.set_depth_attachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetDepthAttachmentMipMapLevelLimit)
{
  framebuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::depth, mipMapLevelCount);

  for(uint i = 0; i < mipMapLevelCount; ++i)
  {
    fb.set_depth_attachment(tex, i);
  }

  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetDepthAttachmentErrorInvalidMipMapLevel)
{
  framebuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::depth, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.set_depth_attachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetDepthAttachmentValidFormats)
{
  framebuffer fb;
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::depth);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.set_depth_attachment(texDepth);
  fb.set_depth_attachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetDepthAttachmentInvalidFormats)
{
  framebuffer fb;
  Texture2 texR(vec2u(4u, 8u), TextureFormat::r);
  Texture2 texRG(vec2u(4u, 8u), TextureFormat::rg);
  Texture2 texRGB(vec2u(4u, 8u), TextureFormat::rgb);
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::stencil);
  HOU_EXPECT_PRECONDITION(fb.set_depth_attachment(texR));
  HOU_EXPECT_PRECONDITION(fb.set_depth_attachment(texRG));
  HOU_EXPECT_PRECONDITION(fb.set_depth_attachment(texRGB));
  HOU_EXPECT_PRECONDITION(fb.set_depth_attachment(texRGBA));
  HOU_EXPECT_PRECONDITION(fb.set_depth_attachment(texStencil));
}



TEST_F(TestFrameBuffer, SetStencilAttachment)
{
  framebuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::stencil, 2u);

  fb.set_stencil_attachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetStencilAttachmentMipMapLevelLimit)
{
  framebuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::stencil, mipMapLevelCount);

  for(uint i = 0; i < mipMapLevelCount; ++i)
  {
    fb.set_stencil_attachment(tex, i);
  }

  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetStencilAttachmentErrorInvalidMipMapLevel)
{
  framebuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::stencil, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.set_stencil_attachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetStencilAttachmentValidFormats)
{
  framebuffer fb;
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::stencil);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.set_stencil_attachment(texStencil);
  fb.set_stencil_attachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetStencilAttachmentInvalidFormats)
{
  framebuffer fb;
  Texture2 texR(vec2u(4u, 8u), TextureFormat::r);
  Texture2 texRG(vec2u(4u, 8u), TextureFormat::rg);
  Texture2 texRGB(vec2u(4u, 8u), TextureFormat::rgb);
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::depth);
  HOU_EXPECT_PRECONDITION(fb.set_stencil_attachment(texR));
  HOU_EXPECT_PRECONDITION(fb.set_stencil_attachment(texRG));
  HOU_EXPECT_PRECONDITION(fb.set_stencil_attachment(texRGB));
  HOU_EXPECT_PRECONDITION(fb.set_stencil_attachment(texRGBA));
  HOU_EXPECT_PRECONDITION(fb.set_stencil_attachment(texDepth));
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachment)
{
  framebuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::DepthStencil, 2u);

  fb.set_depth_stencil_attachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachmentMipMapLevelLimit)
{
  framebuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::DepthStencil, mipMapLevelCount);

  for(uint i = 0; i < mipMapLevelCount; ++i)
  {
    fb.set_depth_stencil_attachment(tex, i);
  }

  SUCCEED();
}



TEST_F(
  TestFrameBufferDeathTest, SetDepthStencilAttachmentErrorInvalidMipMapLevel)
{
  framebuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::DepthStencil, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.set_depth_stencil_attachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachmentValidFormats)
{
  framebuffer fb;
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.set_depth_stencil_attachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetDepthStencilAttachmentInvalidFormats)
{
  framebuffer fb;
  Texture2 texR(vec2u(4u, 8u), TextureFormat::r);
  Texture2 texRG(vec2u(4u, 8u), TextureFormat::rg);
  Texture2 texRGB(vec2u(4u, 8u), TextureFormat::rgb);
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::depth);
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::stencil);
  HOU_EXPECT_PRECONDITION(fb.set_depth_stencil_attachment(texR));
  HOU_EXPECT_PRECONDITION(fb.set_depth_stencil_attachment(texRG));
  HOU_EXPECT_PRECONDITION(fb.set_depth_stencil_attachment(texRGB));
  HOU_EXPECT_PRECONDITION(fb.set_depth_stencil_attachment(texRGBA));
  HOU_EXPECT_PRECONDITION(fb.set_depth_stencil_attachment(texDepth));
  HOU_EXPECT_PRECONDITION(fb.set_depth_stencil_attachment(texStencil));
}



TEST_F(TestFrameBuffer, StatusColorAttachment)
{
  framebuffer fb;
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);

  fb.set_color_attachment(0u, texRGBA);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(TestFrameBuffer, StatusDepthAttachment)
{
  framebuffer fb;
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::depth);

  fb.set_depth_attachment(texDepth);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(TestFrameBuffer, StatusStencilAttachment)
{
  framebuffer fb;
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::stencil);

  fb.set_stencil_attachment(texStencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(TestFrameBuffer, StatusDepthStencilAttachment)
{
  framebuffer fb;
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.set_depth_stencil_attachment(texDepthStencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(TestFrameBuffer, StatusColorDepthStencilAttachment)
{
  framebuffer fb;
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.set_color_attachment(0u, texRGBA);
  fb.set_depth_stencil_attachment(texDepthStencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(TestFrameBuffer, StatusColorDepthAndStencilAttachment)
{
  framebuffer fb;
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::depth);
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::stencil);

  fb.set_color_attachment(0u, texRGBA);
  fb.set_depth_attachment(texDepth);
  fb.set_stencil_attachment(texStencil);
  EXPECT_FALSE(fb.is_complete());
}



TEST_F(TestFrameBuffer, StatusMultisampledColorDepthStencilAttachment)
{
  framebuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba, sampleCount);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.set_color_attachment(0u, texRGBA);
  fb.set_depth_stencil_attachment(texDepthStencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(
  TestFrameBuffer, StatusMultisampledColorMultisampledDepthStencilAttachment)
{
  framebuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba, sampleCount);
  MultisampleTexture2 texDepthStencil(
    vec2u(4u, 8u), TextureFormat::DepthStencil, sampleCount);

  fb.set_color_attachment(0u, texRGBA);
  fb.set_depth_stencil_attachment(texDepthStencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(TestFrameBuffer,
  StatusMultisampledColorMultisampledDepthStencilAttachmentDifferentSamples)
{
  framebuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba, sampleCount);
  MultisampleTexture2 texDepthStencil(
    vec2u(4u, 8u), TextureFormat::DepthStencil, 1u);

  fb.set_color_attachment(0u, texRGBA);
  fb.set_depth_stencil_attachment(texDepthStencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(TestFrameBuffer, HasMultisampleAttachment)
{
  vec2u size(4u, 8u);
  framebuffer fb;
  Texture2 texColorSS(size, TextureFormat::rgba);
  Texture2 texDSSS(size, TextureFormat::DepthStencil);
  MultisampleTexture2 texColorMS(size, TextureFormat::rgba);
  MultisampleTexture2 texDSMS(size, TextureFormat::DepthStencil);

  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.set_color_attachment(0u, texColorSS);
  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.set_depth_stencil_attachment(texDSSS);
  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.set_color_attachment(0u, texColorMS);
  EXPECT_TRUE(fb.hasMultisampleAttachment());
  fb.set_color_attachment(0u, texColorSS);
  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.set_depth_stencil_attachment(texDSMS);
  EXPECT_TRUE(fb.hasMultisampleAttachment());
  fb.set_depth_stencil_attachment(texDSSS);
  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.set_color_attachment(0u, texColorMS);
  fb.set_depth_stencil_attachment(texDSMS);
  EXPECT_TRUE(fb.hasMultisampleAttachment());
}



TEST_F(TestFrameBuffer, BlitColorFullImage)
{
  vec2u size(4u, 8u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgba, size, recti(vec2u(), size),
    framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorSameRect)
{
  vec2u size(8u, 16u);
  recti rect(1u, 2u, 3u, 4u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size, rect,
    TextureFormat::rgba, size, rect, framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorDifferentTextureSizes)
{
  vec2u size1(4u, 8u);
  vec2u size2(8u, 16u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size1,
    recti(vec2u(), size1), TextureFormat::rgba, size2, recti(vec2u(), size1),
    framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorDifferentRects)
{
  vec2u size(8u, 16u);
  recti srcRect(1u, 2u, 3u, 4u);
  recti dstRect(2u, 1u, 4u, 6u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size, srcRect,
    TextureFormat::rgba, size, dstRect, framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorOverflowingRect)
{
  vec2u size(8u, 16u);
  recti rect(4u, 6u, 6u, 16u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size, rect,
    TextureFormat::rgba, size, rect, framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorInvertedRect)
{
  vec2u size(8u, 16u);
  recti srcRect(1u, 2u, 3u, 4u);
  recti dstRect(srcRect.r(), srcRect.b(), -srcRect.w(), -srcRect.h());
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size, srcRect,
    TextureFormat::rgba, size, dstRect, framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorLinearFilter)
{
  vec2u size(4u, 8u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgba, size, recti(vec2u(), size),
    framebuffer_blit_filter::linear);
}



TEST_F(TestFrameBuffer, BlitColorDifferentFormat)
{
  vec2u size(4u, 8u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgb, size, recti(vec2u(), size),
    framebuffer_blit_filter::linear);
}



TEST_F(TestFrameBuffer, BlitColorFullImageMultisample)
{
  vec2u size(4u, 8u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgba, size, recti(vec2u(), size),
    framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorSameRectMultisample)
{
  vec2u size(8u, 16u);
  recti rect(1u, 2u, 3u, 4u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size, rect,
    TextureFormat::rgba, size, rect, framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorDifferentTextureSizesMultisample)
{
  vec2u size1(4u, 8u);
  vec2u size2(8u, 16u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size1,
    recti(vec2u(), size1), TextureFormat::rgba, size2, recti(vec2u(), size1),
    framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorOverflowingRectMultisample)
{
  vec2u size(8u, 16u);
  recti rect(4u, 6u, 6u, 16u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size, rect,
    TextureFormat::rgba, size, rect, framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorInvertedRectMultisample)
{
  vec2u size(8u, 16u);
  recti srcRect(1u, 2u, 3u, 4u);
  recti dstRect(srcRect.r(), srcRect.b(), -srcRect.w(), -srcRect.h());
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size,
    srcRect, TextureFormat::rgba, size, dstRect,
    framebuffer_blit_filter::nearest);
}



TEST_F(TestFrameBuffer, BlitColorLinearFilterMultisample)
{
  vec2u size(4u, 8u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgba, size, recti(vec2u(), size),
    framebuffer_blit_filter::linear);
}



TEST_F(TestFrameBufferDeathTest, BlitErrorColorDifferentRectsMultisample)
{
  vec2u size(8u, 16u);
  recti srcRect(1u, 2u, 3u, 4u);
  recti dstRect(2u, 1u, 4u, 6u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size,
    srcRect, TextureFormat::rgba, size, dstRect, framebuffer_blit_filter::nearest,
    true);
}



TEST_F(TestFrameBufferDeathTest, BlitErrorIncompleteSourceBuffer)
{
  framebuffer src;
  framebuffer dst;
  Texture2 dstTex(vec2u(4u, 8u));
  dst.set_color_attachment(0u, dstTex);

  EXPECT_FALSE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::color, framebuffer_blit_filter::nearest));
}



TEST_F(TestFrameBufferDeathTest, BlitErrorIncompleteDestinationBuffer)
{
  framebuffer src;
  Texture2 srcTex(vec2u(4u, 8u));
  src.set_color_attachment(0u, srcTex);
  framebuffer dst;

  EXPECT_TRUE(src.is_complete());
  EXPECT_FALSE(dst.is_complete());
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::color, framebuffer_blit_filter::nearest));
}



TEST_F(TestFrameBuffer, BlitNoAttachmentSpecified)
{
  framebuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.set_color_attachment(0u, srcTexColor);
  src.set_depth_stencil_attachment(srcTexDS);

  framebuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.set_color_attachment(0u, dstTexColor);
  dst.set_depth_stencil_attachment(dstTexDS);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::none, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitSourceMissingColor)
{
  framebuffer src;
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.set_depth_stencil_attachment(srcTexDS);

  framebuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.set_color_attachment(0u, dstTexColor);
  dst.set_depth_stencil_attachment(dstTexDS);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::color, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitSourceMissingDepthStencil)
{
  framebuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  src.set_color_attachment(0u, srcTexColor);

  framebuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.set_color_attachment(0u, dstTexColor);
  dst.set_depth_stencil_attachment(dstTexDS);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::depth, framebuffer_blit_filter::nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::stencil, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitDestinationMissingColor)
{
  framebuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.set_color_attachment(0u, srcTexColor);
  src.set_depth_stencil_attachment(srcTexDS);

  framebuffer dst;
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.set_depth_stencil_attachment(dstTexDS);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::color, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitDestinationMissingDepthStencil)
{
  framebuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.set_color_attachment(0u, srcTexColor);
  src.set_depth_stencil_attachment(srcTexDS);

  framebuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  dst.set_color_attachment(0u, dstTexColor);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::depth, framebuffer_blit_filter::nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::stencil, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitMissingColor)
{
  framebuffer src;
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.set_depth_stencil_attachment(srcTexDS);

  framebuffer dst;
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.set_depth_stencil_attachment(dstTexDS);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::color, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitMissingDepthStencil)
{
  framebuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  src.set_color_attachment(0u, srcTexColor);

  framebuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  dst.set_color_attachment(0u, dstTexColor);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::depth, framebuffer_blit_filter::nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::stencil, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, BlitErrorLinearFilterWithDepthStencilMask)
{
  framebuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.set_color_attachment(0u, srcTexColor);
  src.set_depth_stencil_attachment(srcTexDS);

  framebuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.set_color_attachment(0u, dstTexColor);
  dst.set_depth_stencil_attachment(dstTexDS);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::depth, framebuffer_blit_filter::linear));
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::stencil, framebuffer_blit_filter::linear));
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::depth | framebuffer_blit_mask::stencil,
      framebuffer_blit_filter::linear));
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::all, framebuffer_blit_filter::linear));
}



TEST_F(TestFrameBuffer, BlitToTexture)
{
  vec2u sizeRef(4u, 8u);
  recti rectRef(vec2i::zero(), sizeRef);

  framebuffer src;
  Texture2 srcTex(sizeRef);
  srcTex.clear(pixelrgba(1u, 2u, 3u, 4u));
  src.set_color_attachment(0u, srcTex);

  Texture2 dstTex(sizeRef);

  blit(src, rectRef, dstTex, rectRef, framebuffer_blit_filter::linear);
  EXPECT_EQ(
    srcTex.get_image<pixel_format::rgba>(), dstTex.get_image<pixel_format::rgba>());
}



TEST_F(TestFrameBuffer, BlitFromTexture)
{
  vec2u sizeRef(4u, 8u);
  recti rectRef(vec2i::zero(), sizeRef);

  Texture2 srcTex(sizeRef);
  srcTex.clear(pixelrgba(1u, 2u, 3u, 4u));

  framebuffer dst;
  Texture2 dstTex(sizeRef);
  dst.set_color_attachment(0u, dstTex);

  blit(srcTex, rectRef, dst, rectRef, framebuffer_blit_filter::linear);
  EXPECT_EQ(
    srcTex.get_image<pixel_format::rgba>(), dstTex.get_image<pixel_format::rgba>());
}



TEST_F(TestFrameBuffer, BlitFromAndToTexture)
{
  vec2u sizeRef(4u, 8u);
  recti rectRef(vec2i::zero(), sizeRef);

  Texture2 srcTex(sizeRef);
  srcTex.clear(pixelrgba(1u, 2u, 3u, 4u));

  Texture2 dstTex(sizeRef);

  blit(srcTex, rectRef, dstTex, rectRef, framebuffer_blit_filter::linear);
  EXPECT_EQ(
    srcTex.get_image<pixel_format::rgba>(), dstTex.get_image<pixel_format::rgba>());
}
