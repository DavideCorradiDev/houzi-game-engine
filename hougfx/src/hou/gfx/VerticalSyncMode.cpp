// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/VerticalSyncMode.hpp"

#define VERTICAL_SYNC_MODE_CASE(vsm, os) \
  case VerticalSyncMode::vsm: return (os) << #vsm



namespace hou
{

std::ostream& operator<<(std::ostream& os, VerticalSyncMode vsm)
{
  switch(vsm)
  {
    VERTICAL_SYNC_MODE_CASE(Disabled, os);
    VERTICAL_SYNC_MODE_CASE(Enabled, os);
    VERTICAL_SYNC_MODE_CASE(Adaptive, os);
    default: return os;
  }
}

}


