// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_BLIT_FILTER_HPP
#define HOU_GFX_FRAME_BUFFER_BLIT_FILTER_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Specifies how to filter when blitting a framebuffer onto another.
 */
enum class FrameBufferBlitFilter : GLenum
{
  /** Do not filter. */
  Nearest = GL_NEAREST,
  /** Linear interpolation filter. */
  Linear = GL_LINEAR,
};

HOU_GFX_API std::ostream& operator<<(
  std::ostream& os, FrameBufferBlitFilter fbbf);

}  // namespace hou

#endif
