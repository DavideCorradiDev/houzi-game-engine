// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/FrameBuffer.hpp"
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
  const recti& dstRect, FrameBufferBlitFilter filter, bool testError = false);

template <typename SrcTexType, typename DstTexType>
void testColorBlit(TextureFormat srcFormat,
  const typename SrcTexType::size_type& srcSize, const recti& srcRect,
  TextureFormat dstFormat, const typename DstTexType::size_type& dstSize,
  const recti& dstRect, FrameBufferBlitFilter filter, bool testError)
{
  using image = image2RGBA;
  using pixel = pixelrgba;

  // Build the framebuffers.
  color colorRef(2u, 3u, 5u, 7u);
  pixel pixelRef(colorRef);

  FrameBuffer srcFb;
  SrcTexType srcTex(srcSize, srcFormat);
  srcFb.setColorAttachment(0u, srcTex);

  FrameBuffer::bind(srcFb);
  gl::setClearColor(colorRef.get_red_f(), colorRef.get_green_f(),
    colorRef.get_blue_f(), colorRef.get_alpha_f());
  gl::clear(GL_COLOR_BUFFER_BIT);
  FrameBuffer::unbind();

  FrameBuffer dstFb;
  DstTexType dstTex(dstSize, dstFormat);
  dstFb.setColorAttachment(0u, dstTex);

  if(testError)
  {
    HOU_EXPECT_PRECONDITION(
      blit(srcFb, srcRect, dstFb, dstRect, FrameBufferBlitMask::color, filter));
  }
  else
  {
    // Blit.
    blit(srcFb, srcRect, dstFb, dstRect, FrameBufferBlitMask::color, filter);

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
  FrameBuffer fb1;
  Texture2 tex1(vec2u(4u, 8u), TextureFormat::rgba);
  fb1.setColorAttachment(0u, tex1);
  EXPECT_TRUE(fb1.isComplete());

  FrameBuffer fb2;
  Texture2 tex2(vec2u(4u, 8u), TextureFormat::rgba);
  fb2.setColorAttachment(0u, tex2);
  EXPECT_TRUE(fb2.isComplete());

  EXPECT_FALSE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_FALSE(fb2.isBoundToDrawTarget());
  EXPECT_FALSE(fb2.isBoundToReadTarget());

  FrameBuffer::bind(fb1);
  EXPECT_TRUE(fb1.isBoundToDrawTarget());
  EXPECT_TRUE(fb1.isBoundToReadTarget());
  EXPECT_FALSE(fb2.isBoundToDrawTarget());
  EXPECT_FALSE(fb2.isBoundToReadTarget());

  FrameBuffer::bind(fb2);
  EXPECT_FALSE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_TRUE(fb2.isBoundToDrawTarget());
  EXPECT_TRUE(fb2.isBoundToReadTarget());

  FrameBuffer::unbind();
  EXPECT_FALSE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_FALSE(fb2.isBoundToDrawTarget());
  EXPECT_FALSE(fb2.isBoundToReadTarget());
}



TEST_F(TestFrameBuffer, SpecificBinding)
{
  FrameBuffer fb1;
  Texture2 tex1(vec2u(4u, 8u), TextureFormat::rgba);
  fb1.setColorAttachment(0u, tex1);
  EXPECT_TRUE(fb1.isComplete());

  FrameBuffer fb2;
  Texture2 tex2(vec2u(4u, 8u), TextureFormat::rgba);
  fb2.setColorAttachment(0u, tex2);
  EXPECT_TRUE(fb2.isComplete());

  EXPECT_FALSE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_FALSE(fb2.isBoundToDrawTarget());
  EXPECT_FALSE(fb2.isBoundToReadTarget());

  FrameBuffer::bindDrawTarget(fb1);
  EXPECT_TRUE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_FALSE(fb2.isBoundToDrawTarget());
  EXPECT_FALSE(fb2.isBoundToReadTarget());

  FrameBuffer::bindReadTarget(fb2);
  EXPECT_TRUE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_FALSE(fb2.isBoundToDrawTarget());
  EXPECT_TRUE(fb2.isBoundToReadTarget());

  FrameBuffer::bindDrawTarget(fb2);
  EXPECT_FALSE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_TRUE(fb2.isBoundToDrawTarget());
  EXPECT_TRUE(fb2.isBoundToReadTarget());

  FrameBuffer::unbindDrawTarget();
  EXPECT_FALSE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_FALSE(fb2.isBoundToDrawTarget());
  EXPECT_TRUE(fb2.isBoundToReadTarget());

  FrameBuffer::unbindReadTarget();
  EXPECT_FALSE(fb1.isBoundToDrawTarget());
  EXPECT_FALSE(fb1.isBoundToReadTarget());
  EXPECT_FALSE(fb2.isBoundToDrawTarget());
  EXPECT_FALSE(fb2.isBoundToReadTarget());
}



TEST_F(TestFrameBufferDeathTest, BindingErrorIncompleteFrameBuffer)
{
  FrameBuffer fb;
  HOU_EXPECT_PRECONDITION(FrameBuffer::bind(fb));
  HOU_EXPECT_PRECONDITION(FrameBuffer::bindDrawTarget(fb));
  HOU_EXPECT_PRECONDITION(FrameBuffer::bindReadTarget(fb));
}



TEST_F(TestFrameBuffer, DefaultConstructor)
{
  FrameBuffer fb;

  EXPECT_NE(0u, fb.getHandle().getName());
  EXPECT_FALSE(fb.isBoundToDrawTarget());
  EXPECT_FALSE(fb.isBoundToReadTarget());
  EXPECT_FALSE(fb.isComplete());
}



TEST_F(TestFrameBuffer, MoveConstructor)
{
  FrameBuffer fbDummy;
  GLuint fbName = fbDummy.getHandle().getName();
  FrameBuffer fb(std::move(fbDummy));

  EXPECT_EQ(0u, fbDummy.getHandle().getName());
  EXPECT_EQ(fbName, fb.getHandle().getName());
  EXPECT_FALSE(fb.isBoundToDrawTarget());
  EXPECT_FALSE(fb.isBoundToReadTarget());
  EXPECT_FALSE(fb.isComplete());
}



TEST_F(TestFrameBuffer, SetColorAttachment)
{
  FrameBuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, 2u);

  fb.setColorAttachment(0u, tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetColorAttachmentAttachmentPointLimit)
{
  FrameBuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, 2u);

  fb.setColorAttachment(FrameBuffer::getColorAttachmentPointCount() - 1u, tex);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetColorAttachmentErrorInvalidAttachmentPoint)
{
  FrameBuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, 2u);
  HOU_EXPECT_PRECONDITION(
    fb.setColorAttachment(FrameBuffer::getColorAttachmentPointCount(), tex));
}



TEST_F(TestFrameBuffer, SetColorAttachmentMipMapLevelLimit)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, mipMapLevelCount);

  for(uint i = 0; i < mipMapLevelCount; ++i)
  {
    fb.setColorAttachment(0u, tex, i);
  }

  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetColorAttachmentErrorInvalidMipMapLevel)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::rgba, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.setColorAttachment(0u, tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetColorAttachmentValidFormats)
{
  FrameBuffer fb;
  Texture2 texR(vec2u(4u, 8u), TextureFormat::r);
  Texture2 texRG(vec2u(4u, 8u), TextureFormat::rg);
  Texture2 texRGB(vec2u(4u, 8u), TextureFormat::rgb);
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  fb.setColorAttachment(0u, texR);
  fb.setColorAttachment(0u, texRG);
  fb.setColorAttachment(0u, texRGB);
  fb.setColorAttachment(0u, texRGBA);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetColorAttachmentInvalidFormats)
{
  FrameBuffer fb;
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::Depth);
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::Stencil);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);
  HOU_EXPECT_PRECONDITION(fb.setColorAttachment(0u, texDepth));
  HOU_EXPECT_PRECONDITION(fb.setColorAttachment(0u, texStencil));
  HOU_EXPECT_PRECONDITION(fb.setColorAttachment(0u, texDepthStencil));
}



TEST_F(TestFrameBuffer, SetDepthAttachment)
{
  FrameBuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::Depth, 2u);

  fb.setDepthAttachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetDepthAttachmentMipMapLevelLimit)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::Depth, mipMapLevelCount);

  for(uint i = 0; i < mipMapLevelCount; ++i)
  {
    fb.setDepthAttachment(tex, i);
  }

  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetDepthAttachmentErrorInvalidMipMapLevel)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::Depth, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetDepthAttachmentValidFormats)
{
  FrameBuffer fb;
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::Depth);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.setDepthAttachment(texDepth);
  fb.setDepthAttachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetDepthAttachmentInvalidFormats)
{
  FrameBuffer fb;
  Texture2 texR(vec2u(4u, 8u), TextureFormat::r);
  Texture2 texRG(vec2u(4u, 8u), TextureFormat::rg);
  Texture2 texRGB(vec2u(4u, 8u), TextureFormat::rgb);
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::Stencil);
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texR));
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texRG));
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texRGB));
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texRGBA));
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texStencil));
}



TEST_F(TestFrameBuffer, SetStencilAttachment)
{
  FrameBuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::Stencil, 2u);

  fb.setStencilAttachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetStencilAttachmentMipMapLevelLimit)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::Stencil, mipMapLevelCount);

  for(uint i = 0; i < mipMapLevelCount; ++i)
  {
    fb.setStencilAttachment(tex, i);
  }

  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetStencilAttachmentErrorInvalidMipMapLevel)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::Stencil, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetStencilAttachmentValidFormats)
{
  FrameBuffer fb;
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::Stencil);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.setStencilAttachment(texStencil);
  fb.setStencilAttachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetStencilAttachmentInvalidFormats)
{
  FrameBuffer fb;
  Texture2 texR(vec2u(4u, 8u), TextureFormat::r);
  Texture2 texRG(vec2u(4u, 8u), TextureFormat::rg);
  Texture2 texRGB(vec2u(4u, 8u), TextureFormat::rgb);
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::Depth);
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texR));
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texRG));
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texRGB));
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texRGBA));
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texDepth));
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachment)
{
  FrameBuffer fb;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::DepthStencil, 2u);

  fb.setDepthStencilAttachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachmentMipMapLevelLimit)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::DepthStencil, mipMapLevelCount);

  for(uint i = 0; i < mipMapLevelCount; ++i)
  {
    fb.setDepthStencilAttachment(tex, i);
  }

  SUCCEED();
}



TEST_F(
  TestFrameBufferDeathTest, SetDepthStencilAttachmentErrorInvalidMipMapLevel)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(vec2u(4u, 8u), TextureFormat::DepthStencil, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.setDepthStencilAttachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachmentValidFormats)
{
  FrameBuffer fb;
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.setDepthStencilAttachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetDepthStencilAttachmentInvalidFormats)
{
  FrameBuffer fb;
  Texture2 texR(vec2u(4u, 8u), TextureFormat::r);
  Texture2 texRG(vec2u(4u, 8u), TextureFormat::rg);
  Texture2 texRGB(vec2u(4u, 8u), TextureFormat::rgb);
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::Depth);
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::Stencil);
  HOU_EXPECT_PRECONDITION(fb.setDepthStencilAttachment(texR));
  HOU_EXPECT_PRECONDITION(fb.setDepthStencilAttachment(texRG));
  HOU_EXPECT_PRECONDITION(fb.setDepthStencilAttachment(texRGB));
  HOU_EXPECT_PRECONDITION(fb.setDepthStencilAttachment(texRGBA));
  HOU_EXPECT_PRECONDITION(fb.setDepthStencilAttachment(texDepth));
  HOU_EXPECT_PRECONDITION(fb.setDepthStencilAttachment(texStencil));
}



TEST_F(TestFrameBuffer, StatusColorAttachment)
{
  FrameBuffer fb;
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);

  fb.setColorAttachment(0u, texRGBA);
  EXPECT_TRUE(fb.isComplete());
}



TEST_F(TestFrameBuffer, StatusDepthAttachment)
{
  FrameBuffer fb;
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::Depth);

  fb.setDepthAttachment(texDepth);
  EXPECT_TRUE(fb.isComplete());
}



TEST_F(TestFrameBuffer, StatusStencilAttachment)
{
  FrameBuffer fb;
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::Stencil);

  fb.setStencilAttachment(texStencil);
  EXPECT_TRUE(fb.isComplete());
}



TEST_F(TestFrameBuffer, StatusDepthStencilAttachment)
{
  FrameBuffer fb;
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_TRUE(fb.isComplete());
}



TEST_F(TestFrameBuffer, StatusColorDepthStencilAttachment)
{
  FrameBuffer fb;
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_TRUE(fb.isComplete());
}



TEST_F(TestFrameBuffer, StatusColorDepthAndStencilAttachment)
{
  FrameBuffer fb;
  Texture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba);
  Texture2 texDepth(vec2u(4u, 8u), TextureFormat::Depth);
  Texture2 texStencil(vec2u(4u, 8u), TextureFormat::Stencil);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthAttachment(texDepth);
  fb.setStencilAttachment(texStencil);
  EXPECT_FALSE(fb.isComplete());
}



TEST_F(TestFrameBuffer, StatusMultisampledColorDepthStencilAttachment)
{
  FrameBuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba, sampleCount);
  Texture2 texDepthStencil(vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_TRUE(fb.isComplete());
}



TEST_F(
  TestFrameBuffer, StatusMultisampledColorMultisampledDepthStencilAttachment)
{
  FrameBuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba, sampleCount);
  MultisampleTexture2 texDepthStencil(
    vec2u(4u, 8u), TextureFormat::DepthStencil, sampleCount);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_TRUE(fb.isComplete());
}



TEST_F(TestFrameBuffer,
  StatusMultisampledColorMultisampledDepthStencilAttachmentDifferentSamples)
{
  FrameBuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(vec2u(4u, 8u), TextureFormat::rgba, sampleCount);
  MultisampleTexture2 texDepthStencil(
    vec2u(4u, 8u), TextureFormat::DepthStencil, 1u);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_TRUE(fb.isComplete());
}



TEST_F(TestFrameBuffer, HasMultisampleAttachment)
{
  vec2u size(4u, 8u);
  FrameBuffer fb;
  Texture2 texColorSS(size, TextureFormat::rgba);
  Texture2 texDSSS(size, TextureFormat::DepthStencil);
  MultisampleTexture2 texColorMS(size, TextureFormat::rgba);
  MultisampleTexture2 texDSMS(size, TextureFormat::DepthStencil);

  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.setColorAttachment(0u, texColorSS);
  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.setDepthStencilAttachment(texDSSS);
  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.setColorAttachment(0u, texColorMS);
  EXPECT_TRUE(fb.hasMultisampleAttachment());
  fb.setColorAttachment(0u, texColorSS);
  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.setDepthStencilAttachment(texDSMS);
  EXPECT_TRUE(fb.hasMultisampleAttachment());
  fb.setDepthStencilAttachment(texDSSS);
  EXPECT_FALSE(fb.hasMultisampleAttachment());
  fb.setColorAttachment(0u, texColorMS);
  fb.setDepthStencilAttachment(texDSMS);
  EXPECT_TRUE(fb.hasMultisampleAttachment());
}



TEST_F(TestFrameBuffer, BlitColorFullImage)
{
  vec2u size(4u, 8u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgba, size, recti(vec2u(), size),
    FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorSameRect)
{
  vec2u size(8u, 16u);
  recti rect(1u, 2u, 3u, 4u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size, rect,
    TextureFormat::rgba, size, rect, FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorDifferentTextureSizes)
{
  vec2u size1(4u, 8u);
  vec2u size2(8u, 16u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size1,
    recti(vec2u(), size1), TextureFormat::rgba, size2, recti(vec2u(), size1),
    FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorDifferentRects)
{
  vec2u size(8u, 16u);
  recti srcRect(1u, 2u, 3u, 4u);
  recti dstRect(2u, 1u, 4u, 6u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size, srcRect,
    TextureFormat::rgba, size, dstRect, FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorOverflowingRect)
{
  vec2u size(8u, 16u);
  recti rect(4u, 6u, 6u, 16u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size, rect,
    TextureFormat::rgba, size, rect, FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorInvertedRect)
{
  vec2u size(8u, 16u);
  recti srcRect(1u, 2u, 3u, 4u);
  recti dstRect(srcRect.r(), srcRect.b(), -srcRect.w(), -srcRect.h());
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size, srcRect,
    TextureFormat::rgba, size, dstRect, FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorLinearFilter)
{
  vec2u size(4u, 8u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgba, size, recti(vec2u(), size),
    FrameBufferBlitFilter::Linear);
}



TEST_F(TestFrameBuffer, BlitColorDifferentFormat)
{
  vec2u size(4u, 8u);
  testColorBlit<Texture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgb, size, recti(vec2u(), size),
    FrameBufferBlitFilter::Linear);
}



TEST_F(TestFrameBuffer, BlitColorFullImageMultisample)
{
  vec2u size(4u, 8u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgba, size, recti(vec2u(), size),
    FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorSameRectMultisample)
{
  vec2u size(8u, 16u);
  recti rect(1u, 2u, 3u, 4u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size, rect,
    TextureFormat::rgba, size, rect, FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorDifferentTextureSizesMultisample)
{
  vec2u size1(4u, 8u);
  vec2u size2(8u, 16u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size1,
    recti(vec2u(), size1), TextureFormat::rgba, size2, recti(vec2u(), size1),
    FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorOverflowingRectMultisample)
{
  vec2u size(8u, 16u);
  recti rect(4u, 6u, 6u, 16u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size, rect,
    TextureFormat::rgba, size, rect, FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorInvertedRectMultisample)
{
  vec2u size(8u, 16u);
  recti srcRect(1u, 2u, 3u, 4u);
  recti dstRect(srcRect.r(), srcRect.b(), -srcRect.w(), -srcRect.h());
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size,
    srcRect, TextureFormat::rgba, size, dstRect,
    FrameBufferBlitFilter::Nearest);
}



TEST_F(TestFrameBuffer, BlitColorLinearFilterMultisample)
{
  vec2u size(4u, 8u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size,
    recti(vec2u(), size), TextureFormat::rgba, size, recti(vec2u(), size),
    FrameBufferBlitFilter::Linear);
}



TEST_F(TestFrameBufferDeathTest, BlitErrorColorDifferentRectsMultisample)
{
  vec2u size(8u, 16u);
  recti srcRect(1u, 2u, 3u, 4u);
  recti dstRect(2u, 1u, 4u, 6u);
  testColorBlit<MultisampleTexture2, Texture2>(TextureFormat::rgba, size,
    srcRect, TextureFormat::rgba, size, dstRect, FrameBufferBlitFilter::Nearest,
    true);
}



TEST_F(TestFrameBufferDeathTest, BlitErrorIncompleteSourceBuffer)
{
  FrameBuffer src;
  FrameBuffer dst;
  Texture2 dstTex(vec2u(4u, 8u));
  dst.setColorAttachment(0u, dstTex);

  EXPECT_FALSE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      FrameBufferBlitMask::color, FrameBufferBlitFilter::Nearest));
}



TEST_F(TestFrameBufferDeathTest, BlitErrorIncompleteDestinationBuffer)
{
  FrameBuffer src;
  Texture2 srcTex(vec2u(4u, 8u));
  src.setColorAttachment(0u, srcTex);
  FrameBuffer dst;

  EXPECT_TRUE(src.isComplete());
  EXPECT_FALSE(dst.isComplete());
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      FrameBufferBlitMask::color, FrameBufferBlitFilter::Nearest));
}



TEST_F(TestFrameBuffer, BlitNoAttachmentSpecified)
{
  FrameBuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.setColorAttachment(0u, srcTexColor);
  src.setDepthStencilAttachment(srcTexDS);

  FrameBuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.setColorAttachment(0u, dstTexColor);
  dst.setDepthStencilAttachment(dstTexDS);

  EXPECT_TRUE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::none, FrameBufferBlitFilter::Nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitSourceMissingColor)
{
  FrameBuffer src;
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.setDepthStencilAttachment(srcTexDS);

  FrameBuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.setColorAttachment(0u, dstTexColor);
  dst.setDepthStencilAttachment(dstTexDS);

  EXPECT_TRUE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::color, FrameBufferBlitFilter::Nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitSourceMissingDepthStencil)
{
  FrameBuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  src.setColorAttachment(0u, srcTexColor);

  FrameBuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.setColorAttachment(0u, dstTexColor);
  dst.setDepthStencilAttachment(dstTexDS);

  EXPECT_TRUE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::Depth, FrameBufferBlitFilter::Nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::Stencil, FrameBufferBlitFilter::Nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitDestinationMissingColor)
{
  FrameBuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.setColorAttachment(0u, srcTexColor);
  src.setDepthStencilAttachment(srcTexDS);

  FrameBuffer dst;
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.setDepthStencilAttachment(dstTexDS);

  EXPECT_TRUE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::color, FrameBufferBlitFilter::Nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitDestinationMissingDepthStencil)
{
  FrameBuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.setColorAttachment(0u, srcTexColor);
  src.setDepthStencilAttachment(srcTexDS);

  FrameBuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  dst.setColorAttachment(0u, dstTexColor);

  EXPECT_TRUE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::Depth, FrameBufferBlitFilter::Nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::Stencil, FrameBufferBlitFilter::Nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitMissingColor)
{
  FrameBuffer src;
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.setDepthStencilAttachment(srcTexDS);

  FrameBuffer dst;
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.setDepthStencilAttachment(dstTexDS);

  EXPECT_TRUE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::color, FrameBufferBlitFilter::Nearest);
  SUCCEED();
}



TEST_F(TestFrameBuffer, BlitMissingDepthStencil)
{
  FrameBuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  src.setColorAttachment(0u, srcTexColor);

  FrameBuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  dst.setColorAttachment(0u, dstTexColor);

  EXPECT_TRUE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::Depth, FrameBufferBlitFilter::Nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    FrameBufferBlitMask::Stencil, FrameBufferBlitFilter::Nearest);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, BlitErrorLinearFilterWithDepthStencilMask)
{
  FrameBuffer src;
  Texture2 srcTexColor(vec2u(4u, 8u));
  Texture2 srcTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  src.setColorAttachment(0u, srcTexColor);
  src.setDepthStencilAttachment(srcTexDS);

  FrameBuffer dst;
  Texture2 dstTexColor(vec2u(4u, 8u));
  Texture2 dstTexDS(vec2u(4u, 8u), TextureFormat::DepthStencil);
  dst.setColorAttachment(0u, dstTexColor);
  dst.setDepthStencilAttachment(dstTexDS);

  EXPECT_TRUE(src.isComplete());
  EXPECT_TRUE(dst.isComplete());

  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      FrameBufferBlitMask::Depth, FrameBufferBlitFilter::Linear));
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      FrameBufferBlitMask::Stencil, FrameBufferBlitFilter::Linear));
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      FrameBufferBlitMask::Depth | FrameBufferBlitMask::Stencil,
      FrameBufferBlitFilter::Linear));
  HOU_EXPECT_PRECONDITION(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      FrameBufferBlitMask::All, FrameBufferBlitFilter::Linear));
}



TEST_F(TestFrameBuffer, BlitToTexture)
{
  vec2u sizeRef(4u, 8u);
  recti rectRef(vec2i::zero(), sizeRef);

  FrameBuffer src;
  Texture2 srcTex(sizeRef);
  srcTex.clear(pixelrgba(1u, 2u, 3u, 4u));
  src.setColorAttachment(0u, srcTex);

  Texture2 dstTex(sizeRef);

  blit(src, rectRef, dstTex, rectRef, FrameBufferBlitFilter::Linear);
  EXPECT_EQ(
    srcTex.get_image<pixel_format::rgba>(), dstTex.get_image<pixel_format::rgba>());
}



TEST_F(TestFrameBuffer, BlitFromTexture)
{
  vec2u sizeRef(4u, 8u);
  recti rectRef(vec2i::zero(), sizeRef);

  Texture2 srcTex(sizeRef);
  srcTex.clear(pixelrgba(1u, 2u, 3u, 4u));

  FrameBuffer dst;
  Texture2 dstTex(sizeRef);
  dst.setColorAttachment(0u, dstTex);

  blit(srcTex, rectRef, dst, rectRef, FrameBufferBlitFilter::Linear);
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

  blit(srcTex, rectRef, dstTex, rectRef, FrameBufferBlitFilter::Linear);
  EXPECT_EQ(
    srcTex.get_image<pixel_format::rgba>(), dstTex.get_image<pixel_format::rgba>());
}
