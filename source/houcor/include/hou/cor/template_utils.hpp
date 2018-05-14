// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_TEMPLATE_UTILS_HPP
#define HOU_COR_TEMPLATE_UTILS_HPP

#include "hou/cor/member_detector.hpp"

#include "hou/cor/cor_export.hpp"

#include <type_traits>



namespace hou
{

HOU_CREATE_MEMBER_DETECTOR(data);
HOU_CREATE_MEMBER_TYPE_DETECTOR(pointer);

namespace prv
{

template <typename T,
  bool HasRequiredMembers
  = has_member_data<T>::value && has_member_type_pointer<T>::value>
struct is_contiguous_container_helper;

template <typename T>
struct is_contiguous_container_helper<T, true>
  : public std::is_convertible<typename T::pointer,
      decltype(std::declval<T>().data())>
{};

template <typename T>
struct is_contiguous_container_helper<T, false> : public std::false_type
{};

}  // namespace prv

/** Template checker to determine if the type is a contiguous container.
 *
 * The check is true if T has a member type named pointer and a member
 * function named data, and if the type returned by data is pointer.
 * This is in accordance to what happens with contiguous containers in the
 * standard library.
 *
 * \tparam T the type to be checked.
 */
template <typename T>
struct is_contiguous_container
  : public prv::is_contiguous_container_helper<std::remove_cv_t<T>>
{};

/** Class implementing a conjunction condition for variadic template parameters.
 *
 * \tparam b the template parameter conditions.
 */
template <bool... b>
struct conjunction
{};

/** Specialization of conjunction for multiple boolean variables.
 *
 * \tparam Head the first boolean variable.
 *
 * \tparam Tail the other boolean variables.
 */
template <bool Head, bool... Tail>
struct conjunction<Head, Tail...>
  : std::integral_constant<bool, Head && conjunction<Tail...>::value>
{};

/** Specialization of conjunction for a single boolean variable.
 *
 * \tparam the boolean value.
 */
template <bool b>
struct conjunction<b> : std::integral_constant<bool, b>
{};

}  // namespace hou

#endif
