// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename ScalPosT, typename ScalSizeT>
constexpr rectangle<ScalPosT, ScalSizeT>::rectangle() noexcept
  : m_position()
  , m_size()
{}



template <typename ScalPosT, typename ScalSizeT>
constexpr rectangle<ScalPosT, ScalSizeT>::rectangle(
  const position_type& position, const size_type& size) noexcept
  : m_position(position)
  , m_size(size)
{}



template <typename ScalPosT, typename ScalSizeT>
constexpr rectangle<ScalPosT, ScalSizeT>::rectangle(scalar_position_type x,
  scalar_position_type y, scalar_size_type w, scalar_size_type h) noexcept
  : rectangle(position_type(x, y), size_type(w, h))
{}



template <typename ScalPosT, typename ScalSizeT>
template <typename OtherScalPosT, typename OtherScalSizeT, typename Enable>
constexpr rectangle<ScalPosT, ScalSizeT>::rectangle(
  const rectangle<OtherScalPosT, OtherScalSizeT>& other) noexcept
  : rectangle<ScalPosT, ScalSizeT>(
      position_type(other.get_position()), size_type(other.get_size()))
{}



template <typename ScalPosT, typename ScalSizeT>
constexpr const typename rectangle<ScalPosT, ScalSizeT>::position_type&
  rectangle<ScalPosT, ScalSizeT>::get_position() const noexcept
{
  return m_position;
}



template <typename ScalPosT, typename ScalSizeT>
constexpr void rectangle<ScalPosT, ScalSizeT>::set_position(
  const position_type& value) noexcept
{
  m_position = value;
}



template <typename ScalPosT, typename ScalSizeT>
constexpr const typename rectangle<ScalPosT, ScalSizeT>::size_type&
  rectangle<ScalPosT, ScalSizeT>::get_size() const noexcept
{
  return m_size;
}



template <typename ScalPosT, typename ScalSizeT>
constexpr void rectangle<ScalPosT, ScalSizeT>::set_size(
  const size_type& value) noexcept
{
  m_size = value;
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_position_type
  rectangle<ScalPosT, ScalSizeT>::x() const noexcept
{
  return m_position.x();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_position_type&
  rectangle<ScalPosT, ScalSizeT>::x() noexcept
{
  return m_position.x();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_position_type
  rectangle<ScalPosT, ScalSizeT>::y() const noexcept
{
  return m_position.y();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_position_type&
  rectangle<ScalPosT, ScalSizeT>::y() noexcept
{
  return m_position.y();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_size_type
  rectangle<ScalPosT, ScalSizeT>::w() const noexcept
{
  return m_size.x();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_size_type&
  rectangle<ScalPosT, ScalSizeT>::w() noexcept
{
  return m_size.x();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_size_type
  rectangle<ScalPosT, ScalSizeT>::h() const noexcept
{
  return m_size.y();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_size_type&
  rectangle<ScalPosT, ScalSizeT>::h() noexcept
{
  return m_size.y();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_position_type
  rectangle<ScalPosT, ScalSizeT>::l() const noexcept
{
  return x();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_position_type
  rectangle<ScalPosT, ScalSizeT>::t() const noexcept
{
  return y();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_position_type
  rectangle<ScalPosT, ScalSizeT>::r() const noexcept
{
  return x() + w();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr typename rectangle<ScalPosT, ScalSizeT>::scalar_position_type
  rectangle<ScalPosT, ScalSizeT>::b() const noexcept
{
  return y() + h();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr bool operator==(const rectangle<ScalPosT, ScalSizeT>& lhs,
  const rectangle<ScalPosT, ScalSizeT>& rhs) noexcept
{
  return lhs.get_position() == rhs.get_position()
    && lhs.get_size() == rhs.get_size();
}



template <typename ScalPosT, typename ScalSizeT>
constexpr bool operator!=(const rectangle<ScalPosT, ScalSizeT>& lhs,
  const rectangle<ScalPosT, ScalSizeT>& rhs) noexcept
{
  return !(lhs == rhs);
}



template <typename ScalPosT, typename ScalSizeT>
constexpr bool close(const rectangle<ScalPosT, ScalSizeT>& lhs,
  const rectangle<ScalPosT, ScalSizeT>& rhs, ScalPosT posAcc,
  ScalSizeT sizeAcc) noexcept
{
  return close(lhs.get_position(), rhs.get_position(), posAcc)
    && close(lhs.get_size(), rhs.get_size(), sizeAcc);
}



template <typename T>
constexpr bool close(
  const rectangle<T, T>& lhs, const rectangle<T, T>& rhs, T acc) noexcept
{
  return close(lhs, rhs, acc, acc);
}



template <typename ScalPosT, typename ScalSizeT>
std::ostream& operator<<(
  std::ostream& os, const rectangle<ScalPosT, ScalSizeT>& rect)
{
  return os << "{position = " << transpose(rect.get_position())
            << ", size = " << transpose(rect.get_size()) << "}";
}



template <typename ScalPosT, typename ScalSizeT>
constexpr bool is_point_in_rectangle(const rectangle<ScalPosT, ScalSizeT>& r,
  const typename rectangle<ScalPosT, ScalSizeT>::position_type& p) noexcept
{
  return p.x() >= r.l() && p.x() <= r.r() && p.y() >= r.t() && p.y() <= r.b();
}

}  // namespace hou
