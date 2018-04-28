// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXTURE_FORMAT_HPP
#define HOU_SYS_TEXTURE_FORMAT_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

/** Represents the ph_pixel format of a texture. */
enum class TextureFormat : GLenum
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
  Depth = GL_DEPTH_COMPONENT24,
  /** 8 bit stencil texture. */
  Stencil = GL_STENCIL_INDEX8,
  /** 32 bit texture using 24 bit for depth and 8 for stencil. */
  DepthStencil = GL_DEPTH24_STENCIL8,
};

/** Writes a TextureFormat enum into a ph_stream.
 *
 * \param os the ph_stream.
 * \param format the TextureFormat enum.
 * \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureFormat format);

}  // namespace hou

#endif
