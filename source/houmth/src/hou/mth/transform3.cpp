// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/transform3.hpp"

#include "hou/mth/math_functions.hpp"
#include "hou/mth/rectangle.hpp"

#include <cmath>



namespace hou
{

template <typename T>
transform3<T> transform3<T>::identity()
{
  return transform3<T>();
}



template <typename T>
transform3<T> transform3<T>::translation(const vec3<T>& translation)
{
  return transform3<T>(mat3x3<T>::identity(), translation);
}



template <typename T>
transform3<T> transform3<T>::rotation(const rot3<T>& rotation)
{
  return transform3<T>(rotation.get_matrix(), vec3<T>::zero());
}



template <typename T>
transform3<T> transform3<T>::scale(const vec3<T>& scale)
{
  // clang-format off
  return transform3<T>(
    mat3x3<T>{
      scale.x(), T(0), T(0),
      T(0), scale.y(), T(0),
      T(0), T(0), scale.z()},
    vec3<T>::zero());
  // clang-format on
}



template <typename T>
transform3<T> transform3<T>::shear(T sxy, T sxz, T syx, T syz, T szx, T szy)
{
  // clang-format off
  return transform3<T>(
    mat3x3<T>{
      T(1), sxy, sxz,
      syx, T(1), syz,
      szx, szy, T(1)},
    vec3<T>::zero());
  // clang-format on
}



template <typename T>
transform3<T>::transform3()
  : m_mat(mat3x3<T>::identity())
  , m_vec(vec3<T>::zero())
{}



template <typename T>
template <typename U>
transform3<T>::transform3(const transform3<U>& other)
  : m_mat(static_cast<mat3x3<T>>(other.m_mat))
  , m_vec(static_cast<vec3<T>>(other.m_vec))
{}



template <typename T>
mat4x4<T> transform3<T>::to_mat4x4() const
{
  // clang-format off
  return mat4x4<T>{
    m_mat(0), m_mat(1), m_mat(2), m_vec(0),
    m_mat(3), m_mat(4), m_mat(5), m_vec(1),
    m_mat(6), m_mat(7), m_mat(8), m_vec(2),
    T(0), T(0), T(0), T(1)};
  // clang-format on
}



template <typename T>
transform3<T>& transform3<T>::operator*=(const transform3<T>& r)
{
  m_vec += m_mat * r.m_vec;
  m_mat = m_mat * r.m_mat;
  return *this;
}



template <typename T>
transform3<T>& transform3<T>::invert()
{
  m_mat.invert();
  m_vec = -m_mat * m_vec;
  return *this;
}



template <typename T>
vec3<T> transform3<T>::transform_vector(const vec3<T>& vec) const
{
  return m_mat * vec;
}



template <typename T>
vec3<T> transform3<T>::transform_point(const vec3<T>& point) const
{
  return m_vec + m_mat * point;
}



template <typename T>
transform3<T>::transform3(const mat3x3<T>& r, const vec3<T>& t)
  : m_mat(r)
  , m_vec(t)
{}



template <typename T>
transform3<T> operator*(transform3<T> lhs, const transform3<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
transform3<T> inverse(transform3<T> t)
{
  return t.invert();
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const transform3<T>& t)
{
  return os << t.to_mat4x4();
}



#define HOU_INSTANTIATE(T) \
  template class transform3<T>; \
  template transform3<T> operator*<T>(transform3<T>, const transform3<T>&); \
  template transform3<T> inverse<T>(transform3<T>); \
  template std::ostream& operator<<<T>(std::ostream&, const transform3<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);
template transform3<float>::transform3<double>(const transform3<double>&);
template transform3<double>::transform3<float>(const transform3<float>&);

}  // namespace hou
