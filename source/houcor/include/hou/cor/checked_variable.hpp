// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_CHECKED_VARIABLE_HPP
#define HOU_COR_CHECKED_VARIABLE_HPP

#include "hou/cor/assertions.hpp"

#include "hou/cor/cor_config.hpp"

#include <type_traits>



namespace hou
{

/** Wrapper used to restrict the values that a variable can be assigned.
 *
 * checked_variable and T can be implictly converted int one another, so that
 * the usage of checked_variable is transparent
 *
 * Please note that when performing an operation on checked_variable objects,
 * the objects will be converted into the underlying type, and the result of the
 * operation will also return an object of the underlying type, meaning that
 * the result will not be checked. In order for the result to be checked, the
 * value should be assigned again to a checked_variable object.
 *
 * \tparam T the underlying type.
 *
 * \tparam Checker a class defining the check performed on the variable.
 * The Checker class must provide a value_type member type indicating what
 * underlying type is checked, and a static bool check(const value_type&)
 * noexcept member function implementing the actual check. Values for which
 * checks return false are not allowed for the checked_variable type.
 */
template <typename T, typename Checker>
class checked_variable
{
  static_assert(std::is_same<T, typename Checker::value_type>::value,
    "Checker::value_type does not match T.");

public:
  /** Constructor.
   *
   * This constructor enables implicit conversions from T to checked_variable.
   *
   * \param var the value.
   *
   * \throws hou::precondition violation if Checker::check(var) returns false.
   */
  constexpr checked_variable(T var);

  /** Retrieves the underlying type.
   *
   * \return the underlying type.
   */
  constexpr const T& get() const noexcept;

  /** Cast operator to the underlying type.
   *
   * This cast operator enables implicit conversions from checked_variable to T.
   */
  constexpr operator T() const noexcept;

private:
  T m_value;
};

/** Positive checker for checked variable.
 *
 * \tparam T the underlying type.
 */
template <typename T>
class positive_checker
{
public:
  /** The value type. */
  using value_type = T;

  /** Checker function.
   *
   * \param t the value.
   * 
   * \return true if t is positive.
   */
  static constexpr bool check(const T& t) noexcept;
};

/** Positive variable. */
template <typename T>
using positive = checked_variable<T, positive_checker<T>>;

/** Non-negative checker for checked variable.
 *
 * \tparam T the underlying type.
 */
template <typename T>
class non_negative_checker
{
public:
  /** The value type. */
  using value_type = T;

  /** Checker function.
   *
   * \param t the value.
   *
   * \return true if t is non-negative (zero or positive).
   */
  static constexpr bool check(const T& t) noexcept;
};

/** Non-negative variable. */
template <typename T>
using non_negative = checked_variable<T, non_negative_checker<T>>;

/** Negative checker for checked variable.
 *
 * \tparam T the underlying type.
 */
template <typename T>
class negative_checker
{
public:
  /** The value type. */
  using value_type = T;

  /** Checker function.
   *
   * \param t the value.
   *
   * \return true if t is negative.
   */
  static constexpr bool check(const T& t) noexcept;
};

/** Negative variable. */
template <typename T>
using negative = checked_variable<T, negative_checker<T>>;

/** Non-positive checker for checked variable.
 *
 * \tparam T the underlying type.
 */
template <typename T>
class non_positive_checker
{
public:
  /** The value type. */
  using value_type = T;

  /** Checker function.
   *
   * \param t the value.
   *
   * \return true if t is non-positive (zero or negative).
   */
  static constexpr bool check(const T& t) noexcept;
};

/** Non-positive variable. */
template <typename T>
using non_positive = checked_variable<T, non_positive_checker<T>>;

/** Bounded checker for checked variable.
 *
 * \tparam T the underlying type.
 *
 * \tparam Min the minimum allowed value.
 *
 * \tparam Max the maximum allowed value.
 */
template <typename T, T Min, T Max>
class bounded_checker
{
public:
  /** The value type. */
  using value_type = T;

  /** Checker function.
   *
   * \param t the value.
   *
   * \return false if t is lower than Min or greater than Max.
   */
  static constexpr bool check(const T& t) noexcept;
};

/** Bounded variable. */
template <typename T, T Min, T Max>
using bounded = checked_variable<T, bounded_checker<T, Min, Max>>;

}  // namespace hou



#include "hou/cor/checked_variable.inl"

#endif
