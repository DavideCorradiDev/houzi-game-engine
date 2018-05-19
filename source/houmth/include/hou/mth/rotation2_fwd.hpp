// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_ROTATION_2_FWD_HPP
#define HOU_MTH_ROTATION_2_FWD_HPP

#include "hou/mth/mth_config.hpp"



namespace hou
{

template <typename T>
class rotation2;

/** 2d rotation */
template <typename T>
using rot2 = rotation2<T>;
/** Float 2d rotation */
using rot2f = rotation2<float>;
/** Double 2d rotation */
using rot2d = rotation2<double>;

}  // namespace hou

#endif
