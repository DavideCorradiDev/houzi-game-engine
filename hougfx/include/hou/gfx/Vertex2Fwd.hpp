// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_2_FWD_HPP
#define HOU_GFX_VERTEX_2_FWD_HPP

#include "hou/gfx/GfxExport.hpp"



namespace hou
{

class Vertex2;

template <typename Vertex> class MeshT;

/** Mesh of Vertex2.
 *
 *  Used to represent 2d shapes such as rectangles, circles...
 */
using Mesh2 = MeshT<Vertex2>;

}

#endif
