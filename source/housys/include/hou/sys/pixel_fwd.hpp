// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_PIXEL_FWD_HPP
#define HOU_SYS_PIXEL_FWD_HPP

#include "hou/sys/pixel_format.hpp"

#include "hou/sys/sys_export.hpp"



namespace hou
{

template <pixel_format format>
class pixel_t;

using pixel_r = pixel_t<pixel_format::r>;
using pixel_rg = pixel_t<pixel_format::rg>;
using pixel_rgb = pixel_t<pixel_format::rgb>;
using pixel_rgba = pixel_t<pixel_format::rgba>;

}  // namespace hou

#endif
