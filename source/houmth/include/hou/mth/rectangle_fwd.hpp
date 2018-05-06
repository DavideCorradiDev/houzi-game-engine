// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_RECTANGLE_FWD_HPP
#define HOU_COR_RECTANGLE_FWD_HPP

#include "hou/cor/basic_types.hpp"

#include "hou/mth/mth_export.hpp"



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
