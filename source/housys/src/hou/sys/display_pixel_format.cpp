// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_pixel_format.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"

#include "hou/cor/exception.hpp"

#define PIXEL_FORMAT_CASE(format, os) \
  case pixel_format::format: \
    return (os) << #format



namespace hou
{

namespace display
{

std::ostream& operator<<(std::ostream& os, const pixel_format& pf)
{
  switch(pf)
  {
    PIXEL_FORMAT_CASE(unknown, os);
    PIXEL_FORMAT_CASE(index1lsb, os);
    PIXEL_FORMAT_CASE(index1msb, os);
    PIXEL_FORMAT_CASE(index4lsb, os);
    PIXEL_FORMAT_CASE(index4msb, os);
    PIXEL_FORMAT_CASE(index8, os);
    PIXEL_FORMAT_CASE(rgb332, os);
    PIXEL_FORMAT_CASE(rgb444, os);
    PIXEL_FORMAT_CASE(rgb555, os);
    PIXEL_FORMAT_CASE(bgr555, os);
    PIXEL_FORMAT_CASE(argb4444, os);
    PIXEL_FORMAT_CASE(rgba4444, os);
    PIXEL_FORMAT_CASE(abgr4444, os);
    PIXEL_FORMAT_CASE(bgra4444, os);
    PIXEL_FORMAT_CASE(argb1555, os);
    PIXEL_FORMAT_CASE(rgba5551, os);
    PIXEL_FORMAT_CASE(abgr1555, os);
    PIXEL_FORMAT_CASE(bgra5551, os);
    PIXEL_FORMAT_CASE(rgb565, os);
    PIXEL_FORMAT_CASE(bgr565, os);
    PIXEL_FORMAT_CASE(rgb24, os);
    PIXEL_FORMAT_CASE(bgr24, os);
    PIXEL_FORMAT_CASE(rgb888, os);
    PIXEL_FORMAT_CASE(rgbx8888, os);
    PIXEL_FORMAT_CASE(bgr888, os);
    PIXEL_FORMAT_CASE(bgrx8888, os);
    PIXEL_FORMAT_CASE(argb8888, os);
    PIXEL_FORMAT_CASE(rgba8888, os);
    PIXEL_FORMAT_CASE(abgr8888, os);
    PIXEL_FORMAT_CASE(bgra8888, os);
    PIXEL_FORMAT_CASE(argb2101010, os);
    PIXEL_FORMAT_CASE(yv12, os);
    PIXEL_FORMAT_CASE(iyuv, os);
    PIXEL_FORMAT_CASE(yuy2, os);
    PIXEL_FORMAT_CASE(uyvy, os);
    PIXEL_FORMAT_CASE(yvyu, os);
    PIXEL_FORMAT_CASE(nv12, os);
    PIXEL_FORMAT_CASE(nv21, os);
  }
  HOU_UNREACHABLE();
  return os;
}

}  // namespace display

}  // namespace hou
