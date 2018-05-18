// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_NARROW_CAST_HPP
#define HOU_COR_NARROW_CAST_HPP

#include "hou/cor/cor_exceptions.hpp"
#include "hou/cor/is_same_signedness.hpp"

#include "hou/cor/cor_config.hpp"
#include "hou/cor/pragmas.hpp"



namespace hou
{

/** Class implementing a check to see if two values of different types have the
 * same sign.
 *
 * This function is used by narrow_cast for the comparison.
 * It is possible to specialize this class for classes requiring special checks
 * for narrow_cast.
 *
 * \tparam T the first type.
 *
 * \tparam U the second type.
 *
 */
template <typename T, typename U>
class check_matching_sign
{
public:
  /** Checks if t and u have matching sign.
   *
   * \param t the first parameter.
   *
   * \param u the second parameter.
   *
   * \return true if the signs of t and u match.
   */
  static bool check(const T& t, const U& u);
};

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
template <typename To, typename From>
constexpr To narrow_cast(const From& from);

}  // namespace hou



#include "hou/cor/narrow_cast.inl"

#endif
