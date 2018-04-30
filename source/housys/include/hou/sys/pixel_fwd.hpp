// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_PIXEL_FWD_HPP
#define HOU_SYS_PIXEL_FWD_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/sys/pixel_format.hpp"



namespace hou
{

template <pixel_format format>
class pixel_t;

using pixelr = pixel_t<pixel_format::r>;
using pixelrg = pixel_t<pixel_format::rg>;
using pixelrgb = pixel_t<pixel_format::rgb>;
using pixelrgba = pixel_t<pixel_format::rgba>;

}  // namespace hou

#endif
