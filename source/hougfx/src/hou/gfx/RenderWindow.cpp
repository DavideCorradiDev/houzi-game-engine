// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/RenderWindow.hpp"

#include "hou/gl/GlFunctions.hpp"

#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/sys/video_mode.hpp"



// Implementation note:
// Drawing is never performed on the default framebuffer of the ph_window.
// When performing draw operations, they are performed on an off-screen
// render target.
// When calling display(), the off-screen target is blit onto the default
// backbuffer.
// Afterwards, the front and back buffer are swapped.
// This is done for the following reasons:
// - Multisampling behaviour is more consistent. Multisampling on the default
// target depends on driver settings an a lot of other things, multisampling
// on offline targets is more consistent.
// - OpenGL has the origin on the lower left corner. In order to have an origin
// on the top left corner, everything has to be mirrored. With the current
// implementation, the mirroring happens during the blit operation, while the
// ph_image on the off-screen target is not mirrored. No mirroring takes place
// until when the rendered ph_image is displayed to the user. IF not doing this,
// each single draw operation would have to be mirrored. Also, blitting would
// not perform correctly as the textures might be flipped multiple times.

namespace hou
{

RenderWindow::RenderWindow(const std::string& title, const vec2u& size,
  window_style style, uint sampleCount)
  : window(title, video_mode(size, GraphicContext::getRenderingColorByteCount()),
      style)
  , RenderSurface(size, sampleCount)
{}



RenderWindow::RenderWindow(RenderWindow&& other)
  : window(std::move(other))
  , RenderSurface(std::move(other))
{}



RenderWindow::~RenderWindow()
{}



void RenderWindow::display()
{
  gl::bindWindow(*this);
  setCurrentRenderSource(*this);
  setDefaultRenderTarget();

  vec2u size = get_size();
  gl::blitFramebuffer(0, 0, size.x(), size.y(), 0, size.y(), size.x(), 0,
    GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
    GL_NEAREST);

  swap_buffers();
}



void RenderWindow::setVerticalSyncMode(VerticalSyncMode mode)
{
  gl::bindWindow(*this);
  setDefaultRenderTarget();
  gl::setVerticalSyncMode(gl::VerticalSyncMode(static_cast<int>(mode)));
}



void RenderWindow::setSampleCount(uint sampleCount)
{
  buildFramebuffer(get_size(), sampleCount);
}



void RenderWindow::set_frame_rect(const vec2i& pos, const vec2u& size)
{
  window::set_frame_rect(pos, size);
  rebuildFramebufferIfNecessary();
}



void RenderWindow::set_client_rect(const vec2i& pos, const vec2u& size)
{
  window::set_client_rect(pos, size);
  rebuildFramebufferIfNecessary();
}



void RenderWindow::rebuildFramebufferIfNecessary()
{
  vec2u newSize = get_client_size();
  if(newSize.x() == 0u)
  {
    newSize.x() = 1u;
  }
  if(newSize.y() == 0u)
  {
    newSize.y() = 1u;
  }
  if(get_size() != newSize)
  {
    buildFramebuffer(newSize, getSampleCount());
  }
}

}  // namespace hou
