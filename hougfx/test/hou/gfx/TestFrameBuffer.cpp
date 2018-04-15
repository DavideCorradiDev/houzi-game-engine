// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/FrameBuffer.hpp"
#include "hou/gfx/Texture.hpp"

using namespace hou;



namespace
{

class TestFrameBuffer : public TestGfxBase
{};

class TestFrameBufferDeathTest : public TestFrameBuffer
{};

}  // namespace



TEST_F(TestFrameBuffer, Binding)
{
  FrameBuffer fb1;
  Texture2 tex1(Vec2u(4u, 8u), TextureFormat::RGBA);
  fb1.setColorAttachment(0u, tex1);
  EXPECT_EQ(FrameBufferStatus::Complete, fb1.getStatus());

  FrameBuffer fb2;
  Texture2 tex2(Vec2u(4u, 8u), TextureFormat::RGBA);
  fb2.setColorAttachment(0u, tex2);
  EXPECT_EQ(FrameBufferStatus::Complete, fb2.getStatus());

  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::bind(fb1);
  EXPECT_TRUE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_TRUE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::bind(fb2);
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_TRUE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_TRUE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::unbind();
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, SpecificBinding)
{
  FrameBuffer fb1;
  Texture2 tex1(Vec2u(4u, 8u), TextureFormat::RGBA);
  fb1.setColorAttachment(0u, tex1);
  EXPECT_EQ(FrameBufferStatus::Complete, fb1.getStatus());

  FrameBuffer fb2;
  Texture2 tex2(Vec2u(4u, 8u), TextureFormat::RGBA);
  fb2.setColorAttachment(0u, tex2);
  EXPECT_EQ(FrameBufferStatus::Complete, fb2.getStatus());

  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::bind(fb1, FrameBufferTarget::Draw);
  EXPECT_TRUE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::bind(fb2, FrameBufferTarget::Read);
  EXPECT_TRUE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_TRUE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::bind(fb2, FrameBufferTarget::Draw);
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_TRUE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_TRUE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::unbind(FrameBufferTarget::Draw);
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_TRUE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::bind(fb1);
  EXPECT_TRUE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_TRUE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Read));

  FrameBuffer::unbind();
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb1.isBound(FrameBufferTarget::Read));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb2.isBound(FrameBufferTarget::Read));
}



TEST_F(TestFrameBufferDeathTest, BindingErrorIncompleteFrameBuffer)
{
  FrameBuffer fb;
  HOU_EXPECT_PRECONDITION(FrameBuffer::bind(fb));
  HOU_EXPECT_PRECONDITION(FrameBuffer::bind(fb, FrameBufferTarget::Draw));
  HOU_EXPECT_PRECONDITION(FrameBuffer::bind(fb, FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, DefaultConstructor)
{
  FrameBuffer fb;

  EXPECT_NE(0u, fb.getHandle().getName());
  EXPECT_FALSE(fb.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb.isBound(FrameBufferTarget::Read));
  EXPECT_EQ(FrameBufferStatus::IncompleteMissingAttachment, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::IncompleteMissingAttachment,
    fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::IncompleteMissingAttachment,
    fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, MoveConstructor)
{
  FrameBuffer fbDummy;
  GLuint fbName = fbDummy.getHandle().getName();
  FrameBuffer fb(std::move(fbDummy));

  EXPECT_EQ(0u, fbDummy.getHandle().getName());
  EXPECT_EQ(fbName, fb.getHandle().getName());
  EXPECT_FALSE(fb.isBound(FrameBufferTarget::Draw));
  EXPECT_FALSE(fb.isBound(FrameBufferTarget::Read));
  EXPECT_EQ(FrameBufferStatus::IncompleteMissingAttachment, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::IncompleteMissingAttachment,
    fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::IncompleteMissingAttachment,
    fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, SetColorAttachment)
{
  FrameBuffer fb;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::RGBA, 2u);

  fb.setColorAttachment(0u, tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetColorAttachmentAttachmentPointLimit)
{
  FrameBuffer fb;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::RGBA, 2u);

  fb.setColorAttachment(FrameBuffer::getColorAttachmentPointCount() - 1u, tex);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetColorAttachmentErrorInvalidAttachmentPoint)
{
  FrameBuffer fb;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::RGBA, 2u);
  HOU_EXPECT_PRECONDITION(
    fb.setColorAttachment(FrameBuffer::getColorAttachmentPointCount(), tex));
}



TEST_F(TestFrameBuffer, SetColorAttachmentMipMapLevelLimit)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::RGBA, mipMapLevelCount);

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
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::RGBA, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.setColorAttachment(0u, tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetColorAttachmentValidFormats)
{
  FrameBuffer fb;
  Texture2 texR(Vec2u(4u, 8u), TextureFormat::R);
  Texture2 texRG(Vec2u(4u, 8u), TextureFormat::RG);
  Texture2 texRGB(Vec2u(4u, 8u), TextureFormat::RGB);
  Texture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA);
  fb.setColorAttachment(0u, texR);
  fb.setColorAttachment(0u, texRG);
  fb.setColorAttachment(0u, texRGB);
  fb.setColorAttachment(0u, texRGBA);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetColorAttachmentInvalidFormats)
{
  FrameBuffer fb;
  Texture2 texDepth(Vec2u(4u, 8u), TextureFormat::Depth);
  Texture2 texStencil(Vec2u(4u, 8u), TextureFormat::Stencil);
  Texture2 texDepthStencil(Vec2u(4u, 8u), TextureFormat::DepthStencil);
  HOU_EXPECT_PRECONDITION(fb.setColorAttachment(0u, texDepth));
  HOU_EXPECT_PRECONDITION(fb.setColorAttachment(0u, texStencil));
  HOU_EXPECT_PRECONDITION(fb.setColorAttachment(0u, texDepthStencil));
}



TEST_F(TestFrameBuffer, SetDepthAttachment)
{
  FrameBuffer fb;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::Depth, 2u);

  fb.setDepthAttachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetDepthAttachmentMipMapLevelLimit)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::Depth, mipMapLevelCount);

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
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::Depth, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetDepthAttachmentValidFormats)
{
  FrameBuffer fb;
  Texture2 texDepth(Vec2u(4u, 8u), TextureFormat::Depth);
  Texture2 texDepthStencil(Vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.setDepthAttachment(texDepth);
  fb.setDepthAttachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetDepthAttachmentInvalidFormats)
{
  FrameBuffer fb;
  Texture2 texR(Vec2u(4u, 8u), TextureFormat::R);
  Texture2 texRG(Vec2u(4u, 8u), TextureFormat::RG);
  Texture2 texRGB(Vec2u(4u, 8u), TextureFormat::RGB);
  Texture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA);
  Texture2 texStencil(Vec2u(4u, 8u), TextureFormat::Stencil);
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texR));
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texRG));
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texRGB));
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texRGBA));
  HOU_EXPECT_PRECONDITION(fb.setDepthAttachment(texStencil));
}



TEST_F(TestFrameBuffer, SetStencilAttachment)
{
  FrameBuffer fb;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::Stencil, 2u);

  fb.setStencilAttachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetStencilAttachmentMipMapLevelLimit)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::Stencil, mipMapLevelCount);

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
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::Stencil, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetStencilAttachmentValidFormats)
{
  FrameBuffer fb;
  Texture2 texStencil(Vec2u(4u, 8u), TextureFormat::Stencil);
  Texture2 texDepthStencil(Vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.setStencilAttachment(texStencil);
  fb.setStencilAttachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetStencilAttachmentInvalidFormats)
{
  FrameBuffer fb;
  Texture2 texR(Vec2u(4u, 8u), TextureFormat::R);
  Texture2 texRG(Vec2u(4u, 8u), TextureFormat::RG);
  Texture2 texRGB(Vec2u(4u, 8u), TextureFormat::RGB);
  Texture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA);
  Texture2 texDepth(Vec2u(4u, 8u), TextureFormat::Depth);
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texR));
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texRG));
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texRGB));
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texRGBA));
  HOU_EXPECT_PRECONDITION(fb.setStencilAttachment(texDepth));
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachment)
{
  FrameBuffer fb;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::DepthStencil, 2u);

  fb.setDepthStencilAttachment(tex);

  SUCCEED();
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachmentMipMapLevelLimit)
{
  FrameBuffer fb;
  uint mipMapLevelCount = 3u;
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::DepthStencil, mipMapLevelCount);

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
  Texture2 tex(Vec2u(4u, 8u), TextureFormat::DepthStencil, mipMapLevelCount);
  HOU_EXPECT_PRECONDITION(fb.setDepthStencilAttachment(tex, mipMapLevelCount));
}



TEST_F(TestFrameBuffer, SetDepthStencilAttachmentValidFormats)
{
  FrameBuffer fb;
  Texture2 texDepthStencil(Vec2u(4u, 8u), TextureFormat::DepthStencil);
  fb.setDepthStencilAttachment(texDepthStencil);
  SUCCEED();
}



TEST_F(TestFrameBufferDeathTest, SetDepthStencilAttachmentInvalidFormats)
{
  FrameBuffer fb;
  Texture2 texR(Vec2u(4u, 8u), TextureFormat::R);
  Texture2 texRG(Vec2u(4u, 8u), TextureFormat::RG);
  Texture2 texRGB(Vec2u(4u, 8u), TextureFormat::RGB);
  Texture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA);
  Texture2 texDepth(Vec2u(4u, 8u), TextureFormat::Depth);
  Texture2 texStencil(Vec2u(4u, 8u), TextureFormat::Stencil);
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
  Texture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA);

  fb.setColorAttachment(0u, texRGBA);
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, StatusDepthAttachment)
{
  FrameBuffer fb;
  Texture2 texDepth(Vec2u(4u, 8u), TextureFormat::Depth);

  fb.setDepthAttachment(texDepth);
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, StatusStencilAttachment)
{
  FrameBuffer fb;
  Texture2 texStencil(Vec2u(4u, 8u), TextureFormat::Stencil);

  fb.setStencilAttachment(texStencil);
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, StatusDepthStencilAttachment)
{
  FrameBuffer fb;
  Texture2 texDepthStencil(Vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, StatusColorDepthStencilAttachment)
{
  FrameBuffer fb;
  Texture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA);
  Texture2 texDepthStencil(Vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, StatusColorDepthAndStencilAttachment)
{
  FrameBuffer fb;
  Texture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA);
  Texture2 texDepth(Vec2u(4u, 8u), TextureFormat::Depth);
  Texture2 texStencil(Vec2u(4u, 8u), TextureFormat::Stencil);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthAttachment(texDepth);
  fb.setStencilAttachment(texStencil);
  EXPECT_EQ(FrameBufferStatus::Unsupported, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Unsupported, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Unsupported, fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer, StatusMultisampledColorDepthStencilAttachment)
{
  FrameBuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA, sampleCount);
  Texture2 texDepthStencil(Vec2u(4u, 8u), TextureFormat::DepthStencil);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(
  TestFrameBuffer, StatusMultisampledColorMultisampledDepthStencilAttachment)
{
  FrameBuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA, sampleCount);
  MultisampleTexture2 texDepthStencil(
    Vec2u(4u, 8u), TextureFormat::DepthStencil, sampleCount);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Read));
}



TEST_F(TestFrameBuffer,
  StatusMultisampledColorMultisampledDepthStencilAttachmentDifferentSamples)
{
  FrameBuffer fb;
  uint sampleCount = 4u;
  MultisampleTexture2 texRGBA(Vec2u(4u, 8u), TextureFormat::RGBA, sampleCount);
  MultisampleTexture2 texDepthStencil(
    Vec2u(4u, 8u), TextureFormat::DepthStencil, 1u);

  fb.setColorAttachment(0u, texRGBA);
  fb.setDepthStencilAttachment(texDepthStencil);
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus());
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Draw));
  EXPECT_EQ(FrameBufferStatus::Complete, fb.getStatus(FrameBufferTarget::Read));
}
