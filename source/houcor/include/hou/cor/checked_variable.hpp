// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_CHECKED_VARIABLE_HPP
#define HOU_COR_CHECKED_VARIABLE_HPP

#include "hou/cor/cor_exceptions.hpp"

#include "hou/cor/cor_config.hpp"

#include <type_traits>



namespace hou
{

template <typename T, typename Checker>
class checked_variable
{
  static_assert(std::is_same<T, typename Checker::value_type>::value,
    "Checker::value_type does not match T.");

public:
  constexpr checked_variable(T var);

  constexpr const T& get() const noexcept;

  constexpr operator T() const noexcept;

private:
  T m_value;
};



template <typename T>
class positive_checker
{
public:
  using value_type = T;

  static constexpr bool check(const T& t) noexcept;
};

template <typename T>
using positive = checked_variable<T, positive_checker<T>>;




template <typename T>
class negative_checker
{
public:
  using value_type = T;

  static constexpr bool check(const T& t) noexcept;
};

template <typename T>
using negative = checked_variable<T, negative_checker<T>>;



template <typename T, T Min, T Max>
class bounded_checker
{
public:
  using value_type = T;

  static constexpr bool check(const T& t) noexcept;
};

template <typename T, T Min, T Max>
using bounded = checked_variable<T, bounded_checker<T, Min, Max>>;

}  // namespace hou



#include "hou/cor/checked_variable.inl"

#endif
