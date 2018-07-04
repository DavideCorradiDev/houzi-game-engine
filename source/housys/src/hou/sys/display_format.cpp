// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/display_format.hpp"

#include "hou/cor/exception.hpp"
#include "hou/cor/narrow_cast.hpp"

#define DISPLAY_FORMAT_CASE(df, os)                                            \
  case display_format::df:                                                     \
    return (os) << #df

#define DISPLAY_FORMAT_TYPE_CASE(dft, os)                                      \
  case display_format_type::dft:                                               \
    return (os) << #dft

#define DISPLAY_FORMAT_BITMAP_ORDER_CASE(dfo, os)                              \
  case display_format_bitmap_order::dfo:                                       \
    return (os) << #dfo

#define DISPLAY_FORMAT_PACKED_ORDER_CASE(dfo, os)                              \
  case display_format_packed_order::dfo:                                       \
    return (os) << #dfo

#define DISPLAY_FORMAT_ARRAY_ORDER_CASE(dfo, os)                               \
  case display_format_array_order::dfo:                                        \
    return (os) << #dfo

#define DISPLAY_FORMAT_PACKED_LAYOUT_CASE(dfl, os)                             \
  case display_format_packed_layout::dfl:                                      \
    return (os) << #dfl



namespace hou
{

uint get_bits_per_pixel(display_format f)
{
  return narrow_cast<uint>(SDL_BITSPERPIXEL(
    static_cast<std::underlying_type<display_format>::type>(f)));
}



uint get_bytes_per_pixel(display_format f)
{
  return narrow_cast<uint>(SDL_BYTESPERPIXEL(
    static_cast<std::underlying_type<display_format>::type>(f)));
}



display_format_type get_type(display_format f)
{
  return display_format_type(
    SDL_PIXELTYPE(static_cast<std::underlying_type<display_format>::type>(f)));
}



display_format_bitmap_order get_bitmap_order(display_format f)
{
  switch(get_type(f))
  {
    case display_format_type::index1:
    case display_format_type::index4:
    case display_format_type::index8:
      return display_format_bitmap_order(SDL_PIXELORDER(
        static_cast<std::underlying_type<display_format>::type>(f)));
    case display_format_type::packed8:
    case display_format_type::packed16:
    case display_format_type::packed32:
    case display_format_type::arrayu8:
    case display_format_type::arrayu16:
    case display_format_type::arrayu32:
    case display_format_type::arrayf16:
    case display_format_type::arrayf32:
    case display_format_type::unknown:
      return display_format_bitmap_order::none;
  }
  HOU_UNREACHABLE();
  return display_format_bitmap_order::none;
}



display_format_packed_order get_packed_order(display_format f)
{
  switch(get_type(f))
  {
    case display_format_type::packed8:
    case display_format_type::packed16:
    case display_format_type::packed32:
      return display_format_packed_order(SDL_PIXELORDER(
        static_cast<std::underlying_type<display_format>::type>(f)));
    case display_format_type::index1:
    case display_format_type::index4:
    case display_format_type::index8:
    case display_format_type::arrayu8:
    case display_format_type::arrayu16:
    case display_format_type::arrayu32:
    case display_format_type::arrayf16:
    case display_format_type::arrayf32:
    case display_format_type::unknown:
      return display_format_packed_order::none;
  }
  HOU_UNREACHABLE();
  return display_format_packed_order::none;
}



display_format_array_order get_array_order(display_format f)
{
  switch(get_type(f))
  {
    case display_format_type::arrayu8:
    case display_format_type::arrayu16:
    case display_format_type::arrayu32:
    case display_format_type::arrayf16:
    case display_format_type::arrayf32:
      return display_format_array_order(SDL_PIXELORDER(
        static_cast<std::underlying_type<display_format>::type>(f)));
    case display_format_type::index1:
    case display_format_type::index4:
    case display_format_type::index8:
    case display_format_type::packed8:
    case display_format_type::packed16:
    case display_format_type::packed32:
    case display_format_type::unknown:
      return display_format_array_order::none;
  }
  HOU_UNREACHABLE();
  return display_format_array_order::none;
}



display_format_packed_layout get_packed_layout(display_format f)
{
  switch(get_type(f))
  {
    case display_format_type::packed8:
    case display_format_type::packed16:
    case display_format_type::packed32:
      return display_format_packed_layout(SDL_PIXELLAYOUT(
        static_cast<std::underlying_type<display_format>::type>(f)));
    case display_format_type::arrayu8:
    case display_format_type::arrayu16:
    case display_format_type::arrayu32:
    case display_format_type::arrayf16:
    case display_format_type::arrayf32:
    case display_format_type::index1:
    case display_format_type::index4:
    case display_format_type::index8:
    case display_format_type::unknown:
      return display_format_packed_layout::none;
  }
  HOU_UNREACHABLE();
  return display_format_packed_layout::none;
}



bool is_indexed(display_format f)
{
  return SDL_ISPIXELFORMAT_INDEXED(
    static_cast<std::underlying_type<display_format>::type>(f));
}



bool has_alpha(display_format f)
{
  return SDL_ISPIXELFORMAT_ALPHA(
    static_cast<std::underlying_type<display_format>::type>(f));
}



bool is_fourcc(display_format f)
{
  return SDL_ISPIXELFORMAT_FOURCC(
    static_cast<std::underlying_type<display_format>::type>(f));
}



std::ostream& operator<<(std::ostream& os, display_format f)
{
  switch(f)
  {
    DISPLAY_FORMAT_CASE(unknown, os);
    DISPLAY_FORMAT_CASE(index1lsb, os);
    DISPLAY_FORMAT_CASE(index1msb, os);
    DISPLAY_FORMAT_CASE(index4lsb, os);
    DISPLAY_FORMAT_CASE(index4msb, os);
    DISPLAY_FORMAT_CASE(index8, os);
    DISPLAY_FORMAT_CASE(rgb332, os);
    DISPLAY_FORMAT_CASE(rgb444, os);
    DISPLAY_FORMAT_CASE(rgb555, os);
    DISPLAY_FORMAT_CASE(bgr555, os);
    DISPLAY_FORMAT_CASE(argb4444, os);
    DISPLAY_FORMAT_CASE(rgba4444, os);
    DISPLAY_FORMAT_CASE(abgr4444, os);
    DISPLAY_FORMAT_CASE(bgra4444, os);
    DISPLAY_FORMAT_CASE(argb1555, os);
    DISPLAY_FORMAT_CASE(rgba5551, os);
    DISPLAY_FORMAT_CASE(abgr1555, os);
    DISPLAY_FORMAT_CASE(bgra5551, os);
    DISPLAY_FORMAT_CASE(rgb565, os);
    DISPLAY_FORMAT_CASE(bgr565, os);
    DISPLAY_FORMAT_CASE(rgb24, os);
    DISPLAY_FORMAT_CASE(bgr24, os);
    DISPLAY_FORMAT_CASE(rgb888, os);
    DISPLAY_FORMAT_CASE(rgbx8888, os);
    DISPLAY_FORMAT_CASE(bgr888, os);
    DISPLAY_FORMAT_CASE(bgrx8888, os);
    DISPLAY_FORMAT_CASE(argb8888, os);
    DISPLAY_FORMAT_CASE(rgba8888, os);
    DISPLAY_FORMAT_CASE(abgr8888, os);
    DISPLAY_FORMAT_CASE(bgra8888, os);
    DISPLAY_FORMAT_CASE(argb2101010, os);
    DISPLAY_FORMAT_CASE(yv12, os);
    DISPLAY_FORMAT_CASE(iyuv, os);
    DISPLAY_FORMAT_CASE(yuy2, os);
    DISPLAY_FORMAT_CASE(uyvy, os);
    DISPLAY_FORMAT_CASE(yvyu, os);
    DISPLAY_FORMAT_CASE(nv12, os);
    DISPLAY_FORMAT_CASE(nv21, os);
  }
  return os << "unknown(" << static_cast<int>(f) << ")";
}



std::ostream& operator<<(std::ostream& os, display_format_type f)
{
  switch(f)
  {
    DISPLAY_FORMAT_TYPE_CASE(unknown, os);
    DISPLAY_FORMAT_TYPE_CASE(index1, os);
    DISPLAY_FORMAT_TYPE_CASE(index4, os);
    DISPLAY_FORMAT_TYPE_CASE(index8, os);
    DISPLAY_FORMAT_TYPE_CASE(packed8, os);
    DISPLAY_FORMAT_TYPE_CASE(packed16, os);
    DISPLAY_FORMAT_TYPE_CASE(packed32, os);
    DISPLAY_FORMAT_TYPE_CASE(arrayu8, os);
    DISPLAY_FORMAT_TYPE_CASE(arrayu16, os);
    DISPLAY_FORMAT_TYPE_CASE(arrayu32, os);
    DISPLAY_FORMAT_TYPE_CASE(arrayf16, os);
    DISPLAY_FORMAT_TYPE_CASE(arrayf32, os);
  }
  return os << "unknown(" << static_cast<int>(f) << ")";
}



std::ostream& operator<<(std::ostream& os, display_format_bitmap_order f)
{
  switch(f)
  {
    DISPLAY_FORMAT_BITMAP_ORDER_CASE(none, os);
    DISPLAY_FORMAT_BITMAP_ORDER_CASE(ev4321, os);
    DISPLAY_FORMAT_BITMAP_ORDER_CASE(ev1234, os);
  }
  return os << "unknown(" << static_cast<int>(f) << ")";
}


std::ostream& operator<<(std::ostream& os, display_format_packed_order f)
{
  switch(f)
  {
    DISPLAY_FORMAT_PACKED_ORDER_CASE(none, os);
    DISPLAY_FORMAT_PACKED_ORDER_CASE(xrgb, os);
    DISPLAY_FORMAT_PACKED_ORDER_CASE(rgbx, os);
    DISPLAY_FORMAT_PACKED_ORDER_CASE(argb, os);
    DISPLAY_FORMAT_PACKED_ORDER_CASE(rgba, os);
    DISPLAY_FORMAT_PACKED_ORDER_CASE(xbgr, os);
    DISPLAY_FORMAT_PACKED_ORDER_CASE(bgrx, os);
    DISPLAY_FORMAT_PACKED_ORDER_CASE(abgr, os);
    DISPLAY_FORMAT_PACKED_ORDER_CASE(bgra, os);
  }
  return os << "unknown(" << static_cast<int>(f) << ")";
}



std::ostream& operator<<(std::ostream& os, display_format_array_order f)
{
  switch(f)
  {
    DISPLAY_FORMAT_ARRAY_ORDER_CASE(none, os);
    DISPLAY_FORMAT_ARRAY_ORDER_CASE(rgb, os);
    DISPLAY_FORMAT_ARRAY_ORDER_CASE(rgba, os);
    DISPLAY_FORMAT_ARRAY_ORDER_CASE(argb, os);
    DISPLAY_FORMAT_ARRAY_ORDER_CASE(bgr, os);
    DISPLAY_FORMAT_ARRAY_ORDER_CASE(bgra, os);
    DISPLAY_FORMAT_ARRAY_ORDER_CASE(abgr, os);
  }
  return os << "unknown(" << static_cast<int>(f) << ")";
}



std::ostream& operator<<(std::ostream& os, display_format_packed_layout f)
{
  switch(f)
  {
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(none, os);
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(ev332, os);
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(ev4444, os);
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(ev1555, os);
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(ev5551, os);
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(ev565, os);
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(ev8888, os);
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(ev2101010, os);
    DISPLAY_FORMAT_PACKED_LAYOUT_CASE(ev1010102, os);
  }
  return os << "unknown(" << static_cast<int>(f) << ")";
}

}  // namespace hou
