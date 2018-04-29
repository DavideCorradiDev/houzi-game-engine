// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTICAL_SYNC_MODE_HPP
#define HOU_GFX_VERTICAL_SYNC_MODE_HPP

#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the vertical sync mode. */
enum class vertical_sync_mode : int
{
  /** disabled. */
  disabled = 0,
  /** enabled, */
  enabled = 1,
  /** vertical sync is enabled only if the frame rate is higher than the sync
   *  rate. */
  adaptive = -1,
};



/** Writes a vertical_sync_mode enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param vsm the vertical_sync_mode enum.
 *  \return a reference to the ph_stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, vertical_sync_mode vsm);

}

#endif

