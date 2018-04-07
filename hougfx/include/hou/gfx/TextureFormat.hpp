// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_TEXTURE_FORMAT_HPP
#define HOU_SYS_TEXTURE_FORMAT_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/gl/OpenGl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the format of a texture. */
enum class TextureFormat : GLenum
{
  /** Single channel (red) format. */
  R = GL_R8,
  /** double channel (red-green) format. */
  RG = GL_RG8,
  /** Triple channel (red-green-blue) format. */
  RGB = GL_RGB8,
  /** Quadruple channel (red-green-blue-alpha) format. */
  RGBA = GL_RGBA8,
  /** 24 bit depth texture. */
  Depth = GL_DEPTH_COMPONENT24,
  /** 8 bit stencil texture. */
  Stencil = GL_STENCIL_INDEX8,
  /** 32 bit texture using 24 bit for depth and 8 for stencil. */
  DepthStencil = GL_DEPTH24_STENCIL8,
};

/** Writes a TextureFormat enum into a stream.
 *
 *  \param os the stream.
 *  \param format the TextureFormat enum.
 *  \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureFormat format);

}  // namespace hou

#endif
