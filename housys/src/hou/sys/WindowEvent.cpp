// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/WindowEvent.hpp"

#include "hou/cor/Error.hpp"

#include <iomanip>



namespace hou
{

WindowEvent WindowEvent::empty()
{
  WindowEvent ev;
  ev.mType = WindowEventType::Empty;
  return ev;
}



WindowEvent WindowEvent::closed()
{
  WindowEvent ev;
  ev.mType = WindowEventType::Closed;
  return ev;
}



WindowEvent WindowEvent::focusGained()
{
  WindowEvent ev;
  ev.mType = WindowEventType::FocusGained;
  return ev;
}



WindowEvent WindowEvent::focusLost()
{
  WindowEvent ev;
  ev.mType = WindowEventType::FocusLost;
  return ev;
}



WindowEvent WindowEvent::resized(uint sizeX, uint sizeY)
{
  WindowEvent ev;
  ev.mType = WindowEventType::Resized;
  ev.mSize.sizeX = sizeX;
  ev.mSize.sizeY = sizeY;
  return ev;
}



WindowEvent WindowEvent::keyPressed(KeyCode kc, ScanCode sc, ModifierKeys modKeys)
{
  WindowEvent ev;
  ev.mType = WindowEventType::KeyPressed;
  ev.mKey.keyCode = kc;
  ev.mKey.scanCode = sc;
  ev.mKey.modifierKeys = modKeys;
  return ev;
}



WindowEvent WindowEvent::keyReleased(KeyCode kc, ScanCode sc, ModifierKeys modKeys)
{
  WindowEvent ev;
  ev.mType = WindowEventType::KeyReleased;
  ev.mKey.keyCode = kc;
  ev.mKey.scanCode = sc;
  ev.mKey.modifierKeys = modKeys;
  return ev;
}



WindowEvent WindowEvent::textEntered(char32_t codePoint)
{
  WindowEvent ev;
  ev.mType = WindowEventType::TextEntered;
  ev.mText.codePoint = codePoint;
  return ev;
}



WindowEvent WindowEvent::mouseMoved(int posX, int posY)
{
  WindowEvent ev;
  ev.mType = WindowEventType::MouseMoved;
  ev.mMouseMove.posX = posX;
  ev.mMouseMove.posY = posY;
  return ev;
}



WindowEvent WindowEvent::mouseEntered()
{
  WindowEvent ev;
  ev.mType = WindowEventType::MouseEntered;
  return ev;
}



WindowEvent WindowEvent::mouseLeft()
{
  WindowEvent ev;
  ev.mType = WindowEventType::MouseLeft;
  return ev;
}



WindowEvent WindowEvent::mouseButtonPressed(MouseButton mb, int posX, int posY)
{
  WindowEvent ev;
  ev.mType = WindowEventType::MouseButtonPressed;
  ev.mMouseButton.button = mb;
  ev.mMouseButton.posX = posX;
  ev.mMouseButton.posY = posY;
  return ev;
}



WindowEvent WindowEvent::mouseButtonReleased(MouseButton mb, int posX, int posY)
{
  WindowEvent ev;
  ev.mType = WindowEventType::MouseButtonReleased;
  ev.mMouseButton.button = mb;
  ev.mMouseButton.posX = posX;
  ev.mMouseButton.posY = posY;
  return ev;
}



WindowEvent WindowEvent::mouseWheelMoved(MouseWheel wheel, int delta, int posX
  , int posY)
{
  WindowEvent ev;
  ev.mType = WindowEventType::MouseWheelMoved;
  ev.mMouseWheel.wheel = wheel;
  ev.mMouseWheel.delta = delta;
  ev.mMouseWheel.posX = posX;
  ev.mMouseWheel.posY = posY;
  return ev;
}



WindowEventType WindowEvent::getType() const
{
  return mType;
}



const WindowEvent::SizeData& WindowEvent::getSizeData() const
{
  HOU_EXPECT(mType == WindowEventType::Resized);
  return mSize;
}



const WindowEvent::KeyData& WindowEvent::getKeyData() const
{
  HOU_EXPECT(mType == WindowEventType::KeyPressed
    || mType == WindowEventType::KeyReleased);
  return mKey;
}



const WindowEvent::TextData& WindowEvent::getTextData() const
{
  HOU_EXPECT(mType == WindowEventType::TextEntered);
  return mText;
}



const WindowEvent::MouseMoveData& WindowEvent::getMouseMoveData() const
{
  HOU_EXPECT(mType == WindowEventType::MouseMoved);
  return mMouseMove;
}



const WindowEvent::MouseButtonData& WindowEvent::getMouseButtonData() const
{
  HOU_EXPECT(mType == WindowEventType::MouseButtonPressed
    || mType == WindowEventType::MouseButtonReleased);
  return mMouseButton;
}



const WindowEvent::MouseWheelData& WindowEvent::getMouseWheelData() const
{
  HOU_EXPECT(mType == WindowEventType::MouseWheelMoved);
  return mMouseWheel;
}



WindowEvent::WindowEvent()
  : mType()
{}



bool operator==(const WindowEvent& l, const WindowEvent& r)
{
  if(l.getType() != r.getType())
  {
    return false;
  }
  switch(l.getType())
  {
    case WindowEventType::Resized:
      return l.getSizeData() == r.getSizeData();
    case WindowEventType::KeyPressed:
    case WindowEventType::KeyReleased:
      return l.getKeyData() == r.getKeyData();
    case WindowEventType::TextEntered:
      return l.getTextData() == r.getTextData();
    case WindowEventType::MouseMoved:
      return l.getMouseMoveData() == r.getMouseMoveData();
    case WindowEventType::MouseButtonPressed:
    case WindowEventType::MouseButtonReleased:
      return l.getMouseButtonData() == r.getMouseButtonData();
    case WindowEventType::MouseWheelMoved:
      return l.getMouseWheelData() == r.getMouseWheelData();
    case WindowEventType::Empty:
    case WindowEventType::Closed:
    case WindowEventType::FocusGained:
    case WindowEventType::FocusLost:
    case WindowEventType::MouseEntered:
    case WindowEventType::MouseLeft:
    default:
      return true;
  }
}



bool operator!=(const WindowEvent& l, const WindowEvent& r)
{
  return !(l == r);
}



bool operator==(const WindowEvent::SizeData& l, const WindowEvent::SizeData& r)
{
  return l.sizeX == r.sizeX && l.sizeY == r.sizeY;
}



bool operator==(const WindowEvent::KeyData& l, const WindowEvent::KeyData& r)
{
  return l.keyCode == r.keyCode && l.scanCode == r.scanCode
    && l.modifierKeys == r.modifierKeys;
}



bool operator==(const WindowEvent::TextData& l, const WindowEvent::TextData& r)
{
  return l.codePoint == r.codePoint;
}



bool operator==(const WindowEvent::MouseMoveData& l
  , const WindowEvent::MouseMoveData& r)
{
  return l.posX == r.posX && l.posY == r.posY;
}



bool operator==(const WindowEvent::MouseButtonData& l
  , const WindowEvent::MouseButtonData& r)
{
  return l.button == r.button && l.posX == r.posX && l.posY == r.posY;
}



bool operator==(const WindowEvent::MouseWheelData& l
  , const WindowEvent::MouseWheelData& r)
{
  return l.wheel == r.wheel && l.delta == r.delta && l.posX == r.posX
    && l.posY == r.posY;
}



bool operator!=(const WindowEvent::SizeData& l, const WindowEvent::SizeData& r)
{
  return !(l == r);
}



bool operator!=(const WindowEvent::KeyData& l, const WindowEvent::KeyData& r)
{
  return !(l == r);
}



bool operator!=(const WindowEvent::TextData& l, const WindowEvent::TextData& r)
{
  return !(l == r);
}



bool operator!=(const WindowEvent::MouseMoveData& l
  , const WindowEvent::MouseMoveData& r)
{
  return !(l == r);
}



bool operator!=(const WindowEvent::MouseButtonData& l
  , const WindowEvent::MouseButtonData& r)
{
  return !(l == r);
}



bool operator!=(const WindowEvent::MouseWheelData& l
  , const WindowEvent::MouseWheelData& r)
{
  return !(l == r);
}



std::ostream& operator<<(std::ostream& os, const WindowEvent& e)
{
  os << "{Type = " << e.getType() << ", Data = ";
  switch(e.getType())
  {
    case WindowEventType::Resized:
      os << e.getSizeData();
      break;
    case WindowEventType::KeyPressed:
    case WindowEventType::KeyReleased:
      os << e.getKeyData();
      break;
    case WindowEventType::TextEntered:
      os << e.getTextData();
      break;
    case WindowEventType::MouseMoved:
      os << e.getMouseMoveData();
      break;
    case WindowEventType::MouseButtonPressed:
    case WindowEventType::MouseButtonReleased:
      os << e.getMouseButtonData();
      break;
    case WindowEventType::MouseWheelMoved:
      os << e.getMouseWheelData();
      break;
    case WindowEventType::Empty:
    case WindowEventType::Closed:
    case WindowEventType::FocusGained:
    case WindowEventType::FocusLost:
    case WindowEventType::MouseEntered:
    case WindowEventType::MouseLeft:
        os << "{}";
    default:
      break;
  }
  return os << "}";
}



std::ostream& operator<<(std::ostream& os, const WindowEvent::SizeData& e)
{
  return os << "{Size = (" << e.sizeX << ", " << e.sizeY << ")}";
}



std::ostream& operator<<(std::ostream& os, const WindowEvent::KeyData& e)
{
  return os << "{KeyCode = " << e.keyCode
    << ", ScanCode = " << e.scanCode
    << ", ModifierKeys = " << e.modifierKeys << "}";
}



std::ostream& operator<<(std::ostream& os, const WindowEvent::TextData& e)
{
  class OutputFormatter
  {
  public:
    OutputFormatter(std::ostream& os)
      : mOldState(nullptr)
    {
      mOldState.copyfmt(os);
      os << std::setfill('0') << std::setw(8) << std::hex;
    }

    ~OutputFormatter()
    {
      std::cout.copyfmt(mOldState);
    }

  private:
    std::ios mOldState;
  };

  os << "{CodePoint = 0x";
  {
    OutputFormatter of(os);
    os << static_cast<uint32_t>(e.codePoint);
  }
  return os << "}";
}



std::ostream& operator<<(std::ostream& os, const WindowEvent::MouseMoveData& e)
{
  return os << "{Position = (" << e.posX << ", " << e.posY << ")}";
}



std::ostream& operator<<(std::ostream& os
  , const WindowEvent::MouseButtonData& e)
{
  return os << "{Button = " << e.button
    << ", Position = (" << e.posX << ", " << e.posY << ")}";
}



std::ostream& operator<<(std::ostream& os
  , const WindowEvent::MouseWheelData& e)
{
  return os << "{Wheel = " << e.wheel
    << ", Delta = " << e.delta
    << ", Position = (" << e.posX << ", " << e.posY << ")}";
}

}

