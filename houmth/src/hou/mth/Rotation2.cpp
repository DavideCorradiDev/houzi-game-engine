// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/mth/Rotation2.hpp"

#include "hou/cor/CorUtils.hpp"
#include "hou/cor/Diagnostics.hpp"

#include "hou/mth/Matrix.hpp"
#include "hou/mth/MthUtils.hpp"



namespace hou
{

namespace
{

template <typename T>
  T toAngle(const Mat2x2<T>& m);
template <typename T>
  Mat2x2<T> toMatrix(T angle);
template <typename T>
  T normalizeAngle(T angle);



template <typename T>
  T toAngle(const Mat2x2<T>& m)
{
  return std::atan2(m(2), m(0));
}



template <typename T>
  Mat2x2<T> toMatrix(T angle)
{
  T c = std::cos(angle);
  T s = std::sin(angle);
  return Mat2x2<T>{c, -s, s, c};
}



template <typename T>
  T normalizeAngle(T angle)
{
  while(angle <= -PI_F)
  {
    angle += 2 * PI_F;
  }
  while(angle > PI_F)
  {
    angle -= 2 * PI_F;
  }
  return angle;
}

}



template <typename T>
  Rotation2<T> Rotation2<T>::identity()
{
  return Rotation2<T>();
}



template <typename T>
  Rotation2<T>::Rotation2()
  : mAngle(0)
{}



template <typename T>
  Rotation2<T>::Rotation2(T angle)
  : mAngle(normalizeAngle(angle))
{}



template <typename T>
  Rotation2<T>::Rotation2(const Mat2x2<T>& m)
  : mAngle(toAngle(m))
{
  HOU_EXPECT(close(T(1), det(m)) && close(Mat2x2<T>::identity(), m * transpose(m)));
  HOU_EXPECT_DEV(mAngle > -PI_F && mAngle <= PI_F);
}



template <typename T>
template <typename U>
  Rotation2<T>::Rotation2(const Rotation2<U>& other)
  : mAngle(static_cast<T>(other.mAngle))
{}



template <typename T>
  T Rotation2<T>::getAngle() const
{
  return mAngle;
}



template <typename T>
  Mat2x2<T> Rotation2<T>::getMatrix() const
{
  return toMatrix(mAngle);
}



template <typename T>
  Rotation2<T>& Rotation2<T>::operator*=(const Rotation2<T>& rhs)
{
  mAngle = normalizeAngle(mAngle + rhs.mAngle);
  return *this;
}



template <typename T>
  Rotation2<T>& Rotation2<T>::invert()
{
  mAngle = normalizeAngle(-mAngle);
  return *this;
}



template <typename T>
  Rotation2<T> operator*(Rotation2<T> lhs, const Rotation2<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
  Rotation2<T> inverse(Rotation2<T> r)
{
  return r.invert();
}



GCC_DIAGNOSTIC_PUSH()
GCC_DIAGNOSTIC_IGNORED(-Wfloat-equal)
template <typename T>
  bool operator==(const Rotation2<T>& lhs, const Rotation2<T>& rhs)
{
  return lhs.getAngle() == rhs.getAngle();
}
GCC_DIAGNOSTIC_POP()



GCC_DIAGNOSTIC_PUSH()
GCC_DIAGNOSTIC_IGNORED(-Wfloat-equal)
template <typename T>
  bool operator!=(const Rotation2<T>& lhs, const Rotation2<T>& rhs)
{
  return lhs.getAngle() != rhs.getAngle();
}
GCC_DIAGNOSTIC_POP()



template <typename T>
  bool close(const Rotation2<T>& lhs, const Rotation2<T>& rhs, T acc)
{
  return close(lhs.getAngle(), rhs.getAngle(), acc);
}



template <typename T>
  std::ostream& operator<<(std::ostream& os, const Rotation2<T>& r)
{
  return os << r.getAngle();
}



#define HOU_INSTANTIATE(T) \
  template class Rotation2<T>; \
  template Rotation2<T> operator*<T>(Rotation2<T>, const Rotation2<T>&); \
  template Rotation2<T> inverse<T>(Rotation2<T>); \
  template bool operator==<T>(const Rotation2<T>&, const Rotation2<T>&); \
  template bool operator!=<T>(const Rotation2<T>&, const Rotation2<T>&); \
  template bool close<T>(const Rotation2<T>&, const Rotation2<T>&, T); \
  template std::ostream& operator<<<T>(std::ostream&, const Rotation2<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template Rotation2<float>::Rotation2<double>(const Rotation2<double>&);
template Rotation2<double>::Rotation2<float>(const Rotation2<float>&);

}

