// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_TRANSFORM_2_FWD_HPP
#define HOU_MTH_TRANSFORM_2_FWD_HPP

#include "hou/mth/mth_export.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T>
class transform2;

/** 2d transform */
template <typename T>
using trans2 = transform2<T>;
/** float 2d transform */
using trans2f = transform2<float>;
/** double 2d transform */
using trans2d = transform2<double>;

}  // namespace hou

#endif
