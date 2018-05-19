// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.


namespace hou
{

template <typename T>
constexpr span<T>::span() noexcept
  : m_data(nullptr)
  , m_size(0u)
{}



#ifndef HOU_DOXYGEN
template <typename T>
constexpr span<T>::span(pointer data, size_type size)
  : m_data(data)
  , m_size(size)
{
  HOU_PRECOND((m_data == nullptr && size == 0u) || (m_data != nullptr));
}
#endif



template <typename T>
constexpr span<T>::span(pointer first, pointer last)
  : span(first, std::distance(first, last))
{
  HOU_PRECOND(first != nullptr && last != nullptr);
}



template <typename T>
template <typename Container, typename Enable>
constexpr span<T>::span(const Container& c) noexcept
  : span(c.data(), c.size())
{}



template <typename T>
template <typename Container, typename Enable>
constexpr span<T>::span(Container& c) noexcept
  : span(const_cast<typename Container::pointer>(c.data()), c.size())
{}



template <typename T>
constexpr typename span<T>::pointer span<T>::data() const noexcept
{
  return m_data;
}



template <typename T>
constexpr typename span<T>::size_type span<T>::size() const noexcept
{
  return m_size;
}



template <typename T>
constexpr typename span<T>::reference span<T>::at(span<T>::size_type idx) const
{
  HOU_CHECK_0(idx < m_size, hou::out_of_range);
  return *(m_data + idx);
}



template <typename T>
constexpr
  typename span<T>::reference span<T>::operator[](span<T>::size_type idx) const
  noexcept
{
  return *(m_data + idx);
}



template <typename T>
constexpr typename span<T>::iterator span<T>::begin() const noexcept
{
  return iterator(*this, 0u);
}



template <typename T>
constexpr typename span<T>::const_iterator span<T>::cbegin() const noexcept
{
  return const_iterator(*this, 0u);
}



template <typename T>
constexpr typename span<T>::reverse_iterator span<T>::rbegin() const noexcept
{
  return reverse_iterator(end());
}



template <typename T>
constexpr typename span<T>::const_reverse_iterator span<T>::crbegin() const
  noexcept
{
  return const_reverse_iterator(cend());
}



template <typename T>
constexpr typename span<T>::iterator span<T>::end() const noexcept
{
  return iterator(*this, m_size);
}



template <typename T>
constexpr typename span<T>::const_iterator span<T>::cend() const noexcept
{
  return const_iterator(*this, m_size);
}



template <typename T>
constexpr typename span<T>::reverse_iterator span<T>::rend() const noexcept
{
  return reverse_iterator(begin());
}



template <typename T>
constexpr typename span<T>::const_reverse_iterator span<T>::crend() const
  noexcept
{
  return const_reverse_iterator(cbegin());
}



template <typename T>
constexpr bool operator==(const span<T>& lhs, const span<T>& rhs) noexcept
{
  return lhs.data() == rhs.data() && lhs.size() == rhs.size();
}



template <typename T>
constexpr bool operator!=(const span<T>& lhs, const span<T>& rhs) noexcept
{
  return !(lhs == rhs);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const span<T>& s)
{
  return os << "{address = " << s.data() << ", size_type = " << s.size() << "}";
}



template <typename Out, typename In>
constexpr span<Out> reinterpret_span(const span<In>& in)
{
  size_t in_byte_count = in.size() * sizeof(In);
  HOU_PRECOND(in_byte_count % sizeof(Out) == 0);
  return span<Out>(reinterpret_cast<typename span<Out>::pointer>(in.data()),
    in_byte_count / sizeof(Out));
}



namespace prv
{

#ifndef HOU_DOXYGEN

template <typename T>
constexpr span_iterator<T>::span_iterator(
  const span<T>& span, size_type index) noexcept
  : m_span(&span)
  , m_index(index)
{}



template <typename T>
constexpr
  typename span_iterator<T>::reference span_iterator<T>::operator*() const
  noexcept
{
  return *(m_span->data() + m_index);
}



template <typename T>
constexpr
  typename span_iterator<T>::pointer span_iterator<T>::operator->() const
  noexcept
{
  return m_span->data() + m_index;
}



template <typename T>
constexpr span_iterator<T>& span_iterator<T>::operator+=(
  difference_type rhs) noexcept
{
  m_index += rhs;
  return *this;
}



template <typename T>
constexpr span_iterator<T>& span_iterator<T>::operator++() noexcept
{
  m_index++;
  return *this;
}



template <typename T>
constexpr span_iterator<T> span_iterator<T>::operator++(int) noexcept
{
  span_iterator retval = *this;
  ++(*this);
  return retval;
}



template <typename T>
constexpr span_iterator<T>& span_iterator<T>::operator-=(
  difference_type rhs) noexcept
{
  m_index -= rhs;
  return *this;
}



template <typename T>
constexpr span_iterator<T>& span_iterator<T>::operator--() noexcept
{
  m_index--;
  return *this;
}



template <typename T>
constexpr span_iterator<T> span_iterator<T>::operator--(int) noexcept
{
  span_iterator retval = *this;
  --(*this);
  return retval;
}



template <typename T>
constexpr typename span_iterator<T>::reference span_iterator<T>::operator[](
  difference_type offset) const noexcept
{
  return (*m_span)[m_index + offset];
}

#endif

}  // namespace prv

}  // namespace hou
