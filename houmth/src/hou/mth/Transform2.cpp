// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/Transform2.hpp"

#include "hou/mth/MathFunctions.hpp"
#include "hou/mth/Rectangle.hpp"
#include "hou/mth/Rotation2.hpp"

#include <cmath>



namespace hou
{

template <typename T>
  Transform2<T> Transform2<T>::identity()
{
  return Transform2<T>();
}



template <typename T>
  Transform2<T> Transform2<T>::translation(const Vec2<T>& translation)
{
  return Transform2<T>(Mat2x2<T>::identity(), translation);
}



template <typename T>
  Transform2<T> Transform2<T>::rotation(const Rot2<T>& rotation)
{
  return Transform2<T>(rotation.getMatrix(), Vec2<T>::zero());
}



template <typename T>
  Transform2<T> Transform2<T>::scale(const Vec2<T>& scale)
{
  return Transform2<T>(Mat2x2<T>(scale.x(), T(0), T(0), scale.y())
  , Vec2<T>::zero());
}



template <typename T>
  Transform2<T> Transform2<T>::shear(T sxy, T syx)
{
  return Transform2<T>(Mat2x2<T>(T(1), sxy, syx, T(1)), Vec2<T>::zero());
}



template <typename T>
  Transform2<T> Transform2<T>::orthographicProjection
  (const Rect<T>& clippingPlane)

{
  return translation(Vec2<T>(T(-1), T(-1)))
    * scale(Vec2<T>(2 / clippingPlane.w(), 2 / clippingPlane.h()))
    * translation(Vec2<T>(-clippingPlane.x(), -clippingPlane.y()));
}



template <typename T>
  Transform2<T>::Transform2()
  : mMat(Mat2x2<T>::identity())
  , mVec(Vec2<T>::zero()) {}



template <typename T>
template <typename U>
  Transform2<T>::Transform2(const Transform2<U>& other)
  : mMat(static_cast<Mat2x2<T>>(other.mMat))
  , mVec(static_cast<Vec2<T>>(other.mVec))
{}



template <typename T>
  Mat4x4<T> Transform2<T>::toMat4x4() const
{
  return Mat4x4<T>
  {
    mMat(0), mMat(1), 0, mVec(0),
    mMat(2), mMat(3), 0, mVec(1),
    T(0),       T(0),       T(1), T(0),
    T(0),       T(0),       T(0), T(1)
  };
}



template <typename T>
  Transform2<T>& Transform2<T>::invert()
{
  mMat.invert();
  mVec = -mMat * mVec;
  return *this;
}



template <typename T>
  Transform2<T>& Transform2<T>::operator*=(const Transform2<T>& rhs)
{
  mVec += mMat * rhs.mVec;
  mMat = mMat * rhs.mMat;
  return *this;
}



template <typename T>
  Vec2<T> Transform2<T>::transformVector(const Vec2<T>& vec) const
{
  return mMat * vec;
}



template <typename T>
  Vec2<T> Transform2<T>::transformPoint(const Vec2<T>& point) const
{
  return mVec + mMat * point;
}



template <typename T>
  Transform2<T>::Transform2(const Mat2x2<T>& r, const Vec2<T>& t)
  : mMat(r)
  , mVec(t)
{}



template <typename T>
  Transform2<T> operator*(Transform2<T> lhs, const Transform2<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
  Transform2<T> inverse(Transform2<T> t)
{
  return t.invert();
}



template <typename T>
  std::ostream& operator<<(std::ostream& os, const Transform2<T>& t)
{
  return os << t.toMat4x4();
}



#define HOU_INSTANTIATE(T) \
  template class Transform2<T>; \
  template Transform2<T> operator*<T>(Transform2<T>, const Transform2<T>&); \
  template Transform2<T> inverse<T>(Transform2<T>); \
  template std::ostream& operator<<<T>(std::ostream&, const Transform2<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template Transform2<float>::Transform2<double>(const Transform2<double>&);
template Transform2<double>::Transform2<float>(const Transform2<float>&);

}

