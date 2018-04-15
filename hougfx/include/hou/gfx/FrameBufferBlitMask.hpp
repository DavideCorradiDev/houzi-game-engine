// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_BLIT_MASK_HPP
#define HOU_GFX_FRAME_BUFFER_BLIT_MASK_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BitwiseOperators.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

enum class FrameBufferBlitMask : GLenum
{
  Color = GL_COLOR_BUFFER_BIT,
  Depth = GL_DEPTH_BUFFER_BIT,
  Stencil = GL_STENCIL_BUFFER_BIT,
};

}  // namespace hou

template <typename FrameBufferBlitMask>
struct EnableBitwiseOperators
{
  static constexpr bool enable = true;
};

#endif
