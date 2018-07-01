// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_FORMAT_HPP
#define HOU_SYS_DISPLAY_FORMAT_HPP

#include "hou/sys/sys_config.hpp"

#include "SDL_video.h"

#include <ostream>



namespace hou
{

/**
 * Represents a display format.
 */
enum class display_format : Uint32
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

/**
 * Represents the type of a display_format.
 */
enum class display_format_type : Uint32
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

/**
 * Represents the bit order in a bitmap display_format.
 */
enum class display_format_bitmap_order : Uint32
{
  none = SDL_BITMAPORDER_NONE,
  ev4321 = SDL_BITMAPORDER_4321,
  ev1234 = SDL_BITMAPORDER_1234,
};

/**
 * Represents the bit order in a packed display_format.
 */
enum class display_format_packed_order : Uint32
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

/**
 * Represents the bit order in an array display_format.
 */
enum class display_format_array_order : Uint32
{
  none = SDL_ARRAYORDER_NONE,
  rgb = SDL_ARRAYORDER_RGB,
  rgba = SDL_ARRAYORDER_RGBA,
  argb = SDL_ARRAYORDER_ARGB,
  bgr = SDL_ARRAYORDER_BGR,
  bgra = SDL_ARRAYORDER_BGRA,
  abgr = SDL_ARRAYORDER_ABGR,
};

/**
 * Represents the bit layout in a packed display_format.
 */
enum class display_format_packed_layout : Uint32
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

/**
 * Gets the number of bits per pixel for a given display_format.
 *
 * \param f the display_format.
 *
 * \return the bits per pixel of f.
 */
HOU_SYS_API uint get_bits_per_pixel(display_format f);

/**
 * Gets the number of bytes per pixel for a given display_format.
 *
 * \param f the display_format.
 *
 * \return the bytes per pixel of f.
 */
HOU_SYS_API uint get_bytes_per_pixel(display_format f);

/**
 * Gets the type of a given display_format.
 *
 * \param f the display_format.
 *
 * \return the type of f.
 */
HOU_SYS_API display_format_type get_type(display_format f);

/**
 * Gets the bit order for a bitmap type display_format.
 *
 * \param f the display_format.
 *
 * \return the bit order of f if f is a bitmap format, or
 * display_format_bitmap_order::none othewise.
 */
HOU_SYS_API display_format_bitmap_order get_bitmap_order(display_format f);

/**
 * Gets the bit order for a packed type display_format.
 *
 * \param f the display_format.
 *
 * \return the bit order of f if f is a packed format, or
 * display_format_packed_order::none othewise.
 */
HOU_SYS_API display_format_packed_order get_packed_order(display_format f);

/**
 * Gets the bit order for a array type display_format.
 *
 * \param f the display_format.
 *
 * \return the bit order of f if f is a array format, or
 * display_format_array_order::none othewise.
 */
HOU_SYS_API display_format_array_order get_array_order(display_format f);

/**
 * Gets the bit layout for a packed type display_format.
 *
 * \param f the display_format.
 *
 * \return the bit layout of f if f is a packed format, or
 * display_format_packed_layout::none othewise.
 */
HOU_SYS_API display_format_packed_layout get_packed_layout(display_format f);

/**
 * Checks if a display_format is indexed.
 *
 * \param f the display_format;
 *
 * \return true if f is indexed.
 */
HOU_SYS_API bool is_indexed(display_format f);

/**
 * Checks if a display_format has alpha bits.
 *
 * \param f the display_format;
 *
 * \return true if f has alpha bits.
 */
HOU_SYS_API bool has_alpha(display_format f);

/**
 * Checks if a display_format is a FourCC format.
 *
 * \param f the display_format;
 *
 * \return true if f is a FourCC format.
 */
HOU_SYS_API bool is_fourcc(display_format f);

/**
 * Writes a display_format enum into a stream.
 *
 * \param os the output stream.
 *
 * \param f the display_format.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, display_format f);

/**
 * Writes a display_format_type enum into a stream.
 *
 * \param os the output stream.
 *
 * \param f the display_format_type.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, display_format_type f);

/**
 * Writes a display_format_bitmap_order enum into a stream.
 *
 * \param os the output stream.
 *
 * \param f the display_format_bitmap_order.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, display_format_bitmap_order f);

/**
 * Writes a display_format_packed_order enum into a stream.
 *
 * \param os the output stream.
 *
 * \param f the display_format_packed_order.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, display_format_packed_order f);

/**
 * Writes a display_format_array_order enum into a stream.
 *
 * \param os the output stream.
 *
 * \param f the display_format_array_order.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, display_format_array_order f);

/**
 * Writes a display_format_packed_layour enum into a stream.
 *
 * \param os the output stream.
 *
 * \param f the display_format_packed_layour.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(
  std::ostream& os, display_format_packed_layout f);

}  // namespace hou

#endif
