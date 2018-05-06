// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_TEMPLATE_UTILS_HPP
#define HOU_COR_TEMPLATE_UTILS_HPP

#include "hou/cor/basic_types.hpp"

#include "hou/cor/cor_export.hpp"

#include <type_traits>



/** Generate a member detector helper to be used in template conditions.
 *
 * This macro created a detector of member X called detect_member_X.
 * If class T has a member called X, detect_member_X<T>::value will be true,
 * otherwise it will be false.
 */
#define HOU_CREATE_MEMBER_DETECTOR(X) \
  template < \
    typename T, \
    bool IsFundamental \
    = std::is_fundamental<T>::value || std::is_enum<T>::value> \
  class detect_member_##X; \
  template <typename T> \
  class detect_member_##X<T, true> \
  { \
  public: \
    enum \
    { \
      value = false \
    }; \
  }; \
  template <typename T> \
  class detect_member_##X<T, false> \
  { \
  private: \
    struct fallback \
    { \
      int X; \
    }; \
    struct derived \
      : public T \
      , fallback \
    {}; \
    template <typename U, U> \
    struct Check \
    {}; \
    using Yes = uint8_t[1]; \
    using No = uint8_t[2]; \
    template <typename U> \
    static No& func(Check<int fallback::*, &U::X>*); \
    template <typename U> \
    static Yes& func(...); \
\
  public: \
    enum \
    { \
      value = sizeof(func<derived>(0)) == sizeof(Yes) \
    }; \
  }



/** Generate a type detector helper to be used in template conditions.
 *
 * This macro created a detector of type X called detect_type_X.
 * If class T has a nested class or typedef called X, detect_type_X<T>::value
 * will be true, otherwise it will be false.
 */
#define HOU_CREATE_TYPE_DETECTOR(X) \
  template <typename T> \
  class detect_type_##X \
  { \
  private: \
    using Yes = uint8_t[1]; \
    using No = uint8_t[2]; \
    template <typename U> \
    static Yes& test(typename U::X*); \
    template <typename U> \
    static No& test(...); \
\
  public: \
    enum \
    { \
      value = sizeof(test<T>(0)) == sizeof(Yes) \
    }; \
  }



namespace hou
{

namespace prv
{

HOU_CREATE_MEMBER_DETECTOR(data);
HOU_CREATE_TYPE_DETECTOR(pointer);

template <
  typename T,
  bool HasRequiredElements
  = detect_member_data<T>::value&& detect_type_pointer<T>::value>
struct is_contiguous_container_helper;

template <typename T>
struct is_contiguous_container_helper<T, true>
  : public std::is_convertible<
      typename T::pointer, decltype(std::declval<T>().data())>
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
