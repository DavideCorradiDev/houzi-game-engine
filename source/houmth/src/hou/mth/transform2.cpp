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
transform2<T> transform2<T>::identity() noexcept
{
  return transform2<T>();
}



template <typename T>
transform2<T> transform2<T>::translation(const vec2<T>& translation) noexcept
{
  return transform2<T>(mat2x2<T>::identity(), translation);
}



template <typename T>
transform2<T> transform2<T>::rotation(const rot2<T>& rotation) noexcept
{
  return transform2<T>(rotation.get_matrix(), vec2<T>::zero());
}



template <typename T>
transform2<T> transform2<T>::scale(const vec2<T>& scale) noexcept
{
  return transform2<T>(
    mat2x2<T>(scale.x(), T(0), T(0), scale.y()), vec2<T>::zero());
}



template <typename T>
transform2<T> transform2<T>::shear(T sxy, T syx) noexcept
{
  return transform2<T>(mat2x2<T>(T(1), sxy, syx, T(1)), vec2<T>::zero());
}



template <typename T>
transform2<T> transform2<T>::orthographic_projection(
  const rect<T>& clipping_plane) noexcept

{
  return translation(vec2<T>(T(-1), T(-1)))
    * scale(vec2<T>(2 / clipping_plane.w(), 2 / clipping_plane.h()))
    * translation(vec2<T>(-clipping_plane.x(), -clipping_plane.y()));
}



template <typename T>
transform2<T>::transform2() noexcept
  : m_mat(mat2x2<T>::identity())
  , m_vec(vec2<T>::zero())
{}



template <typename T>
mat4x4<T> transform2<T>::to_mat4x4() const noexcept
{
  // clang-format off
  return mat4x4<T>{
    m_mat(0), m_mat(1), T(0), m_vec(0),
    m_mat(2), m_mat(3), T(0), m_vec(1),
    T(0), T(0), T(1), T(0),
    T(0), T(0), T(0), T(1)};
  // clang-format on
}



template <typename T>
transform2<T>& transform2<T>::operator*=(const transform2<T>& rhs) noexcept
{
  m_vec += m_mat * rhs.m_vec;
  m_mat = m_mat * rhs.m_mat;
  return *this;
}



template <typename T>
transform2<T>& transform2<T>::invert()
{
  m_mat.invert();
  m_vec = -m_mat * m_vec;
  return *this;
}



template <typename T>
vec2<T> transform2<T>::transform_vector(const vec2<T>& vec) const noexcept
{
  return m_mat * vec;
}



template <typename T>
vec2<T> transform2<T>::transform_point(const vec2<T>& point) const noexcept
{
  return m_vec + m_mat * point;
}



template <typename T>
transform2<T>::transform2(const mat2x2<T>& r, const vec2<T>& t) noexcept
  : m_mat(r)
  , m_vec(t)
{}



template <typename T>
transform2<T> operator*(transform2<T> lhs, const transform2<T>& rhs) noexcept
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



#define HOU_INSTANTIATE(T)                                                     \
  template class transform2<T>;                                                \
  template transform2<T> operator*<T>(transform2<T>, const transform2<T>&);    \
  template transform2<T> inverse<T>(transform2<T>);                            \
  template std::ostream& operator<<<T>(std::ostream&, const transform2<T>&)

HOU_INSTANTIATE(float);
HOU_INSTANTIATE(double);

}  // namespace hou
