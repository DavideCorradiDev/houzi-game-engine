// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
template <typename U, typename Enable>
rotation3<T>::rotation3(const rotation3<U>& other) noexcept
  : m_quaternion(normalized(static_cast<quaternion<T>>(other.m_quaternion)))
{}



template <typename T>
rotation3<T> operator*(rotation3<T> lhs, const rotation3<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
rotation3<T> inverse(rotation3<T> r)
{
  return r.invert();
}



template <typename T>
bool operator==(const rotation3<T>& lhs, const rotation3<T>& rhs) noexcept
{
  return lhs.get_quaternion() == rhs.get_quaternion();
}



template <typename T>
bool operator!=(const rotation3<T>& lhs, const rotation3<T>& rhs) noexcept
{
  return lhs.get_quaternion() != rhs.get_quaternion();
}



template <typename T>
bool close(const rotation3<T>& lhs, const rotation3<T>& rhs, T acc) noexcept
{
  return close(lhs.get_quaternion(), rhs.get_quaternion(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const rotation3<T>& r)
{
  return os << r.get_quaternion();
}

}  // namespace hou
