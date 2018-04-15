// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_TARGET_HPP
#define HOU_GFX_FRAME_BUFFER_TARGET_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

enum class FrameBufferTarget : GLenum
{
  Draw = GL_DRAW_FRAMEBUFFER,
  Read = GL_READ_FRAMEBUFFER,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, FrameBufferTarget fbt);

}  // namespace hou

#endif
