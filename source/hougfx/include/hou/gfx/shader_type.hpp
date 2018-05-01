// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_TYPE_HPP
#define HOU_GFX_SHADER_TYPE_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

enum class shader_type : GLenum
{
  // compute = GL_COMPUTE_SHADER,
  fragment = GL_FRAGMENT_SHADER,
  geometry = GL_GEOMETRY_SHADER,
  // tess_control = GL_TESS_CONTROL_SHADER,
  // tess_evaluation = GL_TESS_EVALUATION_SHADER,
  vertex = GL_VERTEX_SHADER,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, shader_type st);

}  // namespace hou

#endif
