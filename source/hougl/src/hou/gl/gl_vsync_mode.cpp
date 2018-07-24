// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_vsync_mode.hpp"

#include "hou/gl/gl_missing_context_error.hpp"

#include "SDL_video.h"

#define VSYNC_MODE_CASE(vsm, os)                                               \
  case vsync_mode::vsm:                                                        \
    return (os) << #vsm



namespace hou
{

namespace gl
{

vsync_mode get_vsync_mode()
{
  return vsync_mode(SDL_GL_GetSwapInterval());
}



bool set_vsync_mode(vsync_mode mode)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return SDL_GL_SetSwapInterval(static_cast<int>(mode)) == 0;
}



std::ostream& operator<<(std::ostream& os, vsync_mode vsm)
{
  switch(vsm)
  {
    VSYNC_MODE_CASE(adaptive, os);
    VSYNC_MODE_CASE(disabled, os);
    VSYNC_MODE_CASE(enabled, os);
  }
  HOU_UNREACHABLE();
  return os;
}

}  // namespace gl

}  // namespace hou
