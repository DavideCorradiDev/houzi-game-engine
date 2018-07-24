// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
const rotation3<T>& rotation3<T>::identity() noexcept
{
  static const rotation3 r;
  return r;
}



template <typename T>
constexpr rotation3<T> rotation3<T>::x(T angle) noexcept
{
  angle /= T(2);
  return rotation3<T>(
    quaternion<T>(std::sin(angle), T(0), T(0), std::cos(angle)));
}



template <typename T>
constexpr rotation3<T> rotation3<T>::y(T angle) noexcept
{
  angle /= T(2);
  return rotation3<T>(
    quaternion<T>(T(0), std::sin(angle), T(0), std::cos(angle)));
}



template <typename T>
constexpr rotation3<T> rotation3<T>::z(T angle) noexcept
{
  angle /= T(2);
  return rotation3<T>(
    quaternion<T>(T(0), T(0), std::sin(angle), std::cos(angle)));
}



template <typename T>
constexpr rotation3<T>::rotation3() noexcept
  : m_quaternion(quaternion<T>::identity())
{}



template <typename T>
constexpr rotation3<T>::rotation3(const quaternion<T>& q)
  : m_quaternion(normalized(q))
{}



template <typename T>
constexpr rotation3<T>::rotation3(const vec3<T>& v)
  : m_quaternion(normalized(to_quaternion(v)))
{}



template <typename T>
constexpr rotation3<T>::rotation3(const mat3x3<T>& m)
  : m_quaternion(normalized(to_quaternion(m)))
{}



template <typename T>
template <typename U, typename Enable>
constexpr rotation3<T>::rotation3(const rotation3<U>& other) noexcept
  : m_quaternion(normalized(static_cast<quaternion<T>>(other.m_quaternion)))
{}



template <typename T>
constexpr const quaternion<T>& rotation3<T>::get_quaternion() const noexcept
{
  return m_quaternion;
}



template <typename T>
constexpr vec3<T> rotation3<T>::get_vector() const noexcept
{
  return to_vector(m_quaternion);
}



template <typename T>
constexpr mat3x3<T> rotation3<T>::get_matrix() const noexcept
{
  return to_matrix(m_quaternion);
}



template <typename T>
constexpr rotation3<T>& rotation3<T>::operator*=(const rotation3<T>& rhs)
{
  m_quaternion *= rhs.m_quaternion;
  m_quaternion.normalize();
  return *this;
}



template <typename T>
constexpr rotation3<T>& rotation3<T>::invert()
{
  m_quaternion.invert().normalize();
  return *this;
}



template <typename T>
constexpr quaternion<T> rotation3<T>::to_quaternion(vec3<T> v) noexcept
{
  T angle = norm(v);
  v /= angle;
  T s = std::sin(angle / T(2));
  T c = std::cos(angle / T(2));
  return quaternion<T>(v.x() * s, v.y() * s, v.z() * s, c);
}



template <typename T>
constexpr quaternion<T> rotation3<T>::to_quaternion(const mat3x3<T>& m) noexcept
{
  // clang-format off
  T tr = trace(m);
  if(tr > T(0))
  {
    T s = sqrt(T(1) + tr) * T(2);
    return quaternion<T>{
      (m(2, 1) - m(1, 2)) / s,
      (m(0, 2) - m(2, 0)) / s,
      (m(1, 0) - m(0, 1)) / s,
      s / T(4),
    };
  }
  else if((m(0, 0) > m(1, 1)) && (m(0, 0) > m(2, 2)))
  {
    T s = sqrt(T(1) + m(0, 0) - m(1, 1) - m(2, 2)) * T(2);
    return quaternion<T>{
      s / T(4),
      (m(0, 1) + m(1, 0)) / s,
      (m(0, 2) + m(2, 0)) / s,
      (m(2, 1) - m(1, 2)) / s,
    };
  }
  else if(m(1, 1) > m(2, 2))
  {
    T s = sqrt(T(1) + m(1, 1) - m(0, 0) - m(2, 2)) * T(2);
    return quaternion<T>{
      (m(0, 1) + m(1, 0)) / s,
      s / T(4),
      (m(1, 2) + m(2, 1)) / s,
      (m(0, 2) - m(2, 0)) / s,
    };
  }
  else
  {
    T s = sqrt(T(1) + m(2, 2) - m(0, 0) - m(1, 1)) * T(2);
    return quaternion<T>{
      (m(0, 2) + m(2, 0)) / s,
      (m(1, 2) + m(2, 1)) / s,
      s / T(4),
      (m(1, 0) - m(0, 1)) / s,
    };
  }
  // clang-format on
}



template <typename T>
constexpr vec3<T> rotation3<T>::to_vector(const quaternion<T>& q) noexcept
{
  HOU_DEV_ASSERT(close(T(1), norm(q)));
  vec3<T> v(q.x(), q.y(), q.z());
  T vec_norm = norm(v);
  if(!close(T(0), vec_norm))
  {
    v *= T(2) * std::atan2(vec_norm, q.w()) / vec_norm;
  }
  return v;
}



template <typename T>
constexpr mat3x3<T> rotation3<T>::to_matrix(const quaternion<T>& q) noexcept
{
  // clang-format off
  HOU_DEV_ASSERT(close(T(1), norm(q)));
  T xx = T(2) * q.x() * q.x();
  T xy = T(2) * q.x() * q.y();
  T xz = T(2) * q.x() * q.z();
  T xw = T(2) * q.x() * q.w();
  T yy = T(2) * q.y() * q.y();
  T yz = T(2) * q.y() * q.z();
  T yw = T(2) * q.y() * q.w();
  T zz = T(2) * q.z() * q.z();
  T zw = T(2) * q.z() * q.w();
  T ww = T(2) * q.w() * q.w();
  return mat3x3<T>(
    T(-1) + xx + ww,  xy - zw,          xz + yw,
    xy + zw,          T(-1) + yy + ww,  yz - xw,
    xz - yw,          xw + yz,          T(-1) + zz + ww);
  // clang-format on
}



template <typename T>
constexpr rotation3<T> operator*(rotation3<T> lhs, const rotation3<T>& rhs)
{
  return lhs *= rhs;
}



template <typename T>
constexpr rotation3<T> inverse(rotation3<T> r)
{
  return r.invert();
}



template <typename T>
constexpr bool operator==(
  const rotation3<T>& lhs, const rotation3<T>& rhs) noexcept
{
  return lhs.get_quaternion() == rhs.get_quaternion();
}



template <typename T>
constexpr bool operator!=(
  const rotation3<T>& lhs, const rotation3<T>& rhs) noexcept
{
  return lhs.get_quaternion() != rhs.get_quaternion();
}



template <typename T>
constexpr bool close(
  const rotation3<T>& lhs, const rotation3<T>& rhs, T acc) noexcept
{
  return close(lhs.get_quaternion(), rhs.get_quaternion(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const rotation3<T>& r)
{
  return os << "{quaternion = " << r.get_quaternion() << "}";
}

}  // namespace hou
