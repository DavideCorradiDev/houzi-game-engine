// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_HPP
#define HOU_SYS_DISPLAY_HPP

#include "hou/sys/display_mode.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/std_set.hpp"
#include "hou/cor/std_string.hpp"

#include "hou/mth/rectangle.hpp"

#include <functional>



namespace hou
{

namespace display
{

/**
 * Gets the number of available displays.
 *
 * \return the numbero of available displays.
 */
HOU_SYS_API uint get_count();

/**
 * Gets the name of the specified display.
 *
 * \param display_idx the display index.
 * Must be lower than get_count().
 *
 * \throws hou::platform_error in case display_idx >= get_size() or of other
 * errors.
 *
 * \return the name of the specified display.
 */
HOU_SYS_API std::string get_name(uint display_idx);

/**
 * Gets the bounds of the specified display.
 *
 * \param display_idx the display index.
 * Must be lower than get_count().
 *
 * \throws hou::platform_error in case display_idx >= get_size() or of other
 * errors.
 *
 * \return the bounds of the specified display.
 */
HOU_SYS_API recti get_bounds(uint display_idx);

/**
 * Gets the bounds of the usable area of the specified display.
 *
 * \param display_idx the display index.
 * Must be lower than get_count().
 *
 * \throws hou::platform_error in case display_idx >= get_size() or of other
 * errors.
 *
 * \return the bounds of the usable area of the specified display.
 */
HOU_SYS_API recti get_usable_bounds(uint display_idx);

/**
 * Gets the current display mode of the specified display.
 *
 * \param display_idx the display index.
 * Must be lower than get_count().
 *
 * \throws hou::platform_error in case display_idx >= get_size() or of other
 * errors.
 *
 * \return the current display mode of the specified display.
 */
HOU_SYS_API mode get_current_mode(uint display_idx);

/**
 * Gets a list of the supported video modes of the specified display.
 *
 * \param display_idx the display index.
 * Must be lower than get_count().
 *
 * \throws hou::platform_error in case display_idx >= get_size() or of other
 * errors.
 *
 * \return a list of the supported video modes of the specified display.
 */
HOU_SYS_API std::set<mode> get_supported_modes(uint display_idx);

/**
 * Gets the supported display mode which is closest to the one provided.
 *
 * \param display_idx the display index.
 * Must be lower than get_count().
 *
 * \param mode the desired mode.
 *
 * \throws hou::platform_error in case display_idx >= get_size() or of other
 * errors.
 *
 * \return the supported display mode which is closest to the one provided.
 */
HOU_SYS_API mode get_closest_supported_mode(uint display_idx, const mode& mode);

/**
 * Gets the name of the current video driver.
 *
 * \return the name of the current video driver.
 */
HOU_SYS_API std::string get_current_video_driver();

/**
 * Gets a list of the names of the available video drivers.
 *
 * \return a list of the names of the available video drivers.
 */
HOU_SYS_API std::set<std::string> get_available_video_drivers();

}  // namespace display

}  // namespace hou

#endif
