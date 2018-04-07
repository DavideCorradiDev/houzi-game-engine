// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_GFX_ERROR_HPP
#define HOU_GFX_GFX_ERROR_HPP

#include "hou/gfx/gfxExport.hpp"

#include <string>



namespace hou
{

/** Graphics module error codes. */
enum class GfxError
{
  FontLoadFace,
};

/** Retrieves the message string associated to a graphics module error code.
 *
 *  \param ec the error code.
 */
HOU_GFX_API std::string getText(GfxError ec);

}

#endif

