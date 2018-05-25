// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MTH_UTILS_HPP
#define HOU_MTH_MTH_UTILS_HPP

#include "hou/mth/mth_config.hpp"

#include "hou/cor/narrow_cast.hpp"

#include <cmath>
#include <type_traits>



namespace hou
{

/** float value of pi.
 */
constexpr float pi_f = 3.1415927f;

/** double value of pi.
 */
constexpr double pi_d = 3.141592653589793;



template <typename T>
constexpr T pi();

/** Converts degrees to radians.
 *
 * \param deg the angle in degrees.
 *
 * \return the angle in radians.
 */
HOU_MTH_API float deg_to_rad(float deg) noexcept;

/** Converts degrees to radians.
 *
 * \param deg the angle in degrees.
 *
 * \return the angle in radians.
 */
HOU_MTH_API double deg_to_rad(double deg) noexcept;

/** Converts radians to degrees.
 *
 * \param rad the angle in radians.
 *
 * \return the angle in degrees.
 */
HOU_MTH_API float rad_to_deg(float rad) noexcept;

/** Converts radians to degrees.
 *
 * \param rad the angle in radians.
 *
 * \return the angle in degrees.
 */
HOU_MTH_API double rad_to_deg(double rad) noexcept;

/** Computes the logarithm in base n of x.
 *
 * \param n the base.
 *
 * \param x the argument.
 *
 * \return the logarithm in base n of x.
 */
template <typename T,
  typename Enable = std::enable_if_t<std::is_floating_point<T>::value>>
constexpr T log(T x, int n) noexcept;

}  // namespace hou



#include "hou/mth/math_functions.inl"

#endif
