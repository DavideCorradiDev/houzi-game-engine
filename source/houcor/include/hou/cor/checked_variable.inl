// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, typename Checker>
constexpr checked_variable<T, Checker>::checked_variable()
  : m_value()
{}



template <typename T, typename Checker>
constexpr checked_variable<T, Checker>::checked_variable(T var)
  : m_value(var)
{
  HOU_PRECOND(Checker::check(m_value));
}



template <typename T, typename Checker>
constexpr const T& checked_variable<T, Checker>::get() const noexcept
{
  return m_value;
}



template <typename T, typename Checker>
constexpr checked_variable<T, Checker>::operator T() const noexcept
{
  return m_value;
}



template <typename T>
constexpr bool positive_checker<T>::check(const T& t) noexcept
{
  return t > T(0);
}



template <typename T>
constexpr bool non_negative_checker<T>::check(const T& t) noexcept
{
  return t >= T(0);
}



template <typename T>
constexpr bool negative_checker<T>::check(const T& t) noexcept
{
  return t < T(0);
}



template <typename T>
constexpr bool non_positive_checker<T>::check(const T& t) noexcept
{
  return t <= T(0);
}



template <typename T, T Min, T Max>
constexpr bool bounded_checker<T, Min, Max>::check(const T& t) noexcept
{
  return t >= Min && t <= Max;
}

}  // namespace hou
