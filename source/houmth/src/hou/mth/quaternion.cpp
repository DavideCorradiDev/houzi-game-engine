// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/quaternion.hpp"



namespace hou
{

template <typename T>
quaternion<T> quaternion<T>::zero() noexcept
{
  return quaternion<T>(0, 0, 0, 0);
}



template <typename T>
quaternion<T> quaternion<T>::identity() noexcept
{
  return quaternion<T>(0, 0, 0, 1);
}



template <typename T>
quaternion<T>::quaternion() noexcept
  : quaternion(0, 0, 0, 0)
{}



template <typename T>
quaternion<T>::quaternion(T x, T y, T z, T w) noexcept
  : m_elements{x, y, z, w}
{}



template <typename T>
T quaternion<T>::x() const noexcept
{
  return m_elements[0];
}



template <typename T>
T& quaternion<T>::x() noexcept
{
  return m_elements[0];
}



template <typename T>
T quaternion<T>::y() const noexcept
{
  return m_elements[1];
}



template <typename T>
T& quaternion<T>::y() noexcept
{
  return m_elements[1];
}



template <typename T>
T quaternion<T>::z() const noexcept
{
  return m_elements[2];
}



template <typename T>
T& quaternion<T>::z() noexcept
{
  return m_elements[2];
}



template <typename T>
T quaternion<T>::w() const noexcept
{
  return m_elements[3];
}



template <typename T>
T& quaternion<T>::w() noexcept
{
  return m_elements[3];
}



template <typename T>
const T* quaternion<T>::data() const noexcept
{
  return m_elements.data();
}



template <typename T>
quaternion<T>& quaternion<T>::operator+=(const quaternion<T>& rhs) noexcept
{
  m_elements[0] += rhs.m_elements[0];
  m_elements[1] += rhs.m_elements[1];
  m_elements[2] += rhs.m_elements[2];
  m_elements[3] += rhs.m_elements[3];
  return *this;
}



template <typename T>
quaternion<T>& quaternion<T>::operator-=(const quaternion<T>& rhs) noexcept
{
  m_elements[0] -= rhs.m_elements[0];
  m_elements[1] -= rhs.m_elements[1];
  m_elements[2] -= rhs.m_elements[2];
  m_elements[3] -= rhs.m_elements[3];
  return *this;
}



template <typename T>
quaternion<T>& quaternion<T>::operator*=(const quaternion<T>& r) noexcept
{
  // clang-format off
  return *this = quaternion<T>(
    this->w() * r.x() + this->x() * r.w() + this->y() * r.z() - this->z() * r.y(),
    this->w() * r.y() - this->x() * r.z() + this->y() * r.w() + this->z() * r.x(),
    this->w() * r.z() + this->x() * r.y() - this->y() * r.x() + this->z() * r.w(),
    this->w() * r.w() - this->x() * r.x() - this->y() * r.y() - this->z() * r.z());
  // clang-format on
}



template <typename T>
quaternion<T>& quaternion<T>::operator*=(T rhs) noexcept
{
  m_elements[0] *= rhs;
  m_elements[1] *= rhs;
  m_elements[2] *= rhs;
  m_elements[3] *= rhs;
  return *this;
}



template <typename T>
quaternion<T>& quaternion<T>::operator/=(T rhs) noexcept
{
  m_elements[0] /= rhs;
  m_elements[1] /= rhs;
  m_elements[2] /= rhs;
  m_elements[3] /= rhs;
  return *this;
}



template <typename T>
quaternion<T>& quaternion<T>::invert()
{
  T snorm = square_norm(*this);
  HOU_PRECOND(!close(snorm, T(0)));
  return this->conjugate() /= snorm;
}



template <typename T>
quaternion<T>& quaternion<T>::conjugate() noexcept
{
  m_elements[0] = -m_elements[0];
  m_elements[1] = -m_elements[1];
  m_elements[2] = -m_elements[2];
  return *this;
}



template <typename T>
quaternion<T>& quaternion<T>::normalize()
{
  T quatNorm = norm(*this);
  HOU_PRECOND(!close(quatNorm, T(0)));
  return *this /= quatNorm;
}



template class quaternion<float>;
template class quaternion<double>;

}  // namespace hou
