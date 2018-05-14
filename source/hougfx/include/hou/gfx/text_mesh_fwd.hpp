// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_MESH_FWD_HPP
#define HOU_GFX_TEXT_MESH_FWD_HPP

#include "hou/gfx/gfx_config.hpp"



namespace hou
{

class text_vertex;

template <typename vertex>
class mesh_t;

/** mesh of text_vertex.
 *
 *  Used to represent 2d text.
 */
using text_mesh = mesh_t<text_vertex>;

}  // namespace hou

#endif

