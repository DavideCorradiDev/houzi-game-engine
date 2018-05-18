// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, typename Checker>
constexpr checked_variable<T, Checker>::checked_variable(T var)
  : m_value(var)
{
  HOU_CHECK_0(Checker::check(m_value), invalid_value);
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



// template <typename T>
// constexpr bool positive_checker::check(const T& t) noexcept
// {
//   return t > T(0);
// }

}
