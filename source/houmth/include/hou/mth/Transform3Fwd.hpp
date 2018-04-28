// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_TRANSFORM_3_FWD_HPP
#define HOU_MTH_TRANSFORM_3_FWD_HPP

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T> class Transform3;

/** 3d transform */
template <typename T>
  using Trans3 = Transform3<T>;
/** float 3d transform */
using Trans3f = Transform3<float>;
/** double 3d transform */
using Trans3d = Transform3<double>;

}

#endif

