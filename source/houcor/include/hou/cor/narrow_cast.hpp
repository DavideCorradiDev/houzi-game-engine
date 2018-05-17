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
