// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_RECTANGLE_FWD_HPP
#define HOU_COR_RECTANGLE_FWD_HPP

#include "hou/mth/mth_config.hpp"



namespace hou
{

template <typename T>
class rectangle;

/** Axis aligned rectangle */
template <typename T>
using rect = rectangle<T>;
/** Integer rectangle */
using recti = rect<int>;
/** Float rectangle */
using rectf = rect<float>;
/** Double rectangle */
using rectd = rect<double>;

}  // namespace hou

#endif
