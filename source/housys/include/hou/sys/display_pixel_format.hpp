// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_PIXEL_FORMAT_HPP
#define HOU_SYS_DISPLAY_PIXEL_FORMAT_HPP

#include "hou/sys/sys_config.hpp"

#include "SDL2/SDL_video.h"

#include <ostream>



namespace hou
{

namespace display
{

enum class pixel_format : Uint32
{
  unknown = SDL_PIXELFORMAT_UNKNOWN,
  index1lsb = SDL_PIXELFORMAT_INDEX1LSB,
  index1msb = SDL_PIXELFORMAT_INDEX1MSB,
  index4lsb = SDL_PIXELFORMAT_INDEX4LSB,
  index4msb = SDL_PIXELFORMAT_INDEX4MSB,
  index8 = SDL_PIXELFORMAT_INDEX8,
  rgb332 = SDL_PIXELFORMAT_RGB332,
  rgb444 = SDL_PIXELFORMAT_RGB444,
  rgb555 = SDL_PIXELFORMAT_RGB555,
  bgr555 = SDL_PIXELFORMAT_BGR555,
  argb4444 = SDL_PIXELFORMAT_ARGB4444,
  rgba4444 = SDL_PIXELFORMAT_RGBA4444,
  abgr4444 = SDL_PIXELFORMAT_ABGR4444,
  bgra4444 = SDL_PIXELFORMAT_BGRA4444,
  argb1555 = SDL_PIXELFORMAT_ARGB1555,
  rgba5551 = SDL_PIXELFORMAT_RGBA5551,
  abgr1555 = SDL_PIXELFORMAT_ABGR1555,
  bgra5551 = SDL_PIXELFORMAT_BGRA5551,
  rgb565 = SDL_PIXELFORMAT_RGB565,
  bgr565 = SDL_PIXELFORMAT_BGR565,
  rgb24 = SDL_PIXELFORMAT_RGB24,
  bgr24 = SDL_PIXELFORMAT_BGR24,
  rgb888 = SDL_PIXELFORMAT_RGB888,
  rgbx8888 = SDL_PIXELFORMAT_RGBX8888,
  bgr888 = SDL_PIXELFORMAT_BGR888,
  bgrx8888 = SDL_PIXELFORMAT_BGRX8888,
  argb8888 = SDL_PIXELFORMAT_ARGB8888,
  rgba8888 = SDL_PIXELFORMAT_RGBA8888,
  abgr8888 = SDL_PIXELFORMAT_ABGR8888,
  bgra8888 = SDL_PIXELFORMAT_BGRA8888,
  argb2101010 = SDL_PIXELFORMAT_ARGB2101010,
  yv12 = SDL_PIXELFORMAT_YV12,
  iyuv = SDL_PIXELFORMAT_IYUV,
  yuy2 = SDL_PIXELFORMAT_YUY2,
  uyvy = SDL_PIXELFORMAT_UYVY,
  yvyu = SDL_PIXELFORMAT_YVYU,
  nv12 = SDL_PIXELFORMAT_NV12,
  nv21 = SDL_PIXELFORMAT_NV21,
};

/** Writes a pixel_format object into a stream.
 *
 * \param os the stream.
 *
 * \param pf the pixel_format object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const pixel_format& pf);

}  // namespace display

}  // namespace hou

#endif
