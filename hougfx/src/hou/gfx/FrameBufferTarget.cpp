// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/FrameBufferTarget.hpp"

#define FRAME_BUFFER_TARGET_CASE(fbt, os) \
  case FrameBufferTarget::fbt:            \
    return (os) << #fbt



namespace hou
{

std::ostream& operator<<(std::ostream& os, FrameBufferTarget fbt)
{
  switch(fbt)
  {
    FRAME_BUFFER_TARGET_CASE(Draw, os);
    FRAME_BUFFER_TARGET_CASE(Read, os);
  default:
    return os;
  }
}

}  // namespace hou
