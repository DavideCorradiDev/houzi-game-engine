// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_TRANSFORM_2_FWD_HPP
#define HOU_MTH_TRANSFORM_2_FWD_HPP

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T> class Transform2;

/** 2d transform */
template <typename T>
  using Trans2 = Transform2<T>;
/** float 2d transform */
using Trans2f = Transform2<float>;
/** double 2d transform */
using Trans2d = Transform2<double>;

}

#endif

