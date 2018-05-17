// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NARROW_CAST_HPP
#define HOU_COR_NARROW_CAST_HPP

#include "hou/cor/cor_exceptions.hpp"
#include "hou/cor/is_same_signedness.hpp"

#include "hou/cor/cor_config.hpp"



namespace hou
{

/** Cast checking for narrowing errors.
 *
 * \tparam To to target type.
 *
 * \tparam From the source type.
 *
 * \tparam Enable enabling parameter.
 *
 * \param from the input value.
 *
 * \throws hou::narrowing_error if the conversion results in a narrowing error.
 *
 * \return the casted value.
 */
template <typename To, typename From,
  typename Enable = std::enable_if_t<std::is_fundamental<To>::value
    && std::is_fundamental<From>::value>>
constexpr To narrow_cast(const From& from);

}  // namespace hou



#include "hou/cor/narrow_cast.inl"

#endif
