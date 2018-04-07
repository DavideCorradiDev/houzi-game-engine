// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_TEXTURE_FILTER_HPP
#define HOU_GFX_TEXTURE_FILTER_HPP

#include "hou/gfx/GfxExport.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the texture filter type. */
enum class TextureFilter
{
  /** Nearest filter.
   *  No interpolation performed.
   */
  Nearest,
  /** Linear filter.
   *  Linear interpolation between mip-map levels.
   */
  Linear,
  /** Bilinear filter.
   *  Linear interpolation within each mip-map level.
   */
  Bilinear,
  /** Trilinear filter.
   *  Linear interpolation within each mip-map level and between mip-map levels.
   */
  Trilinear,
};

/** Writes a TextureFilter enum into a stream.
 *
 *  \param os the stream.
 *  \param tf the TextureFilter enum.
 *  \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, TextureFilter tf);

}  // namespace hou

#endif
