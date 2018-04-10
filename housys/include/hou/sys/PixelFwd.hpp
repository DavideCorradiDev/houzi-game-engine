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
  class PixelT;

using PixelR = PixelT<PixelFormat::R>;
using PixelRG = PixelT<PixelFormat::RG>;
using PixelRGB = PixelT<PixelFormat::RGB>;
using PixelRGBA = PixelT<PixelFormat::RGBA>;

}

#endif

