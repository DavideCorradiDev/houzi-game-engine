// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_HPP
#define HOU_SYS_WINDOW_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/sys/Image.hpp"
#include "hou/sys/WindowImpl.hpp"

#include <string>



namespace hou
{

class VideoMode;
class WindowEvent;

/** Class representing a Window.
 */
class HOU_SYS_API Window
  : public non_copyable
{
public:
  /** Creates a Window object.
   *
   *  The window client size corresponds to the resolution in videoMode.
   *  The window client is be positioned in the middle of the screen.
   *  The window uses the default system icon.
   *  The window is not visible.
   *  The window does not grab the mouse cursor.
   *  Key repeat is disabled for the window.
   *
   *  \param title the title of the Window.
   *  \param videoMode the video mode of the Window, specifying its client size and
   *  bytes per pixel.
   *  \param style the style of the Window.
   *  Only one Window can be fullscreen.
   *  If fullscreen mode is specified and videoMode is not a valid fullscreen
   *  VideoMode, an error will be thrown.
   */
  Window(const std::string& title, const VideoMode& videoMode
    , WindowStyle style);

  /** Move constructor.
   *
   *  \param other the other Window object.
   */
  Window(Window&& other);

  /** Destructor.
   */
  virtual ~Window() = 0;

  /** Gets the OS dependent window handle associated to this Window.
   *
   *  \return the OS dependent window handle.
   */
  WindowHandle getWindowHandle() const;

  /** Gets the unique identifier of this Window.
   *
   *  \return the unique identifier of this Window.
   */
  uint32_t getUid() const;

  /** Gets the title of this Window.
   *
   *  \return the title of this Window.
   */
  const std::string& getTitle() const;

  /** Sets the title of this window.
   *
   *  \param title the title.
   */
  void setTitle(const std::string& title);

  /** Gets the position of the Window frame.
   *
   *  The Window frame position is the top left corner of the Window, including
   *  the borders.
   *
   *  \return the position of the Window frame.
   */
  vec2i getFramePosition() const;

  /** Gets the size of the Window frame.
   *
   *  The Window frame size includes the borders.
   *
   *  \return the size of the Window frame.
   */
  vec2u getFrameSize() const;

  /** Sets the Window frame ph_rectangle.
   *
   *  The Window frame ph_rectangle includes the borders.
   *
   *  \param pos the Window frame position.
   *  \param size the window frame size.
   */
  virtual void setFrameRect(const vec2i& pos, const vec2u& size) = 0;

  /** Sets the position of the Window frame.
   *
   *  The Window frame position is the top left corner of the Window, including
   *  the borders
   *
   *  \param pos the position of the Window frame.
   */
  void setFramePosition(const vec2i& pos);

  /** Sets the size of the Window frame.
   *
   *  The Window frame size includes the borders
   *
   *  \param size the size of the Window frame.
   */
  void setFrameSize(const vec2u& size);

  /** Gets the position of the Window client.
   *
   *  The Window client position is the top left corner of the Window, not
   *  including the borders.
   *
   *  \return the position of the Window client.
   */
  vec2i getClientPosition() const;

  /** Gets the size of the Window client.
   *
   *  The Window client size does not include the borders.
   *
   *  \return the size of the Window client.
   */
  vec2u getClientSize() const;

  /** Sets the Window client ph_rectangle.
   *
   *  The Window client ph_rectangle does not include the borders.
   *
   *  \param pos the Window client position.
   *  \param size the Window client size.
   */
  virtual void setClientRect(const vec2i& pos, const vec2u& size) = 0;

  /** Sets the position of the Window client.
   *
   *  The Window client position is the top left corner of the Window, not
   *  including the borders.
   *
   *  \param pos the position of the Window client.
   */
  void setClientPosition(const vec2i& pos);

  /** Sets the size of the Window client.
   *
   *  The Window client size does not include the borders.
   *
   *  \param size the size of the Window client.
   */
  void setClientSize(const vec2u& size);

  /** Gets the number of bytes per pixel of this Window.
   *
   *  \return the number of bytes per pixel of this Window.
   */
  uint getBytesPerPixel() const;

  /** Gets the style of this Window.
   *
   *  \return the style of this Window.
   */
  WindowStyle getStyle() const;

  /** Gets the Window icon.
   *
   *  \return the Window icon if a custom icon was set, an empty Image if the
   *  system icon is being used.
   */
  const Image2RGBA& getIcon() const;

  /** Sets the Window icon.
   *
   *  \param icon the icon.
   */
  void setIcon(const Image2RGBA& icon);

  /** Resets the Window icon to the default system icon.
   */
  void setSystemIcon();

  /** Checks if the Window is visible.
   *
   *  \return true if the Window is visible.
   */
  bool isVisible() const;

  /** Sets if the Window is visible.
   *
   *  \param value whether the Window is visible.
   */
  void setVisible(bool value);

  /** Checks if the Window is grabbing the mouse cursor.
   *
   *  \return true if the Window is grabbing the mouse cursor.
   */
  bool isMouseCursorGrabbed() const;

  /** Sets if the Window is grabbing the mouse cursor.
   *
   *  \param value whether the Window is grabbing the mouse cursor.
   */
  void setMouseCursorGrabbed(bool value);

  /** Checks if key repeat is enabled for this Window.
   *
   *  \return true if key repeat is enabled for this Window.
   */
  bool isKeyRepeatEnabled() const;

  /** Sets if key repeat is enabled for this Windows.
   *
   *  \param value whether key repeat is enabled for this Window.
   */
  void setKeyRepeatEnabled(bool value);

  /** Checks if this Window currently has focus.
   *
   *  \return whether this Window currently has focus.
   */
  bool hasFocus() const;

  /** Requests focus for this Window.
   *
   *  Requesting focus does not guarantee that the focus is actually obtained.
   *  Check the return value to see if the request was successfull.
   *
   *  \return true if the focus request was successfull and this Window now has
   *  focus.
   */
  bool requestFocus() const;

  /** Checks if the event queue of this Window is empty.
   *
   *  This function does not automatically update the queue.
   *  Call updateEventQueue before to fill it with events coming from the OS.
   *
   *  \return true if the event queue of this Window is empty.
   */
  bool isEventQueueEmpty() const;

  /** Fills the event queue of this Window with events coming from the OS.
   */
  void updateEventQueue();

  /** Pops the front event in the queue of this Window.
   *
   *  This function does not automatically update the queue.
   *  Call updateEventQueue before to fill it with events coming from the OS.
   *  This function is not blocking.
   *  If the event queue is empty, an event of type Empty is returned.
   *
   *  \return the front event, or an event of type Empty if the queue is empty.
   */
  WindowEvent popEvent();

  /** Pushes an event into the back of the queu of this Window.
   *
   *  \param event the event to be pushed.
   */
  void pushEvent(const WindowEvent& event);

  /** Waits for the event queue of this Window to contain at least one event and
   *  pops it.
   *
   *  This function always updates the event queue, so a call to updateEventQueue
   *  is not necessary.
   *  This function is blocking, it will keep updating and checking the queue
   *  until an event is pushed.
   *  This function only pops the first event.
   *  It might be that multiple events have been inserted in the queue and
   *  therefore the queue might still be filled.
   *
   *  \return the front event.
   */
  WindowEvent waitEvent();

protected:
  /** Swaps the front and back buffers of the Window.
   *
   *  Throws if the Window has no valid buffers.
   *  Derived classes should make sure to only call this function when it is
   *  safe to do so.
   */
  void swapBuffers();

private:
  void reactToEvent(const WindowEvent& event);

private:
  prv::WindowImpl mImpl;
  uint32_t mUid;
  WindowStyle mStyle;
  uint mBytesPerPixel;
  std::string mTitle;
  Image2RGBA mIconImage;
};

}

#endif

