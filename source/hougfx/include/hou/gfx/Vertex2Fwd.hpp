// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_2_FWD_HPP
#define HOU_GFX_VERTEX_2_FWD_HPP

#include "hou/gfx/gfx_export.hpp"



namespace hou
{

class Vertex2;

template <typename Vertex> class mesh_t;

/** mesh of Vertex2.
 *
 *  Used to represent 2d shapes such as rectangles, circles...
 */
using Mesh2 = mesh_t<Vertex2>;

}

#endif
