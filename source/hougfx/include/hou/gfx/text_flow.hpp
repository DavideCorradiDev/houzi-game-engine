// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_TEXT_FLOW_HPP
#define HOU_GFX_TEXT_FLOW_HPP

#include "hou/gfx/gfx_config.hpp"

#include <iostream>



namespace hou
{

/** Represents the direction of the text flow.
 */
enum class text_flow
{
  /** Left to right. */
  left_right,

  /** Right to left. */
  right_left,

  /** Top to bottom. */
  top_bottom,

  /** Bottom to top. */
  bottom_top,
};

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param tf the object.
 *
 * \return a reference to os.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, text_flow tf);

}  // namespace hou

#endif
