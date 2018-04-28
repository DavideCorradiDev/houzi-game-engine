// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/Quaternion.hpp"



namespace hou
{

template <typename T>
  Quaternion<T> Quaternion<T>::zero()
{
  return Quaternion<T>(0, 0, 0, 0);
}



template <typename T>
  Quaternion<T> Quaternion<T>::identity()
{
  return Quaternion<T>(0, 0, 0, 1);
}



template <typename T>
  Quaternion<T>::Quaternion()
  : Quaternion(0, 0, 0, 0)
{}



template <typename T>
  Quaternion<T>::Quaternion(T x, T y, T z, T w)
  : mElements{x, y, z, w}
{}



template <typename T>
  Quaternion<T>::Quaternion(std::initializer_list<T> elements)
  : mElements()
{
  HOU_EXPECT(elements.size() == mElements.size());
  std::copy(elements.begin(), elements.end(), mElements.begin());
}



template <typename T>
template <typename U>
  Quaternion<T>::Quaternion(const Quaternion<U>& other)
  : Quaternion
    ( static_cast<T>(other.x())
    , static_cast<T>(other.y())
    , static_cast<T>(other.z())
    , static_cast<T>(other.w()))
{}



template <typename T>
  T Quaternion<T>::x() const
{
  return mElements[0];
}



template <typename T>
  T& Quaternion<T>::x()
{
  return mElements[0];
}



template <typename T>
  T Quaternion<T>::y() const
{
  return mElements[1];
}



template <typename T>
  T& Quaternion<T>::y()
{
  return mElements[1];
}



template <typename T>
  T Quaternion<T>::z() const
{
  return mElements[2];
}



template <typename T>
  T& Quaternion<T>::z()
{
  return mElements[2];
}



template <typename T>
  T Quaternion<T>::w() const
{
  return mElements[3];
}



template <typename T>
  T& Quaternion<T>::w()
{
  return mElements[3];
}



template <typename T>
  const T* Quaternion<T>::data() const
{
  return mElements.data();
}



template <typename T>
  Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& rhs)
{
  mElements[0] += rhs.mElements[0];
  mElements[1] += rhs.mElements[1];
  mElements[2] += rhs.mElements[2];
  mElements[3] += rhs.mElements[3];
  return *this;
}



template <typename T>
  Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& rhs)
{
  mElements[0] -= rhs.mElements[0];
  mElements[1] -= rhs.mElements[1];
  mElements[2] -= rhs.mElements[2];
  mElements[3] -= rhs.mElements[3];
  return *this;
}



template <typename T>
  Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& r)
{
  return *this = Quaternion<T>
    ( this->w()*r.x() + this->x()*r.w() + this->y()*r.z() - this->z()*r.y()
    , this->w()*r.y() - this->x()*r.z() + this->y()*r.w() + this->z()*r.x()
    , this->w()*r.z() + this->x()*r.y() - this->y()*r.x() + this->z()*r.w()
    , this->w()*r.w() - this->x()*r.x() - this->y()*r.y() - this->z()*r.z());
}



template <typename T>
  Quaternion<T>& Quaternion<T>::operator*=(T rhs)
{
  mElements[0] *= rhs;
  mElements[1] *= rhs;
  mElements[2] *= rhs;
  mElements[3] *= rhs;
  return *this;
}



template <typename T>
  Quaternion<T>& Quaternion<T>::operator/=(T rhs)
{
  mElements[0] /= rhs;
  mElements[1] /= rhs;
  mElements[2] /= rhs;
  mElements[3] /= rhs;
  return *this;
}



template <typename T>
  Quaternion<T>& Quaternion<T>::invert()
{
  T sqNorm = squareNorm(*this);
  HOU_EXPECT(!close(sqNorm, T(0)));
  return this->conjugate() /= sqNorm;
}



template <typename T>
  Quaternion<T>& Quaternion<T>::conjugate()
{
  mElements[0] = -mElements[0];
  mElements[1] = -mElements[1];
  mElements[2] = -mElements[2];
  return *this;
}



template <typename T>
  Quaternion<T>& Quaternion<T>::normalize()
{
  T quatNorm = norm(*this);
  HOU_EXPECT(!close(quatNorm, T(0)));
  return *this /= quatNorm;
}



template <typename T>
  Quaternion<T> operator+(Quaternion<T> lhs, const Quaternion<T>& rhs)
{
  return lhs += rhs;
}



template <typename T>
  Quaternion<T> operator-(Quaternion<T> lhs, const Quaternion<T>& rhs)
{
  return lhs -= rhs;
}



template <typename T>
  Quaternion<T> operator*(Quaternion<T> lhs, const Quaternion<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
  T squareNorm(const Quaternion<T>& q)
{
  return q.x() * q.x() + q.y() * q.y() + q.z() * q.z() + q.w() * q.w();
}



template <typename T>
  T norm(const Quaternion<T>& q)
{
  return std::sqrt(squareNorm(q));
}



template <typename T>
  Quaternion<T> inverse(Quaternion<T> q)
{
  return q.invert();
}



template <typename T>
  Quaternion<T> conjugate(Quaternion<T> q)
{
  return q.conjugate();
}



template <typename T>
  Quaternion<T> normalized(Quaternion<T> q)
{
  return q.normalize();
}



template <typename T>
  std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q)
{
  return os << "(" << q.x() << "," << q.y() << "," << q.z() << "," << q.w()
    << ")";
}



#define HOU_INSTANTIATE(T) \
  template class Quaternion<T>; \
  template Quaternion<T> operator+<T>(Quaternion<T>, const Quaternion<T>&); \
  template Quaternion<T> operator-<T>(Quaternion<T>, const Quaternion<T>&); \
  template Quaternion<T> operator*<T>(Quaternion<T>, const Quaternion<T>&); \
  template Quaternion<T> inverse<T>(Quaternion<T>); \
  template Quaternion<T> conjugate<T>(Quaternion<T>); \
  template T squareNorm<T>(const Quaternion<T>&); \
  template T norm<T>(const Quaternion<T>&); \
  template Quaternion<T> normalized<T>(Quaternion<T>); \
  template std::ostream& operator<<<T>(std::ostream&, const Quaternion<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template Quaternion<float>::Quaternion<double>(const Quaternion<double>&);
template Quaternion<double>::Quaternion<float>(const Quaternion<float>&);

}

