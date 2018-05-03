// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/quaternion.hpp"



namespace hou
{

template <typename T>
quaternion<T> quaternion<T>::zero()
{
  return quaternion<T>(0, 0, 0, 0);
}



template <typename T>
quaternion<T> quaternion<T>::identity()
{
  return quaternion<T>(0, 0, 0, 1);
}



template <typename T>
quaternion<T>::quaternion()
  : quaternion(0, 0, 0, 0)
{}



template <typename T>
quaternion<T>::quaternion(T x, T y, T z, T w)
  : m_elements{x, y, z, w}
{}



template <typename T>
quaternion<T>::quaternion(std::initializer_list<T> elements)
  : m_elements()
{
  DEPRECATED_HOU_EXPECT(elements.size() == m_elements.size());
  std::copy(elements.begin(), elements.end(), m_elements.begin());
}



template <typename T>
template <typename U>
quaternion<T>::quaternion(const quaternion<U>& other)
  : quaternion(static_cast<T>(other.x()), static_cast<T>(other.y()),
      static_cast<T>(other.z()), static_cast<T>(other.w()))
{}



template <typename T>
T quaternion<T>::x() const
{
  return m_elements[0];
}



template <typename T>
T& quaternion<T>::x()
{
  return m_elements[0];
}



template <typename T>
T quaternion<T>::y() const
{
  return m_elements[1];
}



template <typename T>
T& quaternion<T>::y()
{
  return m_elements[1];
}



template <typename T>
T quaternion<T>::z() const
{
  return m_elements[2];
}



template <typename T>
T& quaternion<T>::z()
{
  return m_elements[2];
}



template <typename T>
T quaternion<T>::w() const
{
  return m_elements[3];
}



template <typename T>
T& quaternion<T>::w()
{
  return m_elements[3];
}



template <typename T>
const T* quaternion<T>::data() const
{
  return m_elements.data();
}



template <typename T>
quaternion<T>& quaternion<T>::operator+=(const quaternion<T>& rhs)
{
  m_elements[0] += rhs.m_elements[0];
  m_elements[1] += rhs.m_elements[1];
  m_elements[2] += rhs.m_elements[2];
  m_elements[3] += rhs.m_elements[3];
  return *this;
}



template <typename T>
quaternion<T>& quaternion<T>::operator-=(const quaternion<T>& rhs)
{
  m_elements[0] -= rhs.m_elements[0];
  m_elements[1] -= rhs.m_elements[1];
  m_elements[2] -= rhs.m_elements[2];
  m_elements[3] -= rhs.m_elements[3];
  return *this;
}



template <typename T>
quaternion<T>& quaternion<T>::operator*=(const quaternion<T>& r)
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
quaternion<T>& quaternion<T>::operator*=(T rhs)
{
  m_elements[0] *= rhs;
  m_elements[1] *= rhs;
  m_elements[2] *= rhs;
  m_elements[3] *= rhs;
  return *this;
}



template <typename T>
quaternion<T>& quaternion<T>::operator/=(T rhs)
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
  T sqNorm = square_norm(*this);
  DEPRECATED_HOU_EXPECT(!close(sqNorm, T(0)));
  return this->conjugate() /= sqNorm;
}



template <typename T>
quaternion<T>& quaternion<T>::conjugate()
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
  DEPRECATED_HOU_EXPECT(!close(quatNorm, T(0)));
  return *this /= quatNorm;
}



template <typename T>
quaternion<T> operator+(quaternion<T> lhs, const quaternion<T>& rhs)
{
  return lhs += rhs;
}



template <typename T>
quaternion<T> operator-(quaternion<T> lhs, const quaternion<T>& rhs)
{
  return lhs -= rhs;
}



template <typename T>
quaternion<T> operator*(quaternion<T> lhs, const quaternion<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
T square_norm(const quaternion<T>& q)
{
  return q.x() * q.x() + q.y() * q.y() + q.z() * q.z() + q.w() * q.w();
}



template <typename T>
T norm(const quaternion<T>& q)
{
  return std::sqrt(square_norm(q));
}



template <typename T>
quaternion<T> inverse(quaternion<T> q)
{
  return q.invert();
}



template <typename T>
quaternion<T> conjugate(quaternion<T> q)
{
  return q.conjugate();
}



template <typename T>
quaternion<T> normalized(quaternion<T> q)
{
  return q.normalize();
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const quaternion<T>& q)
{
  return os << "(" << q.x() << "," << q.y() << "," << q.z() << "," << q.w()
            << ")";
}



#define HOU_INSTANTIATE(T) \
  template class quaternion<T>; \
  template quaternion<T> operator+<T>(quaternion<T>, const quaternion<T>&); \
  template quaternion<T> operator-<T>(quaternion<T>, const quaternion<T>&); \
  template quaternion<T> operator*<T>(quaternion<T>, const quaternion<T>&); \
  template quaternion<T> inverse<T>(quaternion<T>); \
  template quaternion<T> conjugate<T>(quaternion<T>); \
  template T square_norm<T>(const quaternion<T>&); \
  template T norm<T>(const quaternion<T>&); \
  template quaternion<T> normalized<T>(quaternion<T>); \
  template std::ostream& operator<<<T>(std::ostream&, const quaternion<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template quaternion<float>::quaternion<double>(const quaternion<double>&);
template quaternion<double>::quaternion<float>(const quaternion<float>&);

}  // namespace hou
