// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_FWD_HPP
#define HOU_GFX_SHADER_FWD_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gfx/ShaderType.hpp"



namespace hou
{

class Shader;

template <ShaderType type>
class ShaderTemplate;

using VertexShader = ShaderTemplate<ShaderType::Vertex>;
using FragmentShader = ShaderTemplate<ShaderType::Fragment>;
using GeometryShader = ShaderTemplate<ShaderType::Geometry>;

}  // namespace hou


#endif
