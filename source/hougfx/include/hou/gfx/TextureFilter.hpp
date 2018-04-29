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
enum class TextureFilter
{
  /** nearest filter.
   *  No interpolation performed.
   */
  nearest,
  /** linear filter.
   *  linear interpolation between mip-map levels.
   */
  linear,
  /** Bilinear filter.
   *  linear interpolation within each mip-map level.
   */
  Bilinear,
  /** Trilinear filter.
   *  linear interpolation within each mip-map level and between mip-map levels.
   */
  Trilinear,
};

/** Writes a TextureFilter enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param tf the TextureFilter enum.
 *  \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureFilter tf);

}  // namespace hou

#endif
