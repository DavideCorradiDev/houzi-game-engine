// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.


namespace hou
{

template <typename T>
span<T>::span()
  : m_data(nullptr)
  , m_size(0u)
{}



#ifndef HOU_DOXYGEN
template <typename T>
span<T>::span(pointer data, size_type size)
  : m_data(data)
  , m_size(size)
{
  HOU_EXPECT((m_data == nullptr && size == 0u) || (m_data != nullptr));
}
#endif



template <typename T>
span<T>::span(pointer first, pointer last)
  : span(first, std::distance(first, last))
{
  HOU_EXPECT(first != nullptr && last != nullptr);
}



template <typename T>
template <typename Container, typename Enable>
span<T>::span(const Container& c)
  : span(c.data(), c.size())
{}



template <typename T>
template <typename Container, typename Enable>
span<T>::span(Container& c)
  : span(const_cast<typename Container::pointer>(c.data()), c.size())
{}



template <typename T>
constexpr typename span<T>::pointer span<T>::data() const
{
  return m_data;
}



template <typename T>
constexpr typename span<T>::size_type span<T>::size() const
{
  return m_size;
}



template <typename T>
constexpr
  typename span<T>::reference span<T>::operator[](span<T>::size_type idx) const
{
  HOU_EXPECT(m_data != nullptr && idx < m_size);
  return *(m_data + idx);
}



template <typename T>
constexpr typename span<T>::iterator span<T>::begin() const
{
  return iterator(*this, 0u);
}



template <typename T>
constexpr typename span<T>::const_iterator span<T>::cbegin() const
{
  return const_iterator(*this, 0u);
}



template <typename T>
constexpr typename span<T>::reverse_iterator span<T>::rbegin() const
{
  return reverse_iterator(end());
}



template <typename T>
constexpr typename span<T>::const_reverse_iterator span<T>::crbegin() const
{
  return const_reverse_iterator(cend());
}



template <typename T>
constexpr typename span<T>::iterator span<T>::end() const
{
  return iterator(*this, m_size);
}



template <typename T>
constexpr typename span<T>::const_iterator span<T>::cend() const
{
  return const_iterator(*this, m_size);
}



template <typename T>
constexpr typename span<T>::reverse_iterator span<T>::rend() const
{
  return reverse_iterator(begin());
}



template <typename T>
constexpr typename span<T>::const_reverse_iterator span<T>::crend() const
{
  return const_reverse_iterator(cbegin());
}



template <typename T>
bool operator==(const span<T>& lhs, const span<T>& rhs)
{
  return lhs.data() == rhs.data() && lhs.size() == rhs.size();
}



template <typename T>
bool operator!=(const span<T>& lhs, const span<T>& rhs)
{
  return !(lhs == rhs);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const span<T>& s)
{
  return os << "{address = " << s.data() << ", size_type = " << s.size() << "}";
}



template <typename Out, typename In>
span<Out> reinterpret_span(const span<In>& in)
{
  size_t in_byte_count = in.size() * sizeof(In);
  HOU_EXPECT(in_byte_count % sizeof(Out) == 0);
  return span<Out>(reinterpret_cast<typename span<Out>::pointer>(in.data()),
    in_byte_count / sizeof(Out));
}



namespace prv
{

template <typename T>
constexpr span_iterator<T>::span_iterator(const span<T>& span, size_type index)
  : m_span(&span)
  , m_index(index)
{
  HOU_EXPECT(index <= span.size());
}



template <typename T>
constexpr
  typename span_iterator<T>::reference span_iterator<T>::operator*() const
{
  HOU_EXPECT_DEV(m_span != nullptr);
  HOU_EXPECT(m_index < m_span->size());
  return *(m_span->data() + m_index);
}



template <typename T>
constexpr
  typename span_iterator<T>::pointer span_iterator<T>::operator->() const
{
  HOU_EXPECT_DEV(m_span != nullptr);
  HOU_EXPECT(m_index < m_span->size());
  return m_span->data() + m_index;
}



template <typename T>
constexpr span_iterator<T>& span_iterator<T>::operator+=(difference_type rhs)
{
  HOU_EXPECT_DEV(m_span != nullptr);
  HOU_EXPECT(m_index + rhs <= m_span->size());
  m_index += rhs;
  return *this;
}



template <typename T>
constexpr span_iterator<T>& span_iterator<T>::operator++()
{
  HOU_EXPECT_DEV(m_span != nullptr);
  HOU_EXPECT(m_index < m_span->size());
  m_index++;
  return *this;
}



template <typename T>
constexpr span_iterator<T> span_iterator<T>::operator++(int)
{
  span_iterator retval = *this;
  ++(*this);
  return retval;
}



template <typename T>
constexpr span_iterator<T>& span_iterator<T>::operator-=(difference_type rhs)
{
  HOU_EXPECT(m_index >= static_cast<size_type>(rhs));
  m_index -= rhs;
  return *this;
}



template <typename T>
constexpr span_iterator<T>& span_iterator<T>::operator--()
{
  HOU_EXPECT(m_index > 0);
  m_index--;
  return *this;
}



template <typename T>
constexpr span_iterator<T> span_iterator<T>::operator--(int)
{
  span_iterator retval = *this;
  --(*this);
  return retval;
}



template <typename T>
constexpr typename span_iterator<T>::reference span_iterator<T>::operator[](
  difference_type offset) const
{
  HOU_EXPECT_DEV(m_span != nullptr);
  return (*m_span)[m_index + offset];
}

}  // namespace prv

}  // namespace hou
