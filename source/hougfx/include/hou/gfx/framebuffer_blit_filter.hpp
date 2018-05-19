// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_BLIT_FILTER_HPP
#define HOU_GFX_FRAME_BUFFER_BLIT_FILTER_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/open_gl.hpp"

#include <iostream>



namespace hou
{

/** Specifies how to filter when blitting a framebuffer onto another.
 */
enum class framebuffer_blit_filter : GLenum
{
  /** Do not filter. */
  nearest = GL_NEAREST,
  /** linear interpolation filter. */
  linear = GL_LINEAR,
};

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param fbbf the framebuffer_blit_filter enum.
 *
 * \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(
  std::ostream& os, framebuffer_blit_filter fbbf);

}  // namespace hou

#endif
