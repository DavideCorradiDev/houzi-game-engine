// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CONTEXT_PROFILE_HPP
#define HOU_GL_GL_CONTEXT_PROFILE_HPP

#include "hou/gl/gl_config.hpp"

#include <iostream>



namespace hou
{

namespace gl
{

enum class context_profile
{
  compatibility,
  core,
  es,
};

HOU_GL_API std::ostream& operator<<(std::ostream& os, context_profile cp);

}  // namespace gl

}  // namespace hou

#endif
