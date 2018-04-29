// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_BUFFER_TARGET_HPP
#define HOU_GFX_VERTEX_BUFFER_TARGET_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

enum class vertex_buffer_target : GLenum
{
  array_buffer = GL_ARRAY_BUFFER,
  element_array_buffer = GL_ELEMENT_ARRAY_BUFFER,
};

HOU_GFX_API std::ostream& operator<<(std::ostream& os, vertex_buffer_target vbt);

}

#endif 

