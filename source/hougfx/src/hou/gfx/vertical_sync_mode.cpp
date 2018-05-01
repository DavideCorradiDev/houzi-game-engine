// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/vertical_sync_mode.hpp"

#define VERTICAL_SYNC_MODE_CASE(vsm, os) \
  case vertical_sync_mode::vsm: \
    return (os) << #vsm



namespace hou
{

std::ostream& operator<<(std::ostream& os, vertical_sync_mode vsm)
{
  switch(vsm)
  {
    VERTICAL_SYNC_MODE_CASE(disabled, os);
    VERTICAL_SYNC_MODE_CASE(enabled, os);
    VERTICAL_SYNC_MODE_CASE(adaptive, os);
    default:
      return os;
  }
}

}  // namespace hou
