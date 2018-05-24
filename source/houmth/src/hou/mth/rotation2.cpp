// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/rotation2.hpp"

#include "hou/cor/core_functions.hpp"
#include "hou/cor/pragmas.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/matrix.hpp"



namespace hou
{

namespace
{

template <typename T>
T to_angle(const mat2x2<T>& m) noexcept;

template <typename T>
mat2x2<T> to_matrix(T angle) noexcept;

template <typename T>
T normalize_angle(T angle) noexcept;



template <typename T>
T to_angle(const mat2x2<T>& m) noexcept
{
  return std::atan2(m(2), m(0));
}



template <typename T>
mat2x2<T> to_matrix(T angle) noexcept
{
  T c = std::cos(angle);
  T s = std::sin(angle);
  return mat2x2<T>{c, -s, s, c};
}



template <typename T>
T normalize_angle(T angle) noexcept
{
  while(angle <= -pi_f)
  {
    angle += 2 * pi_f;
  }
  while(angle > pi_f)
  {
    angle -= 2 * pi_f;
  }
  return angle;
}

}  // namespace



template <typename T>
rotation2<T> rotation2<T>::identity() noexcept
{
  return rotation2<T>();
}



template <typename T>
rotation2<T>::rotation2() noexcept
  : m_angle(0)
{}



template <typename T>
rotation2<T>::rotation2(T angle) noexcept
  : m_angle(normalize_angle(angle))
{}



template <typename T>
rotation2<T>::rotation2(const mat2x2<T>& m)
  : m_angle(to_angle(m))
{
  HOU_PRECOND(
    close(T(1), det(m)) && close(mat2x2<T>::identity(), m * transpose(m)));
  HOU_DEV_ASSERT(m_angle > -pi_f && m_angle <= pi_f);
}



template <typename T>
T rotation2<T>::get_angle() const noexcept
{
  return m_angle;
}



template <typename T>
mat2x2<T> rotation2<T>::get_matrix() const noexcept
{
  return to_matrix(m_angle);
}



template <typename T>
rotation2<T>& rotation2<T>::operator*=(const rotation2<T>& rhs) noexcept
{
  m_angle = normalize_angle(m_angle + rhs.m_angle);
  return *this;
}



template <typename T>
rotation2<T>& rotation2<T>::invert() noexcept
{
  m_angle = normalize_angle(-m_angle);
  return *this;
}



template class rotation2<float>;
template class rotation2<double>;

}  // namespace hou
