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
using image1R = image1<pixel_format::r>;
using image1RG = image1<pixel_format::rg>;
using image1RGB = image1<pixel_format::rgb>;
using image1RGBA = image1<pixel_format::rgba>;

template <pixel_format format>
using image2 = image<2u, format>;
using image2R = image2<pixel_format::r>;
using image2RG = image2<pixel_format::rg>;
using image2RGB = image2<pixel_format::rgb>;
using image2RGBA = image2<pixel_format::rgba>;

template <pixel_format format>
using image3 = image<3u, format>;
using image3R = image3<pixel_format::r>;
using image3RG = image3<pixel_format::rg>;
using image3RGB = image3<pixel_format::rgb>;
using image3RGBA = image3<pixel_format::rgba>;

}  // namespace hou

#endif
