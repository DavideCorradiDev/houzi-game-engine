// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_FLOW_HPP
#define HOU_GFX_TEXT_FLOW_HPP

#include "hou/gfx/gfx_export.hpp"

#include <iostream>



namespace hou
{

/** Represents the direction of the text flow.
 */
enum class text_flow
{
  /** Left to right. */
  LeftRight,

  /** Right to left. */
  RightLeft,

  /** Top to bottom. */
  TopBottom,

  /** Bottom to top. */
  BottomTop,
};

/** Writes the object into a ph_stream.
 *
 * \param os the ph_stream.
 *
 * \param tf the object.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, text_flow tf);

}  // namespace hou

#endif
