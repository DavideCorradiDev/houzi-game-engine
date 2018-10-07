// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/blending_factor.hpp"

#include "hou/cor/core_functions.hpp"

#define BLENDING_FACTOR_CASE(bf, os)                                           \
  case blending_factor::bf:                                                    \
    return (os) << #bf



namespace hou
{

std::ostream& operator<<(std::ostream& os, blending_factor bf)
{
  switch(bf)
  {
    BLENDING_FACTOR_CASE(zero, os);
    BLENDING_FACTOR_CASE(one, os);
    BLENDING_FACTOR_CASE(src_color, os);
    BLENDING_FACTOR_CASE(one_minus_src_color, os);
    BLENDING_FACTOR_CASE(dst_color, os);
    BLENDING_FACTOR_CASE(one_minus_dst_color, os);
    BLENDING_FACTOR_CASE(src_alpha, os);
    BLENDING_FACTOR_CASE(one_minus_src_alpha, os);
    BLENDING_FACTOR_CASE(dst_alpha, os);
    BLENDING_FACTOR_CASE(one_minus_dst_alpha, os);
    BLENDING_FACTOR_CASE(constant_color, os);
    BLENDING_FACTOR_CASE(one_minus_constant_color, os);
    BLENDING_FACTOR_CASE(constant_alpha, os);
    BLENDING_FACTOR_CASE(one_minus_constant_alpha, os);
  }
  return STREAM_VALUE(os, blending_factor, bf);
}

}  // namespace hou
