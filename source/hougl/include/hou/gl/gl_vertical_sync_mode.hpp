// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_VERTICAL_SYNC_MODE_HPP
#define HOU_GL_VERTICAL_SYNC_MODE_HPP

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace gl
{

enum class vertical_sync_mode : int
{
  disabled = 0,
  enabled = 1,
  adaptive = -1,
};
}

}  // namespace hou

#endif