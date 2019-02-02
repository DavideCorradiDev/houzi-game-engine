// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_RECTANGLE_FWD_HPP
#define HOU_COR_RECTANGLE_FWD_HPP

#include "hou/mth/mth_config.hpp"

#include "hou/cor/checked_variable_fwd.hpp"



namespace hou
{

template <typename ScalPosT, typename ScalSizeT>
class rectangle;

/** Axis aligned rectangle with size type equal to position type. */
template <typename T>
using rect = rectangle<T, T>;

/** Integer rectangle. */
using recti = rect<int>;
/** Float rectangle. */
using rectf = rect<float>;
/** Double rectangle. */
using rectd = rect<double>;

/** Asix aligned rectangle with size type equal to position type and
 * non-negative size. */
template <typename T>
using rectu = rectangle<T, non_negative<T>>;

/** Integer rectangle with non negative size. */
using rectui = rectu<int>;
/** Float rectuangle with non negative size. */
using rectuf = rectu<float>;
/** Double rectuangle with non negative size. */
using rectud = rectu<double>;

}  // namespace hou

#endif
