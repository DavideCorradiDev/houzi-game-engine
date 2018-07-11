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

/**
 * Retrieves the value of pi.
 *
 * \tparam T the scalar type.
 *
 * \return the value of pi.
 */
template <typename T>
constexpr T pi() noexcept;

/**
 * Converts degrees to radians.
 *
 * \tparam T the scalar type.
 *
 * \param deg the angle in degrees.
 *
 * \return the angle in radians.
 */
template <typename T>
constexpr T deg_to_rad(T deg) noexcept;

/**
 * Converts radians to degrees.
 *
 * \tparam T the scalar type.
 *
 * \param rad the angle in radians.
 *
 * \return the angle in degrees.
 */
template <typename T>
constexpr T rad_to_deg(T rad) noexcept;

/**
 * Computes the logarithm in base n of x.
 *
 * \tparam T the scalar type.
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
