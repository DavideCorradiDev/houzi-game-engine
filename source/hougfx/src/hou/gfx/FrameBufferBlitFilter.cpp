// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/FrameBufferBlitFilter.hpp"

#define FRAME_BUFFER_BLIT_FILTER_CASE(fbbf, os) \
  case FrameBufferBlitFilter::fbbf:            \
    return (os) << #fbbf



namespace hou
{

std::ostream& operator<<(std::ostream& os, FrameBufferBlitFilter fbbf)
{
  switch(fbbf)
  {
    FRAME_BUFFER_BLIT_FILTER_CASE(Nearest, os);
    FRAME_BUFFER_BLIT_FILTER_CASE(Linear, os);
  default:
    return os;
  }
}

}  // namespace hou
