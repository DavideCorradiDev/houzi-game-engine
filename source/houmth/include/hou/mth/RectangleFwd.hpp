// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_RECTANGLE_FWD_HPP
#define HOU_COR_RECTANGLE_FWD_HPP

#include "hou/cor/basic_types.hpp"



namespace hou
{

template <typename T> class Rectangle;

/** Axis aligned rectangle */
template <typename T>
  using Rect = Rectangle<T>;
/** Integer rectangle */
using Recti = Rect<int>;
/** float rectangle */
using Rectf = Rect<float>;
/** double rectangle */
using Rectd = Rect<double>;

}

#endif

