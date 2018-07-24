// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename CharT, size_t N, typename Traits>
basic_static_string<CharT, N, Traits>::basic_static_string() noexcept
  : m_buffer()
  , m_size(0u)
{
  m_buffer[0] = 0;
}



template <typename CharT, size_t N, typename Traits>
basic_static_string<CharT, N, Traits>::basic_static_string(
  size_t count, CharT ch) noexcept
  : m_buffer()
  , m_size(std::min(N, count))
{
  std::fill(m_buffer.begin(), std::next(m_buffer.begin(), m_size), ch);
  m_buffer[m_size] = 0;
}



template <typename CharT, size_t N, typename Traits>
basic_static_string<CharT, N, Traits>::basic_static_string(
  const CharT* s) noexcept
  : m_buffer()
  , m_size(std::min(N, traits_type::length(s)))
{
  traits_type::copy(m_buffer.data(), s, m_size);
  m_buffer[m_size] = 0;
}



template <typename CharT, size_t N, typename Traits>
template <typename Allocator>
basic_static_string<CharT, N, Traits>::basic_static_string(
  const std::basic_string<CharT, Traits, Allocator>& s) noexcept
  : m_buffer()
  , m_size(std::min(N, s.size()))
{
  traits_type::copy(m_buffer.data(), s.data(), m_size);
  m_buffer[m_size] = 0;
}



template <typename CharT, size_t N, typename Traits>
CharT& basic_static_string<CharT, N, Traits>::at(size_type pos)
{
  HOU_PRECOND(pos < m_size);
  return m_buffer[pos];
}



template <typename CharT, size_t N, typename Traits>
const CharT& basic_static_string<CharT, N, Traits>::at(size_type pos) const
{
  HOU_PRECOND(pos < m_size);
  return m_buffer[pos];
}



template <typename CharT, size_t N, typename Traits>
CharT& basic_static_string<CharT, N, Traits>::operator[](size_type pos) noexcept
{
  return m_buffer[pos];
}



template <typename CharT, size_t N, typename Traits>
const CharT& basic_static_string<CharT, N, Traits>::operator[](
  size_type pos) const noexcept
{
  return m_buffer[pos];
}



template <typename CharT, size_t N, typename Traits>
CharT& basic_static_string<CharT, N, Traits>::front() noexcept
{
  return m_buffer[0];
}



template <typename CharT, size_t N, typename Traits>
const CharT& basic_static_string<CharT, N, Traits>::front() const noexcept
{
  return m_buffer[0];
}



template <typename CharT, size_t N, typename Traits>
CharT& basic_static_string<CharT, N, Traits>::back() noexcept
{
  return m_buffer[m_size - 1];
}



template <typename CharT, size_t N, typename Traits>
const CharT& basic_static_string<CharT, N, Traits>::back() const noexcept
{
  return m_buffer[m_size - 1];
}



template <typename CharT, size_t N, typename Traits>
CharT* basic_static_string<CharT, N, Traits>::data() noexcept
{
  return m_buffer.data();
}



template <typename CharT, size_t N, typename Traits>
const CharT* basic_static_string<CharT, N, Traits>::data() const noexcept
{
  return m_buffer.data();
}



template <typename CharT, size_t N, typename Traits>
const CharT* basic_static_string<CharT, N, Traits>::c_str() const noexcept
{
  return m_buffer.data();
}



template <typename CharT, size_t N, typename Traits>
template <typename Allocator>
basic_static_string<CharT, N, Traits>::
  operator std::basic_string<CharT, Traits, Allocator>() const
{
  return std::basic_string<CharT, Traits>(begin(), end());
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::iterator
  basic_static_string<CharT, N, Traits>::begin() noexcept
{
  return m_buffer.begin();
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::const_iterator
  basic_static_string<CharT, N, Traits>::begin() const noexcept
{
  return m_buffer.begin();
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::iterator
  basic_static_string<CharT, N, Traits>::end() noexcept
{
  return std::next(m_buffer.begin(), m_size);
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::const_iterator
  basic_static_string<CharT, N, Traits>::end() const noexcept
{
  return std::next(m_buffer.begin(), m_size);
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::const_iterator
  basic_static_string<CharT, N, Traits>::cbegin() const noexcept
{
  return m_buffer.cbegin();
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::const_iterator
  basic_static_string<CharT, N, Traits>::cend() const noexcept
{
  return std::next(m_buffer.cbegin(), m_size);
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::reverse_iterator
  basic_static_string<CharT, N, Traits>::rbegin() noexcept
{
  return std::prev(m_buffer.rend(), m_size);
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::const_reverse_iterator
  basic_static_string<CharT, N, Traits>::rbegin() const noexcept
{
  return std::prev(m_buffer.rend(), m_size);
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::reverse_iterator
  basic_static_string<CharT, N, Traits>::rend() noexcept
{
  return m_buffer.rend();
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::const_reverse_iterator
  basic_static_string<CharT, N, Traits>::rend() const noexcept
{
  return m_buffer.rend();
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::const_reverse_iterator
  basic_static_string<CharT, N, Traits>::crbegin() const noexcept
{
  return std::prev(m_buffer.crend(), m_size);
}



template <typename CharT, size_t N, typename Traits>
typename basic_static_string<CharT, N, Traits>::const_reverse_iterator
  basic_static_string<CharT, N, Traits>::crend() const noexcept
{
  return m_buffer.crend();
}



template <typename CharT, size_t N, typename Traits>
bool basic_static_string<CharT, N, Traits>::empty() const noexcept
{
  return m_size == 0u;
}



template <typename CharT, size_t N, typename Traits>
size_t basic_static_string<CharT, N, Traits>::size() const noexcept
{
  return m_size;
}



template <typename CharT, size_t N, typename Traits>
size_t basic_static_string<CharT, N, Traits>::length() const noexcept
{
  return size();
}



template <typename CharT, size_t N, typename Traits>
size_t basic_static_string<CharT, N, Traits>::capacity() const noexcept
{
  return N;
}



template <typename CharT, size_t N, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
  std::basic_ostream<CharT, Traits>& os,
  const basic_static_string<CharT, N, Traits>& s)
{
  return os << s.c_str();
}



template <typename CharT, size_t N, typename Traits>
bool operator==(const basic_static_string<CharT, N, Traits>& lhs,
  const basic_static_string<CharT, N, Traits>& rhs) noexcept
{
  return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}



template <typename CharT, size_t N, typename Traits>
bool operator!=(const basic_static_string<CharT, N, Traits>& lhs,
  const basic_static_string<CharT, N, Traits>& rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace hou
