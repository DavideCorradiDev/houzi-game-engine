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
T toAngle(const mat2x2<T>& m);
template <typename T>
mat2x2<T> to_matrix(T angle);
template <typename T>
T normalize_angle(T angle);



template <typename T>
T toAngle(const mat2x2<T>& m)
{
  return std::atan2(m(2), m(0));
}



template <typename T>
mat2x2<T> to_matrix(T angle)
{
  T c = std::cos(angle);
  T s = std::sin(angle);
  return mat2x2<T>{c, -s, s, c};
}



template <typename T>
T normalize_angle(T angle)
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
rotation2<T> rotation2<T>::identity()
{
  return rotation2<T>();
}



template <typename T>
rotation2<T>::rotation2()
  : m_angle(0)
{}



template <typename T>
rotation2<T>::rotation2(T angle)
  : m_angle(normalize_angle(angle))
{}



template <typename T>
rotation2<T>::rotation2(const mat2x2<T>& m)
  : m_angle(toAngle(m))
{
  DEPRECATED_HOU_EXPECT(
    close(T(1), det(m)) && close(mat2x2<T>::identity(), m * transpose(m)));
  DEPRECATED_HOU_EXPECT_DEV(m_angle > -pi_f && m_angle <= pi_f);
}



template <typename T>
template <typename U>
rotation2<T>::rotation2(const rotation2<U>& other)
  : m_angle(static_cast<T>(other.m_angle))
{}



template <typename T>
T rotation2<T>::get_angle() const
{
  return m_angle;
}



template <typename T>
mat2x2<T> rotation2<T>::get_matrix() const
{
  return to_matrix(m_angle);
}



template <typename T>
rotation2<T>& rotation2<T>::operator*=(const rotation2<T>& rhs)
{
  m_angle = normalize_angle(m_angle + rhs.m_angle);
  return *this;
}



template <typename T>
rotation2<T>& rotation2<T>::invert()
{
  m_angle = normalize_angle(-m_angle);
  return *this;
}



template <typename T>
rotation2<T> operator*(rotation2<T> lhs, const rotation2<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
rotation2<T> inverse(rotation2<T> r)
{
  return r.invert();
}



// clang-format off
HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH()
HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(-Wfloat-equal)
template <typename T>
bool operator==(const rotation2<T>& lhs, const rotation2<T>& rhs)
{
  return lhs.get_angle() == rhs.get_angle();
}
HOU_PRAGMA_GCC_DIAGNOSTIC_POP()
// clang-format on



// clang-format off
HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH()
HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(-Wfloat-equal)
template <typename T>
bool operator!=(const rotation2<T>& lhs, const rotation2<T>& rhs)
{
  return lhs.get_angle() != rhs.get_angle();
}
HOU_PRAGMA_GCC_DIAGNOSTIC_POP()
// clang-format on



template <typename T>
bool close(const rotation2<T>& lhs, const rotation2<T>& rhs, T acc)
{
  return close(lhs.get_angle(), rhs.get_angle(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const rotation2<T>& r)
{
  return os << r.get_angle();
}



#define HOU_INSTANTIATE(T) \
  template class rotation2<T>; \
  template rotation2<T> operator*<T>(rotation2<T>, const rotation2<T>&); \
  template rotation2<T> inverse<T>(rotation2<T>); \
  template bool operator==<T>(const rotation2<T>&, const rotation2<T>&); \
  template bool operator!=<T>(const rotation2<T>&, const rotation2<T>&); \
  template bool close<T>(const rotation2<T>&, const rotation2<T>&, T); \
  template std::ostream& operator<<<T>(std::ostream&, const rotation2<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template rotation2<float>::rotation2<double>(const rotation2<double>&);
template rotation2<double>::rotation2<float>(const rotation2<float>&);

}  // namespace hou
