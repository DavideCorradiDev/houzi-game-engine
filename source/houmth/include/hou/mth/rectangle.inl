// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
constexpr rectangle<T>::rectangle() noexcept
  : m_position()
  , m_size()
{}



template <typename T>
constexpr rectangle<T>::rectangle(
  const vec2<T>& position, const vec2<T>& size) noexcept
  : m_position(position)
  , m_size(size)
{}



template <typename T>
constexpr rectangle<T>::rectangle(T x, T y, T w, T h) noexcept
  : rectangle(vec2<T>(x, y), vec2<T>(w, h))
{}



template <typename T>
template <typename U, typename Enable>
constexpr rectangle<T>::rectangle(const rectangle<U>& other) noexcept
  : rectangle<T>(vec2<T>(other.get_position()), vec2<T>(other.get_size()))
{}



template <typename T>
constexpr const vec2<T>& rectangle<T>::get_position() const noexcept
{
  return m_position;
}



template <typename T>
constexpr void rectangle<T>::set_position(const vec2<T>& value) noexcept
{
  m_position = value;
}



template <typename T>
constexpr const vec2<T>& rectangle<T>::get_size() const noexcept
{
  return m_size;
}



template <typename T>
constexpr void rectangle<T>::set_size(const vec2<T>& value) noexcept
{
  m_size = value;
}



template <typename T>
constexpr T rectangle<T>::x() const noexcept
{
  return m_position.x();
}



template <typename T>
constexpr T& rectangle<T>::x() noexcept
{
  return m_position.x();
}



template <typename T>
constexpr T rectangle<T>::y() const noexcept
{
  return m_position.y();
}



template <typename T>
constexpr T& rectangle<T>::y() noexcept
{
  return m_position.y();
}



template <typename T>
constexpr T rectangle<T>::w() const noexcept
{
  return m_size.x();
}



template <typename T>
constexpr T& rectangle<T>::w() noexcept
{
  return m_size.x();
}



template <typename T>
constexpr T rectangle<T>::h() const noexcept
{
  return m_size.y();
}



template <typename T>
constexpr T& rectangle<T>::h() noexcept
{
  return m_size.y();
}



template <typename T>
constexpr T rectangle<T>::l() const noexcept
{
  return x();
}



template <typename T>
constexpr T rectangle<T>::t() const noexcept
{
  return y();
}



template <typename T>
constexpr T rectangle<T>::r() const noexcept
{
  return x() + w();
}



template <typename T>
constexpr T rectangle<T>::b() const noexcept
{
  return y() + h();
}



template <typename T>
constexpr bool operator==(
  const rectangle<T>& lhs, const rectangle<T>& rhs) noexcept
{
  return lhs.get_position() == rhs.get_position()
    && lhs.get_size() == rhs.get_size();
}



template <typename T>
constexpr bool operator!=(
  const rectangle<T>& lhs, const rectangle<T>& rhs) noexcept
{
  return !(lhs == rhs);
}



template <typename T>
constexpr bool close(
  const rectangle<T>& lhs, const rectangle<T>& rhs, T acc) noexcept
{
  return close(lhs.get_position(), rhs.get_position(), acc)
    && close(lhs.get_size(), rhs.get_size(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const rectangle<T>& rect)
{
  return os << "{position = " << transpose(rect.get_position())
            << ", size = " << transpose(rect.get_size()) << "}";
}



template <typename T>
constexpr bool is_point_in_rectangle(
  const rectangle<T>& r, const vec2<T>& p) noexcept
{
  return p.x() >= r.l() && p.x() <= r.r() && p.y() >= r.t() && p.y() <= r.b();
}

}  // namespace hou
