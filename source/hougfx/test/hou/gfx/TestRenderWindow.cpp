// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/RenderWindow.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/video_mode.hpp"
#include "hou/sys/window_event.hpp"

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
  vec2u screenSize = video_mode::get_desktop_mode().get_resolution();
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  window_style styleRef = window_style::windowed;
  image2RGBA iconRef;
  uint samplesRef = 1u;

  RenderWindow w(titleRef, sizeRef, styleRef, samplesRef);

  EXPECT_NE(0u, w.get_uid());
  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_EQ(styleRef, w.get_style());
  EXPECT_EQ(posRef, w.get_client_position());
  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(graphic_context::get_rendering_color_byte_count(), w.get_bytes_per_pixel());
  EXPECT_EQ(titleRef, w.get_title());
  EXPECT_EQ(iconRef, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());

  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.get_size());
  EXPECT_EQ(samplesRef, w.get_sample_count());
  EXPECT_FALSE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).get_image<pixel_format::rgba>(), w.toTexture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderWindow, CreationWindowedMultisampled)
{
  std::string titleRef(u8"Test");
  vec2u sizeRef(16u, 32u);
  vec2u screenSize = video_mode::get_desktop_mode().get_resolution();
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  window_style styleRef = window_style::windowed;
  image2RGBA iconRef;
  uint samplesRef = 4u;

  RenderWindow w(titleRef, sizeRef, styleRef, samplesRef);

  EXPECT_NE(0u, w.get_uid());
  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_EQ(styleRef, w.get_style());
  EXPECT_EQ(posRef, w.get_client_position());
  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(graphic_context::get_rendering_color_byte_count(), w.get_bytes_per_pixel());
  EXPECT_EQ(titleRef, w.get_title());
  EXPECT_EQ(iconRef, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());

  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.get_size());
  EXPECT_EQ(samplesRef, w.get_sample_count());
  EXPECT_TRUE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).get_image<pixel_format::rgba>(), w.toTexture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderWindow, CreationFullscreen)
{
  std::string titleRef(u8"Test");
  vec2u screenSize = video_mode::get_desktop_mode().get_resolution();
  vec2u sizeRef = screenSize;
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  window_style styleRef = window_style::fullscreen;
  image2RGBA iconRef;
  uint samplesRef = 1u;

  RenderWindow w(titleRef, sizeRef, styleRef, samplesRef);

  EXPECT_NE(0u, w.get_uid());
  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_EQ(styleRef, w.get_style());
  EXPECT_EQ(posRef, w.get_client_position());
  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(graphic_context::get_rendering_color_byte_count(), w.get_bytes_per_pixel());
  EXPECT_EQ(titleRef, w.get_title());
  EXPECT_EQ(iconRef, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());

  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getDefaultViewport());
  EXPECT_EQ(recti(vec2i::zero(), sizeRef), w.getViewport());
  EXPECT_EQ(sizeRef, w.get_size());
  EXPECT_EQ(samplesRef, w.get_sample_count());
  EXPECT_FALSE(w.isMultisampled());
  EXPECT_EQ(Texture2(sizeRef).get_image<pixel_format::rgba>(), w.toTexture().get_image<pixel_format::rgba>());
}



TEST_F(TestRenderWindow, SetClientRect)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2i posRef(2, 3);
  vec2u sizeRef(14u, 17u);
  w.set_client_rect(posRef, sizeRef);

  EXPECT_EQ(posRef, w.get_client_position());
  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientRectNullSizeX)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef(0u, 17u);
  w.set_client_rect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.get_client_size());

  sizeRef.x() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientRectNullSizeY)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef(13u, 0u);
  w.set_client_rect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.get_client_size());

  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientRectNullSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef = vec2u::zero();
  w.set_client_rect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.get_client_size());

  sizeRef.x() = 1u;
  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef(14u, 17u);
  w.set_client_size(sizeRef);

  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientSizeNullSizeX)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u),  window_style::windowed, 4u);

  vec2u sizeRef(0u, 17u);
  w.set_client_size(sizeRef);
  EXPECT_EQ(sizeRef, w.get_client_size());

  sizeRef.x() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientSizeNullSizeY)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef(13u, 0u);
  w.set_client_size(sizeRef);
  EXPECT_EQ(sizeRef, w.get_client_size());

  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetClientSizeNullSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef = vec2u::zero();
  w.set_client_size(sizeRef);
  EXPECT_EQ(sizeRef, w.get_client_size());

  sizeRef.x() = 1u;
  sizeRef.y() = 1u;
  EXPECT_EQ(sizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameRect)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2i posRef(12, 13);
  vec2u sizeRef(60u, 100u);
  w.set_frame_rect(posRef, sizeRef);

  EXPECT_EQ(posRef, w.get_frame_position());
  EXPECT_EQ(sizeRef, w.get_frame_size());
  EXPECT_EQ(w.get_client_size(), w.get_size());
}



TEST_F(TestRenderWindow, SetFrameRectNullSizeX)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef(0u, 42u);
  w.set_frame_rect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.get_frame_size());

  vec2u texSizeRef = w.get_client_size();
  texSizeRef.x() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameRectNullSizeY)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef(42u, 0u);
  w.set_frame_rect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.get_frame_size());

  vec2u texSizeRef = w.get_client_size();
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameRectNullSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef = vec2u::zero();
  w.set_frame_rect(vec2i::zero(), sizeRef);
  EXPECT_EQ(sizeRef, w.get_frame_size());

  vec2u texSizeRef = w.get_client_size();
  texSizeRef.x() = 1u;
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  w.setFrameSize(vec2u(60u, 70u));

  EXPECT_EQ(w.get_client_size(), w.get_size());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSizeX)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef(0u, 42u);
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.get_frame_size());

  vec2u texSizeRef = w.get_client_size();
  texSizeRef.x() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSizeY)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef(42u, 0u);
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.get_frame_size());

  vec2u texSizeRef = w.get_client_size();
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetFrameSizeNullSize)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);

  vec2u sizeRef = vec2u::zero();
  w.setFrameSize(sizeRef);
  EXPECT_EQ(sizeRef, w.get_frame_size());

  vec2u texSizeRef = w.get_client_size();
  texSizeRef.x() = 1u;
  texSizeRef.y() = 1u;
  EXPECT_EQ(texSizeRef, w.get_size());
}



TEST_F(TestRenderWindow, SetVerticalSyncMode)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 4u);
  w.set_vertical_sync_mode(vertical_sync_mode::enabled);
  w.set_vertical_sync_mode(vertical_sync_mode::disabled);
  SUCCEED();
}



TEST_F(TestRenderWindow, SetSamples)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 1u);

  w.setSampleCount(1u);
  EXPECT_EQ(1u, w.get_sample_count());
  EXPECT_FALSE(w.isMultisampled());

  w.setSampleCount(2u);
  EXPECT_EQ(2u, w.get_sample_count());
  EXPECT_TRUE(w.isMultisampled());

  w.setSampleCount(RenderWindow::getMaxSampleCount());
  EXPECT_EQ(RenderWindow::getMaxSampleCount(), w.get_sample_count());
  EXPECT_TRUE(w.isMultisampled());
}



TEST_F(TestRenderWindowDeathTest, SetSamplesTooLarge)
{
  RenderWindow w(u8"Test", vec2u(32u, 16u), window_style::windowed, 1u);
  HOU_EXPECT_PRECONDITION(
    w.setSampleCount(RenderWindow::getMaxSampleCount() + 1u));
}



TEST_F(TestRenderWindow, ResizeFrameBufferOnPopResizedEvent)
{
  vec2u oldSize(vec2u(32u, 16u));
  RenderWindow w(u8"Test", oldSize, window_style::windowed, 4u);
  vec2u newSize(vec2u(12u, 8u));

  window_event ev = window_event::resized(newSize.x(), newSize.y());
  w.push_event(ev);
  EXPECT_EQ(oldSize, w.get_client_size());
  EXPECT_EQ(oldSize, w.get_size());

  EXPECT_EQ(ev, w.pop_event());
  EXPECT_EQ(newSize, w.get_client_size());
  EXPECT_EQ(newSize, w.get_size());
}
