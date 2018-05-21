// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <typename T>
template <typename U, typename Enable>
transform2<T>::transform2(const transform2<U>& other) noexcept
  : m_mat(static_cast<mat2x2<T>>(other.m_mat))
  , m_vec(static_cast<vec2<T>>(other.m_vec))
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
bool operator==(const transform2<T>& lhs, const transform2<T>& rhs) noexcept
{
  return lhs.m_mat == rhs.m_mat && lhs.m_vec == rhs.m_vec;
}



template <typename T>
bool operator!=(const transform2<T>& lhs, const transform2<T>& rhs) noexcept
{
  return !(lhs == rhs);
}



template <typename T>
bool close(const transform2<T>& lhs, const transform2<T>& rhs, T acc) noexcept
{
  return close(lhs.m_mat, rhs.m_mat, acc) && close(lhs.m_vec, rhs.m_vec, acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const transform2<T>& t)
{
  return os << t.to_mat4x4();
}

}  // namespace hou
