// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXTURE_FILTER_HPP
#define HOU_GFX_TEXTURE_FILTER_HPP

#include "hou/gfx/gfx_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the ph_texture filter type. */
enum class texture_filter
{
  /** nearest filter.
   *  No interpolation performed.
   */
  nearest,
  /** linear filter.
   *  linear interpolation between mip-map levels.
   */
  linear,
  /** bilinear filter.
   *  linear interpolation within each mip-map level.
   */
  bilinear,
  /** trilinear filter.
   *  linear interpolation within each mip-map level and between mip-map levels.
   */
  trilinear,
};

/** Writes a texture_filter enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param tf the texture_filter enum.
 *  \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, texture_filter tf);

}  // namespace hou

#endif
