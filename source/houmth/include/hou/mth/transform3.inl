// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
template <typename U, typename Enable>
transform3<T>::transform3(const transform3<U>& other) noexcept
  : m_mat(static_cast<mat3x3<T>>(other.m_mat))
  , m_vec(static_cast<vec3<T>>(other.m_vec))
{}



template <typename T>
transform3<T> operator*(transform3<T> lhs, const transform3<T>& rhs) noexcept
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

}  // namespace hou
