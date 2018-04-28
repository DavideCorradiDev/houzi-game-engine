// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/transform2.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rectangle.hpp"
#include "hou/mth/rotation2.hpp"

#include <cmath>



namespace hou
{

template <typename T>
  transform2<T> transform2<T>::identity()
{
  return transform2<T>();
}



template <typename T>
  transform2<T> transform2<T>::translation(const Vec2<T>& translation)
{
  return transform2<T>(mat2x2<T>::identity(), translation);
}



template <typename T>
  transform2<T> transform2<T>::rotation(const rot2<T>& rotation)
{
  return transform2<T>(rotation.get_matrix(), Vec2<T>::zero());
}



template <typename T>
  transform2<T> transform2<T>::scale(const Vec2<T>& scale)
{
  return transform2<T>(mat2x2<T>(scale.x(), T(0), T(0), scale.y())
  , Vec2<T>::zero());
}



template <typename T>
  transform2<T> transform2<T>::shear(T sxy, T syx)
{
  return transform2<T>(mat2x2<T>(T(1), sxy, syx, T(1)), Vec2<T>::zero());
}



template <typename T>
  transform2<T> transform2<T>::orthographic_projection
  (const Rect<T>& clippingPlane)

{
  return translation(Vec2<T>(T(-1), T(-1)))
    * scale(Vec2<T>(2 / clippingPlane.w(), 2 / clippingPlane.h()))
    * translation(Vec2<T>(-clippingPlane.x(), -clippingPlane.y()));
}



template <typename T>
  transform2<T>::transform2()
  : m_mat(mat2x2<T>::identity())
  , m_vec(Vec2<T>::zero()) {}



template <typename T>
template <typename U>
  transform2<T>::transform2(const transform2<U>& other)
  : m_mat(static_cast<mat2x2<T>>(other.m_mat))
  , m_vec(static_cast<Vec2<T>>(other.m_vec))
{}



template <typename T>
  Mat4x4<T> transform2<T>::to_mat4x4() const
{
  return Mat4x4<T>
  {
    m_mat(0), m_mat(1), 0, m_vec(0),
    m_mat(2), m_mat(3), 0, m_vec(1),
    T(0),       T(0),       T(1), T(0),
    T(0),       T(0),       T(0), T(1)
  };
}



template <typename T>
  transform2<T>& transform2<T>::invert()
{
  m_mat.invert();
  m_vec = -m_mat * m_vec;
  return *this;
}



template <typename T>
  transform2<T>& transform2<T>::operator*=(const transform2<T>& rhs)
{
  m_vec += m_mat * rhs.m_vec;
  m_mat = m_mat * rhs.m_mat;
  return *this;
}



template <typename T>
  Vec2<T> transform2<T>::transform_vector(const Vec2<T>& vec) const
{
  return m_mat * vec;
}



template <typename T>
  Vec2<T> transform2<T>::transform_point(const Vec2<T>& point) const
{
  return m_vec + m_mat * point;
}



template <typename T>
  transform2<T>::transform2(const mat2x2<T>& r, const Vec2<T>& t)
  : m_mat(r)
  , m_vec(t)
{}



template <typename T>
  transform2<T> operator*(transform2<T> lhs, const transform2<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
  transform2<T> inverse(transform2<T> t)
{
  return t.invert();
}



template <typename T>
  std::ostream& operator<<(std::ostream& os, const transform2<T>& t)
{
  return os << t.to_mat4x4();
}



#define HOU_INSTANTIATE(T) \
  template class transform2<T>; \
  template transform2<T> operator*<T>(transform2<T>, const transform2<T>&); \
  template transform2<T> inverse<T>(transform2<T>); \
  template std::ostream& operator<<<T>(std::ostream&, const transform2<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template transform2<float>::transform2<double>(const transform2<double>&);
template transform2<double>::transform2<float>(const transform2<float>&);

}

