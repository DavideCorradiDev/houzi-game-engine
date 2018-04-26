// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTICAL_SYNC_MODE_HPP
#define HOU_GFX_VERTICAL_SYNC_MODE_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the vertical sync mode. */
enum class VerticalSyncMode : int
{
  /** Disabled. */
  Disabled = 0,
  /** Enabled, */
  Enabled = 1,
  /** Vertical sync is enabled only if the frame rate is higher than the sync
   *  rate. */
  Adaptive = -1,
};



/** Writes a VerticalSyncMode enum into a stream.
 *
 *  \param os the stream.
 *  \param vsm the VerticalSyncMode enum.
 *  \return a reference to the stream.
 */
HOU_GFX_API std::ostream& operator<<(std::ostream& os, VerticalSyncMode vsm);

}

#endif

