// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_TRANSFORM_3_FWD_HPP
#define HOU_MTH_TRANSFORM_3_FWD_HPP

#include "hou/mth/mth_export.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T>
class transform3;

/** 3d transform */
template <typename T>
using trans3 = transform3<T>;
/** float 3d transform */
using trans3f = transform3<float>;
/** double 3d transform */
using trans3d = transform3<double>;

}  // namespace hou

#endif
