// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_STATUS_HPP
#define HOU_GFX_FRAME_BUFFER_STATUS_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

enum class FrameBufferStatus : GLenum
{
  Complete = GL_FRAMEBUFFER_COMPLETE,
  Undefined = GL_FRAMEBUFFER_UNDEFINED,
  Unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
  IncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
  IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
  IncompleteDrawBuffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
  IncompleteReadBuffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
  IncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
  IncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, FrameBufferStatus fbs);

}  // namespace hou

#endif
