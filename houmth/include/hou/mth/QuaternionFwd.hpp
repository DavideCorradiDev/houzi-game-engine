// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_MTH_QUATERNION_FWD_HPP
#define HOU_MTH_QUATERNION_FWD_HPP

#include "hou/cor/BasicTypes.hpp"



namespace hou
{

template <typename T> class Quaternion;

/** float quaternion */
using Quatf = Quaternion<float>;
/** double quaternion */
using Quatd = Quaternion<double>;

}

#endif

