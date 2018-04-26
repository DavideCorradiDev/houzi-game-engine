// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_EVENT_HPP
#define HOU_SYS_WINDOW_EVENT_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/KeyCode.hpp"
#include "hou/sys/ModifierKeys.hpp"
#include "hou/sys/MouseButton.hpp"
#include "hou/sys/MouseWheel.hpp"
#include "hou/sys/ScanCode.hpp"
#include "hou/sys/WindowEventType.hpp"

#include "hou/cor/BasicTypes.hpp"



namespace hou
{

/** Class representing a Window event.
 *
 */
class HOU_SYS_API WindowEvent
{
public:
  /** Struct containing data for window resized events. */
  struct SizeData
  {
    /** The new size on the x axis. */
    uint sizeX;
    /** The new size on the y axis. */
    uint sizeY;
  };

  /** Struct containing data for key pressed and key released events. */
  struct KeyData
  {
    /** The key code corresponding to the relevant key. */
    KeyCode keyCode;
    /** The scan code corresponding to the relevant key. */
    ScanCode scanCode;
    /** Bitfield indicating what modifier keys were pressed. */
    ModifierKeys modifierKeys;
  };

  /** Struct containing data for text entered events. */
  struct TextData
  {
    /** The Unicode code point corresponding to the entered character. */
    char32_t codePoint;
  };

  /** Struct containing data for mouse moved events. */
  struct MouseMoveData
  {
    /** The position of the mouse cursor on the x axis. */
    int posX;
    /** The position of the mouse cursor on the y axis. */
    int posY;
  };

  /** Struct containing data for mouse button pressed and released events. */
  struct MouseButtonData
  {
    /** The relevant mouse button. */
    MouseButton button;
    /** The position of the mouse cursor on the x axis. */
    int posX;
    /** The position of the mouse cursor on the y axis. */
    int posY;
  };

  /** Struct containing data for mouse wheel events. */
  struct MouseWheelData
  {
    /** The relevant mouse wheel. */
    MouseWheel wheel;
    /** The delta of the mouse wheel position. */
    int delta;
    /** The position of the mouse cursor on the x axis. */
    int posX;
    /** The position of the mouse cursor on the y axis. */
    int posY;
  };

public:
  /** Creates an empty window event.
   *
   *  \return the window event.
   */
  static WindowEvent empty();

  /** Creates a window closed event.
   *
   *  \return the window event.
   */
  static WindowEvent closed();

  /** Creates a window focus gained event.
   *
   *  \return the window event.
   */
  static WindowEvent focusGained();

  /** Creates a window focus lost event.
   *
   *  \return the window event.
   */
  static WindowEvent focusLost();

  /** Creates a mouse entered window event.
   *
   *  \return the window event.
   */
  static WindowEvent mouseEntered();

  /** Creates a mouse left window event.
   *
   *  \return the window event.
   */
  static WindowEvent mouseLeft();

  /** Creates a window resized lost event.
   *
   *  \param sizeX the x size after the resizing.
   *  \param sizeY the y size after the resizing.
   *  \return the window event.
   */
  static WindowEvent resized(uint sizeX, uint sizeY);

  /** Creates a key pressed window event.
   *
   *  \param kc the key code.
   *  \param sc the scan code.
   *  \param modKeys a bitfield indicating what modifier keys were pressed.
   *  \return the window event.
   */
  static WindowEvent keyPressed(KeyCode kc, ScanCode sc, ModifierKeys modKeys);

  /** Creates a key released window event.
   *
   *  \param kc the key code.
   *  \param sc the scan code.
   *  \param modKeys a bitfield indicating what modifier keys were pressed.
   *  \return the window event.
   */
  static WindowEvent keyReleased(KeyCode kc, ScanCode sc, ModifierKeys modKeys);

  /** Creates a text entered window event.
   *
   *  \param codePoint the Unicode code point of the entere character.
   *  \return the window event.
   */
  static WindowEvent textEntered(char32_t codePoint);

  /** Creates a mouse moved window event.
   *
   *  \param posX the position of the cursor on the x axis.
   *  \param posY the position of the cursor on the y axis.
   *  \return the window event.
   */
  static WindowEvent mouseMoved(int posX, int posY);

  /** Creates a mouse button pressed window event.
   *
   *  \param mb the mouse button.
   *  \param posX the position of the cursor on the x axis.
   *  \param posY the position of the cursor on the y axis.
   *  \return the window event.
   */
  static WindowEvent mouseButtonPressed(MouseButton mb, int posX, int posY);

  /** Creates a mouse button released window event.
   *
   *  \param mb the mouse button.
   *  \param posX the position of the cursor on the x axis.
   *  \param posY the position of the cursor on the y axis.
   *  \return the window event.
   */
  static WindowEvent mouseButtonReleased(MouseButton mb, int posX, int posY);

  /** Creates a mouse wheel moved window event.
   *
   *  \param wheel the mouse wheel.
   *  \param delta the wheel position delta.
   *  \param posX the position of the cursor on the x axis.
   *  \param posY the position of the cursor on the y axis.
   *  \return the window event.
   */
  static WindowEvent mouseWheelMoved(MouseWheel wheel, int delta, int posX
    , int posY);

public:
  /** Retrieves the type of the window event.
   *
   *  \return the type of the window event.
   */
  WindowEventType getType() const;

  /** Returns the size data of this event.
   *
   *  Throws if the event is not of type Resized.
   *
   *  \return the event data.
   */
  const SizeData& getSizeData() const;

  /** Returns the key data of this event.
   *
   *  Throws if the event is not of type KeyPressed or KeyReleased.
   *
   *  \return the event data.
   */
  const KeyData& getKeyData() const;

  /** Returns the text data of this event.
   *
   *  Throws if the event is not of type TextEntered.
   *
   *  \return the event data.
   */
  const TextData& getTextData() const;

  /** Returns the mouse moved data of this event.
   *
   *  Throws if the event is not of type MouseMoved.
   *
   *  \return the event data.
   */
  const MouseMoveData& getMouseMoveData() const;

  /** Returns the mouse button data of this event.
   *
   *  Throws if the event is not of type MouseButtonPressed or MouseButtonReleased.
   *
   *  \return the event data.
   */
  const MouseButtonData& getMouseButtonData() const;

  /** Returns the mouse wheel moved data of this event.
   *
   *  Throws if the event is not of type MouseWheelMoved.
   *
   *  \return the event data.
   */
  const MouseWheelData& getMouseWheelData() const;

private:
  WindowEvent();

private:
  WindowEventType mType;
  union
  {
    SizeData mSize;
    KeyData mKey;
    TextData mText;
    MouseMoveData mMouseMove;
    MouseButtonData mMouseButton;
    MouseWheelData mMouseWheel;
  };
};

/** Checks if two WindowEvent objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const WindowEvent& lhs, const WindowEvent& rhs);

/** Checks if two SizeData objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const WindowEvent::SizeData& lhs
  , const WindowEvent::SizeData& rhs);

/** Checks if two KeyData objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const WindowEvent::KeyData& lhs
  , const WindowEvent::KeyData& rhs);

/** Checks if two TextData objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const WindowEvent::TextData& lhs
  , const WindowEvent::TextData& rhs);

/** Checks if two MouseMoveData objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const WindowEvent::MouseMoveData& lhs
  , const WindowEvent::MouseMoveData& rhs);

/** Checks if two MouseButtonData objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const WindowEvent::MouseButtonData& lhs
  , const WindowEvent::MouseButtonData& rhs);

/** Checks if two MouseWheelData objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const WindowEvent::MouseWheelData& lhs
  , const WindowEvent::MouseWheelData& rhs);

/** Checks if two WindowEvent objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const WindowEvent& lhs, const WindowEvent& rhs);

/** Checks if two SizeData objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const WindowEvent::SizeData& lhs
  , const WindowEvent::SizeData& rhs);

/** Checks if two KeyData objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const WindowEvent::KeyData& lhs
  , const WindowEvent::KeyData& rhs);

/** Checks if two TextData objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const WindowEvent::TextData& lhs
  , const WindowEvent::TextData& rhs);

/** Checks if two MouseMoveData objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const WindowEvent::MouseMoveData& lhs
  , const WindowEvent::MouseMoveData& rhs);

/** Checks if two MouseButtonData objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const WindowEvent::MouseButtonData& lhs
  , const WindowEvent::MouseButtonData& rhs);

/** Checks if two MouseWheelData objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const WindowEvent::MouseWheelData& lhs
  , const WindowEvent::MouseWheelData& rhs);

/** Writes a WindowEvent object into a stream.
 *
 *  \param os the stream.
 *  \param e the WindowEvent object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const WindowEvent& e);

/** Writes a SizeData object into a stream.
 *
 *  \param os the stream.
 *  \param e the SizeData object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const WindowEvent::SizeData& e);

/** Writes a KeyData object into a stream.
 *
 *  \param os the stream.
 *  \param e the KeyData object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const WindowEvent::KeyData& e);

/** Writes a TextData object into a stream.
 *
 *  \param os the stream.
 *  \param e the TextData object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const WindowEvent::TextData& e);

/** Writes a MouseMoveData object into a stream.
 *
 *  \param os the stream.
 *  \param e the MouseMoveData object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const WindowEvent::MouseMoveData& e);

/** Writes a MouseButtonData object into a stream.
 *
 *  \param os the stream.
 *  \param e the MouseButtonData object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const WindowEvent::MouseButtonData& e);

/** Writes a MouseWheelData object into a stream.
 *
 *  \param os the stream.
 *  \param e the MouseWheelData object.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const WindowEvent::MouseWheelData& e);

}

#endif

