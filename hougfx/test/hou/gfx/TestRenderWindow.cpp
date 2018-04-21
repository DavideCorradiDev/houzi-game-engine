// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/VideoMode.hpp"
#include "hou/sys/WindowEvent.hpp"

using namespace hou;



namespace
{

class TestRenderWindow : public TestGfxBase {};

class TestRenderWindowDeathTest : public TestRenderWindow {};

}



TEST_F(TestRenderWindow, CreationWindowed)
{
  std::string titleRef(u8"Test");
  Vec2u sizeRef(16u, 32u);
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  WindowStyle styleRef = WindowStyle::Windowed;
  Image2RGBA iconRef;
  uint samplesRef = 0u;

  RenderWindow w(titleRef, sizeRef, samplesRef, styleRef);

  EXPECT_NE(0u, w.getUid());
  EXPECT_NE(nullptr, w.getWindowHandle());
  EXPECT_EQ(styleRef, w.getStyle());
  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(GraphicContext::getRenderingColorByteCount(), w.getBytesPerPixel());
  EXPECT_EQ(titleRef, w.getTitle());
  EXPECT_EQ(iconRef, w.getIcon());
  EXPECT_FALSE(w.isVisible());
  EXPECT_FALSE(w.isMouseCursorGrabbed());
  EXPECT_FALSE(w.isKeyRepeatEnabled());

  EXPECT_EQ(Recti(Vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.getSize());
  EXPECT_EQ(samplesRef, w.getSampleCount());
  EXPECT_FALSE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).getImage<PixelFormat::RGBA>(), w.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderWindow, CreationWindowedMultisampled)
{
  std::string titleRef(u8"Test");
  Vec2u sizeRef(16u, 32u);
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  WindowStyle styleRef = WindowStyle::Windowed;
  Image2RGBA iconRef;
  uint samplesRef = 4u;

  RenderWindow w(titleRef, sizeRef, samplesRef, styleRef);

  EXPECT_NE(0u, w.getUid());
  EXPECT_NE(nullptr, w.getWindowHandle());
  EXPECT_EQ(styleRef, w.getStyle());
  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(GraphicContext::getRenderingColorByteCount(), w.getBytesPerPixel());
  EXPECT_EQ(titleRef, w.getTitle());
  EXPECT_EQ(iconRef, w.getIcon());
  EXPECT_FALSE(w.isVisible());
  EXPECT_FALSE(w.isMouseCursorGrabbed());
  EXPECT_FALSE(w.isKeyRepeatEnabled());

  EXPECT_EQ(Recti(Vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.getSize());
  EXPECT_EQ(samplesRef, w.getSampleCount());
  EXPECT_TRUE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).getImage<PixelFormat::RGBA>(), w.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderWindow, CreationFullscreen)
{
  std::string titleRef(u8"Test");
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2u sizeRef = screenSize;
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  WindowStyle styleRef = WindowStyle::Fullscreen;
  Image2RGBA iconRef;
  uint samplesRef = 0u;

  RenderWindow w(titleRef, sizeRef, samplesRef, styleRef);

  EXPECT_NE(0u, w.getUid());
  EXPECT_NE(nullptr, w.getWindowHandle());
  EXPECT_EQ(styleRef, w.getStyle());
  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(GraphicContext::getRenderingColorByteCount(), w.getBytesPerPixel());
  EXPECT_EQ(titleRef, w.getTitle());
  EXPECT_EQ(iconRef, w.getIcon());
  EXPECT_FALSE(w.isVisible());
  EXPECT_FALSE(w.isMouseCursorGrabbed());
  EXPECT_FALSE(w.isKeyRepeatEnabled());

  EXPECT_EQ(Recti(Vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.getSize());
  EXPECT_EQ(samplesRef, w.getSampleCount());
  EXPECT_FALSE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).getImage<PixelFormat::RGBA>(), w.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderWindow, SetClientRect)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2i posRef(2, 3);
  Vec2u sizeRef(14u, 17u);
  w.setClientRect(posRef, sizeRef);

  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetClientRectNullSizeX)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(0u, 17u);
  w.setClientRect(Vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.x() = 1u;
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetClientRectNullSizeY)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(13u, 0u);
  w.setClientRect(Vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetClientRectNullSize)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef = Vec2u::zero();
  w.setClientRect(Vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.x() = 1u;
  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetClientSize)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(14u, 17u);
  w.setClientSize(sizeRef);

  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetClientSizeNullSizeX)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(0u, 17u);
  w.setClientSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.x() = 1u;
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetClientSizeNullSizeY)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(13u, 0u);
  w.setClientSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetClientSizeNullSize)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef = Vec2u::zero();
  w.setClientSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.x() = 1u;
  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetFrameRect)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2i posRef(12, 13);
  Vec2u sizeRef(60u, 100u);
  w.setFrameRect(posRef, sizeRef);

  EXPECT_EQ(posRef, w.getFramePosition());
  EXPECT_EQ(sizeRef, w.getFrameSize());
  EXPECT_EQ(w.getClientSize(), w.getSize());
}



TEST_F(TestRenderWindow, SetFrameRectNullSizeX)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(0u, 42u);
  w.setFrameRect(Vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  Vec2u texSizeRef = w.getClientSize();
  texSizeRef.x() = 1u;
  EXPECT_EQ(texSizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetFrameRectNullSizeY)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(42u, 0u);
  w.setFrameRect(Vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  Vec2u texSizeRef = w.getClientSize();
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetFrameRectNullSize)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef = Vec2u::zero();
  w.setFrameRect(Vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  Vec2u texSizeRef = w.getClientSize();
  texSizeRef.x() = 1u;
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetFrameSize)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  w.setFrameSize(Vec2u(60u, 70u));

  EXPECT_EQ(w.getClientSize(), w.getSize());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSizeX)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(0u, 42u);
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  Vec2u texSizeRef = w.getClientSize();
  texSizeRef.x() = 1u;
  EXPECT_EQ(texSizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSizeY)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(42u, 0u);
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  Vec2u texSizeRef = w.getClientSize();
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSize)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef = Vec2u::zero();
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  Vec2u texSizeRef = w.getClientSize();
  texSizeRef.x() = 1u;
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetVerticalSyncMode)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);
  w.setVerticalSyncMode(VerticalSyncMode::Enabled);
  w.setVerticalSyncMode(VerticalSyncMode::Disabled);
  SUCCEED();
}



TEST_F(TestRenderWindow, SetSamples)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 0u, WindowStyle::Windowed);

  w.setSampleCount(1u);
  EXPECT_EQ(1u, w.getSampleCount());
  EXPECT_FALSE(w.isMultisampled());

  w.setSampleCount(2u);
  EXPECT_EQ(2u, w.getSampleCount());
  EXPECT_TRUE(w.isMultisampled());

  w.setSampleCount(RenderWindow::getMaxSampleCount());
  EXPECT_EQ(RenderWindow::getMaxSampleCount(), w.getSampleCount());
  EXPECT_TRUE(w.isMultisampled());
}



TEST_F(TestRenderWindowDeathTest, SetSamplesTooLarge)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 0u, WindowStyle::Windowed);
  HOU_EXPECT_PRECONDITION(
    w.setSampleCount(RenderWindow::getMaxSampleCount() + 1u));
}



TEST_F(TestRenderWindow, ResizeFrameBufferOnPopResizedEvent)
{
  Vec2u oldSize(Vec2u(32u, 16u));
  RenderWindow w(u8"Test", oldSize, 4u, WindowStyle::Windowed);
  Vec2u newSize(Vec2u(12u, 8u));

  WindowEvent ev = WindowEvent::resized(newSize.x(), newSize.y());
  w.pushEvent(ev);
  EXPECT_EQ(oldSize, w.getClientSize());
  EXPECT_EQ(oldSize, w.getSize());

  EXPECT_EQ(ev, w.popEvent());
  EXPECT_EQ(newSize, w.getClientSize());
  EXPECT_EQ(newSize, w.getSize());
}
