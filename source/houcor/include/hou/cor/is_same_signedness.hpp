// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_IS_SAME_SIGNEDNESS_HPP
#define HOU_COR_IS_SAME_SIGNEDNESS_HPP

#include "hou/cor/cor_config.hpp"



namespace hou
{

/**
 * Determines if two types have the same signedness.
 *
 * If T and U have the same signedness, provides the member constant value equal
 * true. Otherwise the value is false.
 *
 * \tparam T the first type.
 *
 * \tparam U the second type.
 */
template <typename T, typename U>
struct is_same_signedness
  : public std::integral_constant<bool,
      std::is_signed<T>::value == std::is_signed<U>::value>
{};

}  // namespace hou

#endif
