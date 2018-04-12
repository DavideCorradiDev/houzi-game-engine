// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_MESH_2_FWD_HPP
#define HOU_GFX_MESH_2_FWD_HPP

#include "hou/gfx/GfxExport.hpp"



namespace hou
{

template <typename VertexType>
class MeshT;

class TextVertex;

using TextMesh = MeshT<TextVertex>;

}  // namespace hou

#endif
