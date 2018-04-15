// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_IMAGE_FWD_HPP
#define HOU_SYS_IMAGE_FWD_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/PixelFormat.hpp"



namespace hou
{

template <size_t dimensions, PixelFormat format>
  class Image;

template<PixelFormat format>
  using Image1 = Image<1u, format>;
using Image1R = Image1<PixelFormat::R>;
using Image1RG = Image1<PixelFormat::RG>;
using Image1RGB = Image1<PixelFormat::RGB>;
using Image1RGBA = Image1<PixelFormat::RGBA>;

template<PixelFormat format>
  using Image2 = Image<2u, format>;
using Image2R = Image2<PixelFormat::R>;
using Image2RG = Image2<PixelFormat::RG>;
using Image2RGB = Image2<PixelFormat::RGB>;
using Image2RGBA = Image2<PixelFormat::RGBA>;

template<PixelFormat format>
  using Image3 = Image<3u, format>;
using Image3R = Image3<PixelFormat::R>;
using Image3RG = Image3<PixelFormat::RG>;
using Image3RGB = Image3<PixelFormat::RGB>;
using Image3RGBA = Image3<PixelFormat::RGBA>;

}

#endif


