// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_IMAGE_FWD_HPP
#define HOU_SYS_IMAGE_FWD_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/sys/pixel_format.hpp"



namespace hou
{

template <size_t dimensions, pixel_format format>
class image;

template <pixel_format format>
using image1 = image<1u, format>;
using image1r = image1<pixel_format::r>;
using image1rg = image1<pixel_format::rg>;
using image1rgb = image1<pixel_format::rgb>;
using image1rgba = image1<pixel_format::rgba>;

template <pixel_format format>
using image2 = image<2u, format>;
using image2r = image2<pixel_format::r>;
using image2rg = image2<pixel_format::rg>;
using image2rgb = image2<pixel_format::rgb>;
using image2rgba = image2<pixel_format::rgba>;

template <pixel_format format>
using image3 = image<3u, format>;
using image3r = image3<pixel_format::r>;
using image3rg = image3<pixel_format::rg>;
using image3rgb = image3<pixel_format::rgb>;
using image3rgba = image3<pixel_format::rgba>;

}  // namespace hou

#endif
