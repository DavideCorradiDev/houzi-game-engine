// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture_wrap_mode.hpp"

#include "hou/cor/core_functions.hpp"

#define TEXTURE_WRAP_MODE_CASE(twm, os) \
  case texture_wrap_mode::twm: \
    return (os) << #twm



namespace hou
{

std::ostream& operator<<(std::ostream& os, texture_wrap_mode twm)
{
  switch(twm)
  {
    TEXTURE_WRAP_MODE_CASE(clamp_to_edge, os);
    TEXTURE_WRAP_MODE_CASE(repeat, os);
    TEXTURE_WRAP_MODE_CASE(mirrored_repeat, os);
  }
  return STREAM_VALUE(os, texture_wrap_mode, twm);
}

}  // namespace hou
