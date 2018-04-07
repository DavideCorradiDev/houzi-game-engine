// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GL_VERTICAL_SYNC_MODE_HPP
#define HOU_GL_VERTICAL_SYNC_MODE_HPP

#include "hou/cor/BasicTypes.hpp"



namespace hou
{

namespace gl
{

enum class VerticalSyncMode : int
{
  Disabled = 0,
  Enabled = 1,
  Adaptive = -1,
};

}

}

#endif

