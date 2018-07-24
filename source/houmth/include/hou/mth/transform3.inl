// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
const transform3<T>& transform3<T>::identity() noexcept
{
  static const transform3 t;
  return t;
}



template <typename T>
constexpr transform3<T> transform3<T>::translation(
  const vec3<T>& translation) noexcept
{
  return transform3<T>(mat3x3<T>::identity(), translation);
}



template <typename T>
constexpr transform3<T> transform3<T>::rotation(
  const rot3<T>& rotation) noexcept
{
  return transform3<T>(rotation.get_matrix(), vec3<T>::zero());
}



template <typename T>
constexpr transform3<T> transform3<T>::scale(const vec3<T>& scale) noexcept
{
  // clang-format off
  return transform3<T>(
    mat3x3<T>{
      scale.x(),  T(0),       T(0),
      T(0),       scale.y(),  T(0),
      T(0),       T(0),       scale.z()},
    vec3<T>::zero());
  // clang-format on
}



template <typename T>
constexpr transform3<T> transform3<T>::shear(
  T sxy, T sxz, T syx, T syz, T szx, T szy) noexcept
{
  // clang-format off
  return transform3<T>(
    mat3x3<T>{
      T(1),  sxy,   sxz,
      syx,   T(1),  syz,
      szx,   szy,   T(1)},
    vec3<T>::zero());
  // clang-format on
}



template <typename T>
constexpr transform3<T>::transform3() noexcept
  : m_mat(mat3x3<T>::identity())
  , m_vec(vec3<T>::zero())
{}



template <typename T>
template <typename U, typename Enable>
constexpr transform3<T>::transform3(const transform3<U>& other) noexcept
  : m_mat(static_cast<mat3x3<T>>(other.m_mat))
  , m_vec(static_cast<vec3<T>>(other.m_vec))
{}



template <typename T>
constexpr transform3<T> operator*(
  transform3<T> lhs, const transform3<T>& rhs) noexcept
{
  return lhs *= rhs;
}



template <typename T>
constexpr transform3<T> inverse(transform3<T> t)
{
  return t.invert();
}



template <typename T>
constexpr mat4x4<T> transform3<T>::to_mat4x4() const noexcept
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
constexpr transform3<T>& transform3<T>::operator*=(
  const transform3<T>& r) noexcept
{
  m_vec += m_mat * r.m_vec;
  m_mat = m_mat * r.m_mat;
  return *this;
}



template <typename T>
constexpr transform3<T>& transform3<T>::invert()
{
  m_mat.invert();
  m_vec = -m_mat * m_vec;
  return *this;
}



template <typename T>
constexpr vec3<T> transform3<T>::transform_vector(const vec3<T>& vec) const
  noexcept
{
  return m_mat * vec;
}



template <typename T>
constexpr vec3<T> transform3<T>::transform_point(const vec3<T>& point) const
  noexcept
{
  return m_vec + m_mat * point;
}



template <typename T>
constexpr transform3<T>::transform3(
  const mat3x3<T>& r, const vec3<T>& t) noexcept
  : m_mat(r)
  , m_vec(t)
{}



template <typename T>
constexpr bool operator==(
  const transform3<T>& lhs, const transform3<T>& rhs) noexcept
{
  return lhs.m_mat == rhs.m_mat && lhs.m_vec == rhs.m_vec;
}



template <typename T>
constexpr bool operator!=(
  const transform3<T>& lhs, const transform3<T>& rhs) noexcept
{
  return !(lhs == rhs);
}



template <typename T>
constexpr bool close(
  const transform3<T>& lhs, const transform3<T>& rhs, T acc) noexcept
{
  return close(lhs.m_mat, rhs.m_mat, acc) && close(lhs.m_vec, rhs.m_vec, acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const transform3<T>& t)
{
  return os << t.to_mat4x4();
}

}  // namespace hou
