// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GFX_ERROR_HPP
#define HOU_GFX_GFX_ERROR_HPP

#include "hou/gfx/gfx_export.hpp"

#include <string>



namespace hou
{

/** Graphics module error codes. */
enum class gfx_error
{
  font_load_face,
};

/** Retrieves the message string associated to a graphics module error code.
 *
 *  \param ec the error code.
 */
HOU_GFX_API std::string get_text(gfx_error ec);

}  // namespace hou

#endif
