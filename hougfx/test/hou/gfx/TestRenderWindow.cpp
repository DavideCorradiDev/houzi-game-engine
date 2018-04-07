// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/VideoMode.hpp"

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
  EXPECT_EQ(RenderContext::getRenderingColorBitCount(), w.getBitsPerPixel());
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
  EXPECT_EQ(RenderContext::getRenderingColorBitCount(), w.getBitsPerPixel());
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
  EXPECT_EQ(RenderContext::getRenderingColorBitCount(), w.getBitsPerPixel());
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



TEST_F(TestRenderWindow, SetSize)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(14u, 17u);
  w.setSize(sizeRef);

  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(sizeRef, w.getSize());
}



TEST_F(TestRenderWindow, SetClientRect)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  Vec2u sizeRef(14u, 17u);
  w.setClientRect(Recti(w.getClientPosition(), sizeRef));

  EXPECT_EQ(sizeRef, w.getClientSize());
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



TEST_F(TestRenderWindow, SetFrameRect)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  w.setFrameRect(Recti(w.getFramePosition(), Vec2u(60u, 70u)));

  EXPECT_EQ(w.getClientSize(), w.getSize());
}



TEST_F(TestRenderWindow, SetFrameSize)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);

  w.setFrameSize(Vec2u(60u, 70u));

  EXPECT_EQ(w.getClientSize(), w.getSize());
}



TEST_F(TestRenderWindow, SetVerticalSyncMode)
{
  RenderWindow w(u8"Test", Vec2u(32u, 16u), 4u, WindowStyle::Windowed);
  w.setVerticalSyncMode(VerticalSyncMode::Enabled);
  w.setVerticalSyncMode(VerticalSyncMode::Disabled);
  SUCCEED();
}

