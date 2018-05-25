// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
const quaternion<T>& quaternion<T>::zero() noexcept
{
  static const quaternion q = quaternion<T>(0, 0, 0, 0);
  return q;
}



template <typename T>
const quaternion<T>& quaternion<T>::identity() noexcept
{
  static const quaternion q = quaternion<T>(0, 0, 0, 1);
  return q;
}



template <typename T>
constexpr quaternion<T>::quaternion() noexcept
  : quaternion(0, 0, 0, 0)
{}



template <typename T>
constexpr quaternion<T>::quaternion(T x, T y, T z, T w) noexcept
  : m_elements{x, y, z, w}
{}



template <typename T>
template <typename U, typename Enable>
constexpr quaternion<T>::quaternion(const quaternion<U>& other) noexcept
  : quaternion(static_cast<T>(other.x()), static_cast<T>(other.y()),
      static_cast<T>(other.z()), static_cast<T>(other.w()))
{}



template <typename T>
constexpr T quaternion<T>::x() const noexcept
{
  return m_elements[0];
}



template <typename T>
constexpr T& quaternion<T>::x() noexcept
{
  return m_elements[0];
}



template <typename T>
constexpr T quaternion<T>::y() const noexcept
{
  return m_elements[1];
}



template <typename T>
constexpr T& quaternion<T>::y() noexcept
{
  return m_elements[1];
}



template <typename T>
constexpr T quaternion<T>::z() const noexcept
{
  return m_elements[2];
}



template <typename T>
constexpr T& quaternion<T>::z() noexcept
{
  return m_elements[2];
}



template <typename T>
constexpr T quaternion<T>::w() const noexcept
{
  return m_elements[3];
}



template <typename T>
constexpr T& quaternion<T>::w() noexcept
{
  return m_elements[3];
}



template <typename T>
constexpr const T* quaternion<T>::data() const noexcept
{
  return m_elements.data();
}



template <typename T>
constexpr quaternion<T>& quaternion<T>::operator+=(
  const quaternion<T>& rhs) noexcept
{
  m_elements[0] += rhs.m_elements[0];
  m_elements[1] += rhs.m_elements[1];
  m_elements[2] += rhs.m_elements[2];
  m_elements[3] += rhs.m_elements[3];
  return *this;
}



template <typename T>
constexpr quaternion<T>& quaternion<T>::operator-=(
  const quaternion<T>& rhs) noexcept
{
  m_elements[0] -= rhs.m_elements[0];
  m_elements[1] -= rhs.m_elements[1];
  m_elements[2] -= rhs.m_elements[2];
  m_elements[3] -= rhs.m_elements[3];
  return *this;
}



template <typename T>
constexpr quaternion<T>& quaternion<T>::operator*=(
  const quaternion<T>& r) noexcept
{
  // clang-format off
  return *this = quaternion<T>(
    this->w() * r.x() + this->x() * r.w() + this->y() * r.z() - this->z() * r.y(),
    this->w() * r.y() - this->x() * r.z() + this->y() * r.w() + this->z() * r.x(),
    this->w() * r.z() + this->x() * r.y() - this->y() * r.x() + this->z() * r.w(),
    this->w() * r.w() - this->x() * r.x() - this->y() * r.y() - this->z() * r.z());
  // clang-format on
}



template <typename T>
constexpr quaternion<T>& quaternion<T>::operator*=(T rhs) noexcept
{
  m_elements[0] *= rhs;
  m_elements[1] *= rhs;
  m_elements[2] *= rhs;
  m_elements[3] *= rhs;
  return *this;
}



template <typename T>
constexpr quaternion<T>& quaternion<T>::operator/=(T rhs) noexcept
{
  m_elements[0] /= rhs;
  m_elements[1] /= rhs;
  m_elements[2] /= rhs;
  m_elements[3] /= rhs;
  return *this;
}



template <typename T>
constexpr quaternion<T>& quaternion<T>::invert()
{
  T snorm = square_norm(*this);
  HOU_CHECK_0(!close(snorm, T(0)), inversion_error);
  return this->conjugate() /= snorm;
}



template <typename T>
constexpr quaternion<T>& quaternion<T>::conjugate() noexcept
{
  m_elements[0] = -m_elements[0];
  m_elements[1] = -m_elements[1];
  m_elements[2] = -m_elements[2];
  return *this;
}



template <typename T>
constexpr quaternion<T>& quaternion<T>::normalize()
{
  T quatNorm = norm(*this);
  HOU_PRECOND(!close(quatNorm, T(0)));
  return *this /= quatNorm;
}



template <typename T>
constexpr quaternion<T> operator+(
  quaternion<T> lhs, const quaternion<T>& rhs) noexcept
{
  return lhs += rhs;
}



template <typename T>
constexpr quaternion<T> operator-(
  quaternion<T> lhs, const quaternion<T>& rhs) noexcept
{
  return lhs -= rhs;
}



template <typename T>
constexpr quaternion<T> operator*(
  quaternion<T> lhs, const quaternion<T>& rhs) noexcept
{
  return lhs *= rhs;
}



template <typename T>
constexpr quaternion<T> inverse(quaternion<T> q)
{
  return q.invert();
}



template <typename T>
constexpr quaternion<T> conjugate(quaternion<T> q) noexcept
{
  return q.conjugate();
}



template <typename T>
constexpr T square_norm(const quaternion<T>& q) noexcept
{
  return q.x() * q.x() + q.y() * q.y() + q.z() * q.z() + q.w() * q.w();
}



template <typename T>
constexpr T norm(const quaternion<T>& q) noexcept
{
  return std::sqrt(square_norm(q));
}



template <typename T>
constexpr quaternion<T> normalized(quaternion<T> q)
{
  return q.normalize();
}



template <typename T>
constexpr bool operator==(
  const quaternion<T>& lhs, const quaternion<T>& rhs) noexcept
{
  return lhs.m_elements == rhs.m_elements;
}



template <typename T>
constexpr bool operator!=(
  const quaternion<T>& lhs, const quaternion<T>& rhs) noexcept
{
  return lhs.m_elements != rhs.m_elements;
}



template <typename T>
constexpr bool close(
  const quaternion<T>& lhs, const quaternion<T>& rhs, T acc) noexcept
{
  return close(lhs.m_elements, rhs.m_elements, acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const quaternion<T>& q)
{
  return os << "(" << q.x() << "," << q.y() << "," << q.z() << "," << q.w()
            << ")";
}

}  // namespace hou
