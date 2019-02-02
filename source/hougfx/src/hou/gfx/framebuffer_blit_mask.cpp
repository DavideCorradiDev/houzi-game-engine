// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/framebuffer_blit_mask.hpp"

#include "hou/cor/core_functions.hpp"

#define FRAMEBUFFER_BLIT_MASK_CASE(fbbm, os)                                   \
  case framebuffer_blit_mask::fbbm:                                            \
    (os) << #fbbm;                                                             \
    break



namespace hou
{

namespace
{

void printer(std::ostream& os, framebuffer_blit_mask fbbm)
{
  switch(fbbm)
  {
    FRAMEBUFFER_BLIT_MASK_CASE(none, os);
    FRAMEBUFFER_BLIT_MASK_CASE(color, os);
    FRAMEBUFFER_BLIT_MASK_CASE(depth, os);
    FRAMEBUFFER_BLIT_MASK_CASE(stencil, os);
    case framebuffer_blit_mask::all:
    default:
      STREAM_VALUE(os, framebuffer_blit_mask, fbbm);
  }
}

}

std::ostream& operator<<(std::ostream& os, framebuffer_blit_mask fbbm)
{
  return stream_bitfield<framebuffer_blit_mask>(os, fbbm, printer);
}

}  // namespace hou
