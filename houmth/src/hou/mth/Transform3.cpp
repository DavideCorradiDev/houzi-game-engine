// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/Transform3.hpp"

#include "hou/mth/MathFunctions.hpp"
#include "hou/mth/Rectangle.hpp"

#include <cmath>



namespace hou
{

template <typename T>
  Transform3<T> Transform3<T>::identity()
{
  return Transform3<T>();
}



template <typename T>
  Transform3<T> Transform3<T>::translation(const Vec3<T>& translation)
{
  return Transform3<T>(Mat3x3<T>::identity(), translation);
}



template <typename T>
  Transform3<T> Transform3<T>::rotation(const Rot3<T>& rotation)
{
  return Transform3<T>(rotation.getMatrix(), Vec3<T>::zero());
}



template <typename T>
  Transform3<T> Transform3<T>::scale(const Vec3<T>& scale)
{
  return Transform3<T>
    ( Mat3x3<T>(scale.x(), T(0), T(0), T(0), scale.y(), T(0), T(0), T(0), scale.z())
    , Vec3<T>::zero());
}



template <typename T>
  Transform3<T> Transform3<T>::shear(T sxy, T sxz, T syx, T syz, T szx
  , T szy)
{
  return Transform3<T>
    ( Mat3x3<T>(T(1), sxy, sxz, syx, T(1), syz, szx, szy, T(1))
    , Vec3<T>::zero());
}



template <typename T>
  Transform3<T>::Transform3()
  : mMat(Mat3x3<T>::identity())
  , mVec(Vec3<T>::zero()) {}



template <typename T>
template <typename U>
  Transform3<T>::Transform3(const Transform3<U>& other)
  : mMat(static_cast<Mat3x3<T>>(other.mMat))
  , mVec(static_cast<Vec3<T>>(other.mVec)) {}



template <typename T>
  Mat4x4<T> Transform3<T>::toMat4x4() const
{
  return Mat4x4<T>
  {
    mMat(0), mMat(1), mMat(2), mVec(0),
    mMat(3), mMat(4), mMat(5), mVec(1),
    mMat(6), mMat(7), mMat(8), mVec(2),
    T(0),     T(0),     T(0),     T(1)
  };
}



template <typename T>
  Transform3<T>& Transform3<T>::operator*=(const Transform3<T>& r)
{
  mVec += mMat * r.mVec;
  mMat = mMat * r.mMat;
  return *this;
}



template <typename T>
  Transform3<T>& Transform3<T>::invert()
{
  mMat.invert();
  mVec = -mMat * mVec;
  return *this;
}



template <typename T>
  Vec3<T> Transform3<T>::transformVector(const Vec3<T>& vec) const
{
  return mMat * vec;
}



template <typename T>
  Vec3<T> Transform3<T>::transformPoint(const Vec3<T>& point) const
{
  return mVec + mMat * point;
}



template <typename T>
  Transform3<T>::Transform3(const Mat3x3<T>& r, const Vec3<T>& t)
  : mMat(r)
  , mVec(t)
{}



template <typename T>
  Transform3<T> operator*(Transform3<T> lhs, const Transform3<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
  Transform3<T> inverse(Transform3<T> t)
{
  return t.invert();
}



template <typename T>
  std::ostream& operator<<(std::ostream& os, const Transform3<T>& t)
{
  return os << t.toMat4x4();
}



#define HOU_INSTANTIATE(T) \
  template class Transform3<T>; \
  template Transform3<T> operator*<T>(Transform3<T>, const Transform3<T>&); \
  template Transform3<T> inverse<T>(Transform3<T>); \
  template std::ostream& operator<<<T>(std::ostream&, const Transform3<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template Transform3<float>::Transform3<double>(const Transform3<double>&);
template Transform3<double>::Transform3<float>(const Transform3<float>&);

}

