// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/sys/SystemWindow.hpp"
#include "hou/sys/VideoMode.hpp"
#include "hou/sys/WindowEvent.hpp"

#include "hou/mth/Rectangle.hpp"

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
  std::string titleRef("SystemWindow");
  Vec2u sizeRef(300u, 600u);
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  WindowStyle styleRef = WindowStyle::Windowed;
  Image2RGBA iconRef;

  SystemWindow w(titleRef, VideoMode(sizeRef, bbpRef), styleRef);

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



TEST_F(TestSystemWindow, CreateWindowedResizable)
{
  std::string titleRef("SystemWindow");
  Vec2u sizeRef(300u, 600u);
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  WindowStyle styleRef = WindowStyle::WindowedResizable;
  Image2RGBA iconRef;

  SystemWindow w(titleRef, VideoMode(sizeRef, bbpRef), styleRef);

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



TEST_F(TestSystemWindow, CreateFullscreen)
{
  std::string titleRef("SystemWindow");
  Vec2u sizeRef(VideoMode::getDesktopMode().getResolution());
  Vec2i posRef(0, 0);
  uint bbpRef(VideoMode::getDesktopMode().getBytesPerPixel());
  WindowStyle styleRef = WindowStyle::Fullscreen;
  Image2RGBA iconRef;

  SystemWindow w(titleRef, VideoMode(sizeRef, bbpRef), styleRef);

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



TEST_F(TestSystemWindowDeathTest, CreateFullscreenErrorInvalidVideoMode)
{
  HOU_EXPECT_ERROR(SystemWindow w1("Win", VideoMode(Vec2u::zero(), 32),
                     WindowStyle::Fullscreen),
    std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestSystemWindowDeathTest,
  CreateFullscreenErrorFullscreenWindowAlreadyExisting)
{
  SystemWindow w2("Win", VideoMode::getDesktopMode(), WindowStyle::Fullscreen);
  HOU_EXPECT_ERROR(SystemWindow w3("Win", VideoMode::getDesktopMode(),
                     WindowStyle::Fullscreen),
    std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestSystemWindow, CreateWindowMultithreadedEnvironment)
{
  // When creating windows some global system state is modified.
  // This test checks if everything runs fine when multiple threads try to
  // create a window.
  auto threadFun = []() {
    SystemWindow w("Win", VideoMode(Vec2u::zero(), 0), WindowStyle::Windowed);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  };

  SystemWindow w("Win", VideoMode::getDesktopMode(), WindowStyle::Fullscreen);

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
  std::string titleRef("SystemWindow");
  Vec2u sizeRef(300u, 600u);
  Vec2u screenSize = VideoMode::getDesktopMode().getResolution();
  Vec2i posRef = static_cast<Vec2i>(screenSize - sizeRef) / 2;
  uint bbpRef = 4u;
  WindowStyle styleRef = WindowStyle::Windowed;
  Image2RGBA iconRef;

  SystemWindow wDummy(titleRef, VideoMode(sizeRef, bbpRef), styleRef);
  WindowHandle handleRef = wDummy.getWindowHandle();

  SystemWindow w(std::move(wDummy));

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



TEST_F(TestSystemWindow, UidGeneration)
{
  SystemWindow firstWindow(
    "Win", VideoMode(Vec2u::zero(), 0), WindowStyle::Windowed);
  uint32_t firstUid = firstWindow.getUid() + 1u;

  for(size_t i = 0; i < 5u; ++i)
  {
    SystemWindow w("Win", VideoMode(Vec2u::zero(), 0), WindowStyle::Windowed);
    EXPECT_EQ(firstUid + i, w.getUid());
  }
}



TEST_F(TestSystemWindow, FrameRect)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Recti refRect = Recti(10, 20, 30, 40);
  w.setFrameRect(refRect);
  EXPECT_EQ(refRect, w.getFrameRect());
}



TEST_F(TestSystemWindowDeathTest, FrameRectErrorNegativeSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  HOU_EXPECT_PRECONDITION(w.setFrameRect(Recti(0, 0, -1, 600)));
  HOU_EXPECT_PRECONDITION(w.setFrameRect(Recti(0, 0, 300, -1)));
}



TEST_F(TestSystemWindow, FramePosition)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Vec2i refPos = Vec2i(30, 40);
  w.setFramePosition(refPos);
  EXPECT_EQ(refPos, w.getFramePosition());
}



TEST_F(TestSystemWindow, FrameSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Vec2u refSize = Vec2u(30u, 40u);
  w.setFrameSize(refSize);
  EXPECT_EQ(refSize, w.getFrameSize());
}



TEST_F(TestSystemWindow, ClientRect)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Recti refRect = Recti(10, 20, 30, 40);
  w.setClientRect(refRect);
  EXPECT_EQ(refRect, w.getClientRect());
}



TEST_F(TestSystemWindowDeathTest, ClientRectErrorNegativeSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  HOU_EXPECT_PRECONDITION(w.setClientRect(Recti(0, 0, -1, 600)));
  HOU_EXPECT_PRECONDITION(w.setClientRect(Recti(0, 0, 300, -1)));
}



TEST_F(TestSystemWindow, ClientPosition)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Vec2i refPos = Vec2i(30, 40);
  w.setClientPosition(refPos);
  EXPECT_EQ(refPos, w.getClientPosition());
}



TEST_F(TestSystemWindow, ClientSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  Vec2u refSize = Vec2u(30u, 40u);
  w.setClientSize(refSize);
  EXPECT_EQ(refSize, w.getClientSize());
}



TEST_F(TestSystemWindow, Title)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  std::string refTitle(u8"NewTitle");
  w.setTitle(refTitle);
  EXPECT_EQ(refTitle, w.getTitle());
}



TEST_F(TestSystemWindow, Icon)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_EQ(Image2RGBA(), w.getIcon());
  Image2RGBA refIcon(
    pngReadFile<PixelFormat::RGBA>(getDataDir() + u8"TestImage.png"));
  w.setIcon(refIcon);
  EXPECT_EQ(refIcon, w.getIcon());
  w.setSystemIcon();
  EXPECT_EQ(Image2RGBA(), w.getIcon());
}



TEST_F(TestSystemWindow, Visibility)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_FALSE(w.isVisible());

  w.setVisible(true);
  EXPECT_TRUE(w.isVisible());

  w.setVisible(false);
  EXPECT_FALSE(w.isVisible());
}



TEST_F(TestSystemWindow, CursorGrabbed)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_FALSE(w.isMouseCursorGrabbed());

  w.setMouseCursorGrabbed(true);
  EXPECT_TRUE(w.isMouseCursorGrabbed());

  w.setMouseCursorGrabbed(false);
  EXPECT_FALSE(w.isMouseCursorGrabbed());
}



TEST_F(TestSystemWindow, KeyRepeatEnabled)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_FALSE(w.isKeyRepeatEnabled());

  w.setKeyRepeatEnabled(true);
  EXPECT_TRUE(w.isKeyRepeatEnabled());

  w.setKeyRepeatEnabled(false);
  EXPECT_FALSE(w.isKeyRepeatEnabled());
}



TEST_F(TestSystemWindow, Focus)
{
  SystemWindow w1(
    "Win1", VideoMode(Vec2u(640u, 480u), 32u), WindowStyle::Windowed);
  SystemWindow w2(
    "Win2", VideoMode(Vec2u(640u, 480u), 32u), WindowStyle::Windowed);
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



TEST_F(TestSystemWindow, EventQueuePushAndPop)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
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



TEST_F(TestSystemWindow, EventQueueWaitEvent)
{
  WindowEvent evRef = WindowEvent::focusGained();
  SystemWindow w("Win", VideoMode(Vec2u::zero(), 0), WindowStyle::Windowed);
  auto threadFun = [&evRef, &w]() {
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



TEST_F(TestSystemWindow, GenerateResizeEventOnSetFrameSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setFrameSize(Vec2u(200u, 400u));
  WindowEvent eventRef
    = WindowEvent::resized(w.getClientSize().x(), w.getClientSize().y());
  EXPECT_FALSE(w.isEventQueueEmpty());
  EXPECT_EQ(eventRef, w.popEvent());
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetFrameSizeWithSameSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setFrameSize(w.getFrameSize());
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, GenerateResizeEventOnSetFrameRect)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setFrameRect(Recti(Vec2i(32, 64), Vec2i(200, 400)));
  WindowEvent eventRef
    = WindowEvent::resized(w.getClientSize().x(), w.getClientSize().y());
  EXPECT_FALSE(w.isEventQueueEmpty());
  EXPECT_EQ(eventRef, w.popEvent());
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetFrameRectWithSameSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(200u, 400u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setFrameRect(Recti(Vec2i(32, 64), static_cast<Vec2i>(w.getFrameSize())));
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetFramePos)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setFramePosition(Vec2i(32, 64));
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, GenerateResizeEventOnSetClientSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setClientSize(Vec2u(200u, 400u));
  WindowEvent eventRef
    = WindowEvent::resized(w.getClientSize().x(), w.getClientSize().y());
  EXPECT_FALSE(w.isEventQueueEmpty());
  EXPECT_EQ(eventRef, w.popEvent());
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetClientSizeWithSameSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setClientSize(w.getClientSize());
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, GenerateResizeEventOnSetClientRect)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setClientRect(Recti(Vec2i(32, 64), Vec2i(200, 400)));
  WindowEvent eventRef
    = WindowEvent::resized(w.getClientSize().x(), w.getClientSize().y());
  EXPECT_FALSE(w.isEventQueueEmpty());
  EXPECT_EQ(eventRef, w.popEvent());
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetClientRectWithSameSize)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setClientRect(Recti(Vec2i(32, 64), static_cast<Vec2i>(w.getClientSize())));
  EXPECT_TRUE(w.isEventQueueEmpty());
}



TEST_F(TestSystemWindow, DoNotGenerateResizeEventOnSetClientPos)
{
  SystemWindow w(
    "Win", VideoMode(Vec2u(300u, 600u), 32u), WindowStyle::Windowed);
  EXPECT_TRUE(w.isEventQueueEmpty());

  w.setClientPosition(Vec2i(32, 64));
  EXPECT_TRUE(w.isEventQueueEmpty());
}

// setClientRect with negative values?



// NOTES:
// - no test for mouse grabbing.
// - no test for key repeat.
// - no test for updateEventQueue and translation of system messages to
//   WindowEvent objects.
