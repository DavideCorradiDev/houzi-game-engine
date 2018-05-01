// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_QUATERNION_FWD_HPP
#define HOU_MTH_QUATERNION_FWD_HPP

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T>
class quaternion;

/** float quaternion */
using quatf = quaternion<float>;
/** double quaternion */
using quatd = quaternion<double>;

}  // namespace hou

#endif
