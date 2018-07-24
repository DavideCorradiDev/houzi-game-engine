// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GRAPHICS_STATE_HPP
#define HOU_GFX_GRAPHICS_STATE_HPP

#include "hou/gfx/gfx_config.hpp"

#include "hou/gfx/blending_factor.hpp"
#include "hou/gfx/blending_equation.hpp"

#include "hou/gl/gl_vsync_mode.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

/** Vertical sync mode enumration. */
using vsync_mode = gl::vsync_mode;

/** Alias for gl::get_vsync_mode. */
using gl::get_vsync_mode;

/**
 * Checks if multisampling is enabled.
 *
 * Multisampling is enabled by default.
 *
 * \return true if multisampling is enabled.
 */
bool is_multisampling_enabled();

/**
 * Sets if multisampling is enabled.
 *
 * \param value true to activate multisampling, false to deactivate it.
 */
void set_multisampling_enabled(bool value);

/**
 * Checks if blending is enabled.
 *
 * Blending is enabled by default.
 *
 * \return true if blending is enabled.
 */
bool is_blending_enabled();

/**
 * Sets if blending is enabled.
 *
 * \param value true to activate blending, false to deactivate it.
 */
void set_blending_enabled(bool value);

/**
 * Gets the source blending factor.
 *
 * The default value is blending_factor::src_alpha.
 *
 * \return the source blending factor.
 */
blending_factor get_source_blending_factor();

/**
 * Sets the source blending factor.
 *
 * \param f the factor.
 */
void set_source_blending_factor(blending_factor f);

/**
 * Gets the destination blending factor.
 *
 * The default value is blending_factor::one_minus_src_alpha.
 *
 * \return the destination blending factor.
 */
blending_factor get_destination_blending_factor();

/**
 * Sets the destination blending factor.
 *
 * \param f the factor.
 */
void set_destination_blending_factor(blending_factor f);

/**
 * Gets the current blending equation.
 *
 * The default value is blending_equation::add.
 *
 * \return the current blending equation.
 */
blending_equation get_blending_equation();

/**
 * Sets the current blending equation.
 *
 * \param eq the blending equation.
 */
void set_blending_equation(blending_equation eq);

/**
 * Gets the current blending color.
 *
 * The default value is color::transparent().
 *
 * \return the current blending color.
 */
color get_blending_color();

/**
 * Sets the current blending color.
 *
 * \param c the color.
 */
void set_blending_color(const color& c);

}  // namespace hou

#endif
