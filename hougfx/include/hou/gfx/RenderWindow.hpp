// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_WINDOW_HPP
#define HOU_GFX_RENDER_WINDOW_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/gfx/RenderSurface.hpp"
#include "hou/sys/Window.hpp"

#include "hou/gfx/VerticalSyncMode.hpp"



namespace hou
{

class VideoMode;

/** Window that can be used for rendering.
 */
class HOU_GFX_API RenderWindow
  : public Window
  , public RenderSurface
{
public:
  /** Creates a RenderTexutre with the desired title, size, sample count, and
   *  style.
   *
   *  \param title the window title.
   *  \param size the size.
   *  \param sampleCount the sample count.
   *  \param style the window style.
   */
  RenderWindow(const std::string& title, const Vec2u& size, uint sampleCount
    , WindowStyle style);

  /** Move constructor.
   *
   *  \param other the other RenderWindow.
   */
  RenderWindow(RenderWindow&& other);

  /** Destructor.
   */
  virtual ~RenderWindow();

  /** Displays what has been rendered onto the RenderWindow.
   */
  void display();

  /** Sets the vertical sync mode for the window.
   *
   *  \param mode the vertical sync mode.
   */
  void setVerticalSyncMode(VerticalSyncMode mode);

  // RenderSurface Overrides.
  void setSize(const Vec2u& size) override;
  Texture2 toTexture() const override;

  // Window overrides.
  void setFrameRect(const Recti& value) override;
  void setClientRect(const Recti& value) override;
};

}

#endif

