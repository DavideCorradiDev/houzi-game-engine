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
  vec2u sizeRef(16u, 32u);
  vec2u screenSize = VideoMode::getDesktopMode().get_resolution();
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  WindowStyle styleRef = WindowStyle::Windowed;
  Image2RGBA iconRef;
  uint samplesRef = 1u;

  RenderWindow w(titleRef, sizeRef, styleRef, samplesRef);

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

  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.get_size());
  EXPECT_EQ(samplesRef, w.getSampleCount());
  EXPECT_FALSE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).getImage<PixelFormat::RGBA>(), w.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderWindow, CreationWindowedMultisampled)
{
  std::string titleRef(u8"Test");
  vec2u sizeRef(16u, 32u);
  vec2u screenSize = VideoMode::getDesktopMode().get_resolution();
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  WindowStyle styleRef = WindowStyle::Windowed;
  Image2RGBA iconRef;
  uint samplesRef = 4u;

  RenderWindow w(titleRef, sizeRef, styleRef, samplesRef);

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

  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.get_size());
  EXPECT_EQ(samplesRef, w.getSampleCount());
  EXPECT_TRUE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).getImage<PixelFormat::RGBA>(), w.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderWindow, CreationFullscreen)
{
  std::string titleRef(u8"Test");
  vec2u screenSize = VideoMode::getDesktopMode().get_resolution();
  vec2u sizeRef = screenSize;
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  WindowStyle styleRef = WindowStyle::Fullscreen;
  Image2RGBA iconRef;
  uint samplesRef = 1u;

  RenderWindow w(titleRef, sizeRef, styleRef, samplesRef);

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

  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.get_size());
  EXPECT_EQ(samplesRef, w.getSampleCount());
  EXPECT_FALSE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).getImage<PixelFormat::RGBA>(), w.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderWindow, SetClientRect)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2i posRef(2, 3);
  vec2u sizeRef(14u, 17u);
  w.setClientRect(posRef, sizeRef);

  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientRectNullSizeX)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef(0u, 17u);
  w.setClientRect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.x() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientRectNullSizeY)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef(13u, 0u);
  w.setClientRect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientRectNullSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef = vec2u::zero();
  w.setClientRect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.x() = 1u;
  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef(14u, 17u);
  w.setClientSize(sizeRef);

  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientSizeNullSizeX)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u),  WindowStyle::Windowed, 4u);

  vec2u sizeRef(0u, 17u);
  w.setClientSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.x() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientSizeNullSizeY)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef(13u, 0u);
  w.setClientSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientSizeNullSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef = vec2u::zero();
  w.setClientSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getClientSize());

  sizeRef.x() = 1u;
  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameRect)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2i posRef(12, 13);
  vec2u sizeRef(60u, 100u);
  w.setFrameRect(posRef, sizeRef);

  EXPECT_EQ(posRef, w.getFramePosition());
  EXPECT_EQ(sizeRef, w.getFrameSize());
  EXPECT_EQ(w.getClientSize(), w.get_size());
}



TEST_F(TestRenderWindow, SetFrameRectNullSizeX)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef(0u, 42u);
  w.setFrameRect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  vec2u texSizeRef = w.getClientSize();
  texSizeRef.x() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameRectNullSizeY)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef(42u, 0u);
  w.setFrameRect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  vec2u texSizeRef = w.getClientSize();
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameRectNullSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef = vec2u::zero();
  w.setFrameRect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  vec2u texSizeRef = w.getClientSize();
  texSizeRef.x() = 1u;
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  w.setFrameSize(vec2u(60u, 70u));

  EXPECT_EQ(w.getClientSize(), w.get_size());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSizeX)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef(0u, 42u);
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  vec2u texSizeRef = w.getClientSize();
  texSizeRef.x() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSizeY)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef(42u, 0u);
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  vec2u texSizeRef = w.getClientSize();
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);

  vec2u sizeRef = vec2u::zero();
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.getFrameSize());

  vec2u texSizeRef = w.getClientSize();
  texSizeRef.x() = 1u;
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetVerticalSyncMode)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 4u);
  w.setVerticalSyncMode(VerticalSyncMode::Enabled);
  w.setVerticalSyncMode(VerticalSyncMode::Disabled);
  SUCCEED();
}



TEST_F(TestRenderWindow, SetSamples)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 1u);

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
  RenderWindow w(u8"Test", vec2u(32u, 16u), WindowStyle::Windowed, 1u);
  HOU_EXPECT_PRECONDITION(
    w.setSampleCount(RenderWindow::getMaxSampleCount() + 1u));
}



TEST_F(TestRenderWindow, ResizeFrameBufferOnPopResizedEvent)
{
  vec2u oldSize(vec2u(32u, 16u));
  RenderWindow w(u8"Test", oldSize, WindowStyle::Windowed, 4u);
  vec2u newSize(vec2u(12u, 8u));

  WindowEvent ev = WindowEvent::resized(newSize.x(), newSize.y());
  w.pushEvent(ev);
  EXPECT_EQ(oldSize, w.getClientSize());
  EXPECT_EQ(oldSize, w.get_size());

  EXPECT_EQ(ev, w.popEvent());
  EXPECT_EQ(newSize, w.getClientSize());
  EXPECT_EQ(newSize, w.get_size());
}
