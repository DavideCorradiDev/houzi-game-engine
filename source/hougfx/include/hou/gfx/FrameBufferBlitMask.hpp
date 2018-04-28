// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_BLIT_MASK_HPP
#define HOU_GFX_FRAME_BUFFER_BLIT_MASK_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/bitwise_operators.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

/** Bitfield used to specify which attachments to blit when blitting a
 *  framebuffer onto another one.
 */
enum class FrameBufferBlitMask : GLenum
{
  /** Don't blit any attachment. */
  None = 0,
  /** Blit the color attachment. */
  Color = GL_COLOR_BUFFER_BIT,
  /** Blit the depth attachment. */
  Depth = GL_DEPTH_BUFFER_BIT,
  /** Blit the stencil attachment. */
  Stencil = GL_STENCIL_BUFFER_BIT,
  /** Blit all attachments. */
  All = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
};

}  // namespace hou

template <>
struct hou::enable_bitwise_operators<hou::FrameBufferBlitMask>
{
  /** Enable bitwise operators. */
  static constexpr bool enable = true;
};

#endif
