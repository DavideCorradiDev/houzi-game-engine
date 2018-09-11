// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXTURE_FORMAT_HPP
#define HOU_SYS_TEXTURE_FORMAT_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/sys/pixel_format.hpp"

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
  /** 32 bit texture using 24 bit for depth and 8 for stencil. */
  depth_stencil = GL_DEPTH24_STENCIL8,
};

/**
 * Writes a texture_format enum into a stream.
 *
 * \param os the stream.
 *
 * \param format the texture_format enum.
 *
 * \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, texture_format format);

HOU_GFX_API uint get_bytes_per_pixel(texture_format tf);

// TODO: remove the following two functions after the new texture class has been
// implemented.
//
/**
 * Gets a compatible pixel format associated to the texture format.
 *
 * \param tf the texture format.
 *
 * \return the compatible pixel format.
 */
HOU_GFX_API pixel_format get_associated_pixel_format(texture_format tf);

/**
 * Check if a pixel and texture formats are compatible with each other.
 *
 * \param tf the texture format.
 *
 * \param pf the pixel format.
 *
 * \return true if the two formats are compatible.
 */
HOU_GFX_API bool check_format_compatibility(texture_format tf, pixel_format pf);

}  // namespace hou

#endif
