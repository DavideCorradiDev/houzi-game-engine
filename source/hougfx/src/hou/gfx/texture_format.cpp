// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture_format.hpp"

#include "hou/cor/cor_exceptions.hpp"
#include "hou/cor/core_functions.hpp"
#include "hou/cor/narrow_cast.hpp"

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
  return STREAM_VALUE(os, texture_format, format);
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
  HOU_ERROR_N(invalid_enum, narrow_cast<int>(tf));
  return 0u;
}

}  // namespace hou
