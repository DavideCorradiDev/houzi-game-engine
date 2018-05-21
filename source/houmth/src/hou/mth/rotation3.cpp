// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/rotation3.hpp"

#include "hou/mth/matrix.hpp"



namespace hou
{

namespace
{

template <typename T>
quaternion<T> to_quaternion(vec3<T> v) noexcept;

template <typename T>
quaternion<T> to_quaternion(const mat3x3<T>& m) noexcept;

template <typename T>
vec3<T> to_vector(const quaternion<T>& q) noexcept;

template <typename T>
mat3x3<T> to_matrix(const quaternion<T>& q) noexcept;



template <typename T>
quaternion<T> to_quaternion(vec3<T> v) noexcept
{
  T angle = norm(v);
  v /= angle;
  T s = std::sin(angle / 2);
  T c = std::cos(angle / 2);
  return quaternion<T>(v.x() * s, v.y() * s, v.z() * s, c);
}



// clang-format off
template <typename T>
quaternion<T> to_quaternion(const mat3x3<T>& m) noexcept
{
  T tr = trace(m);
  if(tr > T(0))
  {
    T s = sqrt(1.f + tr) * 2.f;
    return quaternion<T>{
      (m(2, 1) - m(1, 2)) / s,
      (m(0, 2) - m(2, 0)) / s,
      (m(1, 0) - m(0, 1)) / s,
      0.25f * s,
    };
  }
  else if((m(0, 0) > m(1, 1)) && (m(0, 0) > m(2, 2)))
  {
    T s = sqrt(1.f + m(0, 0) - m(1, 1) - m(2, 2)) * 2.f;
    return quaternion<T>{
      0.25f * s,
      (m(0, 1) + m(1, 0)) / s,
      (m(0, 2) + m(2, 0)) / s,
      (m(2, 1) - m(1, 2)) / s,
    };
  }
  else if(m(1, 1) > m(2, 2))
  {
    T s = sqrt(1.f + m(1, 1) - m(0, 0) - m(2, 2)) * 2.f;
    return quaternion<T>{
      (m(0, 1) + m(1, 0)) / s,
      0.25f * s,
      (m(1, 2) + m(2, 1)) / s,
      (m(0, 2) - m(2, 0)) / s,
    };
  }
  else
  {
    T s = sqrt(1.f + m(2, 2) - m(0, 0) - m(1, 1)) * 2.f;
    return quaternion<T>{
      (m(0, 2) + m(2, 0)) / s,
      (m(1, 2) + m(2, 1)) / s,
      0.25f * s,
      (m(1, 0) - m(0, 1)) / s,
    };
  }
}
// clang-format on



template <typename T>
vec3<T> to_vector(const quaternion<T>& q) noexcept
{
  HOU_DEV_ASSERT(close(T(1), norm(q)));
  vec3<T> v(q.x(), q.y(), q.z());
  T vecNorm = norm(v);
  if(!close(T(0), vecNorm))
  {
    v *= 2 * std::atan2(vecNorm, q.w()) / vecNorm;
  }
  return v;
}



template <typename T>
mat3x3<T> to_matrix(const quaternion<T>& q) noexcept
{
  HOU_DEV_ASSERT(close(T(1), norm(q)));
  T xx = 2 * q.x() * q.x();
  T xy = 2 * q.x() * q.y();
  T xz = 2 * q.x() * q.z();
  T xw = 2 * q.x() * q.w();
  T yy = 2 * q.y() * q.y();
  T yz = 2 * q.y() * q.z();
  T yw = 2 * q.y() * q.w();
  T zz = 2 * q.z() * q.z();
  T zw = 2 * q.z() * q.w();
  T ww = 2 * q.w() * q.w();
  return mat3x3<T>(-1 + xx + ww, xy - zw, xz + yw, xy + zw, -1 + yy + ww,
    yz - xw, xz - yw, xw + yz, -1 + zz + ww);
}

}  // namespace



template <typename T>
rotation3<T> rotation3<T>::identity() noexcept
{
  return rotation3<T>();
}



template <typename T>
rotation3<T> rotation3<T>::x(T angle) noexcept
{
  angle /= 2;
  return rotation3<T>(quaternion<T>(std::sin(angle), 0, 0, std::cos(angle)));
}



template <typename T>
rotation3<T> rotation3<T>::y(T angle) noexcept
{
  angle /= 2;
  return rotation3<T>(quaternion<T>(0, std::sin(angle), 0, std::cos(angle)));
}



template <typename T>
rotation3<T> rotation3<T>::z(T angle) noexcept
{
  angle /= 2;
  return rotation3<T>(quaternion<T>(0, 0, std::sin(angle), std::cos(angle)));
}



template <typename T>
rotation3<T>::rotation3() noexcept
  : m_quaternion(quaternion<T>::identity())
{}



template <typename T>
rotation3<T>::rotation3(const quaternion<T>& q)
  : m_quaternion(normalized(q))
{}



template <typename T>
rotation3<T>::rotation3(const vec3<T>& v)
  : m_quaternion(normalized(to_quaternion(v)))
{}



template <typename T>
rotation3<T>::rotation3(const mat3x3<T>& m)
  : m_quaternion(normalized(to_quaternion(m)))
{}



template <typename T>
const quaternion<T>& rotation3<T>::get_quaternion() const noexcept
{
  return m_quaternion;
}



template <typename T>
vec3<T> rotation3<T>::get_vector() const noexcept
{
  return to_vector(m_quaternion);
}



template <typename T>
mat3x3<T> rotation3<T>::get_matrix() const noexcept
{
  return to_matrix(m_quaternion);
}



template <typename T>
rotation3<T>& rotation3<T>::operator*=(const rotation3<T>& rhs)
{
  m_quaternion *= rhs.m_quaternion;
  m_quaternion.normalize();
  return *this;
}



template <typename T>
rotation3<T>& rotation3<T>::invert()
{
  m_quaternion.invert().normalize();
  return *this;
}



template <typename T>
rotation3<T> operator*(rotation3<T> lhs, const rotation3<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
rotation3<T> inverse(rotation3<T> r)
{
  return r.invert();
}



template <typename T>
bool operator==(const rotation3<T>& lhs, const rotation3<T>& rhs) noexcept
{
  return lhs.get_quaternion() == rhs.get_quaternion();
}



template <typename T>
bool operator!=(const rotation3<T>& lhs, const rotation3<T>& rhs) noexcept
{
  return lhs.get_quaternion() != rhs.get_quaternion();
}



template <typename T>
bool close(const rotation3<T>& lhs, const rotation3<T>& rhs, T acc) noexcept
{
  return close(lhs.get_quaternion(), rhs.get_quaternion(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const rotation3<T>& r)
{
  return os << r.get_quaternion();
}



#define HOU_INSTANTIATE(T)                                                     \
  template class rotation3<T>;                                                 \
  template rotation3<T> operator*<T>(rotation3<T>, const rotation3<T>&);       \
  template rotation3<T> inverse<T>(rotation3<T>);                              \
  template bool operator==<T>(const rotation3<T>&, const rotation3<T>&);       \
  template bool operator!=<T>(const rotation3<T>&, const rotation3<T>&);       \
  template bool close<T>(const rotation3<T>&, const rotation3<T>&, T);         \
  template std::ostream& operator<<<T>(std::ostream&, const rotation3<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);

}  // namespace hou
