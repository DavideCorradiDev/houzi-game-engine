// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_SHADER_FWD_HPP
#define HOU_GFX_SHADER_FWD_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gfx/shader_type.hpp"



namespace hou
{

class shader;

template <shader_type type>
class shader_t;

/** Vertex shader. */
using vertex_shader = shader_t<shader_type::vertex>;

/** Fragment shader. */
using fragment_shader = shader_t<shader_type::fragment>;

/** Geometry shader. */
using geometry_shader = shader_t<shader_type::geometry>;

}  // namespace hou


#endif
