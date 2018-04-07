// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_PIXEL_FWD_HPP
#define HOU_SYS_PIXEL_FWD_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/PixelFormat.hpp"



namespace hou
{

template <PixelFormat format>
  class Pixel;

using PixelR = Pixel<PixelFormat::R>;
using PixelRG = Pixel<PixelFormat::RG>;
using PixelRGB = Pixel<PixelFormat::RGB>;
using PixelRGBA = Pixel<PixelFormat::RGBA>;

}

#endif

