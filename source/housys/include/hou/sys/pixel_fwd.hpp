// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_PIXEL_FWD_HPP
#define HOU_SYS_PIXEL_FWD_HPP

#include "hou/sys/pixel_format.hpp"

#include "hou/sys/sys_config.hpp"



namespace hou
{

template <pixel_format format>
class pixel;

/** Single channel pixel. */
using pixel_r = pixel<pixel_format::r>;

/** Two channels pixel. */
using pixel_rg = pixel<pixel_format::rg>;

/** Three channels pixel. */
using pixel_rgb = pixel<pixel_format::rgb>;

/** Four channels pixel. */
using pixel_rgba = pixel<pixel_format::rgba>;

}  // namespace hou

#endif
