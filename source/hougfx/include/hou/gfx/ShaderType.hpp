// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_TYPE_HPP
#define HOU_GFX_SHADER_TYPE_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

enum class ShaderType : GLenum
{
  // Compute = GL_COMPUTE_SHADER,
  Fragment = GL_FRAGMENT_SHADER,
  Geometry = GL_GEOMETRY_SHADER,
  // TessControl = GL_TESS_CONTROL_SHADER,
  // TessEvaluation = GL_TESS_EVALUATION_SHADER,
  Vertex = GL_VERTEX_SHADER,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, ShaderType st);

}  // namespace hou

#endif
