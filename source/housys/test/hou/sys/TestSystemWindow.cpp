// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/sys/system_window.hpp"
#include "hou/sys/video_mode.hpp"
#include "hou/sys/window_event.hpp"

#include "hou/mth/rectangle.hpp"

#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class TestSystemWindow : public Test
{};

class TestSystemWindowDeathTest : public TestSystemWindow
{};

}  // namespace



TEST_F(TestSystemWindow, CreateWindowed)
{
  std::string titleRef("system_window");
  vec2u sizeRef(300u, 600u);
  vec2u screenSize = video_mode::get_desktop_mode().get_resolution();
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  window_style styleRef = window_style::windowed;
  image2RGBA iconRef;

  system_window w(titleRef, video_mode(sizeRef, bbpRef), styleRef);

  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_NE(0u, w.get_uid());
  EXPECT_EQ(titleRef, w.get_title());
  EXPECT_EQ(posRef, w.get_client_position());
  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(bbpRef, w.get_bytes_per_pixel());
  EXPECT_EQ(styleRef, w.get_style());
  EXPECT_EQ(iconRef, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());
}



TEST_F(TestSystemWindow, CreateWindowedResizable)
{
  std::string titleRef("system_window");
  vec2u sizeRef(300u, 600u);
  vec2u screenSize = video_mode::get_desktop_mode().get_resolution();
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  window_style styleRef = window_style::windowed_resizable;
  image2RGBA iconRef;

  system_window w(titleRef, video_mode(sizeRef, bbpRef), styleRef);

  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_NE(0u, w.get_uid());
  EXPECT_EQ(titleRef, w.get_title());
  EXPECT_EQ(posRef, w.get_client_position());
  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(bbpRef, w.get_bytes_per_pixel());
  EXPECT_EQ(styleRef, w.get_style());
  EXPECT_EQ(iconRef, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());
}



TEST_F(TestSystemWindow, CreateFullscreen)
{
  std::string titleRef("system_window");
  vec2u sizeRef(video_mode::get_desktop_mode().get_resolution());
  vec2i posRef(0, 0);
  uint bbpRef(video_mode::get_desktop_mode().get_bytes_per_pixel());
  window_style styleRef = window_style::fullscreen;
  image2RGBA iconRef;

  system_window w(titleRef, video_mode(sizeRef, bbpRef), styleRef);

  EXPECT_NE(nullptr, w.get_handle());
  EXPECT_NE(0u, w.get_uid());
  EXPECT_EQ(titleRef, w.get_title());
  EXPECT_EQ(posRef, w.get_client_position());
  EXPECT_EQ(posRef, w.get_frame_position());
  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(sizeRef, w.get_frame_size());
  EXPECT_EQ(bbpRef, w.get_bytes_per_pixel());
  EXPECT_EQ(styleRef, w.get_style());
  EXPECT_EQ(iconRef, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());
}



TEST_F(TestSystemWindowDeathTest, CreateFullscreenErrorInvalidVideoMode)
{
  HOU_EXPECT_ERROR(system_window w1("Win", video_mode(vec2u::zero(), 32),
                     window_style::fullscreen),
    std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestSystemWindowDeathTest,
  CreateFullscreenErrorFullscreenWindowAlreadyExisting)
{
  system_window w2("Win", video_mode::get_desktop_mode(), window_style::fullscreen);
  HOU_EXPECT_ERROR(system_window w3("Win", video_mode::get_desktop_mode(),
                     window_style::fullscreen),
    std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestSystemWindow, CreateWindowMultithreadedEnvironment)
{
  // When creating windows some global system state is modified.
  // This test checks if everything runs fine when multiple threads try to
  // create a ph_window.
  auto threadFun = []() {
    system_window w("Win", video_mode(vec2u::zero(), 0), window_style::windowed);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  };

  system_window w("Win", video_mode::get_desktop_mode(), window_style::fullscreen);

  std::thread t1(threadFun);
  std::thread t2(threadFun);
  std::thread t3(threadFun);
  std::thread t4(threadFun);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  SUCCEED();
}



TEST_F(TestSystemWindow, MoveConstructor)
{
  std::string titleRef("system_window");
  vec2u sizeRef(300u, 600u);
  vec2u screenSize = video_mode::get_desktop_mode().get_resolution();
  vec2i posRef = static_cast<vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  window_style styleRef = window_style::windowed;
  image2RGBA iconRef;

  system_window wDummy(titleRef, video_mode(sizeRef, bbpRef), styleRef);
  window_handle handleRef = wDummy.get_handle();

  system_window w(std::move(wDummy));

  EXPECT_EQ(handleRef, w.get_handle());
  EXPECT_NE(0u, w.get_uid());
  EXPECT_EQ(titleRef, w.get_title());
  EXPECT_EQ(posRef, w.get_client_position());
  EXPECT_EQ(sizeRef, w.get_client_size());
  EXPECT_EQ(bbpRef, w.get_bytes_per_pixel());
  EXPECT_EQ(styleRef, w.get_style());
  EXPECT_EQ(iconRef, w.get_icon());
  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
  EXPECT_FALSE(w.is_key_repeat_enabled());
}



TEST_F(TestSystemWindow, UidGeneration)
{
  system_window firstWindow(
    "Win", video_mode(vec2u::zero(), 0), window_style::windowed);
  uint32_t firstUid = firstWindow.get_uid() + 1u;

  for(size_t i = 0; i < 5u; ++i)
  {
    system_window w("Win", video_mode(vec2u::zero(), 0), window_style::windowed);
    EXPECT_EQ(firstUid + i, w.get_uid());
  }
}



TEST_F(TestSystemWindow, FrameRect)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  recti refRect = recti(10, 20, 30, 40);
  vec2i pos(10, 20);
  vec2u size(30u, 40u);
  w.set_frame_rect(pos, size);
  EXPECT_EQ(pos, w.get_frame_position());
  EXPECT_EQ(size, w.get_frame_size());
}



TEST_F(TestSystemWindow, FramePosition)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  vec2i refPos = vec2i(30, 40);
  w.set_frame_position(refPos);
  EXPECT_EQ(refPos, w.get_frame_position());
}



TEST_F(TestSystemWindow, FrameSize)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  vec2u refSize = vec2u(30u, 40u);
  w.setFrameSize(refSize);
  EXPECT_EQ(refSize, w.get_frame_size());
}



TEST_F(TestSystemWindow, ClientRect)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  recti refRect = recti(10, 20, 30, 40);
  vec2i pos(10, 20);
  vec2u size(30u, 40u);
  w.set_client_rect(pos, size);
  EXPECT_EQ(pos, w.get_client_position());
  EXPECT_EQ(size, w.get_client_size());
}



TEST_F(TestSystemWindow, ClientPosition)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  vec2i refPos = vec2i(30, 40);
  w.set_client_position(refPos);
  EXPECT_EQ(refPos, w.get_client_position());
}



TEST_F(TestSystemWindow, ClientSize)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  vec2u refSize = vec2u(30u, 40u);
  w.set_client_size(refSize);
  EXPECT_EQ(refSize, w.get_client_size());
}



TEST_F(TestSystemWindow, Title)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  std::string refTitle(u8"NewTitle");
  w.set_title(refTitle);
  EXPECT_EQ(refTitle, w.get_title());
}



TEST_F(TestSystemWindow, Icon)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_EQ(image2RGBA(), w.get_icon());
  image2RGBA refIcon(
    png_read_file<pixel_format::rgba>(getDataDir() + u8"TestImage.png"));
  w.set_icon(refIcon);
  EXPECT_EQ(refIcon, w.get_icon());
  w.set_system_icon();
  EXPECT_EQ(image2RGBA(), w.get_icon());
}



TEST_F(TestSystemWindow, Visibility)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_FALSE(w.is_visible());

  w.set_visible(true);
  EXPECT_TRUE(w.is_visible());

  w.set_visible(false);
  EXPECT_FALSE(w.is_visible());
}



TEST_F(TestSystemWindow, CursorGrabbed)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());

  w.set_mouse_cursor_grabbed(true);
  EXPECT_TRUE(w.is_mouse_cursor_grabbed());

  w.set_mouse_cursor_grabbed(false);
  EXPECT_FALSE(w.is_mouse_cursor_grabbed());
}



TEST_F(TestSystemWindow, KeyRepeatEnabled)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_FALSE(w.is_key_repeat_enabled());

  w.set_key_repeat_enabled(true);
  EXPECT_TRUE(w.is_key_repeat_enabled());

  w.set_key_repeat_enabled(false);
  EXPECT_FALSE(w.is_key_repeat_enabled());
}



TEST_F(TestSystemWindow, Focus)
{
  system_window w1(
    "Win1", video_mode(vec2u(640u, 480u), 32u), window_style::windowed);
  system_window w2(
    "Win2", video_mode(vec2u(640u, 480u), 32u), window_style::windowed);
  w1.set_visible(true);
  w2.set_visible(true);

  if(w1.request_focus())
  {
    EXPECT_TRUE(w1.has_focus());
    EXPECT_FALSE(w2.has_focus());
  }
  else
  {
    // Failed to take focus. Just pass.
    SUCCEED();
  }
}



TEST_F(TestSystemWindow, EventQueuePushAndPop)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  window_event e1(window_event::closed());
  window_event e2(window_event::focus_gained());
  window_event e3(window_event::focus_lost());

  EXPECT_TRUE(w.is_event_queue_empty());

  w.push_event(e1);
  w.push_event(e2);
  w.push_event(e3);

  EXPECT_FALSE(w.is_event_queue_empty());

  EXPECT_EQ(e1, w.pop_event());
  EXPECT_EQ(e2, w.pop_event());
  EXPECT_EQ(e3, w.pop_event());

  EXPECT_TRUE(w.is_event_queue_empty());

  EXPECT_EQ(window_event::empty(), w.pop_event());
}



TEST_F(TestSystemWindow, EventQueueWaitEvent)
{
  window_event evRef = window_event::focus_gained();
  system_window w("Win", video_mode(vec2u::zero(), 0), window_style::windowed);
  auto threadFun = [&evRef, &w]() {
    // This thread will wait for an event, which will be generated by the
    // main thread.
    window_event ev = w.wait_event();
    EXPECT_EQ(evRef, ev);
  };
  std::thread t1(threadFun);

  w.push_event(evRef);

  t1.join();

  SUCCEED();
}



TEST_F(TestSystemWindow, GenerateResizeEventOnSetFrameSize)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.setFrameSize(vec2u(200u, 400u));
  window_event eventRef
    = window_event::resized(w.get_client_size().x(), w.get_client_size().y());
  EXPECT_FALSE(w.is_event_queue_empty());
  EXPECT_EQ(eventRef, w.pop_event());
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetFrameSizeWithSameSize)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.setFrameSize(w.get_frame_size());
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, GenerateResizeEventOnSetFrameRect)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.set_frame_rect(vec2i(32, 64), vec2u(200u, 400u));
  window_event eventRef
    = window_event::resized(w.get_client_size().x(), w.get_client_size().y());
  EXPECT_FALSE(w.is_event_queue_empty());
  EXPECT_EQ(eventRef, w.pop_event());
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetFrameRectWithSameSize)
{
  system_window w(
    "Win", video_mode(vec2u(200u, 400u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.set_frame_rect(vec2i(32, 64), w.get_frame_size());
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetFramePos)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.set_frame_position(vec2i(32, 64));
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, GenerateResizeEventOnSetClientSize)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.set_client_size(vec2u(200u, 400u));
  window_event eventRef
    = window_event::resized(w.get_client_size().x(), w.get_client_size().y());
  EXPECT_FALSE(w.is_event_queue_empty());
  EXPECT_EQ(eventRef, w.pop_event());
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetClientSizeWithSameSize)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.set_client_size(w.get_client_size());
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, GenerateResizeEventOnSetClientRect)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.set_client_rect(vec2i(32, 64), vec2u(200u, 400u));
  window_event eventRef
    = window_event::resized(w.get_client_size().x(), w.get_client_size().y());
  EXPECT_FALSE(w.is_event_queue_empty());
  EXPECT_EQ(eventRef, w.pop_event());
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetClientRectWithSameSize)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.set_client_rect(vec2i(32, 64), w.get_client_size());
  EXPECT_TRUE(w.is_event_queue_empty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetClientPos)
{
  system_window w(
    "Win", video_mode(vec2u(300u, 600u), 32u), window_style::windowed);
  EXPECT_TRUE(w.is_event_queue_empty());

  w.set_client_position(vec2i(32, 64));
  EXPECT_TRUE(w.is_event_queue_empty());
}



// NOTES:
// - no test for mouse grabbing.
// - no test for key repeat.
// - no test for update_event_queue and translation of system messages to
//   window_event objects.
