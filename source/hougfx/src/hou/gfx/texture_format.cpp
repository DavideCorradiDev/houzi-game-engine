// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture_format.hpp"

#include "hou/cor/cor_exceptions.hpp"

#define TEXTURE_FORMAT_CASE(format, os) \
  case texture_format::format: \
    return (os) << #format



namespace hou
{

std::ostream& operator<<(std::ostream& os, texture_format format)
{
  switch(format)
  {
    TEXTURE_FORMAT_CASE(r, os);
    TEXTURE_FORMAT_CASE(rg, os);
    TEXTURE_FORMAT_CASE(rgb, os);
    TEXTURE_FORMAT_CASE(rgba, os);
    TEXTURE_FORMAT_CASE(depth_stencil, os);
  }
  HOU_UNREACHABLE();
  return os;
}



uint get_bytes_per_pixel(texture_format tf)
{
  switch(tf)
  {
    case texture_format::r:
      return 1u;
    case texture_format::rg:
      return 2u;
    case texture_format::rgb:
      return 3u;
    case texture_format::rgba:
    case texture_format::depth_stencil:
      return 4u;
  }
  HOU_UNREACHABLE();
  return 0u;
}



pixel_format get_associated_pixel_format(texture_format tf)
{
  switch(tf)
  {
    case texture_format::r:
      return pixel_format::r;
    case texture_format::rg:
      return pixel_format::rg;
    case texture_format::rgb:
      return pixel_format::rgb;
    case texture_format::rgba:
      return pixel_format::rgba;
    case texture_format::depth_stencil:
      HOU_ERROR_N(invalid_enum,
        static_cast<std::underlying_type<texture_format>::type>(tf));
  }
  HOU_UNREACHABLE();
  return pixel_format::r;
}



bool check_format_compatibility(texture_format tf, pixel_format pf)
{
  return (tf == texture_format::r && pf == pixel_format::r)
    || (tf == texture_format::rg && pf == pixel_format::rg)
    || (tf == texture_format::rgb && pf == pixel_format::rgb)
    || (tf == texture_format::rgba && pf == pixel_format::rgba);
}

}  // namespace hou
