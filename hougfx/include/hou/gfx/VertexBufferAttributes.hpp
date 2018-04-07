// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_VERTEX_BUFFER_ATTRIBUTES_HPP
#define HOU_GFX_VERTEX_BUFFER_ATTRIBUTES_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BitwiseOperators.hpp"

#include "hou/gl/OpenGl.hpp"



namespace hou
{

enum class VertexBufferAttributes : GLbitfield
{
  None = 0,
  DynamicStorage = GL_DYNAMIC_STORAGE_BIT,
  MapRead = GL_MAP_READ_BIT,
  MapWrite = GL_MAP_WRITE_BIT,
  MapPersistent = GL_MAP_PERSISTENT_BIT,
  MapCoherent = GL_MAP_COHERENT_BIT,
  ClientStorage = GL_CLIENT_STORAGE_BIT,
};



template <>
  struct EnableBitwiseOperators<VertexBufferAttributes>
{
  static constexpr bool enable = true;
};

}




#endif

