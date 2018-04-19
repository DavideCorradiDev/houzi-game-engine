// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_IMPL_HPP
#define HOU_SYS_WINDOW_IMPL_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/cor/CharacterEncodings.hpp"

#include "hou/mth/RectangleFwd.hpp"
#include "hou/mth/Matrix.hpp"

#include "hou/sys/ImageFwd.hpp"
#include "hou/sys/WindowHandle.hpp"
#include "hou/sys/WindowStyle.hpp"
#if defined(HOU_SYSTEM_WINDOWS)
  #include "hou/sys/Win/Win.hpp"
#endif

#include <queue>



namespace hou
{

class VideoMode;
class WindowEvent;



namespace prv
{

class WindowImpl
  : public NonCopyable
{
public:
  WindowImpl(const std::string& title, const VideoMode& videoMode
    , WindowStyle style);
  WindowImpl(WindowImpl&& other);
  ~WindowImpl();

  WindowHandle getWindowHandle() const;

  Recti getFrameRect() const;
  void setFrameRect(const Recti& value);

  Recti getClientRect() const;
  void setClientRect(const Recti& value);

  void setTitle(const std::string& value);

  void setIcon(const Image2RGBA& icon);
  void setSystemIcon();

  bool isVisible() const;
  void setVisible(bool value);

  bool isMouseCursorGrabbed() const;
  void setMouseCursorGrabbed(bool value);

  bool isKeyRepeatEnabled() const;
  void setKeyRepeatEnabled(bool value);

  bool hasFocus() const;
  bool requestFocus() const;

  bool isEventQueueEmpty() const;
  void updateEventQueue();
  WindowEvent waitEvent();
  WindowEvent popEvent();
  void pushEvent(const WindowEvent& event);

  void swapBuffers();

private:
  void grabMouseCursor();
  void ungrabMouseCursor();
  bool isMouseCaptured() const;
  void setMouseCaptured(bool value);

#if defined(HOU_SYSTEM_WINDOWS)
  static void registerWindowClass();
  static void unregisterWindowClass();
  static LRESULT CALLBACK wndProcedure(HWND hwnd, UINT uMsg, WPARAM wParam
    , LPARAM lParam);

  void destroyIcon();
  void destroyCursor();
  void destroyWindow();

  void filterEvent(UINT uMsg, WPARAM wParam , LPARAM lParam);
#endif

private:
  WindowHandle mHandle;
  bool mCursorGrabbed;
  bool mKeyRepeatEnabled;
  std::queue<WindowEvent> mEventQueue;
#if defined(HOU_SYSTEM_WINDOWS)
  HDC mHdc;
  HCURSOR mCursorHandle;
  HICON mIconHandle;
  Wide::CodeUnit mCachedUtf16Char;
  bool mMouseInWindow;
  Vec2u mPreviousSize;
#endif
};

}

}

#endif

