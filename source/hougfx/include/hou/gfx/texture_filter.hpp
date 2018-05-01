// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_FILTER_HPP
#define HOU_GFX_TEXTURE_FILTER_HPP

#include "hou/gfx/gfx_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the texture filter type. */
enum class texture_filter
{
  /** Nearest filter.
   *  No interpolation performed.
   */
  nearest,
  /** Linear filter.
   *  Linear interpolation between mip-map levels.
   */
  linear,
  /** Bilinear filter.
   *  Linear interpolation within each mip-map level.
   */
  bilinear,
  /** Trilinear filter.
   *  Linear interpolation within each mip-map level and between mip-map levels.
   */
  trilinear,
};

/** Writes a texture_filter enum into a stream.
 *
 * \param os the stream.
 *
 * \param tf the texture_filter enum.
 *
 * \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, texture_filter tf);

}  // namespace hou

#endif
