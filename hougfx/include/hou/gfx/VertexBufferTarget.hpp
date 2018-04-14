// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_VERTEX_BUFFER_TARGET_HPP
#define HOU_GFX_VERTEX_BUFFER_TARGET_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

enum class VertexBufferTarget : GLenum
{
  Array = GL_ARRAY_BUFFER,
  ElementArray = GL_ELEMENT_ARRAY_BUFFER,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, VertexBufferTarget vbt);

}

#endif 

