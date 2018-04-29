// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/framebuffer_blit_filter.hpp"

#define FRAME_BUFFER_BLIT_FILTER_CASE(fbbf, os) \
  case framebuffer_blit_filter::fbbf:            \
    return (os) << #fbbf



namespace hou
{

std::ostream& operator<<(std::ostream& os, framebuffer_blit_filter fbbf)
{
  switch(fbbf)
  {
    FRAME_BUFFER_BLIT_FILTER_CASE(nearest, os);
    FRAME_BUFFER_BLIT_FILTER_CASE(linear, os);
  default:
    return os;
  }
}

}  // namespace hou
