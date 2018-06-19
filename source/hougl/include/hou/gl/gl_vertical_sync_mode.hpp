// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_VERTICAL_SYNC_MODE_HPP
#define HOU_GL_VERTICAL_SYNC_MODE_HPP

#include "hou/gl/gl_config.hpp"

#include <iostream>



namespace hou
{

namespace gl
{

/**
 * Represents the vertical sync mode.
 */
enum class vertical_sync_mode : int
{
  /**
   * Vertical sync is enabled only if the frame rate is higher than the sync
   * rate.
   */
  adaptive = -1,

  /**
   * Disabled.
   */
  disabled = 0,

  /**
   * Enabled.
   */
  enabled = 1,
};

/**
 * Gets the current vertical sync mode.
 *
 * \return the current vertical sync mode.
 */
HOU_GL_API vertical_sync_mode get_vertical_sync_mode();

/**
 * Sets the current vertical sync mode.
 *
 * \param mode the vertical sync mode.
 */
HOU_GL_API bool set_vertical_sync_mode(vertical_sync_mode mode);

/**
 * Writes a vertical_sync_mode enum into a stream.
 *
 * \param os the stream.
 *
 * \param vsm the vertical_sync_mode enum.
 *
 * \return a reference to the stream.
 */
HOU_GL_API std::ostream& operator<<(std::ostream& os, vertical_sync_mode vsm);

}  // namespace gl

}  // namespace hou

#endif
