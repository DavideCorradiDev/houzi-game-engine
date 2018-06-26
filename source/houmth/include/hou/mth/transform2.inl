// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <typename T>
const transform2<T>& transform2<T>::identity() noexcept
{
  static const transform2 t;
  return t;
}



template <typename T>
constexpr transform2<T> transform2<T>::translation(
  const vec2<T>& translation) noexcept
{
  return transform2<T>(mat2x2<T>::identity(), translation);
}



template <typename T>
constexpr transform2<T> transform2<T>::rotation(
  const rot2<T>& rotation) noexcept
{
  return transform2<T>(rotation.get_matrix(), vec2<T>::zero());
}



template <typename T>
constexpr transform2<T> transform2<T>::scale(const vec2<T>& scale) noexcept
{
  return transform2<T>(
    mat2x2<T>(scale.x(), T(0), T(0), scale.y()), vec2<T>::zero());
}



template <typename T>
constexpr transform2<T> transform2<T>::shear(T sxy, T syx) noexcept
{
  return transform2<T>(mat2x2<T>(T(1), sxy, syx, T(1)), vec2<T>::zero());
}



template <typename T>
constexpr transform2<T> transform2<T>::orthographic_projection(
  const rect<T>& clipping_plane) noexcept

{
  return translation(vec2<T>(T(-1), T(-1)))
    * scale(vec2<T>(2 / clipping_plane.w(), 2 / clipping_plane.h()))
    * translation(vec2<T>(-clipping_plane.x(), -clipping_plane.y()));
}



template <typename T>
constexpr transform2<T>::transform2() noexcept
  : m_mat(mat2x2<T>::identity())
  , m_vec(vec2<T>::zero())
{}



template <typename T>
template <typename U, typename Enable>
constexpr transform2<T>::transform2(const transform2<U>& other) noexcept
  : m_mat(static_cast<mat2x2<T>>(other.m_mat))
  , m_vec(static_cast<vec2<T>>(other.m_vec))
{}



template <typename T>
constexpr mat4x4<T> transform2<T>::to_mat4x4() const noexcept
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
constexpr transform2<T>& transform2<T>::operator*=(
  const transform2<T>& rhs) noexcept
{
  m_vec += m_mat * rhs.m_vec;
  m_mat = m_mat * rhs.m_mat;
  return *this;
}



template <typename T>
constexpr transform2<T>& transform2<T>::invert()
{
  m_mat.invert();
  m_vec = -m_mat * m_vec;
  return *this;
}



template <typename T>
constexpr vec2<T> transform2<T>::transform_vector(const vec2<T>& vec) const
  noexcept
{
  return m_mat * vec;
}



template <typename T>
constexpr vec2<T> transform2<T>::transform_point(const vec2<T>& point) const
  noexcept
{
  return m_vec + m_mat * point;
}



template <typename T>
constexpr transform2<T>::transform2(
  const mat2x2<T>& r, const vec2<T>& t) noexcept
  : m_mat(r)
  , m_vec(t)
{}



template <typename T>
constexpr transform2<T> operator*(
  transform2<T> lhs, const transform2<T>& rhs) noexcept
{
  return lhs *= rhs;
}



template <typename T>
constexpr transform2<T> inverse(transform2<T> t)
{
  return t.invert();
}



template <typename T>
constexpr bool operator==(
  const transform2<T>& lhs, const transform2<T>& rhs) noexcept
{
  return lhs.m_mat == rhs.m_mat && lhs.m_vec == rhs.m_vec;
}



template <typename T>
constexpr bool operator!=(
  const transform2<T>& lhs, const transform2<T>& rhs) noexcept
{
  return !(lhs == rhs);
}



template <typename T>
constexpr bool close(
  const transform2<T>& lhs, const transform2<T>& rhs, T acc) noexcept
{
  return close(lhs.m_mat, rhs.m_mat, acc) && close(lhs.m_vec, rhs.m_vec, acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const transform2<T>& t)
{
  return os << t.to_mat4x4();
}

}  // namespace hou
