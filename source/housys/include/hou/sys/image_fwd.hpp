// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_IMAGE_FWD_HPP
#define HOU_SYS_IMAGE_FWD_HPP

#include "hou/sys/pixel_format.hpp"

#include "hou/sys/sys_config.hpp"



namespace hou
{

template <size_t dimensions, pixel_format format>
class image;

/** One-dimensional image. */
template <pixel_format format>
using image1 = image<1u, format>;

/** Single channel, one-dimensional image. */
using image1_r = image1<pixel_format::r>;

/** Two channels, one-dimensional image. */
using image1_rg = image1<pixel_format::rg>;

/** Three channels, one-dimensional image. */
using image1_rgb = image1<pixel_format::rgb>;

/** Four channels, one-dimensional image. */
using image1_rgba = image1<pixel_format::rgba>;

/** Two-dimensional image. */
template <pixel_format format>
using image2 = image<2u, format>;

/** Single channel, two-dimensional image. */
using image2_r = image2<pixel_format::r>;

/** Two channels, two-dimensional image. */
using image2_rg = image2<pixel_format::rg>;

/** Three channels, two-dimensional image. */
using image2_rgb = image2<pixel_format::rgb>;

/** Four channels, two-dimensional image. */
using image2_rgba = image2<pixel_format::rgba>;

/** Three-dimensional image. */
template <pixel_format format>
using image3 = image<3u, format>;

/** Single channel, three-dimensional image. */
using image3_r = image3<pixel_format::r>;

/** Two channels, three-dimensional image. */
using image3_rg = image3<pixel_format::rg>;

/** Three channels, three-dimensional image. */
using image3_rgb = image3<pixel_format::rgb>;

/** Four channels, three-dimensional image. */
using image3_rgba = image3<pixel_format::rgba>;

}  // namespace hou

#endif
