// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_ROTATION_3_FWD_HPP
#define HOU_MTH_ROTATION_3_FWD_HPP

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T> class Rotation3;

/** 3d rotation */
template <typename T>
  using Rot3 = Rotation3<T>;
/** float 3d rotation */
using Rot3f = Rotation3<float>;
/** double 3d rotation */
using Rot3d = Rotation3<double>;

}

#endif

