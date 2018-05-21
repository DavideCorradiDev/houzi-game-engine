// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
template <typename U, typename Enable>
quaternion<T>::quaternion(const quaternion<U>& other) noexcept
  : quaternion(static_cast<T>(other.x()), static_cast<T>(other.y()),
      static_cast<T>(other.z()), static_cast<T>(other.w()))
{}

template <typename T>
quaternion<T> operator+(quaternion<T> lhs, const quaternion<T>& rhs) noexcept
{
  return lhs += rhs;
}



template <typename T>
quaternion<T> operator-(quaternion<T> lhs, const quaternion<T>& rhs) noexcept
{
  return lhs -= rhs;
}



template <typename T>
quaternion<T> operator*(quaternion<T> lhs, const quaternion<T>& rhs) noexcept
{
  return lhs *= rhs;
}



template <typename T>
quaternion<T> inverse(quaternion<T> q)
{
  return q.invert();
}



template <typename T>
quaternion<T> conjugate(quaternion<T> q) noexcept
{
  return q.conjugate();
}



template <typename T>
T square_norm(const quaternion<T>& q) noexcept
{
  return q.x() * q.x() + q.y() * q.y() + q.z() * q.z() + q.w() * q.w();
}



template <typename T>
T norm(const quaternion<T>& q) noexcept
{
  return std::sqrt(square_norm(q));
}



template <typename T>
quaternion<T> normalized(quaternion<T> q)
{
  return q.normalize();
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const quaternion<T>& q)
{
  return os << "(" << q.x() << "," << q.y() << "," << q.z() << "," << q.w()
            << ")";
}

}  // namespace hou
