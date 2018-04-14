// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/Rotation3.hpp"

#include "hou/mth/Matrix.hpp"



namespace hou
{

namespace
{

template <typename T>
  Quaternion<T> toQuaternion(Vec3<T> v);
template <typename T>
  Quaternion<T> toQuaternion(const Mat3x3<T>& m);
template <typename T>
  Vec3<T> toVector(const Quaternion<T>& q);
template <typename T>
  Mat3x3<T> toMatrix(const Quaternion<T>& q);



template <typename T>
  Quaternion<T> toQuaternion(Vec3<T> v)
{
  T angle = norm(v);
  v /= angle;
  T s = std::sin(angle / 2);
  T c = std::cos(angle / 2);
  return Quaternion<T>(v.x() * s, v.y() * s, v.z() * s, c);
}



template <typename T>
  Quaternion<T> toQuaternion(const Mat3x3<T>& m)
{
  T tr = trace(m);
  if(tr > T(0))
  {
    T s = sqrt(1.f + tr) * 2.f;
    return Quaternion<T>
    {
      (m(2,1) - m(1,2)) / s,
      (m(0,2) - m(2,0)) / s,
      (m(1,0) - m(0,1)) / s,
      0.25f * s
    };
  }
  else if((m(0,0) > m(1,1)) && (m(0,0) > m(2,2)))
  {
    T s = sqrt(1.f + m(0,0) - m(1,1) - m(2,2)) * 2.f;
    return Quaternion<T>
    {
      0.25f * s,
      (m(0,1) + m(1,0)) / s,
      (m(0,2) + m(2,0)) / s,
      (m(2,1) - m(1,2)) / s,
    };
  }
  else if(m(1,1) > m(2,2))
  {
    T s = sqrt(1.f + m(1,1) - m(0,0) - m(2,2)) * 2.f;
    return Quaternion<T>
    {
      (m(0,1) + m(1,0)) / s,
      0.25f * s,
      (m(1,2) + m(2,1)) / s,
      (m(0,2) - m(2,0)) / s,
    };
  }
  else
  {
    T s = sqrt(1.f + m(2,2) - m(0,0) - m(1,1)) * 2.f;
    return Quaternion<T>
    {
      (m(0,2) + m(2,0)) / s,
      (m(1,2) + m(2,1)) / s,
      0.25f * s,
      (m(1,0) - m(0,1)) / s,
    };
  }
}



template <typename T>
  Vec3<T> toVector(const Quaternion<T>& q)
{
  HOU_EXPECT_DEV(close(T(1), norm(q)));
  Vec3<T> v(q.x(), q.y(), q.z());
  T vecNorm = norm(v);
  if(!close(T(0), vecNorm))
  {
    v *= 2 * std::atan2(vecNorm, q.w()) / vecNorm;
  }
  return v;
}



template <typename T>
  Mat3x3<T> toMatrix(const Quaternion<T>& q)
{
  HOU_EXPECT_DEV(close(T(1), norm(q)));
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
  return Mat3x3<T>
    ( -1 + xx + ww, xy - zw, xz + yw
    , xy + zw, -1 + yy + ww, yz - xw
    , xz - yw, xw + yz, -1 + zz + ww);
}

}



template <typename T>
  Rotation3<T> Rotation3<T>::identity()
{
  return Rotation3<T>();
}



template <typename T>
  Rotation3<T> Rotation3<T>::x(T angle)
{
  angle /= 2;
  return Rotation3<T>(Quaternion<T>(std::sin(angle), 0, 0, std::cos(angle)));
}



template <typename T>
  Rotation3<T> Rotation3<T>::y(T angle)
{
  angle /= 2;
  return Rotation3<T>(Quaternion<T>(0, std::sin(angle), 0, std::cos(angle)));
}



template <typename T>
  Rotation3<T> Rotation3<T>::z(T angle)
{
  angle /= 2;
  return Rotation3<T>(Quaternion<T>(0, 0, std::sin(angle), std::cos(angle)));
}



template <typename T>
  Rotation3<T>::Rotation3()
  : mQuaternion(Quaternion<T>::identity())
{}



template <typename T>
  Rotation3<T>::Rotation3(const Quaternion<T>& q)
  : mQuaternion(normalized(q))
{}



template <typename T>
  Rotation3<T>::Rotation3(const Vec3<T>& v)
  : mQuaternion(normalized(toQuaternion(v)))
{}



template <typename T>
  Rotation3<T>::Rotation3(const Mat3x3<T>& m)
  : mQuaternion(normalized(toQuaternion(m)))
{}



template <typename T>
template <typename U>
  Rotation3<T>::Rotation3(const Rotation3<U>& other)
  : mQuaternion(normalized(static_cast<Quaternion<T>>(other.mQuaternion)))
{}



template <typename T>
  const Quaternion<T>& Rotation3<T>::getQuaternion() const
{
  return mQuaternion;
}



template <typename T>
  Vec3<T> Rotation3<T>::getVector() const
{
  return toVector(mQuaternion);
}



template <typename T>
  Mat3x3<T> Rotation3<T>::getMatrix() const
{
  return toMatrix(mQuaternion);
}



template <typename T>
  Rotation3<T>& Rotation3<T>::operator*=(const Rotation3<T>& rhs)
{
  mQuaternion *= rhs.mQuaternion;
  mQuaternion.normalize();
  return *this;
}



template <typename T>
  Rotation3<T>& Rotation3<T>::invert()
{
  mQuaternion.invert().normalize();
  return *this;
}



template <typename T>
  Rotation3<T> operator*(Rotation3<T> lhs, const Rotation3<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
  Rotation3<T> inverse(Rotation3<T> r)
{
  return r.invert();
}



template <typename T>
  bool operator==(const Rotation3<T>& lhs, const Rotation3<T>& rhs)
{
  return lhs.getQuaternion() == rhs.getQuaternion();
}



template <typename T>
  bool operator!=(const Rotation3<T>& lhs, const Rotation3<T>& rhs)
{
  return lhs.getQuaternion() != rhs.getQuaternion();
}



template <typename T>
  bool close(const Rotation3<T>& lhs, const Rotation3<T>& rhs, T acc)
{
  return close(lhs.getQuaternion(), rhs.getQuaternion(), acc);
}



template <typename T>
  std::ostream& operator<<(std::ostream& os, const Rotation3<T>& r)
{
  return os << r.getQuaternion();
}



#define HOU_INSTANTIATE(T) \
  template class Rotation3<T>; \
  template Rotation3<T> operator*<T>(Rotation3<T>, const Rotation3<T>&); \
  template Rotation3<T> inverse<T>(Rotation3<T>); \
  template bool operator==<T>(const Rotation3<T>&, const Rotation3<T>&); \
  template bool operator!=<T>(const Rotation3<T>&, const Rotation3<T>&); \
  template bool close<T>(const Rotation3<T>&, const Rotation3<T>&, T); \
  template std::ostream& operator<<<T>(std::ostream&, const Rotation3<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template Rotation3<float>::Rotation3<double>(const Rotation3<double>&);
template Rotation3<double>::Rotation3<float>(const Rotation3<float>&);

}

