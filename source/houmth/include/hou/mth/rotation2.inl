// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
const rotation2<T>& rotation2<T>::identity() noexcept
{
  static const rotation2 r;
  return r;
}



template <typename T>
constexpr rotation2<T>::rotation2() noexcept
  : m_angle(0)
{}



template <typename T>
constexpr rotation2<T>::rotation2(T angle) noexcept
  : m_angle(normalize_angle(angle))
{}



template <typename T>
constexpr rotation2<T>::rotation2(const mat2x2<T>& m)
  : m_angle(to_angle(m))
{
  HOU_PRECOND(
    close(T(1), det(m)) && close(mat2x2<T>::identity(), m * transpose(m)));
  HOU_DEV_ASSERT(m_angle > -pi<T>() && m_angle <= pi<T>());
}



template <typename T>
template <typename U, typename Enable>
constexpr rotation2<T>::rotation2(const rotation2<U>& other) noexcept
  : m_angle(static_cast<T>(other.m_angle))
{}



template <typename T>
constexpr T rotation2<T>::get_angle() const noexcept
{
  return m_angle;
}



template <typename T>
constexpr mat2x2<T> rotation2<T>::get_matrix() const noexcept
{
  return to_matrix(m_angle);
}



template <typename T>
constexpr rotation2<T>& rotation2<T>::operator*=(
  const rotation2<T>& rhs) noexcept
{
  m_angle = normalize_angle(m_angle + rhs.m_angle);
  return *this;
}



template <typename T>
constexpr rotation2<T>& rotation2<T>::invert() noexcept
{
  m_angle = normalize_angle(-m_angle);
  return *this;
}



template <typename T>
constexpr T rotation2<T>::to_angle(const mat2x2<T>& m) noexcept
{
  return std::atan2(m(2), m(0));
}



template <typename T>
constexpr mat2x2<T> rotation2<T>::to_matrix(T angle) noexcept
{
  T c = std::cos(angle);
  T s = std::sin(angle);
  return mat2x2<T>{c, -s, s, c};
}



template <typename T>
constexpr T rotation2<T>::normalize_angle(T angle) noexcept
{
  constexpr T increment = T(2) * pi<T>();
  while(angle <= -pi<T>())
  {
    angle += increment;
  }
  while(angle > pi<T>())
  {
    angle -= increment;
  }
  return angle;
}



template <typename T>
constexpr rotation2<T> operator*(
  rotation2<T> lhs, const rotation2<T>& rhs) noexcept
{
  return lhs *= rhs;
}



template <typename T>
constexpr rotation2<T> inverse(rotation2<T> r) noexcept
{
  return r.invert();
}



// clang-format off
HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH()
HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(-Wfloat-equal)
template <typename T>
constexpr bool operator==(
  const rotation2<T>& lhs, const rotation2<T>& rhs) noexcept
{
  return lhs.get_angle() == rhs.get_angle();
}
HOU_PRAGMA_GCC_DIAGNOSTIC_POP()
// clang-format on



// clang-format off
HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH()
HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(-Wfloat-equal)
template <typename T>
constexpr bool operator!=(
  const rotation2<T>& lhs, const rotation2<T>& rhs) noexcept
{
  return lhs.get_angle() != rhs.get_angle();
}
HOU_PRAGMA_GCC_DIAGNOSTIC_POP()
// clang-format on



template <typename T>
constexpr bool close(
  const rotation2<T>& lhs, const rotation2<T>& rhs, T acc) noexcept
{
  return close(lhs.get_angle(), rhs.get_angle(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const rotation2<T>& r)
{
  return os << r.get_angle();
}

}  // namespace hou
