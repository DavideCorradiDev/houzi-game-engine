// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_2_FWD_HPP
#define HOU_GFX_VERTEX_2_FWD_HPP

#include "hou/gfx/gfx_config.hpp"



namespace hou
{

class vertex2;

template <typename vertex>
class mesh_t;

/** mesh of vertex2.
 *
 *  Used to represent 2d shapes such as rectangles, circles...
 */
using mesh2 = mesh_t<vertex2>;

}  // namespace hou

#endif
