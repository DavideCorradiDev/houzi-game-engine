// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/sys/VideoMode.hpp"
#include "hou/sys/Window.hpp"
#include "hou/sys/WindowEvent.hpp"

#include "hou/mth/Rectangle.hpp"

#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class TestWindow : public Test {};
class TestWindowDeathTest : public TestWindow {};

}



TEST_F(TestWindow, CreateWindowed)
{
  std::string titleRef("Window");
  Vec2u sizeRef(300u, 600u);
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  WindowStyle styleRef = WindowStyle::Windowed;
  Image2RGBA iconRef;

  Window w(titleRef, VideoMode(sizeRef, bbpRef), styleRef);

  EXPECT_NE(nullptr, w.getWindowHandle());
  EXPECT_NE(0u, w.getUid());
  EXPECT_EQ(titleRef, w.getTitle());
  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(bbpRef, w.getBytesPerPixel());
  EXPECT_EQ(styleRef, w.getStyle());
  EXPECT_EQ(iconRef, w.getIcon());
  EXPECT_FALSE(w.isVisible());
  EXPECT_FALSE(w.isMouseCursorGrabbed());
  EXPECT_FALSE(w.isKeyRepeatEnabled());
}



TEST_F(TestWindow, CreateWindowedResizable)
{
  std::string titleRef("Window");
  Vec2u sizeRef(300u, 600u);
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  WindowStyle styleRef = WindowStyle::WindowedResizable;
  Image2RGBA iconRef;

  Window w(titleRef, VideoMode(sizeRef, bbpRef), styleRef);

  EXPECT_NE(nullptr, w.getWindowHandle());
  EXPECT_NE(0u, w.getUid());
  EXPECT_EQ(titleRef, w.getTitle());
  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(bbpRef, w.getBytesPerPixel());
  EXPECT_EQ(styleRef, w.getStyle());
  EXPECT_EQ(iconRef, w.getIcon());
  EXPECT_FALSE(w.isVisible());
  EXPECT_FALSE(w.isMouseCursorGrabbed());
  EXPECT_FALSE(w.isKeyRepeatEnabled());
}



TEST_F(TestWindow, CreateFullscreen)
{
  std::string titleRef("Window");
  Vec2u sizeRef(VideoMode::getDesktopMode().getResolution());
  Vec2i posRef(0, 0);
  uint bbpRef(VideoMode::getDesktopMode().getBytesPerPixel());
  WindowStyle styleRef = WindowStyle::Fullscreen;
  Image2RGBA iconRef;

  Window w(titleRef, VideoMode(sizeRef, bbpRef), styleRef);

  EXPECT_NE(nullptr, w.getWindowHandle());
  EXPECT_NE(0u, w.getUid());
  EXPECT_EQ(titleRef, w.getTitle());
  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(posRef, w.getFramePosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(sizeRef, w.getFrameSize());
  EXPECT_EQ(bbpRef, w.getBytesPerPixel());
  EXPECT_EQ(styleRef, w.getStyle());
  EXPECT_EQ(iconRef, w.getIcon());
  EXPECT_FALSE(w.isVisible());
  EXPECT_FALSE(w.isMouseCursorGrabbed());
  EXPECT_FALSE(w.isKeyRepeatEnabled());
}



TEST_F(TestWindowDeathTest, CreateFullscreenErrorInvalidVideoMode)
{
  HOU_EXPECT_ERROR
    ( Window w1("Win", VideoMode(Vec2u::zero(), 32), WindowStyle::Fullscreen)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestWindowDeathTest, CreateFullscreenErrorFullscreenWindowAlreadyExisting)
{
  Window w2("Win", VideoMode::getDesktopMode(), WindowStyle::Fullscreen);
  HOU_EXPECT_ERROR
    ( Window w3("Win", VideoMode::getDesktopMode(), WindowStyle::Fullscreen)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestWindow, CreateWindowMultithreadedEnvironment)
{
  // When creating windows some global system state is modified.
  // This test checks if everything runs fine when multiple threads try to
  // create a window.
  auto threadFun = []()
  {
    Window w("Win", VideoMode(Vec2u::zero(), 0), WindowStyle::Windowed);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  };

  Window w("Win", VideoMode::getDesktopMode(), WindowStyle::Fullscreen);

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



TEST_F(TestWindow, MoveConstructor)
{
  std::string titleRef("Window");
  Vec2u sizeRef(300u, 600u);
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  WindowStyle styleRef = WindowStyle::Windowed;
  Image2RGBA iconRef;

  Window wDummy(titleRef, VideoMode(sizeRef, bbpRef), styleRef);
  WindowHandle handleRef = wDummy.getWindowHandle();

  Window w(std::move(wDummy));

  EXPECT_EQ(handleRef, w.getWindowHandle());
  EXPECT_NE(0u, w.getUid());
  EXPECT_EQ(titleRef, w.getTitle());
  EXPECT_EQ(posRef, w.getClientPosition());
  EXPECT_EQ(sizeRef, w.getClientSize());
  EXPECT_EQ(bbpRef, w.getBytesPerPixel());
  EXPECT_EQ(styleRef, w.getStyle());
  EXPECT_EQ(iconRef, w.getIcon());
  EXPECT_FALSE(w.isVisible());
  EXPECT_FALSE(w.isMouseCursorGrabbed());
  EXPECT_FALSE(w.isKeyRepeatEnabled());
}



TEST_F(TestWindow, UidGeneration)
{
  Window firstWindow("Win", VideoMode(Vec2u::zero(), 0), WindowStyle::Windowed);
  uint32_t firstUid = firstWindow.getUid() + 1u;

  for(size_t i = 0; i < 5u; ++i)
  {
    Window w("Win", VideoMode(Vec2u::zero(), 0), WindowStyle::Windowed);
    EXPECT_EQ(firstUid + i, w.getUid());
  }
}



TEST_F(TestWindow, FrameRect)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Recti refRect = Recti(10, 20, 30, 40);
  w.setFrameRect(refRect);
  EXPECT_EQ(refRect, w.getFrameRect());
}



TEST_F(TestWindow, FramePosition)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Vec2i refPos = Vec2i(30, 40);
  w.setFramePosition(refPos);
  EXPECT_EQ(refPos, w.getFramePosition());
}



TEST_F(TestWindow, FrameSize)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Vec2u refSize = Vec2u(30u, 40u);
  w.setFrameSize(refSize);
  EXPECT_EQ(refSize, w.getFrameSize());
}



TEST_F(TestWindow, ClientRect)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Recti refRect = Recti(10, 20, 30, 40);
  w.setClientRect(refRect);
  EXPECT_EQ(refRect, w.getClientRect());
}



TEST_F(TestWindow, ClientPosition)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Vec2i refPos = Vec2i(30, 40);
  w.setClientPosition(refPos);
  EXPECT_EQ(refPos, w.getClientPosition());
}



TEST_F(TestWindow, ClientSize)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Vec2u refSize = Vec2u(30u, 40u);
  w.setClientSize(refSize);
  EXPECT_EQ(refSize, w.getClientSize());
}



TEST_F(TestWindow, Title)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  std::string refTitle(u8"NewTitle");
  w.setTitle(refTitle);
  EXPECT_EQ(refTitle, w.getTitle());
}



TEST_F(TestWindow, Icon)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_EQ(Image2RGBA(), w.getIcon());
  Image2RGBA refIcon(pngReadFile<PixelFormat::RGBA>(getDataDir() + u8"TestImage.png"));
  w.setIcon(refIcon);
  EXPECT_EQ(refIcon, w.getIcon());
  w.setSystemIcon();
  EXPECT_EQ(Image2RGBA(), w.getIcon());
}



TEST_F(TestWindow, Visibility)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_FALSE(w.isVisible());

  w.setVisible(true);
  EXPECT_TRUE(w.isVisible());

  w.setVisible(false);
  EXPECT_FALSE(w.isVisible());
}



TEST_F(TestWindow, CursorGrabbed)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_FALSE(w.isMouseCursorGrabbed());

  w.setMouseCursorGrabbed(true);
  EXPECT_TRUE(w.isMouseCursorGrabbed());

  w.setMouseCursorGrabbed(false);
  EXPECT_FALSE(w.isMouseCursorGrabbed());
}



TEST_F(TestWindow, KeyRepeatEnabled)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_FALSE(w.isKeyRepeatEnabled());

  w.setKeyRepeatEnabled(true);
  EXPECT_TRUE(w.isKeyRepeatEnabled());

  w.setKeyRepeatEnabled(false);
  EXPECT_FALSE(w.isKeyRepeatEnabled());
}



TEST_F(TestWindow, Focus)
{
  Window w1("Win1", VideoMode(Vec2u(640u, 480u), 32u), WindowStyle::Windowed);
  Window w2("Win2", VideoMode(Vec2u(640u, 480u), 32u), WindowStyle::Windowed);
  w1.setVisible(true);
  w2.setVisible(true);

  if(w1.requestFocus())
  {
    EXPECT_TRUE(w1.hasFocus());
    EXPECT_FALSE(w2.hasFocus());
  }
  else
  {
    // Failed to take focus. Just pass.
    SUCCEED();
  }
}



TEST_F(TestWindow, EventQueuePushAndPop)
{
  Window w("Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  WindowEvent e1(WindowEvent::closed());
  WindowEvent e2(WindowEvent::focusGained());
  WindowEvent e3(WindowEvent::focusLost());

  EXPECT_TRUE(w.isEventQueueEmpty());

  w.pushEvent(e1);
  w.pushEvent(e2);
  w.pushEvent(e3);

  EXPECT_FALSE(w.isEventQueueEmpty());

  EXPECT_EQ(e1, w.popEvent());
  EXPECT_EQ(e2, w.popEvent());
  EXPECT_EQ(e3, w.popEvent());

  EXPECT_TRUE(w.isEventQueueEmpty());

  EXPECT_EQ(WindowEvent::empty(), w.popEvent());
}


TEST_F(TestWindow, EventQueueWaitEvent)
{
  WindowEvent evRef = WindowEvent::focusGained();
  Window w("Win", VideoMode(Vec2u::zero(), 0), WindowStyle::Windowed);
  auto threadFun = [&evRef, &w]()
  {
    // This thread will wait for an event, which will be generated by the
    // main thread.
    WindowEvent ev = w.waitEvent();
    EXPECT_EQ(evRef, ev);
  };
  std::thread t1(threadFun);

  w.pushEvent(evRef);

  t1.join();

  SUCCEED();
}



// NOTES:
// - no test for mouse grabbing.
// - no test for key repeat.
// - no test for updateEventQueue and translation of system messages to
//   WindowEvent objects.

