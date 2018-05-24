// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
template <typename U, typename Enable>
rotation2<T>::rotation2(const rotation2<U>& other) noexcept
  : m_angle(static_cast<T>(other.m_angle))
{}



template <typename T>
rotation2<T> operator*(rotation2<T> lhs, const rotation2<T>& rhs) noexcept
{
  return lhs *= rhs;
}



template <typename T>
rotation2<T> inverse(rotation2<T> r) noexcept
{
  return r.invert();
}



// clang-format off
HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH()
HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(-Wfloat-equal)
template <typename T>
bool operator==(
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
bool operator!=(
  const rotation2<T>& lhs, const rotation2<T>& rhs) noexcept
{
  return lhs.get_angle() != rhs.get_angle();
}
HOU_PRAGMA_GCC_DIAGNOSTIC_POP()
// clang-format on



template <typename T>
bool close(const rotation2<T>& lhs, const rotation2<T>& rhs, T acc) noexcept
{
  return close(lhs.get_angle(), rhs.get_angle(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const rotation2<T>& r)
{
  return os << r.get_angle();
}

}  // namespace hou
