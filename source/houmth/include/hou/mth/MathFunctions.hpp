// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MTH_UTILS_HPP
#define HOU_MTH_MTH_UTILS_HPP

#include "hou/mth/MthExport.hpp"

#include "hou/cor/basic_types.hpp"

#include <cmath>
#include <type_traits>



namespace hou
{

/** float value of pi.
 */
constexpr float PI_F = 3.1415927f;

/** double value of pi.
 */
constexpr double PI_D = 3.141592653589793;

/** Converts degrees to radians.
 *
 *  \param deg the angle in degrees.
 *  \return the angle in radians.
 */
HOU_MTH_API float degToRad(float deg);

/** Converts degrees to radians.
 *
 *  \param deg the angle in degrees.
 *  \return the angle in radians.
 */
HOU_MTH_API double degToRad(double deg);

/** Converts radians to degrees.
 *
 *  \param rad the angle in radians.
 *  \return the angle in degrees.
 */
HOU_MTH_API float radToDeg(float rad);

/** Converts radians to degrees.
 *
 *  \param rad the angle in radians.
 *  \return the angle in degrees.
 */
HOU_MTH_API double radToDeg(double rad);

/** Computes the logarithm in base n of x.
 *
 *  \param n the base.
 *  \param x the argument.
 *  \return the logarithm in base n of x.
 */
template <typename T,
  typename Enable = std::enable_if_t<std::is_floating_point<T>::value>>
T log(T x, int n);

}



#include "hou/mth/MathFunctions.inl"

#endif
