// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXTURE_FORMAT_HPP
#define HOU_SYS_TEXTURE_FORMAT_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Represents the pixel format of a texture. */
enum class texture_format : GLenum
{
  /** Single channel (red) format. */
  r = GL_R8,
  /** double channel (red-green) format. */
  rg = GL_RG8,
  /** Triple channel (red-green-blue) format. */
  rgb = GL_RGB8,
  /** Quadruple channel (red-green-blue-alpha) format. */
  rgba = GL_RGBA8,
  /** 24 bit depth texture. */
  depth = GL_DEPTH_COMPONENT24,
  /** 8 bit stencil texture. */
  stencil = GL_STENCIL_INDEX8,
  /** 32 bit texture using 24 bit for depth and 8 for stencil. */
  depth_stencil = GL_DEPTH24_STENCIL8,
};

/** Writes a texture_format enum into a stream.
 *
 * \param os the stream.
 *
 * \param format the texture_format enum.
 *
 * \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, texture_format format);

}  // namespace hou

#endif
