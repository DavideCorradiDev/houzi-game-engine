// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_ROTATION_3_FWD_HPP
#define HOU_MTH_ROTATION_3_FWD_HPP

#include "hou/mth/mth_export.hpp"



namespace hou
{

template <typename T>
class rotation3;

/** 3d rotation */
template <typename T>
using rot3 = rotation3<T>;
/** float 3d rotation */
using rot3f = rotation3<float>;
/** double 3d rotation */
using rot3d = rotation3<double>;

}  // namespace hou

#endif
