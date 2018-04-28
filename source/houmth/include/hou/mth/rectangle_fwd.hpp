// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_RECTANGLE_FWD_HPP
#define HOU_COR_RECTANGLE_FWD_HPP

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T> class rectangle;

/** Axis aligned ph_rectangle */
template <typename T>
  using Rect = rectangle<T>;
/** Integer ph_rectangle */
using recti = Rect<int>;
/** float ph_rectangle */
using rectf = Rect<float>;
/** double ph_rectangle */
using rectd = Rect<double>;

}

#endif

