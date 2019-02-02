// Houzi Game Engine
// Copyright (c) 2016-2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture_filter.hpp"

#include "hou/cor/core_functions.hpp"

#define TEXTURE_FILTER_CASE(tf, os) \
  case texture_filter::tf: \
    return (os) << #tf



namespace hou
{

std::ostream& operator<<(std::ostream& os, texture_filter tf)
{
  switch(tf)
  {
    TEXTURE_FILTER_CASE(nearest, os);
    TEXTURE_FILTER_CASE(linear, os);
    TEXTURE_FILTER_CASE(bilinear, os);
    TEXTURE_FILTER_CASE(trilinear, os);
  }
  return STREAM_VALUE(os, texture_filter, tf);
}

}  // namespace hou
