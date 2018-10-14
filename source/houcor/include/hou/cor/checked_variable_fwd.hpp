// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_CHECKED_VARIABLE_FWD_HPP
#define HOU_COR_CHECKED_VARIABLE_FWD_HPP

#include "hou/cor/cor_config.hpp"

namespace hou
{

template <typename T, typename Checker>
class checked_variable;

template <typename T>
class positive_checker;

/** Positive variable. */
template <typename T>
using positive = checked_variable<T, positive_checker<T>>;

template <typename T>
class non_negative_checker;

/** Non-negative variable. */
template <typename T>
using non_negative = checked_variable<T, non_negative_checker<T>>;

template <typename T>
class negative_checker;

/** Negative variable. */
template <typename T>
using negative = checked_variable<T, negative_checker<T>>;

template <typename T>
class non_positive_checker;

/** Non-positive variable. */
template <typename T>
using non_positive = checked_variable<T, non_positive_checker<T>>;

template <typename T, T Min, T Max>
class bounded_checker;

/** Bounded variable. */
template <typename T, T Min, T Max>
using bounded = checked_variable<T, bounded_checker<T, Min, Max>>;

}

#endif
