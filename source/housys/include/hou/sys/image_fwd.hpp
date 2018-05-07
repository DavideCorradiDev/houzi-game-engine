// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_IMAGE_FWD_HPP
#define HOU_SYS_IMAGE_FWD_HPP

#include "hou/sys/pixel_format.hpp"

#include "hou/sys/sys_export.hpp"



namespace hou
{

template <size_t dimensions, pixel_format format>
class image;

template <pixel_format format>
using image1 = image<1u, format>;
using image1_r = image1<pixel_format::r>;
using image1_rg = image1<pixel_format::rg>;
using image1_rgb = image1<pixel_format::rgb>;
using image1_rgba = image1<pixel_format::rgba>;

template <pixel_format format>
using image2 = image<2u, format>;
using image2_r = image2<pixel_format::r>;
using image2_rg = image2<pixel_format::rg>;
using image2_rgb = image2<pixel_format::rgb>;
using image2_rgba = image2<pixel_format::rgba>;

template <pixel_format format>
using image3 = image<3u, format>;
using image3_r = image3<pixel_format::r>;
using image3_rg = image3<pixel_format::rg>;
using image3_rgb = image3<pixel_format::rgb>;
using image3_rgba = image3<pixel_format::rgba>;

}  // namespace hou

#endif
