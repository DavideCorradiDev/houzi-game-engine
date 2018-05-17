// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NARROW_CAST_HPP
#define HOU_COR_NARROW_CAST_HPP

#include "hou/cor/cor_exceptions.hpp"

#include "hou/cor/cor_config.hpp"



namespace hou
{

/** Determines if two types have the same signedness.
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
      std::is_signed<T>::value && std::is_signed<U>::value>
{};



/** Cast checking for narrowing errors.
 *
 * \tparam To to target type.
 *
 * \tparam From the source type.
 *
 * \param from the input value.
 *
 * \throws hou::narrowing_error if the conversion results in a narrowing error.
 *
 * \return the casted value.
 */
template <typename To, typename From>
constexpr To narrow_cast(const From& from);

}  // namespace hou



#include "hou/cor/narrow_cast.inl"

#endif
