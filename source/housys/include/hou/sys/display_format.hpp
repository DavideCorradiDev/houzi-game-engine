// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_FORMAT_HPP
#define HOU_SYS_DISPLAY_FORMAT_HPP

#include "hou/sys/sys_config.hpp"

#include "SDL2/SDL_video.h"

#include <ostream>



namespace hou
{

namespace display
{

enum class format : Uint32
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

enum class format_type : Uint32
{
  unknown = SDL_PIXELTYPE_UNKNOWN,
  index1 = SDL_PIXELTYPE_INDEX1,
  index4 = SDL_PIXELTYPE_INDEX4,
  index8 = SDL_PIXELTYPE_INDEX8,
  packed8 = SDL_PIXELTYPE_PACKED8,
  packed16 = SDL_PIXELTYPE_PACKED16,
  packed32 = SDL_PIXELTYPE_PACKED32,
  arrayu8 = SDL_PIXELTYPE_ARRAYU8,
  arrayu16 = SDL_PIXELTYPE_ARRAYU16,
  arrayu32 = SDL_PIXELTYPE_ARRAYU32,
  arrayf16 = SDL_PIXELTYPE_ARRAYF16,
  arrayf32 = SDL_PIXELTYPE_ARRAYF32,
};

enum class format_bitmap_order : Uint32
{
  none = SDL_BITMAPORDER_NONE,
  ev4321 = SDL_BITMAPORDER_4321,
  ev1234 = SDL_BITMAPORDER_1234,
};

enum class format_packed_order : Uint32
{
  none = SDL_PACKEDORDER_NONE,
  xrgb = SDL_PACKEDORDER_XRGB,
  rgbx = SDL_PACKEDORDER_RGBX,
  argb = SDL_PACKEDORDER_ARGB,
  rgba = SDL_PACKEDORDER_RGBA,
  xbgr = SDL_PACKEDORDER_XBGR,
  bgrx = SDL_PACKEDORDER_BGRX,
  abgr = SDL_PACKEDORDER_ABGR,
  bgra = SDL_PACKEDORDER_BGRA,
};

enum class format_array_order : Uint32
{
  none = SDL_ARRAYORDER_NONE,
  rgb = SDL_ARRAYORDER_RGB,
  rgba = SDL_ARRAYORDER_RGBA,
  argb = SDL_ARRAYORDER_ARGB,
  bgr = SDL_ARRAYORDER_BGR,
  bgra = SDL_ARRAYORDER_BGRA,
  abgr = SDL_ARRAYORDER_ABGR,
};

enum class format_packed_layout : Uint32
{
  none = SDL_PACKEDLAYOUT_NONE,
  ev332 = SDL_PACKEDLAYOUT_332,
  ev4444 = SDL_PACKEDLAYOUT_4444,
  ev1555 = SDL_PACKEDLAYOUT_1555,
  ev5551 = SDL_PACKEDLAYOUT_5551,
  ev565 = SDL_PACKEDLAYOUT_565,
  ev8888 = SDL_PACKEDLAYOUT_8888,
  ev2101010 = SDL_PACKEDLAYOUT_2101010,
  ev1010102 = SDL_PACKEDLAYOUT_1010102,
};

HOU_SYS_API uint get_bits_per_pixel(format f);
HOU_SYS_API uint get_bytes_per_pixel(format f);
HOU_SYS_API format_type get_type(format f);
HOU_SYS_API format_bitmap_order get_bitmap_order(format f);
HOU_SYS_API format_packed_order get_packed_order(format f);
HOU_SYS_API format_array_order get_array_order(format f);
HOU_SYS_API format_packed_layout get_packed_layout(format f);
HOU_SYS_API bool is_indexed(format f);
HOU_SYS_API bool has_alpha(format f);
HOU_SYS_API bool is_fourcc(format f);

HOU_SYS_API std::ostream& operator<<(std::ostream& os, format f);
HOU_SYS_API std::ostream& operator<<(std::ostream& os, format_type f);
HOU_SYS_API std::ostream& operator<<(std::ostream& os, format_bitmap_order f);
HOU_SYS_API std::ostream& operator<<(std::ostream& os, format_packed_order f);
HOU_SYS_API std::ostream& operator<<(std::ostream& os, format_array_order f);
HOU_SYS_API std::ostream& operator<<(std::ostream& os, format_packed_layout f);

}  // namespace display

}  // namespace hou

#endif
